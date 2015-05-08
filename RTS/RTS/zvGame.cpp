#include "zvGame.h"

IrrlichtDevice * Game::device =0;
IVideoDriver * Game::ivideo=0;
ISceneManager * Game::menage=0;
ICameraSceneNode * Game::kam=0;
IGUIEnvironment * Game::guienv=0;
Control * Game::klawiatura=0;
GUIManager * Game::guiManager=0;
ListObject * Game::allObiekt=0;
PhysicWorld * Game::fizWorld=0;
Settings * Game::settStart=0;
SettLoader * Game::settLoader=0;
CameraManager * Game::cameraManager=0;
/////
float Game::frameDeltaTime=0;
unsigned long Game::prevTime=0;

void Game::setDevice(irr::IrrlichtDevice * _device){
	device=_device;
}
void Game::setVideo(IVideoDriver * _video){
	ivideo=_video;
}
void Game::setSceneManager(ISceneManager * _manager){
	menage=_manager;
}
void Game::addCamera(ICameraSceneNode * _kam){
	kam=_kam;//nie ustawiac tylko dodac
}
void Game::setControl(Control * _klawiatura){
	klawiatura=_klawiatura;
}
void Game::setGUIManager(GUIManager * _guiManager){
	guiManager=_guiManager;
}
void Game::setListObiekt(){
	allObiekt=new ListObject();;
}
void Game::setFizWorld(PhysicWorld * _fizWorld){
	fizWorld=_fizWorld;
}
void Game::setSettings(Settings * _settStart){
	settStart=_settStart;
}
void Game::setSettLoader(SettLoader * _settLoader){
	settLoader=_settLoader;
}

void Game::prepareIrrlicht(){
	klawiatura=new Control();
	device = createDevice(EDT_OPENGL,dimension2d<u32>(settStart->weidthRes, settStart->heightRes ),settStart->colorDepth, settStart->fullScreen, settStart->stencil, settStart->vSync, Game::klawiatura );
	ivideo = device->getVideoDriver();
	menage = device->getSceneManager();
	cameraManager= new CameraManager(menage);
	cameraManager->addCamera(RTS_CAMERA);
}
void Game::prepareZv(){
	MainGUI * loadingGUI;
	MainGUI * mainGUI;
	guiManager=new GUIManager();
	Console::setOutputFilePath(settStart->consoleOutputPath);

	ObjectMainLoader *objectsLoader=new ObjectMainLoader("objects/obiekty.obl");
	objectsLoader->load();

	fizWorld=new PhysicWorld(9.78,1);

	loadingGUI=new MainGUI();

	guiManager->addMainGui(loadingGUI);
	GUIMainLoader *GUILoadingloader=new GUIMainLoader("settings/gui/mainLoading.gui",loadingGUI);
	GUILoadingloader->loadGUI();

	Game::ivideo->beginScene( false, true, video::SColor( 255, 0, 10, 200 ) );
	Game::getGUI(0)->drawGUI();
	Game::ivideo->endScene();

	mainGUI=new MainGUI();
	guiManager->addMainGui(mainGUI);

	GUIMainLoader *GUIMainloader=new GUIMainLoader("settings/gui/main.gui",mainGUI);
	GUIMainloader->loadGUI();

	make_scena(menage,ivideo,fizWorld,allObiekt);
}
Settings * Game::loadSettings(){
	Game::settStart=new Settings();
	settLoader= new SettLoader("settings/start.set");
	settLoader->loadStartSetting();
	delete settLoader;
	return Game::settStart;
}

Camera * Game::prepereCamera(int mode){
	cameraManager=new CameraManager(menage);
	return cameraManager->addCamera(mode);
}

MainGUI * Game::getGUI(int num){
	return guiManager->getGUI(num);
}

float Game::computeTimeDiff(){
	float now = Game::device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - prevTime) / 30.f; // Time in seconds
	prevTime = now;
	return frameDeltaTime;
}

float Game::getTimeDiff(){
	return frameDeltaTime;
}

void Game::kam_update(){
	//cameraManager->getActiveCamera()->getCameraNode()->setTarget(core::vector3df(player->getPhysicBody()->getPosition().x,
	//															player->getPhysicBody()->getPosition().y+20,
	//															player->getPhysicBody()->getPosition().z));

}

void Game::loadMap(std::string path){

}

void Game::createUnit(Vector position){
	Unit * unit=new Unit();
	PhysicSphere * body=new PhysicSphere(50,position,1);
	unit->setPhysicBody(body);
	body->setMass(50);
	body->setPosition(position);
	body->setStaticFriction(0.5f);
	body->setKineticFriction(0.2f);
	body->setCoefficientOfRestitution(0.01f);
	Game::fizWorld->obiekty.push_back(body);

	IAnimatedMesh * mesh = Game::menage->getMesh( "models/unit/infantry.obj" );
	IMeshSceneNode* meshBody=Game::menage->addOctreeSceneNode( mesh,0,-1,512);

	meshBody->setPosition( core::vector3df( position.x,position.y, position.z ) );
	meshBody->setMaterialFlag( video::EMF_LIGHTING, true );
	meshBody->setMaterialTexture( 0, Game::ivideo->getTexture( "textures/red.png" ) );
	meshBody->setScale(vector3df(1,1,1));

	unit->setMesh(meshBody);
	Game::allObiekt->listObiekt.push_back(unit);

	Game::fizWorld->obiekty.push_back(body);
}

void show_fps(){
	if (Game::device->isWindowActive())
	{
		int fps = Game::ivideo->getFPS();

		core::stringw str = L"RTS by Tomasz Gajda 2013-2014 ||  FPS:";
		str += fps;
		Game::device->setWindowCaption(str.c_str());
	}
	else{
		Game::device->yield();
	}
}

void make_scena(scene::ISceneManager * menage,video::IVideoDriver * ivideo,PhysicWorld*fizWorld,ListObject* allObiekt){
	menage->setAmbientLight(video::SColorf(1,1,1,1));
	menage->setShadowColor(video::SColor(200,0,0,0));
	ILightSceneNode* light1 =menage->addLightSceneNode( 0, core::vector3df(0,10000,0), video::SColorf(0.8f,0.8f,0.8f), 100000.0f, 1 );
	//ivideo->setFog(video::SColor(0,138,125,81), video::EFT_FOG_LINEAR, 5, 1000, .3f, true, false);
	///
	Object *ground=new Object();
	Vector pos=Vector(0,0,0);
	ground->setPhysicBody(new PhysicGround(5,2048));
	ground->getPhysicBody()->setMass(0);
	ground->getPhysicBody()->setPosition(pos);
	ground->getPhysicBody()->setStaticFriction(0.5f);
	ground->getPhysicBody()->setKineticFriction(0.2f);
	ground->getPhysicBody()->setCoefficientOfRestitution(0.3f);

	//fizWorld->obiekty.push_back(ground->getPhysicBody());
	PhysicGround* obGround = dynamic_cast<PhysicGround*>(ground->getPhysicBody());
	std::fstream plik;
	plik.open( "models/testMapFlat.obj", std::ios::in );

	if( plik.good()&&obGround )
	{
		std::string dane;
		std::string sNull;
		std::cout << "Uzyskano dostep do pliku z modelem!" << std::endl;

		for(int i=obGround->mapHeigth.size()-1;i>=0;i--){
			for(int j=obGround->mapHeigth.size()-1;j>=0;j--){
				plik>>dane;
				if (dane =="v"){//troche za malo ogolny na razie

					plik >>sNull;
					plik >>dane;
					plik >>sNull;
					//tu trzeba dynamic cast zrobic albo jakos ladniej
					obGround->mapHeigth.at(j).at(i)=atof(dane.c_str());
				}else{j++;}
			}
		}
		plik.close();
	}else{ std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;}

	IAnimatedMesh * mesh = menage->getMesh( "models/testMapFlat.obj" );
	ground->setMesh(menage->addOctreeSceneNode( mesh,0,-1,512));
	//  ground->getMesh()->setScale( core::vector3df(  1,  1,  1) );
	ground->getMesh()->setPosition( core::vector3df( 0, 0, 0 ) );
	ground->getMesh()->setMaterialFlag( video::EMF_LIGHTING, true );
	ground->getMesh()->setMaterialTexture( 0, ivideo->getTexture( "textures/island_texture.jpg" ) );
	ground->getMesh()->addShadowVolumeSceneNode();
	allObiekt->listObiekt.push_back(ground);
	///////

	fizWorld->obiekty.push_back(ground->getPhysicBody());
	////
	ISceneNode* skyBox = menage->addSkyBoxSceneNode(
		ivideo->getTexture("textures/sky_top.jpg"),
		ivideo->getTexture("textures/sky_bottom.jpg"),
		ivideo->getTexture("textures/sky_forward.jpg"),
		ivideo->getTexture("textures/sky_back.jpg"),
		ivideo->getTexture("textures/sky_right.jpg"),
		ivideo->getTexture("textures/sky_left.jpg"));
}

bool collision(ISceneNode* one, ISceneNode* two) {
	if(one->getTransformedBoundingBox().intersectsWithBox(two->getTransformedBoundingBox())) {
		return true;
	}
	return false;
}

void update_alive(ListObject* allObiekt,PhysicWorld* fizWorld){
	//to bedzie mozna zroib bardziej wybiorczo, a nie leciec po wszystkich
	for (int i=0;i<allObiekt->listObiekt.size();){//poprawic usuwania tak generalnie walic delete

		if (allObiekt->listObiekt.at(i)->getAlive()==false){
			std::cout<<"smierc"<<std::endl;
			Object * deadObiekt=allObiekt->listObiekt.at(i);
			deadObiekt->getMesh()->remove();
			allObiekt->listObiekt.erase(allObiekt->listObiekt.begin()+i);
			for(int j=0;j<fizWorld->obiekty.size();j++){
				if(deadObiekt->getPhysicBody()==fizWorld->obiekty.at(j)){
					fizWorld->obiekty.erase(fizWorld->obiekty.begin()+j);
					break;
				}
			}
		}else{i++;}
	}
}

/////////////////////
