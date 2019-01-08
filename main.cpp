#include <iostream>
#include <graphics.h>
#include <algorithm>
#include "Punct.h"
#include "GraphicsFunctions.h"
#include "PlgSpecific.h"

using namespace std;


int gm, gd=DETECT;

int main()
{

ifstream f ("date.in");
initgraph(&gd,&gm,"c:\\turboC3\\bgi");

vector <Punct> fig1, fig2, joined;
vector < pair < Punct, Punct > > corners;
Punct offset (3,4), moveabit(0,-2);

int varfuri;
f>>varfuri;
fig1.resize(varfuri);
fig2.resize(varfuri);

for (int i=0; i<varfuri; i++)
{
    f>>fig1[i];
    fig1[i] = fig1[i] + moveabit;
    fig2[i] = fig1[i] + offset;
    joined.push_back(fig1[i]);
    joined.push_back(fig2[i]);
}


///DE MODIFICAT CHESTIA ASTA
fig1 = GrahamScan(fig1);
fig2 = GrahamScan(fig2);

fig1.resize(varfuri);
fig2.resize(varfuri);

exibitForms(fig1, fig2);

joined = GrahamScan(joined,true);

for(int i=0; i<joined.size(); i++)
    cout<<joined[i]<<" ";

return 0;
}
