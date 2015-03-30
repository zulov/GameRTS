#ifndef ZVSETTINGS_H
#define ZVSETTINGS_H
#include <fstream>
#include <string>
class Settings{
public:
int qShadow;
unsigned int heightRes;
unsigned int weidthRes;
unsigned int colorDepth;
bool fullScreen;
bool vSync;
bool stencil;
std::string hudSize;
std::string hudSizeTx;
std::string consoleOutputPath;
int getHudSizeI();
Settings();
};



#endif
