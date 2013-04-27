#include "kometa.h"
#include <QPainter>

Kometa::Kometa(Vector2 sr, Vector2 k)
{
    masa = 1;
    srodek = sr;
    pozPocz = sr;
    promien = 5;
    kierunek = k;
    sciezka = new QPainterPath();
    sciezka->moveTo(sr.x, sr.y);
    interaktywne = true;
    rysujSciezke = false;
    kolor = QColor::fromRgb(0xcc, 0x67, 0x33);
    this->setRect(boundingRect());
}

void Kometa::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (rysujSciezke) {
        painter->setPen(QPen(kolor));
        painter->drawPath(*sciezka);
    }

    painter->setBrush(QBrush(kolor));
    if (interaktywne) {
        painter->drawEllipse(QPointF(srodek.x, srodek.y), promien, promien);
    } else {
        painter->drawEllipse(QPointF(pozPocz.x, pozPocz.y), promien, promien);
    }


}

void Kometa::ustawPozycje(Vector2 p) {
    srodek = p;
    if (!interaktywne)
        sciezka->lineTo(p.x, p.y);
    this->setRect(boundingRect());
}

void Kometa::narysujSciezke()
{
    rysujSciezke = true;
}
