#ifndef KOMETA_H
#define KOMETA_H

#include "planeta.h"
#include <QPainterPath>

class Kometa : public Planeta
{
/*This is not the best Kometa in the world. This is just a tribute!*/

public:
    Kometa(){}
    Kometa(Vector2 sr, Vector2 k);
    Vector2 zwrocKierunek(){ return kierunek; }
    void ustawPozycje(Vector2 p);
    void ustawKierunek(Vector2 k){ kierunek = k; }
    void narysujSciezke();
    void ustawInteraktywne(bool enabled) { interaktywne = enabled; }
    void ustawKolor(QColor k) { kolor = k; }
    void dodajOstatni();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Vector2 pozPocz;
    Vector2 kierunek;
    QPainterPath *sciezka;
    QColor kolor;
    bool interaktywne;
    bool rysujSciezke;
    int counter;
};
#endif // KOMETA_H
