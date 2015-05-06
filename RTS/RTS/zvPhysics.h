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
    float masa;
    float sprintFactor;
    float maxSpeed;
    float jumpForce;
    float surface;
    Vector position;
    Vector turnForce;//=Vector(0,0,0);
    Vector rotation;
    float peneDist;
    Vector move(float timeDif);
    Vector centerOfMass;
    float mass;
    float inertia;
    float staticFriction;
    float kineticFriction;
    float restitution;
    Vector linearVelocity;
    float orientation;
    float angularVelocity;
    Vector angularVelocityVector;

    Vector totalForce;
    float totalTorque;
    Vector totalTorqueVector;
    Vector frictionForce;
    Vector resistForce;
    float totalImpulse;

    PhysicObject();
    ~PhysicObject();
    PhysicObject(float _masa,float _x,float _y,float _z);
    Vector getRotation();
    Vector getPosition();
    void setRotation(Vector rot);
    virtual int collision(PhysicObject *ob);

    void simulate (float fStep);
    void applyLinearForce (Vector rkForce);
    void applyTorque (float fTorque);
    void applyTorque (Vector fTorque);
    void applyForce (Vector & rkForce, Vector & rkPointOfContact);
    void applyFriction (float fGravity);
    void applyResist ();
    void handleCollision (PhysicObject *rkOtherEntity, Vector  rkCollisionNormal);
    void setPosition (Vector  rkPosition);
    void setOrientation (float fOrientation);
    void setLinearVelocity (Vector rkLinearVelocity);
    void setAngularVelocity (float fAngularVelocity);
    void setMass (float fMass);
    void setCenterOfMass (Vector & rkCenterOfMass);
    void setInertia (float fInertia);
    void setStaticFriction (float fStaticFrictionCoefficient);
    void setKineticFriction (float fKineticFrictionCoefficient);
    void setCoefficientOfRestitution (float fCoefficientOfRestitution);
    void HandleCollision (PhysicObject  rkOtherEntity, Vector rkCollisionNormal);
    float getOrientation (void);
    Vector getLinearVelocity (void);
    float getAngularVelocity (void);
    float getMass (void);
    Vector getCenterOfMass (void);
    float getInertia (void);
    float getStaticFriction (void);
    float getKineticFriction (void);
    float getCoefficientOfRestitution (void);
};
class PhysicSphere :public PhysicObject{
    public:
    float radius;
    PhysicSphere();
    PhysicSphere(float _masa,float _x,float _y,float _z,float _radius);
    virtual int collision(PhysicObject *ob);
};
class PhysicBox :public PhysicObject{
public:
    float xLength;
    float yLength;
    float zLength;
    PhysicBox();
    PhysicBox(float _xLength,float _yLength,float _zLength);
};
class PhysicGround:public PhysicObject{
public:
    int nSize;
    float fizSize;
    std::vector<std::vector<float> > mapHeigth;
    PhysicGround(int n,int rozm);
    float getHeight(int x,int y);
    float getHeight(float x,float z);
};
class PhysicWorld{
public:
    float gravitation;
    float maxDokladnosc;//im mniej tym dokladniej
    std::vector<PhysicObject*> obiekty;
    PhysicWorld(float _gravitation,float _maxDokladnosc);
    PhysicWorld();
    void move(float timeDif);//ruch plus grawitacja
    int collision(float timeDif);
};
#endif
