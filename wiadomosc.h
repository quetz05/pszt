#include <QtCore>

#ifndef WIADOMOSC_H
#define WIADOMOSC_H

typedef enum
{
    rusz, zakonczyl, sekwencja, krzyzuj, mutuj, tworz, ocena
} TYP_WIADOMOSCI;

typedef struct ProstaWiadomosc {

    ProstaWiadomosc() {}
    ProstaWiadomosc(TYP_WIADOMOSCI nTyp) : typ(nTyp) {}

    TYP_WIADOMOSCI typ;

} ProstaWiadomosc;

typedef struct Wiadomosc
{
    Wiadomosc() {}
    Wiadomosc(qreal nX, qreal nY, TYP_WIADOMOSCI nTyp):
        x(nX), y(nY), typ(nTyp) {}

    qreal x, y;
    TYP_WIADOMOSCI typ;

} Wiadomosc;

#endif // WIADOMOSC_H
