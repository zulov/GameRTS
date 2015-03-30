// *** ADDED BY HEADER FIXUP ***
#include <iostream>
// *** END ***
// *** ADDED BY HEADER FIXUP ***
#include <iterator>
// *** END ***
#include "zvObject.h"
Object::Object(){
	actionAble=false;
	attackAble=false;
	alive=true;
	takeAble=false;
	name=std::string("");
}
Player::Player(){
	plecak =new Plecak();
	thirst=11;
	hunger=12;
	tired=10;//1-100
	illness=0;
	maxLoad=21000;//w gramach
	maxSprintTime=100;
	currentSprintTime=100;
}
Animal::Animal(){
}
bool Object::use(Object * usedObiekt){
	return 0;	
}
bool Player::use(Object * usedObiekt){
	if (usedObiekt->useAble==true){
		Console::writeTo("uzyto obiekt");
		Food* food = dynamic_cast<Food*>(usedObiekt);
		if (food!=0){
			this->hunger=this->hunger-(food->kCal/2500)*100;
			if (this->hunger<0){this->hunger=0;}
		}
	}
	return 0;
}
Thing::Thing(){
	takeAble=true;
	name=std::string("obiekt");
	endurace=10;//wytrzymalosc
	waga=100;//w gramach
}
std::string Object::getName(void){
	return name;
}
void Animal::move(float x,float z){
	//to mozliwe ze tylo raz trzeba
	float distance =1;// rand() % 30;
	float playerDistance=sqrt((x-this->bodyFiz->position.x)*(x-this->bodyFiz->position.x)+(z-this->bodyFiz->position.z)*(z-this->bodyFiz->position.z));
	float ratioDistance=distance/playerDistance;
}
void  Object::move(float x,float z){
}

void Player::printPlecak(void){
	std::cout<<"plecak----------"<<std::endl;
	for(int i=0;i<plecak->listaRzeczy.size();i++){

		plecak->listaRzeczy.at(i)->image;
		std::cout<<plecak->listaRzeczy.at(i)->getName()<<std::endl;
	}
	std::cout<<"plecak----------"<<std::endl;

}

void Player::update_stat(float fstep){
	if (this->maxSprintTime>this->currentSprintTime){this->currentSprintTime=this->currentSprintTime+((this->currentSprintTime+10)/this->maxSprintTime)*fstep*30/100;}
	if (this->maxSprintTime<=this->currentSprintTime){this->currentSprintTime=this->maxSprintTime;}
	if (this->hunger<100){this->hunger=this->hunger+fstep*30/1000;}
}

void Alive::attack(Object * attackObiekt){
	atak=1;
	HP=95;
	regeneration=1;
	strength=10;
	defense=20;
	agression=1;
	rAttack=30;
}

void Animal::attack(Object * attackObiekt){
}
bool Animal::actionColide(Object * actionObiekt){
	return 0;
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


void Animal::action(Object * actionObiekt){
}
void Alive::action(Object * actionObiekt){
}
void Object::action(Object * actionObiekt){
}
void Object::attack(Object * attackObiekt){
}
bool Object::actionColide(Object * actionObiekt){
	return 0;
}
bool Object::attackColide(Object * attackObiekt){
	return 0;
}
void Animal::applyDamage(float damage){
	this->HP=this->HP-(damage*(1-this->defense/100));
	if (this->HP<=0){this->alive=false;}
}
float Animal::getDamage(void){
	return 0.0f;
}
void Object::applyDamage(float damage){

}
float Object::getDamage(void){
	return 1;
}

void ListObject::update_position(){

	for(int i=0;i<listObiekt.size();i++){
		if (listObiekt.at(i)->bodyIrr!=0){
			listObiekt.at(i)->bodyIrr->setPosition(vector3df(listObiekt.at(i)->bodyFiz->position.x,listObiekt.at(i)->bodyFiz->position.y,listObiekt.at(i)->bodyFiz->position.z));
			listObiekt.at(i)->bodyIrr->setRotation(vector3df(listObiekt.at(i)->bodyFiz->rotation.x,listObiekt.at(i)->bodyFiz->rotation.y,listObiekt.at(i)->bodyFiz->rotation.z));
		}else if(listObiekt.at(i)->bodyIrrAnim!=0){
			listObiekt.at(i)->bodyIrrAnim->setPosition(vector3df(listObiekt.at(i)->bodyFiz->position.x,listObiekt.at(i)->bodyFiz->position.y,listObiekt.at(i)->bodyFiz->position.z));
			listObiekt.at(i)->bodyIrrAnim->setRotation(vector3df(listObiekt.at(i)->bodyFiz->rotation.x,listObiekt.at(i)->bodyFiz->rotation.y,listObiekt.at(i)->bodyFiz->rotation.z));
		}
		//if (i==0) { std::cout<<listObiekt.at(i)->bodyFiz->position.y<<std::endl;}
	}
}

void ListObject::actionColide(Object* doer){
	for(int i=0;i<listObiekt.size();i++){
		if(doer==listObiekt.at(i)){continue;}
		if(doer->actionColide(listObiekt.at(i))){
			doer->action(listObiekt.at(i));
		}
	}
}
void ListObject::attackColide(Object* attacer){
	for(int i=0;i<listObiekt.size();i++){
		if(attacer==listObiekt.at(i)){continue;}
		if(attacer->attackColide(listObiekt.at(i))){
			attacer->attack(listObiekt.at(i));
		}
	}
}
