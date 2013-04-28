#include "algorytm.h"
#include <QGlobal.h>
#include <qmath.h>
#include <time.h>
#include <iostream>
#include <QDebug>
#include <algorithm>



static double tau = 1 / (qSqrt(2 * qSqrt(N)));
static double tau2 = 1 / (qSqrt(2 * N));

Populacja::Populacja(std::vector<Planeta *> * p) : generator(rd()), rozkladNorm(0,1)
{
    this->plansza = p;
    for(int i = 0; i < N; i++)
    {
        osobniki.push_back(new Kometa(Vector2(losuj(10,780),losuj(10,580)), Vector2(losuj(2,2),losuj(-2,2))));

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

    QList <Kometa*> temp;

    for(unsigned int j=0; j<osobniki.size(); j++)
        temp.push_back(osobniki[j]);

    for(unsigned int i=0; i<potomki.size();i++)
        temp.push_back(potomki[i]);


        for( int a=0; a<temp.size(); a++)
            for( int b=0; b<temp.size(); b++)
                if(temp[b]->czasZycia < temp[b+1]->czasZycia)
                {
                    Kometa *t;
                    t = temp[b];
                    temp[b] = temp[b+1];
                    temp[b+1] = t;
                }

    osobniki.clear();

    for(unsigned int k=0; k<N; k++)
        osobniki.push_back(temp[k]);

    emit gotowe();

}

/**
 * @brief Populacja::oceniaj ocenianie
 */
void Populacja::oceniaj(vector<Kometa *> *k)
{
    Symulation** sim = new Symulation* [k->size()];

    for (unsigned int i = 0; i <k->size(); ++i) {
        sim[i] = new Symulation(i);
        sim[i]->dodajGracza(k->at(i));
        sim[i]->ustawInteraktywne(false);
        for (unsigned int j = 0; j < this->plansza->size(); ++j)
            sim[i]->dodajPlanete(plansza->at(j));

       // connect(sim[i], SIGNAL(powiadom(Kometa*,Wiadomosc)),
         //       this, SLOT(odbierzWiadomosc(Kometa*,Wiadomosc)));

    }

    for (unsigned int i = 0; i <k->size(); ++i) {
        sim[i]->start();
    }
    for (unsigned int i = 0; i <k->size(); ++i) {
        while(!sim[i]->czyzakonczony())
            //QApplication::processEvents();
            this->thread()->msleep(100);
    }

    /*
     *usuwanie symulacji
     */
    for (unsigned int i = 0; i <k->size(); ++i) {
        delete sim[i];
    }
    delete [] sim;
}

double Populacja::losuj(int a, int b)
{
    return ((double)((double)rand() / (double)RAND_MAX) * b) + a;
}


