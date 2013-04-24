#ifndef SYMULATION_H
#define SYMULATION_H

#include "planeta.h"
#include "kometa.h"
#include "vector.h"
#include <vector>
#include <QThread>
#include "wiadomosc.h"

#define FRAME_TIME 33.3333

class Symulation : public QObject
{

    Q_OBJECT

private:
    std::vector <Planeta*> planety;
    Kometa *gracz;
    QThread *watek;
    bool interaktywne;
    int ident;

public:
    Symulation(int id);

    Vector2 dvGrav(Planeta *p, Kometa *k, double dt);
    bool HitTest(Planeta *p ,Kometa *k);
    bool krokSymulacji(double dt, Kometa *k);
    void dodajPlanete(Planeta *nowa);
    void dodajGracza(Kometa *nowy) { gracz = nowy; }
    void usunPlanety();
    void start();

    void ustawInteraktywne(bool enable) { interaktywne = enable; }

signals:
    void powiadom(Kometa *naCzym, Wiadomosc wiad);

public slots:

    void doWork();
};

#endif // SYMULATION_H
