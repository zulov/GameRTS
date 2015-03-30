
#include <cstdlib>
#include <fstream>

#include "zvLoader.h"
#include "zvGame.h"
SettLoader::SettLoader(std::string _path){
	path=_path;
}
Loader::Loader(){
	//sett=Game::settStart;
}
//Loader::Loader(Settings *_sett){
//sett=Game::settStart;
//}
ObjectLoader::ObjectLoader(std::string _path){
	path=_path;
}
GUIMainLoader::GUIMainLoader(std::string _path,MainGUI *_mainGUI){
	path=_path;
	mainGUI=_mainGUI;
}
ObjectMainLoader::ObjectMainLoader(std::string _path){
	path=_path;
}
PlayerLoader::PlayerLoader(std::string _path){
	path=_path;
}
GUILoader::GUILoader(std::string _path,ElementGUI *_elemGUI){
	path=_path;
	elemGUI=_elemGUI;
	amount=0;
}
MapLoader::MapLoader(std::string _path){
	path=_path;
}

std::string replaceChar(std::string napis,char ch,char repCh){
	std::cout<<napis<<std::endl;
	std::replace( napis.begin(), napis.end(), ch, repCh);
	return napis;
}
int SettLoader::loadStartSetting(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		// std::string sNull;
		std::cout << "> Uzyskano dostep do pliku z ustawiniami!" << std::endl;
		Console::writeTo("> Uzyskano dostep do pliku z ustawiniami!" );
		while (!plik.eof()){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}
		plik.close();
	}else{ std::cout << "error> problem z plikiem ustawieñ!" << std::endl;
	Console::writeTo("error> problem z plikiem ustawieñ! ("+ path+")" );
	return -1;}
	return 0;
}
int PlayerLoader::loadPlayer(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		//  std::string sNull;
		std::cout << "> Uzyskano dostep do pliku parametrami gracza!" << std::endl;
		Console::writeTo("> Uzyskano dostep do pliku parametrami gracza!" );
		while (!plik.eof()){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}
		plik.close();
	}else{ std::cout << "error> problem z plikiem paramaetrów gracza!" << std::endl;
	Console::writeTo("error> problem z plikiem paramaetrów gracza! (" + path +")");
	return -1;}
	return 0;
}
std::string Loader::getKey(std::string dane){
	std::string key;
	for(int i=0;i<dane.length();i++){
		if (dane[i]!='='){
			key+=dane[i];
		}else{return key;}
	}
	return key;
}
void Loader::setKey(std::string key,std::string value){
}
std::string Loader::getValue(std::string dane){
	std::string value;
	int i=0;
	for(;i<dane.length();i++){
		if (dane[i]=='='){i++;break;}
	}
	for(;i<dane.length();i++){
		if (dane[i]!=';'){
			value+=dane[i];
		}else{return value;}
	}
	return value;
}
double Loader::getKomaValue(std::string dane,int num){
	std::string value;
	int i=0;
	int numFound=1;
	for (int j=1;j<num;j++){
		for(;i<dane.length();i++){
			if (dane[i]==','){i++;numFound++;break;}
		}
	}

	if(numFound!=num){i=0;}//tu dac zeby wczytywal tylko statni a nie pierwszy chyba
	for(;i<dane.length();i++){
		if (dane[i]!=';' &&dane[i]!=','){
			value+=dane[i];
		}else{return atof(value.c_str());}
	}
	return atof(value.c_str());
}
int GUIMainLoader::loadGUI(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		std::cout << "> Uzyskano dostep do pliku gui!" << std::endl;
		Console::writeTo("> Uzyskano dostep do pliku gui!" );
		//to poprawic zeby wczytywalo tylko amount
		while (!plik.eof()){

			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}

		plik.close();
	}else{ std::cout << "error> problem z plikiem gui! (" << path <<")" << std::endl;
	Console::writeTo("error> problem z plikiem gui! (" + path +")");
	return -1;}

	return 0;
}
void GUIMainLoader::setKey(std::string key,std::string value){
	if (key=="path"||key=="pathA"||key=="pathT"||key=="pathC"||key=="pathM"){
		ElementGUI *elemGUI;
		if (key=="pathA"){
			elemGUI=new ActiveElementGUI();
		}else if(key=="pathT"){
			elemGUI=new TableGUI();
		}else if(key=="pathM"){
			CursorGUI * kursorGui= new CursorGUI();
			elemGUI=kursorGui;
			Cursor::setCursorGUI(kursorGui);
		}else if(key=="pathC"){
			elemGUI=new ConsoleGUI();
		}else{
			elemGUI=new ElementGUI();
		}
		elemGUI->hudSize=Game::settStart->getHudSizeI();
		GUILoader *elemGUILoad=new GUILoader(value,elemGUI);
		elemGUILoad->loadGUI();
		char repChar=Game::settStart->hudSizeTx.c_str()[0];

		for(int i=0;i<elemGUI->imagePaths.size();i++){//to mozna wciepnac w jednego fora z tym ponizej
			std::replace( elemGUI->imagePaths.at(i).begin(), elemGUI->imagePaths.at(i).end(), '*', repChar);
		}

		for(int i=0;i<elemGUI->cords2dTx.size();i++){
			double sizeX=getKomaValue(elemGUI->cords2dTx.at(i)->rozX,Game::settStart->getHudSizeI());
			double sizeY=getKomaValue(elemGUI->cords2dTx.at(i)->rozY,Game::settStart->getHudSizeI());
			double cx;
			double cy;
			double vx;
			double vy;
			int aX=-1;
			int aY=-1;
			if (elemGUI->cords2dTx.at(i)->x!="!"){//tu dac jeszcze zeby bralo z koma walu a nie pierwsze
				cx=atof(elemGUI->cords2dTx.at(i)->x.c_str());
			}else{
				cx=(atof(elemGUI->cords2dTx.at(i)->xp.c_str())/100)*Game::settStart->weidthRes;
			}
			if (elemGUI->cords2dTx.at(i)->y!="!"){
				cy=atof(elemGUI->cords2dTx.at(i)->y.c_str());
			}else{
				cy=(atof(elemGUI->cords2dTx.at(i)->yp.c_str())/100)*Game::settStart->heightRes;
			}
			if (elemGUI->cords2dTx.at(i)->visibleX!="!"){
				vx=atof(elemGUI->cords2dTx.at(i)->visibleX.c_str());
			}else if (elemGUI->cords2dTx.at(i)->visibleXp!="!"){
				vx=(atof(elemGUI->cords2dTx.at(i)->visibleXp.c_str())/100)*sizeX;
			}else{
				vx=sizeX;
			}
			if (elemGUI->cords2dTx.at(i)->visibleY!="!"){
				vy=atof(elemGUI->cords2dTx.at(i)->visibleY.c_str());
			}else if (elemGUI->cords2dTx.at(i)->visibleYp!="!"){
				vy=(atof(elemGUI->cords2dTx.at(i)->visibleYp.c_str())/100)*sizeY;
			}else{
				vy=sizeY;
			}

			if(elemGUI->cords2dTx.at(i)->aY!="!"){
				aY=atoi((elemGUI->cords2dTx.at(i)->aY).c_str());
			}
			if(elemGUI->cords2dTx.at(i)->aX!="!"){
				aX=atoi((elemGUI->cords2dTx.at(i)->aX).c_str());
			}
			elemGUI->addImage((int)cx+elemGUI->absX,(int)cy+elemGUI->absY,(int)sizeX,(int)sizeY,elemGUI->imagePaths.at(i),aX,aY,(int)vx,(int)vy);
		}
		if(elemGUI->pathFont!="!"){
			std::replace( elemGUI->pathFont.begin(), elemGUI->pathFont.end(), '*', repChar);
			elemGUI->loadFont(Game::device->getGUIEnvironment()->getFont(elemGUI->pathFont.c_str()));
		}
		this->mainGUI->addElement(elemGUI);
	}


}
int GUILoader::loadGUI(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		std::cout << "> Uzyskano dostep do pliku gui! ("<<path<<")" <<std::endl;
		Console::writeTo("> Uzyskano dostep do pliku gui! ("+path+")");
		//to poprawic zeby wczytywalo tylko amount
		while (!plik.eof()&&amount==0){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value,-1);
		}
		//to chyba nie potrzebme ale to sie kiedys sprawdzi zobacze jak wyjdzie
		int i1=0;
		int i2=0;
		int i3=0;
		int i4=0;
		int i5=0;
		int i6=0;
		int i7=0;
		int i8=0;
		int i9=0;
		int i10=0;
		int i11=0;
		int i12=0;
		int i13=0;
		while (!plik.eof()&&amount!=0){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);//pewnie niepotrzebne sa te ify bo i tak pozniej sa
			if(key=="path"&&i1<amount){this->setKey(key,value,i1);i1++;}/// dodac  tu elsy
			else if(key=="sizeX"&&i2<amount){this->setKey(key,value,i2);i2++;}
			else if(key=="sizeY"&&i3<amount){this->setKey(key,value,i3);i3++;}
			else if(key=="posX%"&&i4<amount){this->setKey(key,value,i4);i4++;}
			else if(key=="posX"&&i5<amount){this->setKey(key,value,i5);i5++;}
			else if(key=="posY"&&i6<amount){this->setKey(key,value,i6);i6++;}
			else if(key=="posY%"&&i7<amount){this->setKey(key,value,i7);i7++;}
			else if(key=="visX%"&&i8<amount){this->setKey(key,value,i8);i8++;}
			else if(key=="visY%"&&i9<amount){this->setKey(key,value,i9);i9++;}
			else if(key=="visX"&&i10<amount){this->setKey(key,value,i10);i10++;}
			else if(key=="visY"&&i11<amount){this->setKey(key,value,i11);i11++;}
			else if(key=="aX"&&i12<amount){this->setKey(key,value,i12);i12++;}
			else if(key=="aY"&&i13<amount){this->setKey(key,value,i13);i13++;}
			else if(key=="type"){this->setKey(key,value,-1);}
			else if(key=="activeValueX"){this->setKey(key,value,-1);}
			else if(key=="activeValueY"){this->setKey(key,value,-1);}
			else if(key=="absX"){this->setKey(key,value,-1);}
			else if(key=="absY"){this->setKey(key,value,-1);}
			else if(key!=""&&value!=""){this->setKey(key,value,-1);}
		}
		plik.close();
	}else{ std::cout << "error> problem z plikiem gui!" << "("<<path<<")" << std::endl;
	Console::writeTo("error> problem z plikiem gui! ("+path+")");
	return -1;}
	return 0;
}
int Loader::load(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		std::cout << "> "<<successMsg<< " ("<<path<<")" <<std::endl;
		Console::writeTo("> "+successMsg+ " ("+path+')' );
		while (!plik.eof()){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}
		plik.close();
	}else{  std::cout << "error> "<<failureMsg<< " ("<<path<<")" <<std::endl;
	Console::writeTo("error> "+failureMsg+ " ("+path+')' );}
	return 0;
}
int ObjectLoader::load(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		std::cout << "> Uzyskano dostep do pliku wlasciwosci obiektu " << "("<<path<<")" <<std::endl;
		Game::allObiekt->loadedObject.push_back(new ObjectProperties());
		while (!plik.eof()){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}
		plik.close();
	}else{ std::cout << "error> problem z plikiem wlasciwosci obiektu!" << "("<<path<<")" << std::endl;
	Console::writeTo("error> problem z plikiem wlasciwosci obiektu!" + '('+path+')');}
	return 0;
}
void ObjectLoader::setKey(std::string key,std::string value){
	std::cout<<key<<" "<<value<<std::endl;
	if (key=="name"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->name=value;}
	else if(key=="type"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->type=value;}
	else if(key=="opis"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->opis=value;}
	else if(key=="id"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->id=atoi(value.c_str());}
	else if(key=="meshPath"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->meshPath=value;}
	else if(key=="texturePath"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->texturePath=value;}
	else if(key=="iconPath"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->iconPath=replaceChar(value,'*',Game::settStart->hudSizeTx.c_str()[0]);}
	else if(key=="alive"){if(value=="true"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->alive=true;}
	else{(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->alive=false;}}
	else if(key=="actionAble"){if(value=="true"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->actionAble=true;}
	else{(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->actionAble=false;}}
	else if(key=="attackAble"){if(value=="true"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->attackAble=true;}
	else{(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->attackAble=false;}}
	else if(key=="takeAble"){if(value=="true"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->takeAble=true;}
	else{(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->takeAble=false;}}
	else if(key=="endurace"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->endurace=atof(value.c_str());}
	else if(key=="waga"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->waga=atof(value.c_str());}
	else if(key=="kCal"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->kCal=atof(value.c_str());}
	else if(key=="poison"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->poison=atof(value.c_str());}
	else if(key=="fresh"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->fresh=atof(value.c_str());}
	else if(key=="staticFriction"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->staticFriction=atof(value.c_str());}
	else if(key=="kineticFriction"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->kineticFriction=atof(value.c_str());}
	else if(key=="coefficientOfRestitution"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->coefficientOfRestitution=atof(value.c_str());}
	else if(key=="surface"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->surface=atof(value.c_str());}
	else if(key=="radius"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->radius=atof(value.c_str());}
	else if(key=="collision"){(Game::allObiekt->loadedObject.at(Game::allObiekt->loadedObject.size()-1))->collision=value;}
	else{std::cout << "warning> nieznany klucz!" <<"("<<key<<")" <<std::endl;
	Console::writeTo("warning> nieznany klucz!" + ' (' + key + ')');}

}
void GUILoader::setKey(std::string key,std::string value,int i_n){
	if (key=="amount"){this->amount=atoi(value.c_str());}
	else if(amount!=0){
		//  std::cout<<key<<" "<<value<<std::endl;
		if (elemGUI->cords2dTx.size()<i_n+1){ScreenCordsTx *tempCTx=new ScreenCordsTx();
		elemGUI->cords2dTx.push_back(tempCTx);}

		if (key=="path"){elemGUI->imagePaths.push_back(value);}
		else if(key=="sizeX"){elemGUI->cords2dTx.at(i_n)->rozX=value;}
		else if(key=="sizeY"){elemGUI->cords2dTx.at(i_n)->rozY=value;}
		else if(key=="posX%"){elemGUI->cords2dTx.at(i_n)->xp=value;}
		else if(key=="posY%"){elemGUI->cords2dTx.at(i_n)->yp=value;}
		else if(key=="posX"){elemGUI->cords2dTx.at(i_n)->x=value;}
		else if(key=="posY"){elemGUI->cords2dTx.at(i_n)->y=value;}
		else if(key=="visX%"){elemGUI->cords2dTx.at(i_n)->visibleXp=value;}
		else if(key=="visY%"){elemGUI->cords2dTx.at(i_n)->visibleYp=value;}
		else if(key=="visX"){elemGUI->cords2dTx.at(i_n)->visibleX=value;}
		else if(key=="visY"){elemGUI->cords2dTx.at(i_n)->visibleY=value;}
		else if(key=="type"){elemGUI->type=atoi(value.c_str());}
		else if(key=="activeValueX"){elemGUI->addActiveX(atoi(value.c_str()));}
		else if(key=="activeValueY"){elemGUI->addActiveY(atoi(value.c_str()));}
		else if(key=="gap"){elemGUI->setGap(getKomaValue(value,Game::settStart->getHudSizeI()));}
		else if(key=="itemWidth"){elemGUI->setItemWidth(getKomaValue(value,Game::settStart->getHudSizeI()));}
		else if(key=="itemHeight"){elemGUI->setItemHeight(getKomaValue(value,Game::settStart->getHudSizeI()));}
		else if(key=="maxItemX"){elemGUI->setMaxItemX(atoi(value.c_str()));}
		else if(key=="maxItemY"){elemGUI->setMaxItemY(atoi(value.c_str()));}
		else if(key=="absX"){elemGUI->absX=getKomaValue(value,Game::settStart->getHudSizeI());}
		else if(key=="absY"){elemGUI->absY=getKomaValue(value,Game::settStart->getHudSizeI());}
		else if(key=="aX"){elemGUI->cords2dTx.at(i_n)->aX=(atoi(value.c_str()));}
		else if(key=="aY"){elemGUI->cords2dTx.at(i_n)->aY=(atoi(value.c_str()));}
		else if(key=="pathFont"){elemGUI->pathFont=value;}
		else if(key=="numberLines"){elemGUI->setNumberLines(getKomaValue(value.c_str(),Game::settStart->getHudSizeI()));}
		else if(key=="txCordX"){elemGUI->txCordX=(int)getKomaValue(value,Game::settStart->getHudSizeI());}
		else if(key=="txCordY"){elemGUI->txCordY=(int)getKomaValue(value,Game::settStart->getHudSizeI());}
		else{std::cout << "warning> nieznany klucz!" <<"("<<key<<")" <<std::endl;
		Console::writeTo("warning> nieznany klucz!" + ' (' + key + ')');}
	}

}
void SettLoader::setKey(std::string key,std::string value){
	if (key=="qShadow"){Game::settStart->qShadow=atoi(value.c_str());}
	else if (key=="heightresolution"){Game::settStart->heightRes=atoi(value.c_str());}
	else if (key=="weidthresolution"){Game::settStart->weidthRes=atoi(value.c_str());}
	else if (key=="colordepth"){Game::settStart->colorDepth=atoi(value.c_str());}
	else if (key=="fullscreen"){if (value=="true"){Game::settStart->fullScreen=true;}else{Game::settStart->fullScreen=false;}}
	else if (key=="vsync"){if (value=="true"){Game::settStart->vSync=true;}else{Game::settStart->vSync=false;}}
	else if (key=="stencil"){if (value=="true"){Game::settStart->stencil=true;}else{Game::settStart->stencil=false;}}
	else if (key=="outputFilePath"){Game::settStart->consoleOutputPath=value;}

	else if (key=="hudsize"){
		if (value=="small"){Game::settStart->hudSize="16";Game::settStart->hudSizeTx="S";}
		else if(value=="medium"){Game::settStart->hudSize="24";Game::settStart->hudSizeTx="M";}
		else if(value=="big"){Game::settStart->hudSize="36";Game::settStart->hudSizeTx="L";}
		else if(value=="extra"){Game::settStart->hudSize="48";Game::settStart->hudSizeTx="X";}
		//else{Game::settStart->hudSize="24";Game::settStart->hudSizeTx="M";}
		else{Game::settStart->hudSize="24";Game::settStart->hudSizeTx=value;}
	}
	else{std::cout << "warning> nieznany klucz!" <<"("<<key<<")" <<std::endl;
	Console::writeTo("warning> nieznany klucz!" + ' (' + key + ')');}

}
void PlayerLoader::setKey(std::string key,std::string value){
	if (key=="position"){
		Game::player->bodyFiz->position=Vector(getKomaValue(value,1),getKomaValue(value,2),getKomaValue(value,3));}
	else if (key=="rotation"){Game::player->bodyFiz->rotation=Vector(getKomaValue(value,1),getKomaValue(value,2),getKomaValue(value,3));}
	else if (key=="fizObject"){
		if (true){PhysicSphere* obSphere = dynamic_cast<PhysicSphere*>(Game::player->bodyFiz);
		obSphere->radius=getKomaValue(value,2);}
	}
	else if (key=="mesh"){Game::player->meshPath=value;}
	else if (key=="texture"){Game::player->texturePath=value;}
	else if (key=="movementForce"){Game::player->bodyFiz->maxSpeed=atof(value.c_str());;}
	else if (key=="jumpForce"){Game::player->bodyFiz->jumpForce=atof(value.c_str());}
	else if (key=="mass"){Game::player->bodyFiz->mass=atof(value.c_str());}
	else if (key=="gravitation"){Game::player->bodyFiz->grav=Vector(getKomaValue(value,1),getKomaValue(value,2),getKomaValue(value,3));}
	else if (key=="inertia"){Game::player->bodyFiz->inertia=atof(value.c_str());}
	else if (key=="staticFriction"){Game::player->bodyFiz->staticFriction=atof(value.c_str());}
	else if (key=="kineticFriction"){Game::player->bodyFiz->kineticFriction=atof(value.c_str());}
	else if (key=="restitution"){Game::player->bodyFiz->restitution=atof(value.c_str());}
	else if (key=="HP"){Game::player->HP=atof(value.c_str());}
	else if (key=="maxLoad"){Game::player->maxLoad=atof(value.c_str());}
	else if (key=="rAction"){Game::player->rAction=atof(value.c_str());}
	else if (key=="rAttack"){Game::player->rAttack=atof(value.c_str());}
	else if (key=="atak"){Game::player->atak=atof(value.c_str());}
	else if (key=="defense"){Game::player->defense=atof(value.c_str());}
	else if (key=="strength"){Game::player->strength=atof(value.c_str());}
	else if (key=="regeneration"){Game::player->regeneration=atof(value.c_str());}
	else if (key=="turnForce"){Game::player->bodyFiz->turnForce=Vector(getKomaValue(value,1),getKomaValue(value,2),getKomaValue(value,3));}

}
int ObjectMainLoader::load(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		std::cout << "> Uzyskano dostep do pliku z lista obiektow!" << std::endl;
		Console::writeTo("> Uzyskano dostep do pliku z lista obiektow!" );
		while (!plik.eof()){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}

		plik.close();
	}else{ std::cout << "error> problem z plikiem z listami obiektow!" << std::endl;
	Console::writeTo("error> problem z plikiem z listami obiektow!" + ' (' + path + ')');
	return -1;}
}
void ObjectMainLoader::setKey(std::string key,std::string value){
	if (key=="path"){
		ObjectLoader *objLoad;
		if(Game::settStart!=0){objLoad= new ObjectLoader(value);}
		else{objLoad= new ObjectLoader(value);}

		objLoad->load();
	}else{std::cout << "warning> nieznany klucz!" <<"("<<key<<")" <<std::endl;
	Console::writeTo("warning> nieznany klucz! (" + key + ')');
	}

}
int MapLoader::load(){
	std::fstream plik;
	plik.open( path.c_str(), std::ios::in );
	if( plik.good() )
	{
		std::string dane;
		std::string key;
		std::string value;
		std::cout << "> Uzyskano dostep do pliku z mapa! " << path  << std::endl;
		Console::writeTo("> Uzyskano dostep do pliku z lista obiektow!"+ ' (' + path + ')' );

		while (!plik.eof()){
			getline( plik, dane );
			if (dane[0]=='#'){continue;}
			key=this->getKey(dane);
			value=this->getValue(dane);
			this->setKey(key,value);
		}

		plik.close();
	}else{ std::cout << "error> problem z plikiem z mapą! "<< path << std::endl;
	Console::writeTo("error> problem z plikiem z mapą!" + ' (' + path + ')');
	return -1;}
}
void MapLoader::setKey(std::string key,std::string value){
	if (key=="path"){//laduje wlasciwosci potrzebnych plików
		ObjectMainLoader *objMainLoad;
		objMainLoad= new ObjectMainLoader(value);
		objMainLoad->load();
	}else if(key=="id"){}//trzeba stworzyc obiekt i dodac go do sceny
	else if(key=="position"){}
	else{std::cout << "warning> nieznany klucz!" <<"("<<key<<")" <<std::endl;
	Console::writeTo("warning> nieznany klucz! (" + key + ')');
	}

}

void updateLoadBar(MainGUI * mainGUI,video::IVideoDriver * ivideo,double*loadBar,double var){
	ivideo->beginScene( true, true, video::SColor( 255, 0, 10, 200 ) );
	*loadBar=*loadBar+var;
	mainGUI->drawGUI();
	ivideo->endScene();
}
