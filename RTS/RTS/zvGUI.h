#ifndef ZVGUI_H
#define ZVGUI_H
//#include <irrlicht.h>
#include "zvGlobal.h"
#include <vector>
#include <string>
#include <iostream>
#include "zvObject.h"

//#include "Console.h"

//#include "zvSterowanie.h"//to jest zle za duzo polaczen miedzy modulami

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;

struct ScreenCords{
int x;
int y;
int rozX;
int rozY;
int visibleX;
int visibleY;
//int aX=-1;
//int aY=-1;
ScreenCords(int _x,int _y,int _rozX,int _rozY);
ScreenCords(int _x,int _y,int _rozX,int _rozY,int _visibleX,int _visibleY);
};
struct ScreenCordsTx{
    std::string xp;
    std::string yp;
    std::string x;
    std::string y;

    std::string rozX;
    std::string rozY;
    std::string visibleXp;
    std::string visibleYp;
    std::string visibleX;
    std::string visibleY;
    std::string aX;
    std::string aY;
	ScreenCordsTx();
};
class ElementGUI{
    public:
    int type;
    int absX;
    int absY;
    int absXp;
    int absYp;
    int txCordX;
    int txCordY;
    int txCordXp;
    int txCordYp;
    int hudSize;
    std::string text;
    std::vector<std::string> imagePaths;
    irr::video::IVideoDriver * ivideo;
    std::vector<irr::video::ITexture*> images;
    std::vector<ScreenCords*> cords2d;
    std::vector<ScreenCordsTx*> cords2dTx;
    std::string pathFont;
    irr::gui::IGUIFont* font;

    void addImage(int x,int y,int rozX,int rozY,std::string path,int aX,int aY,int vX,int vY);
    void addImage(int x,int y,int rozX,int rozY,irr::video::ITexture* image,int aX,int aY,int vX,int vY);
    void loadFont(irr::gui::IGUIFont* font);
    virtual void drawElement(void);
    virtual void printText(std::string textToPrint);
    virtual void setGap(int _gap);
    virtual void setItemWidth(int _itemWidth);
    virtual void setItemHeight(int _itemHeight);
    virtual void setMaxItemX(int _maxItemX);
    virtual void setNumberLines(int _numLines);
    virtual void setMaxItemY(int _maxItemY);
    virtual int addActiveX(int actX);
    virtual int addActiveY(int actY);
    ElementGUI();
};
class TableGUI:public ElementGUI{
    public:
    int gap;
    int itemWidth;
    int itemHeight;
    int maxItemX;
    int maxItemY;
    virtual void setGap(int _gap);
    virtual void setItemWidth(int _itemWidth);
    virtual void setItemHeight(int _itemHeight);
    virtual void setMaxItemX(int _maxItemX);
    virtual void setMaxItemY(int _maxItemY);
    virtual void drawElement(void);
    TableGUI();
};
class ActiveElementGUI:public ElementGUI{
    public:
//ListObject *allObiekty;
ActiveElementGUI();

std::vector<double *> activeSizeX;
std::vector<double *> activeSizeY;
virtual void drawElement(void);
virtual int addActiveX(int actX);
virtual int addActiveY(int actY);
};
class PlayerElementGUI:public ActiveElementGUI{
public:
Player *player;
virtual void drawElement(void);
PlayerElementGUI();
};
class CursorGUI:public ElementGUI{
public:
int cordX,cordY;
//Control * klawiatura;
virtual void drawElement(void);
//CursorGUI(irr::video::IVideoDriver * _ivideo,Control * _klawiatura);
CursorGUI();
void updateCords(int x,int y);
};
class MainGUI{
public:
    int allowedType;
  //  irr::video::IVideoDriver * ivideo;
  //  irr::IrrlichtDevice *device;
    std::vector<ElementGUI*> listElement;
  //  ListObject *allObiekt;
void drawGUI();
void addElement(ElementGUI* elem);
void loadGUI(void);
void refreshItems(Plecak* plecak);
MainGUI();
};
class ConsoleGUI:public ElementGUI{
public:
    int visibleLines;
    virtual void drawElement(void);
    virtual void printText(std::string textToPrint);
    virtual void setNumberLines(int _numLines);
    void printConsole();
    ConsoleGUI(int _visibleLines=12);
};
class Cursor{
private:
   static int x;
   static int y;
   static CursorGUI * kursorGUI;
public:
   static void setCursorGUI(CursorGUI * _cursorGUI);
   static void updateCursor(int _x,int _y);
};
class GUIManager{
private:
   //static Console * konsola;//nie potrzebne bo dconsola i tak jest statyczna
   vector<MainGUI*> mainsGUI;
   Cursor * kursor;
public:
   void addMainGui(MainGUI * _mainGUI);
   void setCursor(Cursor * _Cursor);
   MainGUI * getGUI(int num);
   void drawGUI(int num);

};
#endif
