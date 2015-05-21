#ifndef ZVCAMERA_H
#define ZVCAMERA_H
#include "zvGlobal.h"
#include "zvConsole.h"
class Camera{
protected:
    ICameraSceneNode * cameraNode;
    int cameraMode;
	float maxHeight;
	float minHeight;
	float verticalSpeed;
	float horizontalSpeed;
	std::string name;

public:
	Camera();
	Camera(int mode);
	void setCameraNode(ICameraSceneNode * _cameraNode);
	ICameraSceneNode * getCameraNode();
	int getCameraMode();
	virtual void move(Vector move);
	virtual void rotate(Vector rotate);
	void setMaxHeight(float _maxHeight);
	void setMinHeight(float _minHeight);
	void setVerticalSpeed(float _verticalSpeed);
	void setHorizontalSpeed(float _horizontalSpeed);
	float getVerticalSpeed();
	float getHorizontalSpeed();
	void setName(std::string _name);
	std::string getName();
};

class RTSCamera:public Camera{
private:
	
public:
	RTSCamera();
	RTSCamera(int mode);
	virtual void move(Vector move);
	virtual void rotate(Vector rotate);
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
	void rotateActiveCamera(Vector rotate);
    CameraManager(ISceneManager * _menage);
	void nextCamera();
	void prevCamera();
};


#endif
