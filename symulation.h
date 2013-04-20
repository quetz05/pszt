#ifndef SYMULATION_H
#define SYMULATION_H

#include "planeta.h"
#include "kometa.h"
#include "vector.h"
#include <vector>

class Symulation
{
public:
    Symulation();

    std::vector <Planeta> planety;
    Kometa kometa;

    Vector2 dvGrav(Planeta p, Kometa k, double dt);
    bool HitTest(Planeta p ,Kometa k);
};

#endif // SYMULATION_H
