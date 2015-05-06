#ifndef ZVGAME_H
#define ZVGAME_H
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "zvLoader.h"
#include "zvGUI.h"
#include "zvControl.h"
#include "zvObject.h"
#include "zvCamera.h"
#include "zvEnums.h"
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace std;

class  Game{
public:
	static IrrlichtDevice * device ;
	static IVideoDriver * ivideo;
	static ISceneManager * menage;

	static ICameraSceneNode * kam;
	static Camera * camera;
	static gui::IGUIEnvironment* guienv;
	static Control * klawiatura;

	static CameraManager * cameraManager;
	static GUIManager * guiManager;
	static ListObject * allObiekt;
	static PhysicWorld * fizWorld;
	static Settings * settStart;
	static SettLoader * settLoader;

	static float frameDeltaTime;
	static unsigned long prevTime;

	static void setDevice(IrrlichtDevice * _device);
	static void setVideo(IVideoDriver * _video);
	static void setSceneManager(ISceneManager * _manager);
	static void addCamera(ICameraSceneNode * _kam);
	static void setControl(Control * _klawiatura);
	static void setGUIManager(GUIManager * _guiManager);
	static void setListObiekt();
	static void setFizWorld(PhysicWorld * _fizWorld);
	static void setSettings(Settings * _settStart);
	static void setSettLoader(SettLoader * _settLoader);


	static void prepareIrrlicht();
	static void prepareZv();
	static Settings * loadSettings();
	static Camera * prepereCamera(int mode);

	static MainGUI * getGUI(int num);
	static float computeTimeDiff();
	static float getTimeDiff();
	static void loadMap(std::string path);

	static void update_ai();
	static void kam_update();
};
////////////////

void make_scena(ISceneManager * menage, IVideoDriver * ivideo, PhysicWorld*fizWorld, ListObject* allObiekt);

void show_fps(int lastFPS);

bool collision(ISceneNode* one, ISceneNode* two);

void update_alive(ListObject* allObiekt, PhysicWorld* fizWorld);
void update_stat(float fstep);
////////////////
#endif
