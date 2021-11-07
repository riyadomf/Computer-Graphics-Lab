#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
using namespace std;

struct PT
{
    int x, y;
    PT(){}
    PT(int a, int b)
    {
        x = a;
        y = b;
    }
};

const int WINDOW_W = GetSystemMetrics(SM_CXSCREEN), WINDOW_H = GetSystemMetrics(SM_CYSCREEN);

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
    putpixel(p.x, p.y, color);
}

void drawLineBresenham(PT a, PT b)
{
       if(a.y == b.y)
    {
        if(a.x > b.x) swap(a, b);

        for(int x = a.x; x<=b.x; x++)
        {
            drawPixel(PT(x, a.y), YELLOW);
        }
    }

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y<=b.y; y++)
        {
            drawPixel(PT(a.x, y), YELLOW);
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
            drawPixel(PT(x, y), YELLOW);

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
                drawPixel(PT(x, y), YELLOW);
            }
        }
        //m>=1
        else
        {
            drawPixel(PT(x, y), YELLOW);

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
                drawPixel(PT(x, y), YELLOW);
            }
        }
    }
}

int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    drawLineBresenham(PT(10,200), PT(200,300));
    drawLineBresenham(PT(10,5), PT(100,200));
    drawLineBresenham(PT(100,-50), PT(-200,200));
    drawLineBresenham(PT(100,-100), PT(50,200));

    getchar();

    return 0;
}
