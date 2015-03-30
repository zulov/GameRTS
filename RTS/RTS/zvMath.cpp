#include "zvMath.h"
Vector::Vector(){x=y=z=0;}
Vector::Vector(double _x,double _y,double _z){
	x=_x;
	y=_y;
	z=_z;
}
double Vector::length(){
	return sqrt(x*x+y*y+z*z);
}

void Vector::normalize (void)
{
	double fLength;
	fLength = length ();

	if (0 != fLength)
	{
		x/= fLength;
		y/= fLength;
		z/= fLength;
	}
}

Vector Vector::perpendicular (void)
{
	Vector vTemp;
	if(this->z!=-1){
		vTemp=Vector(0,0,1);
	}
	else{
		vTemp=Vector(0,1,0);
	}

	return Vector (y, -x,z);///tu zrobic cos sensownego
}

double Vector::dotProduct (Vector  rkVector)
{
	return x * rkVector.x +y * rkVector.y+z * rkVector.z;
}

double Vector::angle (Vector & rkVector)
{
	return (double) acos (dotProduct (rkVector) /(length() * rkVector.length()));
}

double Vector::perpDotProduct (Vector & rkVector)
{
	return perpendicular ().dotProduct (rkVector);
}

void Vector::reset (void)
{
	x=0;
	y=0;
	z=0;
}

void Vector::setVector (Vector & rkVector)
{
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;

}
double Vector::horizLength (void){
	return sqrt(x*x+z*z);
}

//double * Vector::getVector (void)
//{
// return  this;
//}
