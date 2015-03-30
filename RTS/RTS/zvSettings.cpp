#include "zvSettings.h"
//poprawic nazwe pliku bo jest zla
Settings::Settings(){
}
int Settings::getHudSizeI(){
	//te ustawienia tez pozniej wczytac z pliku
	//a jak nie to mozna to zpotymalziowac pierwszego ifa da sie usunac
	if(hudSizeTx=="S"){return 1;}
	else if(hudSizeTx=="M"){return 2;}
	else if(hudSizeTx=="L"){return 3;}
	else if(hudSizeTx=="X"){return 4;}
	return 1;
}
