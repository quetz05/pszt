#include "algorytm.h"
#include <QGlobal.h>
#include <qmath.h>
#include <time.h>
#include <iostream>
#include <QDebug>



static double tau = 1 / (qSqrt(2 * qSqrt(N)));
static double tau2 = 1 / (qSqrt(2 * N));

Populacja::Populacja() : generator(rd()), rozkladNorm(0,1)
{
    for(int i = 0; i < N; i++)
    {
        osobniki.push_back(new Kometa(Vector2(losuj(10,800),losuj(10,600)), Vector2(losuj(-300,300),losuj(-300,300))));

        for(int j = 0; j<ARG; j++)
        {
            double a =rozkladNorm(generator);
            osobniki[i]->rozklady.push_back(a);
        }

    }
}

Populacja::Populacja(vector <Kometa*> nowaPopulacja)
{
    osobniki = nowaPopulacja;
}


void Populacja::tworzSekwencje()
{
    int indeks = 0;
    int i=0;
    while(i < 2*N)
    {
        indeks  = losuj(0,10);
        sekwencjaRodzicow.push_back(osobniki[indeks]);
        i++;

    }
}

void Populacja::krzyzowanie()
{
    Vector2 sr;
    Vector2 kier;

    for(unsigned int i = 0; i < (sekwencjaRodzicow.size()-1); i++)
    {
        kier = (sekwencjaRodzicow[i]->zwrocKierunek()+sekwencjaRodzicow[i+1]->zwrocKierunek())/2;
        sr = (sekwencjaRodzicow[i]->zwrocSrodek()+sekwencjaRodzicow[i+1]->zwrocSrodek())/2;

        zarodki.push_back(new Kometa(sr, kier));

        for(int j=0; j< ARG; j++)
            zarodki.back()->rozklady.push_back((sekwencjaRodzicow[i]->rozklady[j]+ sekwencjaRodzicow[i+1]->rozklady[j])/2);

    }

}


void Populacja::mutacja()
{
    double xi = 0;


    for(unsigned int i = 0; i<zarodki.size(); i++)
    {
       xi = rozkladNorm(generator);

       vector <double> rozk;

       for(unsigned int j=0; j<ARG; j++)
                 rozk.push_back(zarodki[i]->rozklady[j]*qExp(tau2*xi + tau*rozkladNorm(generator)));

       rozkladyZarodkow.push_back(rozk);
    }

}

void Populacja::tworzNowychOsobnikow()
{
\
    Vector2 kier;
    Vector2 sr;

    for(unsigned int i=0; i<zarodki.size();i++)
    {
        sr.x = zarodki[i]->zwrocSrodek().x + rozkladNorm(generator)*rozkladyZarodkow[i][0];
        sr.y = zarodki[i]->zwrocSrodek().y + rozkladNorm(generator)*rozkladyZarodkow[i][1];
        kier.x = zarodki[i]->zwrocKierunek().x + rozkladNorm(generator)*rozkladyZarodkow[i][2];
        kier.y = zarodki[i]->zwrocKierunek().y + rozkladNorm(generator)*rozkladyZarodkow[i][3];

        potomki.push_back(new Kometa(sr, kier));

        for(unsigned int j=0; j<ARG; j++)
            potomki.back()->rozklady.push_back(rozkladyZarodkow[i][j]);
    }
}


void Populacja::tworzNowaPopulacje()
{
    this->tworzSekwencje();
    this->krzyzowanie();
    this->mutacja();
    this->tworzNowychOsobnikow();


}

double Populacja::losuj(int a, int b)
{
    int min = 100*a;
    int max = 100*b;

    double losowa = rand()%(max-min+1)+min;

    double wylosuj = losowa/100.0f;

    return wylosuj;
}


