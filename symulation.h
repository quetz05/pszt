#ifndef SYMULATION_H
#define SYMULATION_H
#include "vector.h"
#include <vector>

class Symulation
{
private:
    Vector <Planeta> planety;
public:
    Symulation();






    Vector2 dvGrav(Planeta p, Kometa k,double dt);
    bool HitTest(Planeta p ,Kometa k);
    bool krokSymulacji (double dt, kometa k);
};

#endif // SYMULATION_H
