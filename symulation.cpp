#include "symulation.h"
#include "planeta.h"
#include "kometa.h"
#include "math.h"

#define G 6.67384
Symulation::Symulation()
{
}

/// liczymy
Vector2 Symulation::dvGrav(Planeta p, Kometa k, double dt)
{
    Vector2 posPlaneta= p.zwrocSrodek();
    double mPlaneta = p.zwrocMase();
    Vector2 posKometa = k.zwrocSrodek();
    Vector2 r = posPlaneta - posKometa;
    double rd = r.dlugosc();
    Vector2 dv = (r/rd) * (G*mPlaneta/rd*rd);
    return dv;
}



bool Symulation::HitTest(Planeta planet, Kometa player)
{
    Vector2 pp = planet.zwrocSrodek();
    Vector2 pk = player.zwrocSrodek();
    double rd = (pp-pk).dlugosc();
    rd = fabs(rd);
    if (rd < (planet.zwrocPromien() + player.zwrocPromien())){
        return true;
    }
    return false;

}
