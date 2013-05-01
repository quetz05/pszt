#ifndef REPLAY_H
#define REPLAY_H

#include <QObject>
#include <QRunnable>
#include "kometa.h"
#include "wiadomosc.h"

#define FRAME_TIME 33.3333

class Replay : public QObject, public QRunnable
{
    Q_OBJECT

public :
    Replay(Kometa *naCzym, QPainterPath *poCzym) : gracz(naCzym), sciezka(poCzym) {}

    void run();

signals:
    void nadajWiadomosc(Kometa* naCzym, Wiadomosc wiad);

private :
    Kometa *gracz;
    QPainterPath *sciezka;
};

#endif // REPLAY_H
