#include "zvMath.h"

Vector::Vector(){x=y=z=0;}
Vector::Vector(float _x,float _y,float _z){
	x=_x;
	y=_y;
	z=_z;
}
float Vector::length(){
	return sqrt(x*x+y*y+z*z);
}

void Vector::normalize (void)
{
	float fLength;
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

float Vector::dotProduct (Vector  rkVector)
{
	return x * rkVector.x +y * rkVector.y+z * rkVector.z;
}

float Vector::angle (Vector & rkVector)
{
	return (float) acos (dotProduct (rkVector) /(length() * rkVector.length()));
}

float Vector::perpDotProduct (Vector & rkVector)
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
float Vector::horizLength (void){
	return sqrt(x*x+z*z);
}

//float * Vector::getVector (void)
//{
// return  this;
//}
