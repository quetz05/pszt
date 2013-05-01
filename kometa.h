#ifndef KOMETA_H
#define KOMETA_H

#include <vector>
#include "planeta.h"
#include <QPainterPath>


class Kometa : public Planeta
{
/*This is not the best Kometa in the world. This is just a tribute!*/

public:
    Kometa(){}
    Kometa(Vector2 sr, Vector2 k);
    ~Kometa() { delete sciezka; }


    Vector2 zwrocKierunek(){ return kierunek; }
    Vector2 zwrocPozycjePocz(){ return pozPocz; }
    Vector2 zwrocKierunekPocz() { return kierPocz; }
    QColor zwrocKolor() {return kolor; }
    QPainterPath* zwrocSciezke() { return sciezka; }
    void ustawPozycje(Vector2 p);
    void ustawKierunek(Vector2 k){ kierunek = k; }
    void narysujSciezke();
    void ustawInteraktywne(bool enabled) { interaktywne = enabled; }
    void ustawUsuwanie(bool enabled) { delMode = enabled; }
    void ustawKolor(QColor k) { kolor = k; }
    void dodajOstatni();

    QString pozycjaString();
    QString kierunekString();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    std::vector <double> rozklady;
    double czasZycia;


private:
    Vector2 pozPocz;
    Vector2 kierPocz;
    Vector2 kierunek;
    QPainterPath *sciezka;
    QColor kolor;
    bool interaktywne;
    bool rysujSciezke;
    bool delMode;
    int counter;

};
#endif // KOMETA_H
