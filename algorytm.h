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
    vector <Kometa> osobniki;
    vector <double> rozklady;


    Kometa reprodukcja(Kometa os1, Kometa os2);
    double liczRozklad();

private:
    static double tau = 1/(qSqrt(2*qSqrt(N)));
    static double tau2 = 1/(qSqrt(2N));

};

#endif // ALGORYTM_H
