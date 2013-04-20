#ifndef PLANETA_H
#define PLANETA_H

#include "vector.h"

class Planeta
{

public:
   Planeta();
   Planeta(Vector2 vec, double m);
   const double zwrocPromien(){return promien;}
   const Vector2 zwrocSrodek(){return srodek;}
   const double zwrocMase(){return masa;}


protected:
   //wartosc pola masa jest w istocie liczbą, która po przemnożeniu przez 10^24 daje faktyczną masę planety
   double masa;
   double promien;
   Vector2 srodek;


};
#endif
