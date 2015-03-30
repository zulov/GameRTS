#ifndef ZVCAMERA_H
#define ZVCAMERA_H
#include "zvGlobal.h"

class Camera{
    ICameraSceneNode * cameraNode;
    int cameraMode;
public:
	Camera();
	Camera(int mode);
	void setCameraNode(ICameraSceneNode * _cameraNode);
	ICameraSceneNode * getCameraNode();
	int getCameraMode();
};

class CameraManager{
    std::vector<Camera*> cameraList;
	ISceneManager * menage;
	Camera * activeCamera;
public:
    ICameraSceneNode * getCamera(int n);
    Camera * addCamera(Camera * newCamera);
	Camera * addCamera(int mode);
	Camera * getActiveCamera();
    void deleteCamera(Camera * camToDelete);
    void deleteCamera(int n);
	void moveActiveCamera(vector3df v);
    CameraManager(ISceneManager * _menage);
};


#endif
