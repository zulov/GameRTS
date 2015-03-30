// *** ADDED BY HEADER FIXUP ***
#include <iterator>
// *** END ***
#include "zvPhysics.h"


PhysicObject::PhysicObject(double _masa,double _x,double _y,double _z){
	masa=_masa;
	mass=_masa;
	position=Vector(_x,_y,_z);
	grav=Vector(0,-9.78,0);
	peneDist=0;
	inertia                    = 0.1;
	staticFriction  = 0;
	kineticFriction = 0;
	surface =1;
	angularVelocity            = 0;
	orientation                = 0;
	totalTorque                = 0;
	totalTorqueVector          = Vector(0,0,0);
	totalImpulse               = 0;
	centerOfMass               = Vector (0, 0,0);
	position                   = Vector (0, 0,0);
	linearVelocity             = Vector (0, 0,0);
	totalForce                 = Vector (0, 0,0);
	frictionForce              = Vector (0, 0,0);
	sprintFactor=1.66;
}
PhysicSphere::PhysicSphere(double _masa,double _x,double _y,double _z,double _radius):PhysicObject(_masa,_x,_y,_z){
	radius=_radius;
}
PhysicSphere::PhysicSphere(void){

}
int PhysicObject::collision(PhysicObject *ob){
	//std::cout<<"kolzja virtualna prawie ze"<<std::endl;
	return false;
}

Vector PhysicObject::getRotation(){
	return this->rotation;
}
Vector PhysicObject::getPosition(){
	return this->position;
}

void PhysicObject::setRotation(Vector rot){
	rotation=rot;
}

Vector PhysicObject::move(double timeDif){
	if(this->masa!=0){
		// this->prevPosition=this->position;
		//    Vector accelStep=this->acceleration*(timeDif*this->masa);
		//    Vector gravStep=this->grav*(timeDif*this->masa);
		//    accelStep=accelStep+gravStep;
		//    Vector tempVel=this->velocity+accelStep;
		//    Vector tempVelMovement=tempVel+this->movement;
		//    Vector moveStep=tempVelMovement*timeDif;
		//    this->position=this->position+moveStep;
		//return tempPosition;
	}
	return this->position;
}

int PhysicSphere::collision(PhysicObject *ob){

	PhysicSphere* obSphere = dynamic_cast<PhysicSphere*>(ob);

	if(obSphere!=0){
		double suma=this->radius+obSphere->radius;
		double xDif=(this->position.x-obSphere->position.x);
		double yDif=(this->position.y-obSphere->position.y);
		double zDif=(this->position.z-obSphere->position.z);
		suma=suma*suma;
		double distance=xDif*xDif+zDif*zDif+yDif*yDif;
		if (distance>=suma){return 0;}
		else {
			double sqrtV=sqrt(distance);
			this->peneDist=(this->radius+obSphere->radius)-sqrtV;
			this->peneDist=this->peneDist/(this->getMass()+obSphere->getMass())*obSphere->getMass();
			obSphere->peneDist=(this->radius+obSphere->radius)-sqrtV;
			obSphere->peneDist=obSphere->peneDist/(this->getMass()+obSphere->getMass())*this->getMass();
			return 1;}//kolizja
	}

	PhysicGround* obGround = dynamic_cast<PhysicGround*>(ob);//tu poprawic ify
	if(obGround!=0) {//zrobic tak zeby dzilac na trojkatach a nie na kwadratach zobaczyc czy to cos da
		//  if(this->mass==0){return 0;}
		double x_pos=this->position.x/obGround->fizSize+0.5;
		double z_pos=this->position.z/obGround->fizSize+0.5;
		double height;

		//  x_pos+=obGround->fizSize/2;//tu jedno dzielenie jesli bedzie kwadrat
		//  z_pos+=obGround->fizSize/2;
		//  x_pos/=obGround->fizSize;
		x_pos*=obGround->nSize-1;
		//  z_pos/=obGround->fizSize;
		z_pos*=obGround->nSize-1;

		//   std::cout<<x_pos<< "xxx"<<z_pos<<std::endl;
		double x_pos_b=x_pos-((int)x_pos);
		double x_pos_a=1-x_pos_b;
		double z_pos_b=z_pos-((int)z_pos);
		double z_pos_a=1-z_pos_b;

		height= obGround->getHeight((int)x_pos,(int)z_pos)*x_pos_a*z_pos_a + obGround->getHeight((int)x_pos+1,(int)z_pos)*x_pos_b*z_pos_a +
			obGround->getHeight((int)x_pos,(int)z_pos+1)*x_pos_a*z_pos_b+ obGround->getHeight((int)x_pos+1,(int)z_pos+1)*x_pos_b*z_pos_b;

		if (this->position.y<height+obGround->position.y+this->radius){
			this->position.y= height+obGround->position.y+this->radius;
			return 2;
		}
		else{return 0;}
	}

	PhysicBox* obBox = dynamic_cast<PhysicBox*>(ob);
	if(obBox!=0) {
		//double suma=this->radius;
	}
	return 0;
}

PhysicWorld::PhysicWorld(double _gravitation,double _maxDokladnosc){
	maxDokladnosc=_maxDokladnosc;
	gravitation=_gravitation;
}
PhysicWorld::PhysicWorld(){
	maxDokladnosc=1;
	gravitation=9.78;
}

void PhysicWorld::move(double timeDif){
	for(int i=0;i<obiekty.size();i++){
		//       obiekty[i]->prevPosition=obiekty[i]->position;
		obiekty[i]->applyLinearForce(obiekty[i]->grav*obiekty[i]->getMass());
		obiekty[i]->simulate(timeDif);
	}
}

PhysicGround::PhysicGround(int n,int rozm):PhysicObject(0,0,0,0){
	for(int i=0;i<n;i++){
		mapHeigth.push_back(std::vector<double>(n, 0));
		nSize=n;
		fizSize=rozm;
	}
}

double PhysicGround::getHeight(double x,double z){
	double x_pos=x/fizSize+0.5;
	double z_pos=z/fizSize+0.5;
	double height;

	//x_pos+=this->fizSize/2;//tu jedno dzielenie jesli bedzie kwadrat
	//  z_pos+=this->fizSize/2;
	//  x_pos/=this->fizSize;
	x_pos*=this->nSize-1;
	// z_pos/=this->fizSize;
	z_pos*=this->nSize-1;
	//   std::cout<<x_pos<< "xxx"<<z_pos<<std::endl;
	double x_pos_b=x_pos-((int)x_pos);
	double x_pos_a=1-x_pos_b;
	double z_pos_b=z_pos-((int)z_pos);
	double z_pos_a=1-z_pos_b;

	height= this->getHeight((int)x_pos,(int)z_pos)*x_pos_a*z_pos_a + this->getHeight((int)x_pos+1,(int)z_pos)*x_pos_b*z_pos_a +
		this->getHeight((int)x_pos,(int)z_pos+1)*x_pos_a*z_pos_b+ this->getHeight((int)x_pos+1,(int)z_pos+1)*x_pos_b*z_pos_b;
	return height;
}

double PhysicGround::getHeight(int x,int y){
	if((x<0)||(y<0)||(x>=mapHeigth.size())||(y>=mapHeigth.at(0).size())){return 0;}
	return mapHeigth.at(x).at(y);
}

int PhysicWorld::collision(double timeDif){//kolizje liczyc tylko dla obiektów poruszajacych sie z reszta obiektów
	int typeCollision;
	Vector vecTemp;
	for(int i=0;i<obiekty.size()-1;i++){
		for (int j=i+1;j<obiekty.size();j++){
			obiekty[i]->peneDist=0;
			obiekty[j]->peneDist=0;
			if(obiekty[i]->mass==0 &&obiekty[j]->mass==0){continue;}
			typeCollision=obiekty[i]->collision(obiekty[j]);
			if (typeCollision>0){

				if (typeCollision!=2){
					///
					vecTemp=obiekty[i]->position-obiekty[j]->position;
					vecTemp.normalize();
					//vecTemp=vecTemp*obiekty[i]->peneDist;
					obiekty[i]->position+=vecTemp*obiekty[i]->peneDist;

					// vecTemp=obiekty[j]->position-obiekty[i]->position;
					//  vecTemp.normalize();
					// vecTemp=vecTemp*obiekty[j]->peneDist;
					obiekty[j]->position+=-vecTemp*obiekty[j]->peneDist;
					///
					obiekty[i]->handleCollision(obiekty[j],(obiekty[i]->getPosition()-obiekty[j]->getPosition()));

					//            vecTemp=obiekty[i]->linearVelocity;
					//            vecTemp.normalize();
					//            vecTemp=vecTemp*obiekty[i]->peneDist;
					//            obiekty[i]->position+=vecTemp;
					//
					//            vecTemp=obiekty[j]->linearVelocity;
					//            vecTemp.normalize();
					//            vecTemp=vecTemp*obiekty[j]->peneDist;
					//            obiekty[j]->position+=vecTemp;

				}else{
					obiekty[i]->handleCollision(obiekty[j],Vector(0,0.1,0));//dokladnieszja normalna dac
				}
			}
		}
	}
	return 0;
}


/* Konstruktor domyślny */
PhysicObject::PhysicObject (void)
{
	grav=Vector(0,-9.78,0);
	peneDist=0;
	mass                       = 0;
	inertia                    = 0.1;
	staticFriction  = 0;
	kineticFriction = 0;
	surface =1;
	angularVelocity            = 0;
	orientation                = 0;
	totalTorque                = 0;
	totalTorqueVector          = Vector(0,0,0);
	totalImpulse               = 0;
	centerOfMass               = Vector (0, 0,0);
	position                   = Vector (0, 0,0);
	linearVelocity             = Vector (0, 0,0);
	totalForce                 = Vector (0, 0,0);
	frictionForce              = Vector (0, 0,0);
}

/* Destruktor */
PhysicObject::~PhysicObject (void)
{
	mass                       = 0;
	inertia                    = 0.1;
	staticFriction  = 0;
	kineticFriction = 0;
	angularVelocity            = 0;
	orientation                = 0;
	totalTorque                = 0;
	totalImpulse               = 0;
	centerOfMass               = Vector (0, 0,0);
	position                   = Vector (0, 0,0);
	linearVelocity             = Vector (0, 0,0);
	totalForce                 = Vector (0, 0,0);
	frictionForce              = Vector (0, 0,0);
}

/* Przykładamy do obiektu siłę liniową */
void PhysicObject::applyLinearForce (Vector  rkForce)
{
	totalForce =totalForce+ rkForce;
}

/* Przykładamy do obiektu moment */
void PhysicObject::applyTorque (double fTorque)
{
	totalTorque =totalTorque+ fTorque;
}

/* Przykładamy do obiektu moment */
void PhysicObject::applyTorque (Vector fTorque)
{
	totalTorqueVector =totalTorqueVector+ fTorque;
}
/* Przykładamy do obiektu siłę */
void PhysicObject::applyForce (Vector & rkForce,Vector & rkPointOfContact)
{
	if (mass!=0){
		totalForce = totalForce+ rkForce;
		Vector rkArm;
		/* Obliczamy długość ramienia */
		rkArm = rkPointOfContact - centerOfMass;
		//totalTorque = totalTorque+rkArm.perpDotProduct (rkForce);
		totalTorque = totalTorque+rkArm.perpDotProduct (rkForce);
		//    totalTorqueVector = totalTorqueVector+rkArm.perpDotProduct (rkForce);
	}
}

/* Przykładamy do obiektu opór areodynamiczny */
void PhysicObject::applyResist()
{
	//if (mass!=0){
	Vector resistVector;
	double resistLength=linearVelocity.length()*linearVelocity.length()+linearVelocity.length();

	// std::cout<<"---------"<<linearVelocity.horizLength()<<std::endl;
	resistVector = linearVelocity;
	resistVector.normalize();
	resistVector=resistVector*resistLength;
	resistVector =resistVector* (-surface)*0.000009;
	resistForce =resistForce+ resistVector;
	//}
}

/* Przykładamy do obiektu siłę tarcia */
void PhysicObject::applyFriction (double fGravity)
{

	/* Jeśli prędkość bardzo mała, używamy tarcia statycznego, w przeciwnym srazie dynamicznego */
	//if (mass!=0){
	Vector kFrictionVector;
	if (linearVelocity.horizLength() < 1)
	{
		/* Liczymy wektor tarcia */
		kFrictionVector = totalForce+linearVelocity;
		kFrictionVector.y=0;
		kFrictionVector.normalize ();
		kFrictionVector =kFrictionVector* -(fGravity * this->getMass()) *staticFriction;
	}
	else
	{
		/* Liczymy wektor tarcia */
		kFrictionVector = linearVelocity;
		kFrictionVector.y=0;
		kFrictionVector.normalize ();
		kFrictionVector =kFrictionVector* -(fGravity * this->getMass()) *kineticFriction;
	}
	frictionForce =frictionForce+ kFrictionVector;
	//}
}

/* Obsługa zderzenia dwóch obiektów */
void PhysicObject::handleCollision (PhysicObject  *rkOtherEntity,Vector rkCollisionNormal)
{
	double fImpulse;
	Vector kRelativeVelocity;
	/* Normalizacja wektora kolizji */
	rkCollisionNormal.normalize ();
	/* Ustalenie wzglednej prędkości */
	kRelativeVelocity = (linearVelocity -rkOtherEntity->getLinearVelocity());
	kRelativeVelocity =kRelativeVelocity* (-1 - restitution*rkOtherEntity->restitution);
	/* Suma odwrotności mas */
	double fInverseMassSum= (1 / this->getMass()) + (1 / rkOtherEntity->getMass ());
	/* Obliczenie impulsu */
	fImpulse = (kRelativeVelocity.dotProduct (rkCollisionNormal)) /rkCollisionNormal.dotProduct (rkCollisionNormal * fInverseMassSum);
	/* Prędkość obiektu */
	if (mass!=0){
		linearVelocity = linearVelocity +(rkCollisionNormal * (fImpulse / this->getMass()));
	}
	/* Prędkość drugiego obiektu */
	Vector kOtherVelocity;
	if (rkOtherEntity->mass!=0){
		rkOtherEntity->setLinearVelocity (rkOtherEntity->getLinearVelocity () -rkCollisionNormal * (fImpulse / rkOtherEntity->getMass ()));
	}
}

/* Symulacja obiektu */
void PhysicObject::simulate (double fStep)
{
	/* Całkowanie Eulera */
	if (this->mass!=0){
		linearVelocity  += (totalForce /this->getMass()) * fStep;
		angularVelocity += (totalTorque / inertia) * fStep;
		//orientation     += angularVelocity * fStep;
		angularVelocityVector += (totalTorqueVector / inertia) * fStep;
		rotation     += angularVelocityVector * fStep;

		this->applyFriction(-this->grav.y);//to aplokowac tylko wtedy gdy wczesniej bylo w kolzji dodadkowa zmienna!!!
		this->applyResist();
		/* Tarcie nie może powodować ruchu */
		if (fabs (linearVelocity.x) >=fabs ((frictionForce.x / this->getMass()) * fStep))
		{linearVelocity.x += (frictionForce.x / this->getMass()) * fStep;}
		else{linearVelocity.x = 0;}
		if (fabs (linearVelocity.y) >=fabs ((frictionForce.y / this->getMass()) * fStep))
		{linearVelocity.y += (frictionForce.y / this->getMass()) * fStep;}
		else{linearVelocity.y = 0;}
		if (fabs (linearVelocity.z) >=fabs ((frictionForce.z / this->getMass()) * fStep))
		{linearVelocity.z += (frictionForce.z / this->getMass()) * fStep;}
		else{linearVelocity.z = 0;}

		if (fabs (linearVelocity.x) >=fabs ((resistForce.x ) * fStep))
		{linearVelocity.x += (resistForce.x ) * fStep;}
		else{linearVelocity.x = 0;}
		if (fabs (linearVelocity.y) >=fabs ((resistForce.y ) * fStep))
		{linearVelocity.y += (resistForce.y ) * fStep;}
		else{linearVelocity.y = 0;}
		if (fabs (linearVelocity.z) >=fabs ((resistForce.z ) * fStep))
		{linearVelocity.z += (resistForce.z ) * fStep;}
		else{linearVelocity.z = 0;}
		////
		/* Wygaszamy błędy związane z niedokładnością operacji zmiennopozycyjnych  */
		if (fabs (linearVelocity.x) <= 0.01f){linearVelocity.x = 0;}
		if (fabs (linearVelocity.y) <= 0.01f){linearVelocity.y = 0;}
		if (fabs (linearVelocity.z) <= 0.01f){linearVelocity.z = 0;}
		/* Stosujemy wygaszanie ponieważ nie ma tarcia związanego z prędkością kątową */
		//angularVelocity *= 0.9f;
		angularVelocityVector=angularVelocityVector-angularVelocityVector*0.15*fStep;
		position        += linearVelocity * fStep;

		/* Zerujemy siły */
		totalTorque                = 0;
		totalTorqueVector          = Vector(0,0,0);
		totalImpulse               = 0;
		totalForce                 = Vector(0,0,0);
		frictionForce              = Vector(0,0,0);
		resistForce                = Vector(0,0,0);
	}
}

void PhysicObject::setPosition (Vector  rkPosition)
{
	position = rkPosition;
}

void PhysicObject::setOrientation (double fOrientation)
{
	orientation = fOrientation;
}

void PhysicObject::setLinearVelocity (Vector rkLinearVelocity)
{
	linearVelocity = rkLinearVelocity;
}

void PhysicObject::setAngularVelocity (double fAngularVelocity)
{
	angularVelocity = fAngularVelocity;
}

void PhysicObject::setMass (double fMass)
{
	mass = fMass;
}

void PhysicObject::setCenterOfMass (Vector & rkCenterOfMass)
{
	centerOfMass = rkCenterOfMass;
}

void PhysicObject::setInertia (double fInertia)
{
	inertia = fInertia;
}

void PhysicObject::setStaticFriction (double fStaticFriction)
{
	staticFriction = fStaticFriction;
}

void PhysicObject::setKineticFriction (double fKineticFriction)
{
	kineticFriction = fKineticFriction;
}

void PhysicObject::setCoefficientOfRestitution (double fCoefficientOfRestitution)
{
	restitution = fCoefficientOfRestitution;
}

double PhysicObject::getOrientation (void)
{
	return orientation;
}

Vector PhysicObject::getLinearVelocity (void)
{
	return linearVelocity;
}

double PhysicObject::getAngularVelocity (void)
{
	return angularVelocity;
}

double PhysicObject::getMass (void)
{
	if(mass==0){return 99999999999;}
	return mass;
}

Vector PhysicObject::getCenterOfMass (void)
{
	return centerOfMass;
}

double PhysicObject::getInertia (void)
{
	return inertia;
}

double PhysicObject::getStaticFriction (void)
{
	return staticFriction;
}

double PhysicObject::getKineticFriction (void)
{
	return kineticFriction;
}

double PhysicObject::getCoefficientOfRestitution (void)
{
	return restitution;
}
