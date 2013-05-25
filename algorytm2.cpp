#include "algorytm2.h"
#include <QGlobal.h>
#include <qmath.h>
#include <time.h>
#include <iostream>
#include <QDebug>
#include <algorithm>
#include <QThreadPool>


void Populacja2::krzyzowanie()
{

    double a = rozkladNorm(generator);
    Vector2 sr;
    Vector2 kier;

    for(unsigned int i = 0; i < (sekwencjaRodzicow.size()-1); i++)
    {
        kier = a*(sekwencjaRodzicow[i]->zwrocKierunek())+(1-a)*(sekwencjaRodzicow[i+1]->zwrocKierunek());
        sr = a*(sekwencjaRodzicow[i]->zwrocSrodek())+(1-a)*(sekwencjaRodzicow[i+1]->zwrocSrodek());

        zarodki.push_back(new Kometa(sr, kier));

        for(int j=0; j< ARG; j++)
            zarodki.back()->rozklady.push_back(a*(sekwencjaRodzicow[i]->rozklady[j])+ (1-a)*(sekwencjaRodzicow[i+1]->rozklady[j]));

    }
}

void Populacja2::tworzNowaPopulacje()
{

    while (1) {
        mux->lock();

        potomki.clear();
        sekwencjaRodzicow.clear();
        zarodki.clear();
        rozkladyZarodkow.clear();

        emit nadajWiadomosc(ProstaWiadomosc(sekwencja));
        this->tworzSekwencje();
        emit nadajWiadomosc(ProstaWiadomosc(krzyzuj));
        this->krzyzowanie();
        emit nadajWiadomosc(ProstaWiadomosc(mutuj));
        this->mutacja();
        emit nadajWiadomosc(ProstaWiadomosc(tworz));
        this->tworzNowychOsobnikow();
        emit nadajWiadomosc(ProstaWiadomosc(ocena));

        oceniaj(&potomki);

        QList <Kometa*> temp;

        for(unsigned int j=0; j<osobniki.size(); j++)
            temp.push_back(osobniki[j]);

        for(unsigned int i=0; i<potomki.size();i++)
            temp.push_back(potomki[i]);


        for( int a=0; a<temp.size() - 1; a++)
            for( int b=0; b<temp.size() - 1; b++)
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

        emit nadajWiadomosc(ProstaWiadomosc(zakonczyl));
        emit gotowe();

        //mux->unlock();
    }
}
