#ifndef ZVFIZYKA_H
#define ZVFIZYKA_H
#include <vector>
#include <cmath>
#include <iostream>
#include "zvMath.h"

class PhysicObject{
  public:
    int tag;
    bool colide;
    Vector grav;
    double masa;
    double sprintFactor;
    double maxSpeed;
    double jumpForce;
    double surface;
    Vector position;
    Vector turnForce;//=Vector(0,0,0);
    Vector rotation;
    double peneDist;
    Vector move(double timeDif);
    Vector centerOfMass;
    double mass;
    double inertia;
    double staticFriction;
    double kineticFriction;
    double restitution;
    Vector linearVelocity;
    double orientation;
    double angularVelocity;
    Vector angularVelocityVector;

    Vector totalForce;
    double totalTorque;
    Vector totalTorqueVector;
    Vector frictionForce;
    Vector resistForce;
    double totalImpulse;

    PhysicObject();
    ~PhysicObject();
    PhysicObject(double _masa,double _x,double _y,double _z);
    Vector getRotation();
    Vector getPosition();
    void setRotation(Vector rot);
    virtual int collision(PhysicObject *ob);

    void simulate (double fStep);
    void applyLinearForce (Vector rkForce);
    void applyTorque (double fTorque);
    void applyTorque (Vector fTorque);
    void applyForce (Vector & rkForce, Vector & rkPointOfContact);
    void applyFriction (double fGravity);
    void applyResist ();
    void handleCollision (PhysicObject *rkOtherEntity, Vector  rkCollisionNormal);
    void setPosition (Vector  rkPosition);
    void setOrientation (double fOrientation);
    void setLinearVelocity (Vector rkLinearVelocity);
    void setAngularVelocity (double fAngularVelocity);
    void setMass (double fMass);
    void setCenterOfMass (Vector & rkCenterOfMass);
    void setInertia (double fInertia);
    void setStaticFriction (double fStaticFrictionCoefficient);
    void setKineticFriction (double fKineticFrictionCoefficient);
    void setCoefficientOfRestitution (double fCoefficientOfRestitution);
    void HandleCollision (PhysicObject  rkOtherEntity, Vector rkCollisionNormal);
    double getOrientation (void);
    Vector getLinearVelocity (void);
    double getAngularVelocity (void);
    double getMass (void);
    Vector getCenterOfMass (void);
    double getInertia (void);
    double getStaticFriction (void);
    double getKineticFriction (void);
    double getCoefficientOfRestitution (void);
};
class PhysicSphere :public PhysicObject{
    public:
    double radius;
    PhysicSphere();
    PhysicSphere(double _masa,double _x,double _y,double _z,double _radius);
    virtual int collision(PhysicObject *ob);
};
class PhysicBox :public PhysicObject{
public:
    double xLength;
    double yLength;
    double zLength;
    PhysicBox();
    PhysicBox(double _xLength,double _yLength,double _zLength);
};
class PhysicGround:public PhysicObject{
public:
    int nSize;
    double fizSize;
    std::vector<std::vector<double> > mapHeigth;
    PhysicGround(int n,int rozm);
    double getHeight(int x,int y);
    double getHeight(double x,double z);
};
class PhysicWorld{
public:
    double gravitation;
    double maxDokladnosc;//im mniej tym dokladniej
    std::vector<PhysicObject*> obiekty;
    PhysicWorld(double _gravitation,double _maxDokladnosc);
    PhysicWorld();
    void move(double timeDif);//ruch plus grawitacja
    int collision(double timeDif);
};
#endif
