#ifndef ZVMATH_H
#define ZVMATH_H
#include <cmath>
class Vector{
  public:
    float x;
    float y;
    float z;
    //funkcja wez wartosc z trzech
float length();
Vector();
Vector(float _x,float _y,float _z);
Vector operator+ ( Vector v )
{
    return Vector( this->x + v.x, this->y + v.y, this->z + v.z );
}
Vector operator* ( Vector v )
{
    return Vector( this->x * v.x, this->y * v.y, this->z * v.z );
}
Vector operator- ( Vector v )
{
    return Vector( this->x - v.x, this->y - v.y, this->z - v.z );
}
Vector operator* ( const float &A )
{
     Vector ret;
    ret.x = this->x * A;
    ret.y = this->y * A;
    ret.z = this->z * A;

    return ret;
}
Vector operator - (void)
{
	return Vector (-x, -y,-z);
}
Vector & operator += (Vector  rkVector)
{
 x += rkVector.x;
 y += rkVector.y;
 z += rkVector.z;
 return *this;
}
Vector & operator -= (Vector  rkVector)
{
 x -= rkVector.x;
 y -= rkVector.y;
 z -= rkVector.z;
 return *this;
}
Vector operator / (float iDivider)
{
	return Vector (x / iDivider,y/ iDivider,z/iDivider);
}
    float Length (void);
    float horizLength (void);
	void normalize (void);
	Vector perpendicular (void);
	float dotProduct (Vector  rkVector);
	float angle (Vector & rkVector);
	float perpDotProduct (Vector & rkVector);
	void reset (void);
	void setVector (Vector & rkVector);
	float * getVector (void);
};
#endif
