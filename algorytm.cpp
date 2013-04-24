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
        osobniki.push_back(new Kometa(Vector2(losuj(0,800),losuj(0,600)), Vector2(losuj(-100,100),losuj(-100,100))));
        //wektor rozkładów osobnika
        vector <double> rozOs;
        for(int j = 0; j<ARG; j++)
        {
            double a =rozkladNorm(generator);
            rozOs.push_back(a);
        }

        rozklady.push_back(rozOs);
    }
}

Populacja::Populacja(vector <Kometa*> nowaPopulacja, vector <vector<double>> noweRozklady)
{





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


void Populacja::mutacja()
{
    double xi = 0;


    for(unsigned int i = 0; i<rozkladyZarodkow.size(); i++)
    {
       xi = rozkladNorm(generator);

       double odch;
       vector <double> rozk;

       for(unsigned int j=0; j<rozkladyZarodkow[i].size(); j++)
       {
                 odch = rozkladyZarodkow[i][j]*qExp(tau2*xi + tau*rozkladNorm(generator));
                 rozk.push_back(odch);
       }

       noweRozklady.push_back(rozk);
    }

}

void Populacja::tworzNowychOsobnikow()
{

    this->mutacja();

    Vector2 kier;
    Vector2 sr;

    for(int i=0; i<N;i++)
    {
        sr.x = zarodki[i]->zwrocSrodek().x + rozkladNorm(generator)*rozkladyZarodkow[i][0];
        sr.y = zarodki[i]->zwrocSrodek().y + rozkladNorm(generator)*rozkladyZarodkow[i][1];
        kier.x = zarodki[i]->zwrocKierunek().x + rozkladNorm(generator)*rozkladyZarodkow[i][2];
        kier.y = zarodki[i]->zwrocKierunek().y + rozkladNorm(generator)*rozkladyZarodkow[i][3];

        nowiOsobnicy.push_back(new Kometa(sr, kier));
    }
}


void Populacja::tworzNowaPopulacje()
{
    osobniki.clear();
    rozklady.clear();

    for(int i = 0; i<N; i++)
    {
        osobniki.push_back(nowiOsobnicy[i]);
        rozklady.push_back(noweRozklady[i]);
    }
}

double Populacja::losuj(int a, int b)
{
    int min = 100*a;
    int max = 100*b;

    double losowa = rand()%(max-min+1)+min;

    double wylosuj = losowa/100.0f;

    return wylosuj;
}


