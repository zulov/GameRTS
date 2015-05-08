#pragma once
#include "zvObject.h"

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