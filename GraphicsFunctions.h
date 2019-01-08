#ifndef GraphicsFunctions

#define GraphicsFunctions

#include <graphics.h>
#include "Punct.h"

void onPressReset()
{
getch();
cleardevice();
}

void drawPoint (Punct P, unsigned int aDelay = 0, int color = WHITE)
{
    circle(P.getGhX(),P.getGhY(),5);
    floodfill(P.getGhX(),P.getGhY(),color);

    if(aDelay > 0) delay(aDelay);
}

void drawLine (Punct startP, Punct endP, unsigned int aDelay = 0, int color = WHITE)
{
    int lastColor = getcolor();
    setcolor(color);
    line(startP.getGhX(),startP.getGhY(),endP.getGhX(),endP.getGhY());
    setcolor(lastColor);

    if(aDelay > 0) delay(aDelay);
}

void undoLine (Punct startP, Punct endP)
{
    drawLine(startP,endP,0,BLACK);
}


void drawLineMultiple (const vector<Punct>& vct, int startPoz, int endPoz, unsigned int aDelay = 0, int color = WHITE)
{
    for(int i=startPoz; i < endPoz; i++)
        drawLine(vct[i],vct[i+1],0,color);

    if(aDelay > 0) delay(aDelay);
}

void undoLineMultiple (const vector<Punct>& vct, int startPoz, int endPoz)
{
    drawLineMultiple(vct, startPoz, endPoz,0,BLACK);
}

void drawForm (const vector<Punct>& vct, unsigned int aDelay = 0, int color = WHITE)
{
    drawLine (vct[ vct.size()-1 ], vct[0],0,color);
    drawLineMultiple(vct, 0, vct.size(), aDelay, color);
}

void drawPoints(const vector <Punct>& aVect, unsigned int waitDelay = 0, bool clearAfterDelay = FALSE)
{
    for(int i = 0; i< aVect.size(); i++)
    {
        drawPoint(aVect[i],waitDelay);
    }

    if(waitDelay > 0)
    {
        delay(2000);
        if(clearAfterDelay) cleardevice();
    }
}

#endif // GraphicsFunctions
