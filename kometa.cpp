#include "kometa.h"
#include <QPainter>
#include <QDebug>
#include <QStringBuilder>

Kometa::Kometa(Vector2 sr, Vector2 k)
{
    masa = 1;
    srodek = sr;
    pozPocz = sr;
    promien = 5;
    kierunek = k;
    kierPocz = k;
    sciezka = new QPainterPath();
    sciezka->moveTo(sr.x, sr.y);
    interaktywne = false;
    rysujSciezke = false;
    czasZycia = 0;
    counter = 0;
    kolor = QColor::fromRgb(rand() % 255, rand() % 255, rand() % 255);
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
    if (!interaktywne || rysujSciezke) {
        ++counter;

        if (!(counter % 5))
            sciezka->lineTo(p.x, p.y);
    }

    if (interaktywne)
        this->setRect(boundingRect());
}

void Kometa::narysujSciezke()
{
    rysujSciezke = true;
}

void Kometa::dodajOstatni()
{
    sciezka->lineTo(srodek.x, srodek.y);
}

QString Kometa::pozycjaString() {
    return QString("x = ") % QString::number(pozPocz.x) % QString("<br>y = ") % QString::number(pozPocz.y);
}

QString Kometa::kierunekString() {
    return QString("x = ") % QString::number(kierPocz.x) % QString("<br>y = ") % QString::number(kierPocz.y);
}
