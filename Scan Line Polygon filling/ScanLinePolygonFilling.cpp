#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
using namespace std;

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



const int WINDOW_W = 800, WINDOW_H = 600;

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

PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    //delay(1);
    p = convertPixel(p);
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


void drawPolygon(vector<PT> points)
{
    int n = points.size();
    for(int i = 0; i< n; i++)
    {
        drawLineBresenham(points[i], points[(i+1)%n], YELLOW);
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

int main()
{
    initwindow(WINDOW_W, WINDOW_H);
//    drawAxis();

    vector<PT> poly;
    poly.push_back(PT(40, 35));
    poly.push_back(PT(100, 70));
    poly.push_back(PT(155, 140));
    poly.push_back(PT(50, 180));
    poly.push_back(PT(-60, 100));
    poly.push_back(PT(-30, -100));



    drawPolygon(poly);

    scanLine(poly, RED);

    getchar();

    return 0;
}




