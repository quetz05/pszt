#include "kometa.h"
#include <QPainter>

Kometa::Kometa(Vector2 sr, Vector2 k)
{
    masa = 1;
    srodek = sr;
    promien = 5;
}

void Kometa::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(QColor::fromRgb(0xcc, 0x67, 0x33)));
    painter->drawEllipse(QPointF(srodek.x, srodek.y), promien, promien);
}
