#ifndef ZVOBIEKTY_H
#define ZVOBIEKTY_H
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "zvGlobal.h"


class Object{
protected:
	std::string name;
	std::string description;

	int groupId;
	int id;
	bool alive;

	std::string meshPath;
	std::string texturePath;
	std::string iconPath;

	bool actionAble;
	bool attackAble;

	PhysicObject *physicBody;
	IMeshSceneNode *mesh;
	ITexture* image;


public:	
	virtual void  move(float x,float z);
	std::string getName(void);
	PhysicObject * getPhysicBody();
	void setPhysicBody(PhysicObject *_physicBody);
	IMeshSceneNode * getMesh();
	void setMesh(IMeshSceneNode *_mesh);
	bool getAlive();
	void setAlive(bool _alive);
	Object();
};
struct ObjectProperties{
public:
	std::string name;
	std::string opis;
	std::string type;
	std::string meshPath;
	std::string texturePath;
	std::string iconPath;
	int id;
	int groupID;
	bool alive;
	bool attackAble;
	bool actionAble;
	bool takeAble;
	float endurace;
	float kCal;
	float waga;
	float poison;
	float fresh;
	float atak;
	float HP;
	float regeneration;
	float strength;
	float defense;
	float rAttack;
	float agression;
	float xNest;
	float zNest;
	float rNest;
	float morale;
	float radius;
	float masa;
	float staticFriction;
	float kineticFriction;
	float coefficientOfRestitution;
	float surface;
	std::string collision;

};

class ListObject{
public:
	std::vector<Object*>listObiekt;
	void actionColide(Object* doer);
	void attackColide(Object* attacer);
	void update_position();
	std::vector<float*>activeVelues;
	std::vector<ObjectProperties*>loadedObject;
	ObjectProperties * getObjectById(int id);
	ObjectProperties * getObjectByName(std::string);
	void makeNewObject ();
};
class Alive:public Object{
private:
	float attackCoef;
	float health;
	float regeneration;
	float speed; 
	float armor;
	float radiusOfAttack;
	float radiusOfSight;
public:
	virtual void attack(Object * attackObiekt);
	Alive();
};
class Thing:public Object{
private:

public:
	float endurace;//wytrzymalosc
	Thing();
};


class Animal:public Alive{
private:
	float morale;
public:	
	virtual void attack(Object * attackObiekt);
	void move(float x,float z);
	int ai();
	Animal();
};



#endif
