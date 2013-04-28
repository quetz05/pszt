#ifndef ALGORYTM_H
#define ALGORYTM_H
#include <vector>
#include <cstdlib>
#include "kometa.h"
#include <random>



#define N 10 /*liczba osobników w populacji*/
#define ARG 4 /*liczba argumentów jednego osobnika*/

/**dodanie pair do vectora**/
/**likwidacja zbędnych wektorów**/
/**do 1 funkcji**/

using namespace std;

typedef vector<double> vectorDouble;

class Populacja
{

public:
    Populacja();
    Populacja(vector <Kometa*> nowaPopulacja, vector <vector<double>> noweRozklady);

    //początkowi osobnicy populacji
    vector <Kometa*> osobniki;
    //rozklady osobników
    vector <vector<double>> rozklady;



    vector <Kometa*> nowiOsobnicy;
    vector <vector<double>> noweRozklady;


    void ustawCzasDocelowy(int czas) { czasDocelowy = czas; }


    //losuje sekwencje rodziców do rozmnażania - (N+1) osobników
    void tworzSekwencje();
    //krzyżuje osobniki z sekwencji, tworząc zarodki
    void krzyzowanie();

    //towrzy nowych osobników na podstawie rozkładów
    void tworzNowychOsobnikow();
    //tworzy nowa populacje
    void tworzNowaPopulacje();

    double oceniaj();


private:

    //czas ktory uznajemy za nieskonczonosc
    int czasDocelowy;

    //sekwencja rodziców do rozmnażania
    vector <Kometa*> sekwencjaRodzicow;
    //rozklady osobników
    vector <vector<double>> rozkladySekwencji;

    //zardoki
    vector <Kometa*> zarodki;
    //rozklady osobników
    vector <vector<double>> rozkladyZarodkow;

    //mutuje zarodek tworząc nowe rozklady
    void mutacja();

    //metoda losująca liczbę z przedziału <a,b>
    static double losuj(int a, int b);

    std::random_device rd;
    //generator liczb pseudolosowych (do rozkladu normalnego)
    std::mt19937 generator;
    std::normal_distribution<> rozkladNorm;
};

#endif // ALGORYTM_H
