#include "symulation.h"
#include "planeta.h"
#include "kometa.h"
#include "math.h"

#define G 6.67384

using namespace std;


Symulation::Symulation()
{
}
/**
 * @brief Symulation::dvGrav
 * @param p planeta ktora wytwaza pole grawitacyjne
 * @param k kometa ktora jest w tym polu
 * @param dt delta time
 * @return
 */
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


/**
 * @brief Symulation::HitTest
 * @param planet planeta z ktora mozna sie zdezyc
 * @param player kometa ktora sterujemy
 * @return true jezeli nastepuje zdezenie
 */
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
/**
 * @brief Symulation::krokSymulacji
 * @param dt delta time
 * @param k kometa do zmodyfikowania (poruszenia)
 * @return zwraca false jezeli kometa z czyms sie zdezyla i ma zostac zniszczona
 */
bool Symulation::krokSymulacji(double dt, kometa &k)
{
    for(vector<planeta>::iterator it = this->planety.begin(); it!=planety.end(); ++it){
        this->dvGrav(*it,k,dt);
    }
    // tu robimy set pozycja

    for(vector<planeta>::iterator it = this->planety.begin(); it!=planety.end(); ++it){
        if(this->HitTest(*it,k)) return false;
    }
    return true;
}
