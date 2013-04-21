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

public:
    Algorytm();

private:
    vector <Kometa> osobniki;
    vector <double> rozklady;


    Kometa reprodukcja(Kometa os1, Kometa os2);
    double liczRozklad();

    static double losuj(double a, double b);
    static double rozkladNormalny();

private:
    static const double tau = 1/(qSqrt(2*qSqrt(N)));
    static const double tau2 = 1/(qSqrt(2N));
    static const double pi = 3.14159265358979323846264338327950288419717;

};

#endif // ALGORYTM_H
