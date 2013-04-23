#include <QtCore>

#ifndef WIADOMOSC_H
#define WIADOMOSC_H

typedef enum
{
    predkosc, polozenie, delta, rusz, fps
} TYP_WIADOMOSCI;

typedef struct Wiadomosc
{
    Wiadomosc(qreal nX, qreal nY, TYP_WIADOMOSCI nTyp):
        x(nX), y(nY), typ(nTyp) {}

    qreal x, y;
    TYP_WIADOMOSCI typ;

} Wiadomosc;

#endif // WIADOMOSC_H
