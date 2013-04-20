#ifndef KOMETA_H
#define KOMETA_H
#include "planeta.h"

class Kometa: public Planeta
{
/*This is not the best cometa in the universe. This is just a tribute!*/

public:
    Kometa(Vector2 sr, Vector2 k);

private:
    Vector2 kierunek;



}

#endif // KOMETA_H
