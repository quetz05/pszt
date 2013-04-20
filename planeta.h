#ifndef PLANETA_H
#define PLANETA_H

#include vector.h


class Planeta
{
   Planeta();
   Planeta(Vector2 vec, double m);

   double masa;
   double promien;
   Vector2 srodek;


};



#endif // PLANETA_H
