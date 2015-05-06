#include "zvGUI.h"
#include "zvGame.h"

int Cursor::x;
int Cursor::y;
CursorGUI * Cursor::kursorGUI;

MainGUI::MainGUI(){
	allowedType=0;
}

ElementGUI::ElementGUI(){
	type=-1;
	absX=0;
	absY=0;
	absXp=0;
	absYp=0;
	txCordX=0;
	txCordY=0;
	txCordXp=0;
	txCordYp=0;
	hudSize=0;
	text="";
	pathFont="!";
	font=0;
}
//CursorGUI::CursorGUI(irr::video::Game::ivideoDriver * _Game::ivideo,zvControl * _klawiatura):ElementGUI(_Game::ivideo){
//Game::ivideo=_Game::ivideo;
//klawiatura=_klawiatura;
//type=10;
//}Control
CursorGUI::CursorGUI():ElementGUI(){
	type=10;
}
ActiveElementGUI::ActiveElementGUI():ElementGUI(){
}
TableGUI::TableGUI():ElementGUI(){
}

ConsoleGUI::ConsoleGUI(int _visibleLines):ElementGUI(){
	visibleLines=_visibleLines;
}
ScreenCords::ScreenCords(int _x,int _y,int _rozX,int _rozY){
	x=_x;
	y=_y;
	rozX=_rozX;
	rozY=_rozY;
	visibleX=_rozX;
	visibleY=_rozY;
}

ScreenCords::ScreenCords(int _x,int _y,int _rozX,int _rozY,int _visibleX,int _visibleY){
	x=_x;
	y=_y;
	rozX=_rozX;
	rozY=_rozY;
	visibleX=_visibleX;
	visibleY=_visibleY;
}

void ElementGUI::addImage(int x,int y,int rozX,int rozY,std::string path,int aX,int aY,int vX,int vY){
	irr::video::ITexture* image = Game::ivideo->getTexture(path.c_str());
	//std::cout<<aX<<"dssssssssssssssssssssssssssssssssssssssssssssssssss"<<std::endl;
	if(aX>=0&&aY>=0){
		Game::ivideo->makeColorKeyTexture(image, irr::core::position2d<irr::s32>(aX,aY));
	}
	images.push_back(image);

	ScreenCords* cord=new ScreenCords(x,y,rozX,rozY,vX,vY);
	cords2d.push_back(cord);
}

void ElementGUI::printText(std::string textToPrint){
	if (this->font!=0){
		irr::core::stringw str;
		if (textToPrint!=""){
			str=textToPrint.c_str();
		}else{str=(this->text).c_str();}
		font->draw(str,core::rect<s32>(absX+txCordX,absY+txCordY,300,50),video::SColor(255,255,255,255));
	}
}

void ElementGUI::addImage(int x,int y,int rozX,int rozY,irr::video::ITexture* image,int aX,int aY,int vX,int vY){
	//irr::video::ITexture* image = Game::ivideo->getTexture(path.c_str());
	if(aX>=0&&aY>=0){
		Game::ivideo->makeColorKeyTexture(image, irr::core::position2d<irr::s32>(aX,aY));
	}
	images.push_back(image);

	ScreenCords* cord=new ScreenCords(x,y,rozX,rozY,vX,vY);
	cords2d.push_back(cord);
}


void ElementGUI::drawElement(){
	for(int i=0;i<images.size();i++){
		Game::ivideo->draw2DImage(images.at(i),irr::core::position2d<irr::s32>(cords2d.at(i)->x,cords2d.at(i)->y),irr::core::rect<irr::s32>(0,0,cords2d.at(i)->visibleX,cords2d.at(i)->visibleY),0,irr::video::SColor(255,255,255,255), true);
	}
}

void CursorGUI::drawElement(){
	for(int i=0;i<images.size();i++){
		Game::ivideo->draw2DImage(images.at(i),irr::core::position2d<irr::s32>(cordX,cordY),irr::core::rect<irr::s32>(0,0,cords2d.at(i)->rozX,cords2d.at(i)->rozY),0,irr::video::SColor(255,255,255,255), true);
	}
}

void CursorGUI::updateCords(int x,int y){
	cordX=x;
	cordY=y;
}

void Cursor::updateCursor(int _x,int _y){
	x=_x;
	y=_y;
	kursorGUI->updateCords(_x,_y);
}

void Cursor::setCursorGUI(CursorGUI * _cursorGUI){
	kursorGUI=_cursorGUI;
}
void TableGUI::drawElement(){
	int k=0;
	std::cout<<maxItemX<<" "<<maxItemY<<" "<<images.size()<<" "<<gap<<" "<<itemWidth<<" "<<absY<<" "<<itemHeight<<" "<<std::endl;
	for(int i=0;i<maxItemY;i++){//mozna poprawic te petelki
		for(int j=0;j<maxItemX;j++){
			if (k<images.size()){
				Game::ivideo->draw2DImage(images.at(k),irr::core::position2d<irr::s32>(absX+(gap+itemWidth)*j,absY+(gap+itemHeight)*i),irr::core::rect<irr::s32>(0,0,itemWidth,itemHeight),0,irr::video::SColor(255,255,255,255),true);
				k++;
			}
			else{break;}
		}
	}
}

void ActiveElementGUI::drawElement(){
	for(int i=0;i<images.size();i++){
		if ((activeSizeX.size()>i)&&activeSizeX.at(i)!=0){cords2d.at(i)->visibleX=(int)(cords2d.at(i)->rozX*(*(activeSizeX.at(i))/100));}
		if ((activeSizeY.size()>i)&&activeSizeY.at(i)!=0){cords2d.at(i)->visibleY=(int)(cords2d.at(i)->rozY*(*(activeSizeY.at(i))/100));}
		Game::ivideo->draw2DImage(images.at(i), irr::core::position2d<irr::s32>(cords2d.at(i)->x,cords2d.at(i)->y),irr::core::rect<irr::s32>(0,0,cords2d.at(i)->visibleX,cords2d.at(i)->visibleY),0,irr::video::SColor(255,255,255,255), true);
	}
}

void TableGUI::setGap(int _gap){
	this->gap=_gap;
}

void TableGUI::setItemWidth(int _itemWidth){
	this->itemWidth=_itemWidth;
}

void TableGUI::setItemHeight(int _itemHeight){
	this->itemHeight=_itemHeight;
}

void TableGUI::setMaxItemX(int _maxItemX){
	this->maxItemX=_maxItemX;
}

void TableGUI::setMaxItemY(int _maxItemY){
	this->maxItemY=_maxItemY;
}

void ElementGUI::setGap(int _gap){
}

void ElementGUI::setItemWidth(int _itemWidth){
}

void ElementGUI::setItemHeight(int _itemHeight){
}

void ElementGUI::setMaxItemX(int _maxItemX){
}

void ElementGUI::setMaxItemY(int _maxItemY){
}

int ActiveElementGUI::addActiveX(int actX){
	if (actX<0){this->activeSizeX.push_back(0);}
	else{
		this->activeSizeX.push_back((Game::allObiekt->activeVelues.at(actX)));
	}
	return 0;
}

int ActiveElementGUI::addActiveY(int actY){
	if (actY<0){this->activeSizeY.push_back(0);}
	else{
		this->activeSizeY.push_back((Game::allObiekt->activeVelues.at(actY)));
	}
	return 0;
}
int ElementGUI::addActiveY(int actY){//sprawdzic cos takiego jak pure virtual
	return 0;
}
int ElementGUI::addActiveX(int actX){
	return 0;
}


void ElementGUI::loadFont(irr::gui::IGUIFont* font){
	this->font=font;
}

void MainGUI::drawGUI(){
	for(int i=0;i<listElement.size();i++){
		if(listElement.at(i)->type==0 || listElement.at(i)->type==this->allowedType||listElement.at(i)->type==10){//poprawic moment kiedy wyswietlany jest kursor
			//listElement.at(i)->Game::ivideo=this->Game::ivideo;
			listElement.at(i)->drawElement();
			listElement.at(i)->printText("");
		}
	}
}
void MainGUI::addElement(ElementGUI* elem){
	listElement.push_back(elem);
}
void ConsoleGUI::drawElement(){
	for(int i=0;i<images.size();i++){
		Game::ivideo->draw2DImage(images.at(i),irr::core::position2d<irr::s32>(cords2d.at(i)->x,cords2d.at(i)->y),irr::core::rect<irr::s32>(0,0,cords2d.at(i)->visibleX,cords2d.at(i)->visibleY),0,irr::video::SColor(128,255,255,255), true);
	}
}

void ConsoleGUI::printText(std::string textToPrint){
	ElementGUI::printText("");
	printConsole();
}

void ConsoleGUI::printConsole(){
	for(int i=0;i<visibleLines;i++){
		if (this->font!=0){
			irr::core::stringw str;
			if (Console::getLine(i)!=""){
				str=Console::getLine(i).c_str();
			}else{str=(this->text).c_str();}
			font->draw(str,irr::core::rect<s32>(absX+cords2d.at(0)->x,absY+cords2d.at(0)->y+i*(hudSize*2+10),300,50),video::SColor(255,255,255,255));//sparametryzowac wspolrzedne
		}
	}
}
void ConsoleGUI::setNumberLines(int _numLines){
	visibleLines=_numLines;
}
void ElementGUI::setNumberLines(int _numLines){

}

void GUIManager::addMainGui(MainGUI * _mainGUI){
	mainsGUI.push_back(_mainGUI);
}

MainGUI * GUIManager::getGUI(int num){
	//if (mainsGUI.size()>=)
	return mainsGUI.at(num);
}

void GUIManager::drawGUI(int num){
	Game::ivideo->beginScene( false, true, video::SColor( 255, 0, 10, 200 ) );
	getGUI(num)->drawGUI();
	Game::ivideo->endScene();
}
ScreenCordsTx::ScreenCordsTx(){
	xp="!";
	yp="!";
	x="!";
	y="!";

	rozX;
	rozY;
	visibleXp="!";
	visibleYp="!";
	visibleX="!";
	visibleY="!";
	aX="!";
	aY="!";
}