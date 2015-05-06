#include <iostream>

#include <iterator>
#include "zvObject.h"

Object::Object(){
	actionAble=false;
	attackAble=false;
	alive=true;
	name=std::string("");
}

Animal::Animal(){
}

Alive::Alive(){
}


Thing::Thing(){

	name=std::string("obiekt");
	endurace=10;//wytrzymalosc

}
std::string Object::getName(void){
	return name;
}
void Animal::move(float x,float z){
	//to mozliwe ze tylo raz trzeba
	float distance =1;// rand() % 30;
	float playerDistance=sqrt((x-this->getPhysicBody()->position.x)*(x-this->getPhysicBody()->position.x)+(z-this->getPhysicBody()->position.z)*(z-this->getPhysicBody()->position.z));
	float ratioDistance=distance/playerDistance;
}
void  Object::move(float x,float z){
}

void Alive::attack(Object * attackObiekt){

}

void Animal::attack(Object * attackObiekt){
}

ObjectProperties * ListObject::getObjectById(int id){
	for(int i=0;i<loadedObject.size();i++){
		if(loadedObject.at(i)->id==id){return loadedObject.at(i);}
	}
	return 0;
}
ObjectProperties * ListObject::getObjectByName(std::string name){
	for(int i=0;i<loadedObject.size();i++){
		if(loadedObject.at(i)->name==name){return loadedObject.at(i);}
	}
	return 0;
}

void ListObject::update_position(){
	for(int i=0;i<listObiekt.size();i++){
		if (listObiekt.at(i)->getMesh()!=0){
			listObiekt.at(i)->getMesh()->setPosition(vector3df(listObiekt.at(i)->getPhysicBody()->position.x,listObiekt.at(i)->getPhysicBody()->position.y,listObiekt.at(i)->getPhysicBody()->position.z));
			listObiekt.at(i)->getMesh()->setRotation(vector3df(listObiekt.at(i)->getPhysicBody()->rotation.x,listObiekt.at(i)->getPhysicBody()->rotation.y,listObiekt.at(i)->getPhysicBody()->rotation.z));
		}
	}
}

PhysicObject * Object::getPhysicBody(){
	return physicBody;
}
void Object::setPhysicBody(PhysicObject *_physicBody){
	physicBody=_physicBody;
}
IMeshSceneNode * Object::getMesh(){
	return mesh;
}
void Object::setMesh(IMeshSceneNode *_mesh){
	 mesh=_mesh;
}
bool Object::getAlive(){
	return alive;
}
void Object::setAlive(bool _alive){
	alive=_alive;	
}
