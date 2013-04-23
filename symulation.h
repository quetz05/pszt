#ifndef SYMULATION_H
#define SYMULATION_H

#include "planeta.h"
#include "kometa.h"
#include "vector.h"
#include <vector>
#include <QThread>

#define FRAME_TIME 33.3333

class Symulation : public QObject
{

    Q_OBJECT

private:
    std::vector <Planeta*> planety;
    Kometa *gracz;
    QThread *watek;

public:
    Symulation();

    Vector2 dvGrav(Planeta *p, Kometa *k, double dt);
    bool HitTest(Planeta *p ,Kometa *k);
    bool krokSymulacji(double dt, Kometa *k);
    void dodajPlanete(Planeta *nowa);
    void dodajGracza(Kometa *nowy) { gracz = nowy; }
    void usunPlanety();
    void start();

public slots:

    void doWork();
};

#endif // SYMULATION_H
