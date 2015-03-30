//Tomasz Gajda projekt testowy Irrlicht 2013
#pragma comment(lib, "Irrlicht.lib")
#include "zvGame.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;

double loadProgres;

int main(){ 

	loadProgres=0;
	Game::setListObiekt();
	Game::allObiekt->activeVelues.push_back(&loadProgres);
	//zrobic gdzies update load bary zeby byl ekran ladowanie ale pozniej to i tak jakos lepiej zrobic
	//a z zvgame zrobic prawdziwy obiekt moze nie wszystko musi byc statycze?

	Game::loadSettings();
	Game::prepareIrrlicht();
	Game::prepareZv();

	Game::prepereCamera(RTS_CAMERA);

	updateLoadBar(Game::getGUI(0),Game::ivideo,&loadProgres,20.0);
	///////////////////////
	int lastFPS;

	Game::device->run();
	updateLoadBar(Game::getGUI(0),Game::ivideo,&loadProgres,50.0);
	Game::device->getCursorControl()->setVisible(false);
	while( Game::device->run() ){
		Game::computeTimeDiff();
		//        show_fps(Game::device,Game::ivideo,lastFPS);
		if(Game::klawiatura->control(Game::device,Game::getTimeDiff(),Game::player,Game::allObiekt, Game::getGUI(1),Game::cameraManager)==-1){Console::saveConsole(0); return 0;}
		//        update_alive(Game::allObiekt,Game::fizWorld);
		Game::player->update_stat(Game::getTimeDiff());
		Game::fizWorld->move(Game::getTimeDiff());
		Game::fizWorld->collision(Game::getTimeDiff());
		Cursor::updateCursor(Game::klawiatura->getMouseX(),Game::klawiatura->getMouseY());
		Game::allObiekt->update_position();
		Game::kam_update();
		Game::ivideo->beginScene( false, true, video::SColor( 255, 0, 10, 200 ) );
		Game::menage->drawAll();
		Game::getGUI(1)->drawGUI();
		Game::ivideo->endScene();
	}
	Console::saveConsole(0);
}
