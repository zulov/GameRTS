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
	newCamera->getCameraNode()->setPosition(vector3df(0,1000,0));
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

	camTar.Y=minHeight-1;//+od wyokosci w danym miejscu mapy  powinno byc
	camTar.X=camPos.X;
	camTar.Z=camPos.Z+50+(maxHeight/camPos.Y)*2;//uwzglednic minHeight
	camTar.X=camPos.X-(maxHeight/camPos.Y)/2;//uwzglednic minHeight
	getCameraNode()->setPosition(camPos);
	getCameraNode()->setTarget(camTar);
}

void CameraManager::moveActiveCamera(Vector move){
	getActiveCamera()->move(move);
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