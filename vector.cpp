#include "vector.h"

bool Vector2::operator ==( Vector2 const &vector)
{
    if( (this->x == vector.x) && (this->y == vector.y) )
          return true;
     else
          return false;
}
