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
    // a = (gm1/r2)*r->/r
    // a = dv/dt
    // dv = a*dt
    Vector2 posPlaneta= p.zwrocSrodek();
    double mPlaneta = p.zwrocMase();
    Vector2 posKometa = k.zwrocSrodek();
    vector2 r = posPlaneta - posKometa;
    double rd = r.dlogosc;
    Vector2 dv = (G*mPlaneta/rd*rd)*(r/rd);
    return dv;
}



bool Symulation::HitTest(Planeta planet, Kometa player)
{
    Vector2 pp=planet.zwrocSrodek();
    Vector2 pk = player.zwrocSrodek();
    double rd = (pp-pk).dlogosc;
    rd = fabs(rd);
    if (rd < (planet.zwrocPromien() + player.zwrocPromien())){
        return true;
    }
    return false;

}
