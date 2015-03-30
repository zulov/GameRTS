#ifndef ZVMATH_H
#define ZVMATH_H
#include <cmath>
class Vector{
  public:
    double x;
    double y;
    double z;
    //funkcja wez wartosc z trzech
double length();
Vector();
Vector(double _x,double _y,double _z);
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
Vector operator* ( const double &A )
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
Vector operator / (double iDivider)
{
	return Vector (x / iDivider,y/ iDivider,z/iDivider);
}
    double Length (void);
    double horizLength (void);
	void normalize (void);
	Vector perpendicular (void);
	double dotProduct (Vector  rkVector);
	double angle (Vector & rkVector);
	double perpDotProduct (Vector & rkVector);
	void reset (void);
	void setVector (Vector & rkVector);
	double * getVector (void);
};
#endif
