#ifndef ALGORYTM_H
#define ALGORYTM_H
#include <cstdlib>
#include "kometa.h"
#include <random>

#define N 10 /*liczba osobników w populacji*/
#define ARG 4 /*liczba argumentów jednego osobnika*/

using namespace std;


class Populacja
{

public:
    Populacja();
    Populacja(vector <Kometa*> nowaPopulacja);

    //początkowi osobnicy populacji
    vector <Kometa*> osobniki;
    //rozklady osobników
    vector <vector<double>> rozklady;

    //potomki populacji
    vector <Kometa*> potomki;

    //nowa populacja
    vector <Kometa*> noweOsobniki;

    //tworzy nowa populacje
    void tworzNowaPopulacje();

    double oceniaj();




private:

    //sekwencja rodziców do rozmnażania
    vector <Kometa*> sekwencjaRodzicow;
    //zardoki
    vector <Kometa*> zarodki;
    //rozkłady zarodków
    vector <vector<double>> rozkladyZarodkow;


    //losuje sekwencje rodziców do rozmnażania - (N+1) osobników
    void tworzSekwencje();
    //krzyżuje osobniki z sekwencji, tworząc zarodki
    void krzyzowanie();
    //mutuje zarodek tworząc nowe rozklady
    void mutacja();
    //towrzy nowych osobników na podstawie rozkładów
    void tworzNowychOsobnikow();

    //metoda losująca liczbę z przedziału <a,b>
    static double losuj(int a, int b);

    std::random_device rd;
    //generator liczb pseudolosowych (do rozkladu normalnego)
    std::mt19937 generator;
    std::normal_distribution<> rozkladNorm;
};

#endif // ALGORYTM_H
