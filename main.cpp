#include <iostream>
#include <graphics.h>
#include <algorithm>
#include "Punct.h"
#include "GraphicsFunctions.h"

using namespace std;


void drawAllPoints(const vector <Punct>& aVect, unsigned int waitDelay = 0, bool clearAfterDelay = FALSE)
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

int badPointDelay = 350;

bool rmBadPoints (vector<Punct>& frt, int wrongWay)
{
    int last = frt.size() -1;
    drawLineMultiple(frt,last-2,last,badPointDelay,YELLOW);

    if(wrongWay == Punct::Position(frt [last-2], frt [last -1], frt [last] ))
    {
        drawLine(frt[last-1],frt[last],badPointDelay,RED);
        undoLineMultiple(frt,last-2,last);

        frt.erase (frt.begin() + last-1);
        return 1;
    }

    drawLineMultiple(frt,last-2,last,badPointDelay,GREEN);
    drawLineMultiple(frt,last-2,last,badPointDelay,WHITE);

    return 0;

}


int pointDelay = 350;

vector<Punct> GrahamScan (const vector <Punct>& vecPct)
{
    vector<Punct> vctSrt = vecPct;
    sort (vctSrt.begin(), vctSrt.end());
    vector<Punct> frontiera;

    drawAllPoints(vctSrt,pointDelay);

    frontiera.push_back(vctSrt[0]);
    frontiera.push_back(vctSrt[1]);

    drawPoint(frontiera[0],pointDelay);
    drawPoint(frontiera[1],pointDelay);

    int alCatelea = 2;
    int badWay = RIGHT_POINT_POZ;

    while (alCatelea < vctSrt.size())
    {
        frontiera.push_back (vctSrt[alCatelea]);

        while ( frontiera.size() > 2 && rmBadPoints (frontiera, badWay) ) {}
        alCatelea ++ ;
    }


    alCatelea = vctSrt.size() - 2; /// PENULTIMUL DIN SORTARE
    frontiera.push_back(vctSrt[alCatelea]);
    alCatelea--;

    int minimSize = frontiera.size(); ///FRONTIERA INFERIOARA + 1 ELEMENT DIN CEA SUPERIOARA

    while( alCatelea >= 0 )
    {
        frontiera.push_back (vctSrt [alCatelea]);

        while ( frontiera.size() > minimSize && rmBadPoints (frontiera, badWay) ) {}
        alCatelea -- ;
    }

    cleardevice();
    drawAllPoints(vctSrt);
    drawLineMultiple(frontiera,0,frontiera.size());

    return frontiera;
}


int gm, gd=DETECT;

int main()
{


initgraph(&gd,&gm,"c:\\turboC3\\bgi");

ifstream f ("date.in");
vector <Punct> P;
int n;
f>>n;
P.resize(n);
for(int i=0;i<n;i++)
    f>>P[i];
vector<Punct> rez = GrahamScan(P);

for(int i=0; i < rez.size(); i++ )
    cout<<rez[i]<<" ";

    getch();
    closegraph();



return 0;
}
