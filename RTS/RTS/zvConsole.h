#ifndef ZVCONSOLE_H
#define ZVCONSOLE_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//using namespace std;

class  Console{
private:
   static std::string outputFilePath;
   static std::vector<std::string> lines;
public:

   static void setOutputFilePath(std::string _outputFilePath);
   static void saveConsole(int numLine);
   static void writeTo(std::string line);
   static std::string getLine(int num);

};

#endif
