#ifndef ZVOBIEKTY_H
#define ZVOBIEKTY_H
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "zvGlobal.h"


class Object{
private:
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

	PhysicObject *bodyFiz;
	irr::scene::IMeshSceneNode *bodyIrr;
	irr::scene::IAnimatedMeshSceneNode *bodyIrrAnim;
	irr::video::ITexture* image;
	std::string getName(void);

public:	
	virtual void  move(float x,float z);
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
	float attack;
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

class Unit: public Alive{
private:

public:	
	Unit();
};


class Worker: public Unit{
private:

public:	
	Worker();
};

class Solider: public Unit{
private:
	float experience;
public:	
	Solider();
};

class Cavalry: public Solider{
private:
	
public:	
	Cavalry();
};

class Infantry: public Solider{
private:
	
public:	
	Infantry();
};


class Artillery: public Solider{
private:
	
public:	
	Artillery();
};

class Artillery: public Solider{
private:
	
public:	
	Artillery();
};

#endif
