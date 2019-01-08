#ifndef PoligonSpecific

#define PoligonSpecific

#include "GraphicsFunctions.h"

int badPointDelay = 200;
int pointDelay = 0;

/** REMOVE BAD POINTS */
bool rmBadPoints (vector<Punct>& frt, int wrongWay, bool Graphical = false)
{
    int last = frt.size() -1;
    if(Graphical) drawLineMultiple(frt,last-2,last,badPointDelay,YELLOW);

    if(wrongWay == Punct::Position(frt [last-2], frt [last -1], frt [last] ))
    {
        if(Graphical)
            {
                drawLine(frt[last-1],frt[last],badPointDelay,RED);
                undoLineMultiple(frt,last-2,last);
            }

        frt.erase (frt.begin() + last-1);
        return 1;
    }

    if(Graphical)
        {
                drawLineMultiple(frt,last-2,last,badPointDelay,GREEN);
                drawLineMultiple(frt,last-2,last,badPointDelay,WHITE);
        }
    return 0;

}


/** GRAHAM SCAN */
vector<Punct> GrahamScan (const vector <Punct>& vecPct, bool Graphical = false)
{
    vector<Punct> vctSrt = vecPct;
    sort (vctSrt.begin(), vctSrt.end());
    vector<Punct> frontiera;

    for(int i=0; i< vctSrt.size()-1; i++)
    {
        if(vctSrt[i] == vctSrt[i+1])
            {
                vctSrt.erase(vctSrt.begin() + i);
                i--;
            }

    }

    if(Graphical) drawPoints(vctSrt,pointDelay);

    frontiera.push_back(vctSrt[0]);
    frontiera.push_back(vctSrt[1]);

    if(Graphical) drawPoint(frontiera[0],pointDelay);
    if(Graphical) drawPoint(frontiera[1],pointDelay);

    int alCatelea = 2;
    int badWay = RIGHT_POINT_POZ;

    while (alCatelea < vctSrt.size())
    {
        frontiera.push_back (vctSrt[alCatelea]);

        while ( frontiera.size() > 2 && rmBadPoints (frontiera, badWay, Graphical) ) {}
        alCatelea ++ ;
    }


    alCatelea = vctSrt.size() - 2; /// PENULTIMUL DIN SORTARE
    frontiera.push_back(vctSrt[alCatelea]);
    alCatelea--;

    int minimSize = frontiera.size(); ///FRONTIERA INFERIOARA + 1 ELEMENT DIN CEA SUPERIOARA

    while( alCatelea >= 0 )
    {
        frontiera.push_back (vctSrt [alCatelea]);

        while ( frontiera.size() > minimSize && rmBadPoints (frontiera, badWay, Graphical) ) {}
        alCatelea -- ;
    }


    if(Graphical)
        {
            cleardevice();
            drawPoints(vctSrt);
            drawLineMultiple(frontiera,0,frontiera.size()-1);
            onPressReset();
        }

    return frontiera;
}

/** AFISARI FIGURI */
void exibitForms(const vector <Punct>& fig1, const vector <Punct>& fig2)
{
unsigned int formDelay = 200;
unsigned int pointsDelay = 0;

outtextxy(50, 50, "PRIMUL");

drawPoints(fig1,pointsDelay);
drawForm(fig1,formDelay);

onPressReset();


outtextxy(50, 50, "AL DOILEA");

drawPoints(fig2,pointsDelay);
drawForm(fig2,formDelay);

onPressReset();

outtextxy(50, 50, "AMBELE");
drawPoints(fig1,pointsDelay);
drawForm(fig1,formDelay,BLUE);

getch();

drawPoints(fig2,pointsDelay);
drawForm(fig2,formDelay,GREEN);

getch();

for(int i=0; i<fig1.size(); i++)
    drawLine(fig1[i],fig2[i],0,YELLOW);

onPressReset();

}

#endif // PoligonSpecific
