#ifndef PLANETA_H
#define PLANETA_H

#include "vector.h"
#include <QGraphicsItem>

class Planeta : public QGraphicsItem
{

public:
   Planeta();
   Planeta(Vector2 vec, double m);
   const double zwrocPromien(){return promien;}
   Vector2 zwrocSrodek(){return srodek;}
   const double zwrocMase(){return masa;}

   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   QRectF boundingRect() const;


protected:
   //wartosc pola masa jest w istocie liczbą, która po przemnożeniu przez 10^24 daje faktyczną masę planety
   double masa;
   double promien;
   Vector2 srodek;


};
#endif
