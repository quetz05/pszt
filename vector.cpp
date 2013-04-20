#include "vector.h"

bool Vector3::operator ==( Vector3 const &vector)
{
    if((this->x == vector.x) &&(this->y == vector.y))
          return true;
     else
          return false;
}
