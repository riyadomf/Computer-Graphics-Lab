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


int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    int originX = 0, originY = 0, radius = 150;
    drawCircleBresenham(PT(originX,originY), radius, GREEN);

    getchar();

    return 0;
}


