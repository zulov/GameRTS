#include "zvCamera.h"

Camera * CameraManager::addCamera(Camera * newCamera){
	if (newCamera!=nullptr){
		cameraList.push_back(newCamera);
	}
	return newCamera;
}

Camera * CameraManager::addCamera(int mode){
	Camera * newCamera= new Camera(mode);
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

void CameraManager::moveActiveCamera(vector3df v){
	if(activeCamera->getCameraMode()==RTS_CAMERA){
		vector3df camPos=activeCamera->getCameraNode()->getPosition();
		vector3df camTar=activeCamera->getCameraNode()->getTarget();
		camPos+=v;
		camTar+=v;
		camTar.Y=0;
		camTar.Z=camPos.Z+(2000000/(camPos.Y))+5000;
		camTar.X=camPos.X-(1000000/(camPos.Y))+500;
		activeCamera->getCameraNode()->setPosition(camPos);
		activeCamera->getCameraNode()->setTarget(camTar);
	}
}