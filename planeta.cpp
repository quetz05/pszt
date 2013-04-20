#include "planeta.h"

Planeta::Planeta()
{
    srodek.x = 0;
    srodek.y = 0;
    masa = 1;
    promien = 5 + 2*masa;
}


Planeta::Planeta(Vector2 vec, double m)
{
    srodek.x = vec.x;
    srodek.y = vec.y;
    masa = m;
    promien = 5 + 0,5*masa;
}
