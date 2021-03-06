#ifndef VECTOR_H
#define VECTOR_H

#include <qmath.h>

/** @brief Vector2 struktura wektora dwuwymiarowego*/
struct Vector2{

    /** @brief Vector2 kontruktor tworzący wektor o współrzędnych [a,b]*/
    inline Vector2(double a, double b){x=a;y=b;}
    /** @brief Vector2 kontruktor bezargumentowy (tworzy wektor [0,0])*/
    inline Vector2(): x(0),y(0){}
    /** @brief operator* przeciążenie operatora mnożenia wektora dwywymiarowego przez wartość*/
    Vector2 operator*(double val){return Vector2(x*val,y*val);}
    /** @brief operator/ przeciążenie operatora dzielenia wektora dwywymiarowego przez wartość*/
    Vector2 operator/(double val){return Vector2(x/val,y/val);}
    /** @brief operator+ przeciążenie operatora dodawania wartości do wektora dwywymiarowego*/
    Vector2 operator+(double val){return Vector2(x+val,y+val);}
    /** @brief operator- przeciążenie operatora odejmowania wartości od współrzęcnych wektora dwywymiarowego*/
    Vector2 operator-(double val){return Vector2(x-val,y-val);}
    /** @brief operator+ przeciążenie operatora dodawania wektora dwywymiarowego do drugiego wektora*/
    Vector2 operator+(Vector2 vec) {return Vector2(x+vec.x, y+vec.y);}
    /** @brief operator- przeciążenie operatora odejmowania wektora dwywymiarowego od drugiego wektora*/
    Vector2 operator-(Vector2 vec) {return Vector2(x-vec.x, y-vec.y);}

    double dlugosc(){ return qSqrt( (x*x) + (y*y) );}

    Vector2& operator=(Vector2 const &vector){x = vector.x; y = vector.y; return *this;}

    bool operator==( Vector2 const &vector);

    /** @brief x współrzędna x wektora dwuwymiarowego*/
    double x;
    /** @brief y współrzędna y wektora dwuwymiarowego*/
    double y;
};

#endif // VECTOR_H
