#include "planeta.h"
#include <QPainter>

Planeta::Planeta()
{
    srodek.x = 0;
    srodek.y = 0;
    masa = 1;
    promien = 5 + 2*masa;
    setToolTip(QString("Masa planety = ").append(QString::number(masa)).append(" x 10 <sup>24</sup> kg"));
}


Planeta::Planeta(Vector2 vec, double m)
{
    srodek.x = vec.x;
    srodek.y = vec.y;
    masa = m;
    promien = 5 + 0.5*masa;

    setToolTip(QString("Masa planety = ").append(QString::number(masa)).append(" x 10 <sup>24</sup> kg"));
}

void Planeta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(QColor::fromRgb(0x33, 0x66, 0xff)));
    painter->drawEllipse(QPointF(srodek.x, srodek.y), promien, promien);
}

QRectF Planeta::boundingRect() const
{
    return QRectF(srodek.x - promien, srodek.y - promien, promien * 2, promien * 2);
}
