#ifndef ALGORYTM_H
#define ALGORYTM_H
#include <vector>
#include <cstdlib>
#include "kometa.h"



#define N 10 /*liczba osobników w populacji*/
#define ARG 4 /*liczba argumentów jednego osobnika*/

using namespace std;


class Populacja
{

public:
    Populacja();

    //początkowi osobnicy populacji
    vector <Kometa*> osobniki;
    //rozklady osobników
    vector <vector<double>> rozklady;

    //sekwencja rodziców do rozmnażania
    vector <Kometa*> sekwencjaRodzicow;
    //rozklady osobników
    vector <vector<double>> rozkladySekwencji;

    //zardoki
    vector <Kometa*> zarodki;
    //rozklady osobników
    vector <vector<double>> rozkladyZarodkow;




    //losuje sekwencje rodziców do rozmnażania - (N+1) osobników
    void tworzSekwencje();
    //krzyżuje osobniki z sekwencji, tworząc zarodki
    void krzyzowanie();
    //mutuje zarodki tworząc nowe osobniki
    void mutacja();


    //metoda losująca liczbę z przedziału <a,b>
    static double losuj(double a, int b);
    //metoda zwracająca liczbę z rozkładu normalnego dla danego x
    static double rozkladNormalny(int x);

private:

};

#endif // ALGORYTM_H
