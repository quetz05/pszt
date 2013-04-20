#ifndef KOMETA_H
#define KOMETA_H

#include "planeta.h"

class Kometa : public Planeta
{
/*This is not the best Kometa in the world. This is just a tribute!*/

public:
    Kometa(){}
    Kometa(Vector2 sr, Vector2 k);
    Vector2 zwrocKierunek(){return kierunek;}
    void ustawPozycje(Vector2 p){this->srodek = p;}
    void ustawKierunek(Vector2 k){this->kierunek = k;}

private:
    Vector2 kierunek;
};

#endif // KOMETA_H
