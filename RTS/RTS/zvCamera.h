#ifndef ZVCAMERA_H
#define ZVCAMERA_H
#include "zvGlobal.h"

class Camera{
protected:
    ICameraSceneNode * cameraNode;
    int cameraMode;
	float maxHeight;
	float minHeight;
public:
	Camera();
	Camera(int mode);
	void setCameraNode(ICameraSceneNode * _cameraNode);
	ICameraSceneNode * getCameraNode();
	int getCameraMode();
	virtual void move(Vector move);
	void setMaxHeight(float _maxHeight);
	void setMinHeight(float _minHeight);
	

};

class RTSCamera:public Camera{
private:
	
public:
	RTSCamera();
	RTSCamera(int mode);
	virtual void move(Vector move);
};

class CameraManager{
private:
	int getNumberOfActiveCamera();
    std::vector<Camera*> cameraList;
	ISceneManager * menage;
	Camera * activeCamera;
	void setActiveCamera(Camera * _activeCamera);
public:
    ICameraSceneNode * getCamera(int n);
    Camera * addCamera(Camera * newCamera);
	Camera * addCamera(int mode);
	Camera * getActiveCamera();
    void deleteCamera(Camera * camToDelete);
    void deleteCamera(int n);
	void moveActiveCamera(Vector v);
    CameraManager(ISceneManager * _menage);
	void nextCamera();
	void prevCamera();
};


#endif
