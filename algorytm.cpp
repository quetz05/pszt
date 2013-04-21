#include "algorytm.h"
#include <QGlobal.h>

Algorytm::Algorytm()
{

    for(int i = 0; i++; i<N)
        kometa.push_back(new Kometa(new Vector2(losuj(0,800),losuj(0,600)), new Vector2(losuj(0,800),losuj(0,600)));






}

static double Algorytm::losuj(double a, double b)
{
    return qrand() % b + a;
}
