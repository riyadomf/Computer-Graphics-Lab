#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
using namespace std;

const int WINDOW_W = GetSystemMetrics(SM_CXSCREEN), WINDOW_H = GetSystemMetrics(SM_CYSCREEN)-20;

struct PT
{
    double x, y;
    PT(){}
    PT(double a, double b)
    {
        x = a;
        y = b;
    }

    bool operator < (const PT &p)const
    {
        return x < p.x;
    }
};

struct EDGE
{
    double y_min, y_max, x_with_y_min, m_inv;
    EDGE(){}
    EDGE(double a, double b, double c, double d)
    {
        y_min = a;
        y_max = b;
        x_with_y_min = c;
        m_inv = d;
    }

    bool operator < (const EDGE &p) const
    {
        return y_min < p.y_min;
    }
};

void drawAxis()
{
    for(int i = 0; i<WINDOW_W; i++)
    {
        putpixel(i, WINDOW_H/2, WHITE);
    }

    for(int i = 0; i<WINDOW_H; i++)
    {
        putpixel(WINDOW_W/2, i, WHITE);
    }
}

void drawPixel(PT p, int color)
{
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}

void drawLineBresenham(PT a, PT b, int  col)
{
       if(a.y == b.y)
    {
        if(a.x > b.x) swap(a, b);

        for(int x = a.x; x<=b.x; x++)
        {
            drawPixel(PT(x, a.y), col);
        }
    }

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y<=b.y; y++)
        {
            drawPixel(PT(a.x, y), col);
        }
    }

    else
    {
        double dx, dy, x, y;
        dx = (double)(b.x - a.x);
        dy = (double)(b.y - a.y);
        x = a.x, y = a.y;

        //m<1
        if(abs(dx) > abs(dy))
        {
            drawPixel(PT(x, y), col);

            int d = 2*abs(dy) - abs(dx);

            for(int i = 0; i< abs(dx); i++)
            {
                x = dx<0? x-1 : x+1;
                if(d<0)
                {
                    d = d + 2*abs(dy);
                }
                else
                {
                    y = dy<0? y-1: y+1;
                    d = d + 2*(abs(dy)-abs(dx));
                }
                drawPixel(PT(x, y), col);
            }
        }
        //m>=1
        else
        {
            drawPixel(PT(x, y), col);

            int d = 2*abs(dx) - abs(dy);

            for(int i = 0; i< abs(dy); i++)
            {
                y = dy<0? y-1 : y+1;
                if(d<0)
                {
                    d = d + 2*abs(dx);
                }
                else
                {
                    x = dx<0? x-1: x+1;
                    d = d + 2*(abs(dx)-abs(dy));
                }
                drawPixel(PT(x, y), col);
            }
        }
    }
}



void drawCircleBresenham(PT c, int r, int color)
{
    int x = 0, y = r;
    int d = 3 - 2*r;

    drawPixel(PT(y+c.x, x+c.y), color);
    drawPixel(PT(-y+c.x, x+c.y), color);
    drawPixel(PT(y+c.x, -x+c.y), color);
    drawPixel(PT(-y+c.x, -x+c.y), color);
    drawPixel(PT(x+c.x, y+c.y), color);
    drawPixel(PT(x+c.x, -y+c.y), color);
    drawPixel(PT(-x+c.x, y+c.y), color);
    drawPixel(PT(-x+c.x, -y+c.y), color);

    while(x <= y)
    {
        x++;

        if(d>=0)
        {
            y-- ;
            d = d + 4*x - 4*y + 10;
        }
        else
        {
            d = d + 4*x + 6;
        }

    drawPixel(PT(y+c.x, x+c.y), color);
    drawPixel(PT(-y+c.x, x+c.y), color);
    drawPixel(PT(y+c.x, -x+c.y), color);
    drawPixel(PT(-y+c.x, -x+c.y), color);
    drawPixel(PT(x+c.x, y+c.y), color);
    drawPixel(PT(x+c.x, -y+c.y), color);
    drawPixel(PT(-x+c.x, y+c.y), color);
    drawPixel(PT(-x+c.x, -y+c.y), color);
    }
}

void BoundaryFill(int originX, int originY, int boundaryColor, int fillColor)
{
    int currColor = getpixel(originX, originY);
    if(currColor == boundaryColor || currColor == fillColor )
    {
        return;
    }

    drawPixel(PT(originX,originY), fillColor);

    BoundaryFill(originX, originY+1, boundaryColor, fillColor);
    BoundaryFill(originX, originY-1, boundaryColor, fillColor);
    BoundaryFill(originX+1, originY, boundaryColor, fillColor);
    BoundaryFill(originX-1, originY, boundaryColor, fillColor);
}

void drawPolygon(vector<PT> points, int color)
{
    int n = points.size();
    for(int i = 0; i< n; i++)
    {
        drawLineBresenham(points[i], points[(i+1)%n], color);
    }
}

void scanLine(vector<PT> points, int color)
{
    vector<EDGE> edges;

    int n = points.size();
    double st = 1e15, en = -1e15;

    unordered_map< double, int >  mp;

    for(int i = 0; i<n; i++)
    {
        PT a = points[i];
        PT b = points[(i+1)%n];

        if(a.y == b.y) continue;

        EDGE temp;
        temp.y_min = min(a.y, b.y);
        temp.y_max = max(a.y, b.y);
        temp.x_with_y_min = a.y < b.y ? a.x : b.x;
        temp.m_inv = (b.x-a.x)/(b.y-a.y);

        st = min(st, temp.y_min);
        en = max(en, temp.y_max);

        mp[temp.y_min] = 1;

        edges.push_back(temp);
    }

    n = edges.size();

    sort(edges.begin(), edges.end());

    for(int i=0; i<n; i++)
    {
        if(mp[edges[i].y_max]) edges[i].y_max--;
    }

    for(double y = st; y<=en; y++)
    {
        vector<PT> int_points;
        for(int i=0; i<n; i++)
        {
            if(y >= edges[i].y_min && y <= edges[i].y_max)
            {
                PT tmp;

                tmp.x = edges[i].x_with_y_min;
                tmp.y = y;

                edges[i].x_with_y_min += edges[i].m_inv;

                int_points.push_back(tmp);
            }
        }

        sort(int_points.begin(), int_points.end());

        for(int i=0; i<int_points.size()-1; i+=2)
        {
            drawLineBresenham(int_points[i], int_points[i+1], color);
        }
    }
}


bool pointInsideCircle(PT cc, int r, PT cursorpt )
{
    double d = sqrt(pow((cursorpt.x-cc.x),2) + pow((cursorpt.y-cc.y),2));
    if (d< r) return TRUE;
    else return FALSE;
}

bool pointInsideRectangle(PT rp, PT rq, PT cursorpt)
{
    if(cursorpt.x>rp.x && cursorpt.x < rq.x && cursorpt.y>rp.y && cursorpt.y<rq.y) return TRUE;
}

int main()
{
    initwindow(WINDOW_W, WINDOW_H, "Paint the Flag");

    //rectangle: height = 120, width = 72  , Magnify = 12
    int rx1 = 800, ry1 = 500, rx2 = 920, ry2 = 572;
    PT rp = PT(rx1,ry1), rq = PT(rx2, ry2);

    //circle: centre = (150*(9/20), 90/2), radius = 24
    int cx = rp.x + ((double)(rq.x-rp.x))*9/20, cy = rp.y + ((double)(rq.y-rp.y))/2, r = 24;
    PT cc = PT(cx, cy);

    bool rectangleFilled = FALSE;
    bool circleFilled = FALSE;
    PT cursorpt;

    vector<PT> poly;
    poly.push_back(rq);
    poly.push_back(PT(rq.x, rp.y));
    poly.push_back(rp);
    poly.push_back(PT(rp.x, rq.y));

    drawPolygon(poly, GREEN);
    drawCircleBresenham(cc, r, RED);

    int page = 0, transition = 15;

    while(1)
    {
        setactivepage(page);                                      //Double Buffering
        setvisualpage(1-page);

        cleardevice();

        settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
        outtextxy(70, 40, "Press arrow keys to move the flag.");
        outtextxy(70, 80, "Click the flag to paint it in respective colors.");


        if (GetAsyncKeyState(VK_LBUTTON))
        {
            POINT cursorPos;
            GetCursorPos(& cursorPos);
            ScreenToClient(GetForegroundWindow(), &cursorPos);
            cursorpt = PT(cursorPos.x, cursorPos.y);

            if (pointInsideCircle(cc, r, cursorpt))
            {
                circleFilled = !circleFilled;
            }
            else if (pointInsideRectangle(rp, rq, cursorpt))
            {
                rectangleFilled = !rectangleFilled;
            }
        }

        drawPolygon(poly, GREEN);
        if(rectangleFilled) scanLine(poly, GREEN);

        drawCircleBresenham(cc, r, RED);
        if(circleFilled)  BoundaryFill(cc.x, cc.y, RED, RED);
        else BoundaryFill(cc.x, cc.y, RED, BLACK);

        if(GetAsyncKeyState(VK_RIGHT) )
            {
                if (rq.x+transition<WINDOW_W)
                {
                    cc.x += transition;
                    rp.x += transition;
                    rq.x += transition;

                    poly.clear();
                    poly.push_back(rq);
                    poly.push_back(PT(rq.x, rp.y));
                    poly.push_back(rp);
                    poly.push_back(PT(rp.x, rq.y));
                }
            }
        else if (GetAsyncKeyState(VK_LEFT) )
            {
                if(rp.x-transition>0)
                {
                    cc.x -= transition;
                    rp.x -= transition;
                    rq.x -= transition;

                    poly.clear();
                    poly.push_back(rq);
                    poly.push_back(PT(rq.x, rp.y));
                    poly.push_back(rp);
                    poly.push_back(PT(rp.x, rq.y));
                }
            }
        else if (GetAsyncKeyState(VK_UP))
            {
                if (rp.y-transition>100)
                {
                    cc.y -= transition;
                    rp.y -= transition;
                    rq.y -= transition;

                    poly.clear();
                    poly.push_back(rq);
                    poly.push_back(PT(rq.x, rp.y));
                    poly.push_back(rp);
                    poly.push_back(PT(rp.x, rq.y));
                }
            }
        else if (GetAsyncKeyState(VK_DOWN))
            {
                if (rq.y+transition<WINDOW_H)
                {
                    cc.y += transition;
                    rp.y += transition;
                    rq.y += transition;

                    poly.clear();
                    poly.push_back(rq);
                    poly.push_back(PT(rq.x, rp.y));
                    poly.push_back(rp);
                    poly.push_back(PT(rp.x, rq.y));
                }
            }

        if (GetAsyncKeyState(VK_ESCAPE) )
            break;

        page = 1 - page;
        delay(40);
    }

    getchar();
    return 0;
}
