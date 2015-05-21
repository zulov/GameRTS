#include "zvCamera.h"

Camera * CameraManager::addCamera(Camera * newCamera){
	if (newCamera!=nullptr){
		cameraList.push_back(newCamera);
	}
	return newCamera;
}

Camera * CameraManager::addCamera(int mode){
	Camera * newCamera;
	if(mode==RTS_CAMERA){
		newCamera= new RTSCamera(mode);
	}else{
		newCamera= new Camera(mode);

	}
	newCamera->setMaxHeight(200);
	newCamera->setMinHeight(2);

	newCamera->setCameraNode(menage->addCameraSceneNode());
	newCamera->getCameraNode()->setFarValue(64000);
	newCamera->getCameraNode()->setPosition(vector3df(0,100,0));
	newCamera->getCameraNode()->bindTargetAndRotation(true);
	newCamera->getCameraNode()->setTarget(vector3df(0,2,100));
	

	activeCamera=newCamera;
	cameraList.push_back(newCamera);
	return newCamera;
}

void CameraManager::deleteCamera(Camera * camToDelete){
	for (int i=0;i<cameraList.size();i++){
		if (cameraList.at(i)==camToDelete){
			delete cameraList.at(i);
			cameraList.erase(cameraList.begin()+i);
			break;
		}
	}
}
void CameraManager::deleteCamera(int n){
	if (n<cameraList.size()){
		cameraList.erase(cameraList.begin()+n);
	}
}

CameraManager::CameraManager(ISceneManager * _menage){
	menage=_menage;
}

Camera::Camera(){

}

Camera::Camera(int mode){
	cameraMode=mode;
}
RTSCamera::RTSCamera(int mode):Camera(mode){

}

void Camera::setCameraNode(ICameraSceneNode * _cameraNode){
	cameraNode=_cameraNode;
}

ICameraSceneNode * Camera::getCameraNode(){
	return cameraNode;
}

Camera * CameraManager::getActiveCamera(){
	return activeCamera;
}

int Camera::getCameraMode(){
	return cameraMode;
}



void Camera::move(Vector move){

}

void Camera::rotate(Vector rotate){
	rotate=rotate*5;
	vector3df pos=getCameraNode()->getTarget();
	vector3df posCam=getCameraNode()->getPosition();
	float sin_t = sin(rotate.y*3.14/180);
    float cos_t = cos(rotate.y*3.14/180);
	float translated_x = pos.X - posCam.X;
	float translated_z = pos.Z - posCam.Z;


	pos.X = translated_x * cos_t - translated_z * sin_t+posCam.X;
	pos.Z = translated_z * cos_t + translated_x * sin_t+posCam.Z;
	getCameraNode()->setTarget(pos);
	Console::writeTo(std::to_string(pos.X)+" "+ std::to_string(pos.Y)+" "+std::to_string(pos.Z));
}

void RTSCamera::rotate(Vector rotate){
	Camera::rotate(rotate);

}

void RTSCamera::move(Vector move){
	move.x*=horizontalSpeed;
	move.z*=horizontalSpeed;
	move.y*=verticalSpeed;

	vector3df camPos=getCameraNode()->getPosition();
	vector3df camTar=getCameraNode()->getTarget();
	camPos.X+=move.x;
	camPos.Z+=move.z;
	camPos.Y+=move.y*(camPos.Y/maxHeight);

	if(camPos.Y<minHeight){
		camPos.Y=minHeight;
	}else if (camPos.Y>maxHeight){
		camPos.Y=maxHeight;
	}

	camTar.X=camTar.X+move.x;
	camTar.Z=camTar.Z+move.z;

	getCameraNode()->setPosition(camPos);
	getCameraNode()->setTarget(camTar);

}

void CameraManager::moveActiveCamera(Vector move){
	getActiveCamera()->move(move);
}
void CameraManager::rotateActiveCamera(Vector rotate){
	getActiveCamera()->rotate(rotate);
}

void Camera::setMaxHeight(float _maxHeight){
	maxHeight=_maxHeight;
}
void Camera::setMinHeight(float _minHeight){
	minHeight=_minHeight;
}

void CameraManager::nextCamera(){
	int index=getNumberOfActiveCamera();
	if(cameraList.size()>index+1){
		setActiveCamera(cameraList.at(index+1));
	}else if (cameraList.at(0)!=0){
		setActiveCamera(cameraList.at(0));
	}
}

void CameraManager::prevCamera(){
	int index=getNumberOfActiveCamera();
	if(index>0){
		setActiveCamera(cameraList.at(index-1));
	}else if (cameraList.at(cameraList.size()-1)!=0){
		setActiveCamera(cameraList.at(cameraList.size()-1));
	}
} 

int CameraManager::getNumberOfActiveCamera(){
	for (int i=0;i<cameraList.size();i++){
		if (cameraList.at(i)==getActiveCamera()){
			return i;
		}
	}
	return -1;
}

void CameraManager::setActiveCamera(Camera * _activeCamera){
	activeCamera=_activeCamera;
	menage->setActiveCamera(activeCamera->getCameraNode());
	Console::writeTo(activeCamera->getName());
}
void Camera::setVerticalSpeed(float _verticalSpeed){
	verticalSpeed=_verticalSpeed;
}
void Camera::setHorizontalSpeed(float _horizontalSpeed){
	horizontalSpeed=_horizontalSpeed;
}
float Camera::getVerticalSpeed(){
	return verticalSpeed;
}
float Camera::getHorizontalSpeed(){
	return horizontalSpeed;
}
void Camera::setName(std::string _name){
	name=_name;
}
std::string Camera::getName(){
	return name;
}