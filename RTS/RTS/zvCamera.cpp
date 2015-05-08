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