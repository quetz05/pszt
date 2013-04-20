#ifndef SYMULATION_H
#define SYMULATION_H
#include "vector.h"

class Symulation
{
public:
    Symulation();

    Vector2 dvGrav(Planeta p, Kometa k,double dt);
    bool HitTest(Planeta p ,Kometa k);
};

#endif // SYMULATION_H
