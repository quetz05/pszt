#ifndef ALGORYTM_H
#define ALGORYTM_H
#include <vector>
#include <cstdlib>
#include "kometa.h"
#include <qmath.h>
#define N 10 /*liczba osobników w populacji*/

using namespace std;

class Algorytm
{

private:
    vector <Kometa*> osobniki;
    vector <double> rozklady;


    Kometa* reprodukcja(Kometa *os1, Kometa *os2);
    double liczRozklad();

private:
    static double tau;
    static double tau2;

};

#endif // ALGORYTM_H
