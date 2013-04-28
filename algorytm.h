#ifndef ALGORYTM_H
#define ALGORYTM_H
#include <cstdlib>
#include "kometa.h"
#include <random>
#include "symulation.h"
#include <QObject>



#define N 10 /*liczba osobników w populacji*/
#define ARG 4 /*liczba argumentów jednego osobnika*/

using namespace std;

typedef vector<double> vectorDouble;

class Populacja : public QObject
{

    Q_OBJECT
public:
    Populacja(std::vector <Planeta*>*p);
    Populacja(vector <Kometa*> nowaPopulacja);

    //początkowi osobnicy populacji
    vector <Kometa*> osobniki;
    //rozklady osobników
    vector <vector<double>> rozklady;

    //potomki populacji  do oceny
    vector <Kometa*> potomki;

    void ustawCzasDocelowy(int czas) { czasDocelowy = czas; }

    //tworzy nowa populacje
    void tworzNowaPopulacje();
    /**
     * @brief oceniaj funkcja oceniajaca potomkow
     */
    void oceniaj(vector<Kometa*>* k);


signals:
    void gotowe();

private:

    //czas ktory uznajemy za nieskonczonosc
    int czasDocelowy;

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

   /* //funkcja porownujaca czas zycia osobnikow
    static bool porownajCzasZycia(Kometa a, Kometa b);*/

    std::random_device rd;
    //generator liczb pseudolosowych (do rozkladu normalnego)
    std::mt19937 generator;
    std::normal_distribution<> rozkladNorm;
    /**
     * @brief plansza wskaźnik na wektor planet który stanowi nasze środowisko obliczeniowe
     */
    std::vector <Planeta*>* plansza;
};

#endif // ALGORYTM_H
