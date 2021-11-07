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

void drawLineDDA(PT a, PT b)
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
        double dx, dy, steps, x, y, xinc, yinc;
        dx = (double)(b.x - a.x);
        dy = (double)(b.y - a.y);

        if(abs(dx)>=abs(dy))
        {
            steps = abs(dx);
        }
        else
        {
            steps = abs(dy);
        }

        xinc = dx / (double) steps;
        yinc = dy / (double) steps;
        x = a.x, y = a.y;
        for(int i = 0; i<=steps; i++)
        {
            drawPixel(PT(int(x+0.5), int(y+0.5)), YELLOW);
            x= x + xinc;
            y= y + yinc;
        }
    }
}

int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    drawLineDDA(PT(3,2), PT(100, 2));
    drawLineDDA(PT(3,200), PT(3, 2));
    drawLineDDA(PT(100,-100), PT(-200,200));

    getchar();

    return 0;
}
