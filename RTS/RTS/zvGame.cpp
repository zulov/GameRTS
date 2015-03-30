
#include "zvGame.h"

IrrlichtDevice * Game::device =0;
IVideoDriver * Game::ivideo=0;
ISceneManager * Game::menage=0;
ICameraSceneNode * Game::kam=0;
gui::IGUIEnvironment * Game::guienv=0;
Control * Game::klawiatura=0;
GUIManager * Game::guiManager=0;
ListObject * Game::allObiekt=0;
PhysicWorld * Game::fizWorld=0;
Settings * Game::settStart=0;
SettLoader * Game::settLoader=0;
Player* Game::player=0;
CameraManager * Game::cameraManager=0;
/////
double Game::frameDeltaTime=0;
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
void Game::setGracz(Player* _player){
	player=_player;
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
	player= make_gracz(menage,ivideo,fizWorld,allObiekt);
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

	make_things(menage,ivideo,fizWorld,allObiekt);
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

double Game::computeTimeDiff(){
	double now = Game::device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - prevTime) / 30.f; // Time in seconds
	prevTime = now;
	return frameDeltaTime;
}

double Game::getTimeDiff(){
	return frameDeltaTime;
}

void Game::update_ai(){
	srand( time( NULL ) );
	for(int i=0;i<allObiekt->listObiekt.size();i++){
		Object*ob=allObiekt->listObiekt[i];
		Animal* obAnimal = dynamic_cast<Animal*>(ob);
		if (obAnimal!=0){
			obAnimal->move(Game::player->bodyFiz->position.x,Game::player->bodyFiz->position.z);
		}
	}
}

void Game::kam_update(){
	//cameraManager->getActiveCamera()->getCameraNode()->setTarget(core::vector3df(player->bodyFiz->getPosition().x,
	//															player->bodyFiz->getPosition().y+20,
	//															player->bodyFiz->getPosition().z));

}

void Game::loadMap(std::string path){

}






/////////////////////
void show_fps(int lastFPS){
	if (Game::device->isWindowActive())
	{
		int fps = Game::ivideo->getFPS();
		if (lastFPS != fps)
		{
			core::stringw str = L"RTS by Tomasz Gajda 2013-2014 ||  FPS:";
			str += fps;
			Game::device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
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
	ground->bodyFiz=new PhysicGround(81,64000);
	ground->bodyFiz->setMass(0);
	ground->bodyFiz->setPosition(pos);
	ground->bodyFiz->setStaticFriction(0.5f);
	ground->bodyFiz->setKineticFriction(0.2f);
	ground->bodyFiz->setCoefficientOfRestitution(0.3f);

	//fizWorld->obiekty.push_back(ground->bodyFiz);
	PhysicGround* obGround = dynamic_cast<PhysicGround*>(ground->bodyFiz);
	std::fstream plik;
	plik.open( "models/ground_7.obj", std::ios::in );

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

	IAnimatedMesh * mesh = menage->getMesh( "models/ground_7.obj" );
	ground->bodyIrr = menage->addOctreeSceneNode( mesh,0,-1,512);
	//  ground->bodyIrr->setScale( core::vector3df(  1,  1,  1) );
	ground->bodyIrr->setPosition( core::vector3df( 0, 0, 0 ) );
	ground->bodyIrr->setMaterialFlag( video::EMF_LIGHTING, true );
	ground->bodyIrr->setMaterialTexture( 0, ivideo->getTexture( "textures/island_texture.jpg" ) );
	ground->bodyIrr->addShadowVolumeSceneNode();
	allObiekt->listObiekt.push_back(ground);
	///////
	IAnimatedMesh * meshStone = menage->getMesh( "models/stones_2.obj" );
	irr::video::ITexture* textStone=ivideo->getTexture( "textures/stone_1.jpg" );
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			if(rand()%10<7){continue;}
			Thing * kamien=new Thing();
			Vector pos=Vector(0,0,0);
			pos.x=-20000+2000*i+rand()%1800-900;
			pos.z=-20000+2000*j+rand()%1800-900;
			pos.y=obGround->getHeight(pos.x,pos.z);
			kamien->bodyFiz=new PhysicSphere(0,pos.x,pos.y,pos.z,370);
			kamien->bodyFiz->setPosition(pos);
			kamien->bodyFiz->setRotation(Vector(0,rand()%360,0));
			kamien->bodyFiz->setStaticFriction(0.5f);
			kamien->bodyFiz->setKineticFriction(0.3f);
			kamien->bodyFiz->setCoefficientOfRestitution(0.7f);

			fizWorld->obiekty.push_back(kamien->bodyFiz);
			//nowyGracz->bodyIrrAnim =menage->addAnimatedMeshSceneNode(mesh);
			kamien->bodyIrr = menage->addOctreeSceneNode( meshStone,0,-1,512);
			kamien->bodyIrr->setPosition( core::vector3df( pos.x,pos.y, pos.z ) );
			kamien->bodyIrr->setMaterialFlag( video::EMF_LIGHTING, true );
			kamien->bodyIrr->setMaterialTexture( 0,textStone  );
			//kamien->bodyIrr->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			kamien->bodyIrr->addShadowVolumeSceneNode();
			allObiekt->listObiekt.push_back(kamien);
		}
	}
	/////
	Object * sea=new Object();
	pos=Vector(0,75,0);
	sea->bodyFiz=new PhysicGround(2,256000);
	sea->bodyFiz->setMass(0);
	sea->bodyFiz->setPosition(pos);
	sea->bodyFiz->setStaticFriction(0.5f);
	sea->bodyFiz->setKineticFriction(0.2f);
	sea->bodyFiz->setCoefficientOfRestitution(0.01f);
	fizWorld->obiekty.push_back(sea->bodyFiz);
	IAnimatedMesh * meshSea = menage->getMesh( "models/sea_3.obj" );
	sea->bodyIrr = menage->addOctreeSceneNode( meshSea,0,-1,512);
	// scene::ISceneNode* node =menage->addWaterSurfaceSceneNode(meshSea, 3.0f, 300.0f, 30.0f);
	sea->bodyIrr->setPosition( core::vector3df( pos.x,pos.y, pos.z ) );
	sea->bodyIrr->setMaterialFlag( video::EMF_LIGHTING, true );
	sea->bodyIrr->setMaterialTexture( 0, ivideo->getTexture( "textures/sea_1.jpg" ) );
	// sea->bodyIrr->setMaterialType(video::EMT_REFLECTION_2_LAYER);
	// sea->bodyIrr->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	sea->bodyIrr->addShadowVolumeSceneNode();
	allObiekt->listObiekt.push_back(sea);
	//////
	fizWorld->obiekty.push_back(ground->bodyFiz);
	////
	ISceneNode* skyBox = menage->addSkyBoxSceneNode(
		ivideo->getTexture("textures/sky_top.jpg"),
		ivideo->getTexture("textures/sky_bottom.jpg"),
		ivideo->getTexture("textures/sky_forward.jpg"),
		ivideo->getTexture("textures/sky_back.jpg"),
		ivideo->getTexture("textures/sky_right.jpg"),
		ivideo->getTexture("textures/sky_left.jpg"));
}

Player* make_gracz(ISceneManager * menage,IVideoDriver * ivideo,PhysicWorld*fizWorld,ListObject* allObiekt){
	Player * nowyGracz=new Player();
	Game::player=nowyGracz;
	nowyGracz->bodyFiz=new PhysicSphere();
	PlayerLoader * playerLoad=new PlayerLoader("settings/player.set");
	playerLoad->loadPlayer();
	Vector pos=nowyGracz->bodyFiz->position;//Vector(1000,1000,0);

	nowyGracz->bodyFiz->surface=17*17;
	fizWorld->obiekty.push_back(nowyGracz->bodyFiz);
	IAnimatedMesh * mesh = menage->getMesh( nowyGracz->meshPath.c_str() );
	nowyGracz->bodyIrrAnim =menage->addAnimatedMeshSceneNode(mesh);
	nowyGracz->bodyIrrAnim->setMaterialFlag( video::EMF_LIGHTING, true );
	nowyGracz->bodyIrrAnim->setMaterialTexture( 0, ivideo->getTexture( nowyGracz->texturePath.c_str() ) );
	nowyGracz->bodyIrrAnim->setFrameLoop(0,0);
	nowyGracz->bodyIrrAnim->setPosition( core::vector3df( pos.x,pos.y, pos.z ) );
	nowyGracz->bodyIrrAnim->addShadowVolumeSceneNode();
	//   nowyGracz->bodyIrrAnim->setAnimationSpeed(3);
	allObiekt->listObiekt.push_back(nowyGracz);

	allObiekt->activeVelues.push_back(&(nowyGracz->HP));
	allObiekt->activeVelues.push_back(&(nowyGracz->hunger));
	allObiekt->activeVelues.push_back(&(nowyGracz->thirst));
	allObiekt->activeVelues.push_back(&(nowyGracz->tired));
	allObiekt->activeVelues.push_back(&(nowyGracz->currentSprintTime));

	return nowyGracz;
}

void make_enemies(scene::ISceneManager * menage,video::IVideoDriver * ivideo,PhysicWorld*fizWorld,ListObject* allObiekt){
	IAnimatedMesh * mesh = menage->getMesh( "models/enemy_1.X" );
	irr::video::ITexture* texture=ivideo->getTexture( "textures/star_e.jpg" );
	for (int i=0;i<0;i++){
		for(int j=0;j<10;j++){
			Animal * nowyWrog=new Animal();
			Vector pos=Vector(-1000+i*90,800,-1000+j*90);

			nowyWrog->bodyFiz=new PhysicSphere(20,pos.x,pos.y,pos.z,35);
			nowyWrog->bodyFiz->setPosition(pos);
			nowyWrog->bodyFiz->setStaticFriction(0.4f);
			nowyWrog->bodyFiz->setKineticFriction(0.2f);
			nowyWrog->bodyFiz->setCoefficientOfRestitution(0.9f);
			nowyWrog->bodyFiz->surface=35*35;
			nowyWrog->attackAble=true;

			fizWorld->obiekty.push_back(nowyWrog->bodyFiz);
			//  nowyGracz->bodyIrr = menage->addOctreeSceneNode( mesh,0,-1,512);
			nowyWrog->bodyIrrAnim =menage->addAnimatedMeshSceneNode(mesh);
			nowyWrog->bodyIrrAnim->setPosition( core::vector3df(pos.x,pos.y,pos.z));
			nowyWrog->bodyIrrAnim->setMaterialFlag( video::EMF_LIGHTING, true );
			nowyWrog->bodyIrrAnim->setMaterialTexture( 0,texture  );
			nowyWrog->bodyIrrAnim->setFrameLoop(0,0);
			nowyWrog->bodyIrrAnim->addShadowVolumeSceneNode();
			//   nowyWrog->bodyIrrAnim->setAnimationSpeed(3);
			allObiekt->listObiekt.push_back(nowyWrog);
		}
	}
}

void make_things(scene::ISceneManager * menage,video::IVideoDriver * ivideo,PhysicWorld*fizWorld,ListObject* allObiekt){
	ObjectProperties *obpProp=allObiekt->getObjectFromID(11);
	IAnimatedMesh * mesh = menage->getMesh((obpProp->meshPath).c_str());
	irr::video::ITexture* texture=ivideo->getTexture((obpProp->texturePath).c_str());
	for (int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			Thing * nowyThing=new Thing();
			nowyThing->name=obpProp->name;
			nowyThing->image=ivideo->getTexture((obpProp->iconPath).c_str());
			Vector pos=Vector(i*20,8000,j*20);
			if (obpProp->collision=="sphere"){
				nowyThing->bodyFiz=new PhysicSphere(obpProp->radius,pos.x,pos.y,pos.z,obpProp->masa);
			}else{
				nowyThing->bodyFiz=new PhysicObject(obpProp->masa,pos.x,pos.y,pos.z);
			}

			nowyThing->bodyFiz->setPosition(pos);
			nowyThing->bodyFiz->setStaticFriction(obpProp->staticFriction);
			nowyThing->bodyFiz->setKineticFriction(obpProp->kineticFriction);
			nowyThing->bodyFiz->setCoefficientOfRestitution(obpProp->coefficientOfRestitution);
			nowyThing->bodyFiz->surface=obpProp->surface;
			nowyThing->actionAble=obpProp->actionAble;
			nowyThing->takeAble=obpProp->takeAble;
			fizWorld->obiekty.push_back(nowyThing->bodyFiz);
			//  nowyGracz->bodyIrr = menage->addOctreeSceneNode( mesh,0,-1,512);
			nowyThing->bodyIrrAnim =menage->addAnimatedMeshSceneNode(mesh);
			nowyThing->bodyIrrAnim->setPosition( core::vector3df(pos.x,pos.y,pos.z));
			nowyThing->bodyIrrAnim->setMaterialFlag( video::EMF_LIGHTING, true );
			nowyThing->bodyIrrAnim->setMaterialTexture( 0, texture  );
			//nowyThing->bodyIrrAnim->setMaterialType( video::EMT_TRANSPARENT_ALPHA_CHANNEL );
			nowyThing->bodyIrrAnim->setFrameLoop(0,0);
			nowyThing->bodyIrrAnim->addShadowVolumeSceneNode();
			//   nowyWrog->bodyIrrAnim->setAnimationSpeed(3);
			allObiekt->listObiekt.push_back(nowyThing);
		}
	}
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

		if (allObiekt->listObiekt.at(i)->alive==false){
			std::cout<<"smierc"<<std::endl;
			Object * deadObiekt=allObiekt->listObiekt.at(i);
			deadObiekt->bodyIrrAnim->remove();
			allObiekt->listObiekt.erase(allObiekt->listObiekt.begin()+i);
			for(int j=0;j<fizWorld->obiekty.size();j++){
				if(deadObiekt->bodyFiz==fizWorld->obiekty.at(j)){
					fizWorld->obiekty.erase(fizWorld->obiekty.begin()+j);
					break;
				}
			}
		}else{i++;}
	}
}

/////////////////////
