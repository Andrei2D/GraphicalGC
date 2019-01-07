#include <iostream>
#include <graphics.h>
#include <algorithm>
#include "Punct.h"

using namespace std;


void drawPoint (Punct P)
{
    circle(P.getGhX(),P.getGhY(),5);
    floodfill(P.getGhX(),P.getGhY(),WHITE);
}

bool rmBadPoints (vector<Punct>& frt, int wrongWay)
{
    int last = frt.size() -1;
    if(wrongWay == Punct::Position(frt [last-2], frt [last -1], frt [last] ))
    {
        frt.erase (frt.begin() + last-1);
        return 1;
    }

    return 0;


}

void drawAllPoints(const vector <Punct>& unordVect, const vector <Punct>& ordVect)
{
    for(int i = 0; i< unordVect.size(); i++)
    {
        drawPoint(unordVect[i]);
        delay(500);
    }
    outtextxy(100,100, "Gata punctele normale.");
    delay(2000);


    cleardevice();

        for(int i = 0; i< ordVect.size(); i++)
    {
        drawPoint(ordVect[i]);
        delay(500);
    }
    outtextxy(100,100, "Gata punctele ordonate.");
    delay(2000);

    cleardevice();
    for(int i = 0; i< ordVect.size(); i++)
        drawPoint(ordVect[i]);

}


vector<Punct> GrahamScan (const vector <Punct>& vecPct)
{
    vector<Punct> vctSrt = vecPct;
    sort (vctSrt.begin(), vctSrt.end());
    vector<Punct> frontiera;

    drawAllPoints(vecPct, vctSrt);

    frontiera.push_back(vctSrt[0]);
    frontiera.push_back(vctSrt[1]);

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
