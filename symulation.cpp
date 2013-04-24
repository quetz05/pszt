#include "symulation.h"
#include "planeta.h"
#include "kometa.h"
#include "math.h"
#include <QTime>
#include <QDebug>

#define G 6.67384

using namespace std;


Symulation::Symulation()
{
    watek = new QThread();
    connect(watek, SIGNAL(started()), this, SLOT(doWork()));
    moveToThread(watek);

}
/**
 * @brief Symulation::dvGrav
 * @param p planeta ktora wytwaza pole grawitacyjne
 * @param k kometa ktora jest w tym polu
 * @param dt delta time
 * @return
 */
Vector2 Symulation::dvGrav(Planeta *p, Kometa *k, double dt)
{
    // a = (gm1/r2)*r->/r
    // a = dv/dt
    // dv = a*dt
    Vector2 posPlaneta= p->zwrocSrodek();
    double mPlaneta = p->zwrocMase();
    Vector2 posKometa = k->zwrocSrodek();
    Vector2 r = posPlaneta - posKometa;
    double rd = r.dlugosc();
    Vector2 dv = (r/rd) * (G*mPlaneta/(rd*rd));
    dv = dv*dt;
    return dv;
}


/**
 * @brief Symulation::HitTest
 * @param planet planeta z ktora mozna sie zdezyc
 * @param player kometa ktora sterujemy
 * @return true jezeli nastepuje zdezenie
 */
bool Symulation::HitTest(Planeta *planet, Kometa *player)
{
    Vector2 pp = planet->zwrocSrodek();
    Vector2 pk = player->zwrocSrodek();
    double rd = (pp-pk).dlugosc();
    rd = fabs(rd);
    if (rd < (planet->zwrocPromien() + player->zwrocPromien())){
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
bool Symulation::krokSymulacji(double dt, Kometa *k)
{
    Vector2 dv(0,0);

    int i = 0;

    for(vector<Planeta*>::iterator it = this->planety.begin(); it != planety.end(); ++it){
        qDebug() << i++;
        dv = dv + this->dvGrav(*it, k, dt);
    }

    // tu robimy set pozycja
    k->ustawKierunek(k->zwrocKierunek() + dv);


    for(vector<Planeta*>::iterator it = this->planety.begin(); it!=planety.end(); ++it){
        if(this->HitTest(*it,k)) return false;
    }

    if(k->zwrocSrodek().x-k->zwrocPromien() <= 0 || k->zwrocSrodek().x+k->zwrocPromien() >= 800)
        k->ustawKierunek( Vector2( k->zwrocKierunek().x * (-1), k->zwrocKierunek().y) );

    if(k->zwrocSrodek().y- k->zwrocPromien() <= 0 || k->zwrocSrodek().y +k->zwrocPromien() >= 600)
        k->ustawKierunek( Vector2( k->zwrocKierunek().x, k->zwrocKierunek().y * (-1) ) );


    //pozycje ustawiamy na koncu jak wiemy juz gdzie ma leciec czy nie
    Vector2 nowaPozycja = k->zwrocKierunek() * dt + k->zwrocSrodek();
    emit powiadom(k, Wiadomosc(nowaPozycja.x, nowaPozycja.y, rusz));
    //k->ustawPozycje(k->zwrocKierunek() * dt + k->zwrocSrodek());

    return true;
}

void Symulation::dodajPlanete(Planeta *nowa)
{
    planety.push_back(nowa);
}

void Symulation::usunPlanety()
{
    planety.clear();
}

void Symulation::start()
{
    watek->start();
}

void Symulation::doWork()
{
    QTime zegar;
    zegar.start();
    int last_time = zegar.elapsed(), current_time = 0;
    double diff = 1;

    while (1) {
        last_time = zegar.elapsed();
        if (!krokSymulacji(/*qMax(diff, 1.0)*/1, gracz))
            break;
        current_time = zegar.elapsed();
        diff = current_time - last_time ;
        qDebug() << "roznica == " << diff;
        qDebug() << gracz->zwrocSrodek().x << " :: " << gracz->zwrocSrodek().y;
        watek->msleep(qMax(FRAME_TIME - (current_time - last_time), 0.0));
    }
}
