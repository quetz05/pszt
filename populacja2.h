#ifndef POPULACJA2_H
#define POPULACJA2_H

#include "algorytm.h"

class Populacja2 : public Populacja
{

public:

    Populacja2(std::vector <Planeta*>*p) : Populacja(p) {}
    Populacja2(vector <Kometa*> *nowaPopulacja, std::vector<Planeta *> * p) : Populacja(nowaPopulacja, p) {}

    //tworzy nowa populacje
    void tworzNowaPopulacje();



private:
    //krzyżuje osobniki z sekwencji, tworząc zarodki
    void krzyzowanie();




};
#endif // ALGORYTM2_H
