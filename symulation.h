#ifndef SYMULATION_H
#define SYMULATION_H

#include "planeta.h"
#include "kometa.h"
#include "vector.h"
#include <vector>

class Symulation
{
private:
    std::vector <Planeta*> planety;
public:
    Symulation();

    Vector2 dvGrav(Planeta *p, Kometa *k, double dt);
    bool HitTest(Planeta *p ,Kometa *k);
    bool krokSymulacji(double dt, Kometa *k);
};

#endif // SYMULATION_H
