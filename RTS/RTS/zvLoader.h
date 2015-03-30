#ifndef ZVLOADER_H
#define ZVLOADER_H

#include "zvGUI.h"
#include <iostream>
#include <algorithm>
#include <string>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//funkcje loadujace zmienic na ta sama dziedziczona bo nie ma nraczej roznicy
class Control;
void __cdecl loadThread( void * Args );
void updateLoadBar(MainGUI * mainGUI,video::IVideoDriver * ivideo,double*loadBar,double var);
std::string replaceChar(std::string napis,char ch,char repCh);
class Loader{
    public:
std::string successMsg;
std::string failureMsg;
std::string path;
std::string getKey(std::string dane);
virtual void setKey(std::string key,std::string value);
std::string getValue(std::string dane);
double getKomaValue(std::string dane,int num);
virtual int load();
Loader();

};
class SettLoader:public Loader{
    public:
SettLoader(std::string _path);
int loadStartSetting();
virtual void setKey(std::string key,std::string value);
};
class ObjectLoader:public Loader{
    public:
//ListObject *allObiekt;
ObjectLoader(std::string _path);
virtual int load();
virtual void setKey(std::string key,std::string value);
};
class PlayerLoader:public Loader{
public:
//Player * player;
PlayerLoader(std::string _path);
int loadPlayer();
virtual void setKey(std::string key,std::string value);
};
class GUILoader:public Loader{
public:
int amount;
ElementGUI *elemGUI;
GUILoader(std::string _path,ElementGUI *_elemGUI);
int loadGUI();
void setKey(std::string key,std::string value,int i_n);
};
class GUIMainLoader:public Loader{
    public:
MainGUI *mainGUI;
int loadGUI();
GUIMainLoader(std::string _path,MainGUI *_mainGUI);
virtual void setKey(std::string key,std::string value);
};
class ObjectMainLoader:public Loader{
public:
//ListObject *allObiekt;
virtual int load();
ObjectMainLoader(std::string _path);
virtual void setKey(std::string key,std::string value);
};
class MapLoader:public Loader{
 public:
//ListObject *allObiekt;
virtual int load();
MapLoader(std::string _path);
virtual void setKey(std::string key,std::string value);
};
#endif
