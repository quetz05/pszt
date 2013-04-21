#include "algorytm.h"
#include <QGlobal.h>
#include <qmath.h>
#include <time.h>

const double pi = 3.14159265358979323;
static double tau = 1 / (qSqrt(2 * qSqrt(N)));
static double tau2 = 1 / (qSqrt(2 * N));

Populacja::Populacja()
{
    //wektor rozkładów osobnika
    vector <double> rozOs;

    for(int i = 0; i < N; i++)
    {
        osobniki.push_back(new Kometa(Vector2(losuj(0,800),losuj(0,600)), Vector2(losuj(0,800),losuj(0,600))));

        for(int j = 0; j<ARG; j++)
        {
            rozOs.push_back(rozkladNormalny(losuj(0,4)));
        }

        rozklady.push_back(rozOs);
    }
}

void Populacja::tworzSekwencje()
{
    int indeks = 0;
    int i=0;
    while(i < 2*N)
    {
        indeks  = losuj(0,10);
        sekwencjaRodzicow.push_back(osobniki[indeks]);
        rozkladySekwencji.push_back(rozklady[indeks]);

        i++;

    }
}

void Populacja::krzyzowanie()
{
    Vector2 sr;
    Vector2 kier;
    vector <double> rozkl;

    for(unsigned int i = 0; i < (sekwencjaRodzicow.size()-1); i++)
    {
        kier = (sekwencjaRodzicow[i]->zwrocKierunek()+sekwencjaRodzicow[i+1]->zwrocKierunek())/2;
        sr = (sekwencjaRodzicow[i]->zwrocSrodek()+sekwencjaRodzicow[i+1]->zwrocSrodek())/2;

        for(int j=0; j< ARG; j++)
        {
            rozkl.push_back(rozkladySekwencji[i][j]);
        }

        rozkladyZarodkow.push_back(rozkl);
        zarodki.push_back(new Kometa(sr, kier));


    }

}


/*void Populacja::mutacja(int i)
{
    double odchylenie;

    vector

    odchylenie = rozkladyZarodkow[i].





}*/


double Populacja::losuj(double a, int b)
{
    return ((qrand() % b) + a);
}

double Populacja::rozkladNormalny(int x)
{
    return 1/qSqrt(2*pi)*qExp(-(x*x)/2);
}

