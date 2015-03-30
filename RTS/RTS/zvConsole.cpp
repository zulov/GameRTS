#include "zvConsole.h"

std::string Console::outputFilePath;
std::vector<std::string> Console::lines;
void Console::setOutputFilePath(std::string _outputFilePath){
	outputFilePath=_outputFilePath;
}

void Console::saveConsole(int numLine){
	std::fstream logFile;
	logFile.open( outputFilePath.c_str(),  std::ios::out );
	if (numLine<=0 || numLine>Console::lines.size()){numLine=Console::lines.size();}
	if( logFile.good() == true ){
		std::cout << "Uzyskano dostep do pliku!" << std::endl;

		for(int i=Console::lines.size()-numLine;i<Console::lines.size();i++){
			logFile<<i;
			logFile<<">> ";
			logFile<<Console::lines.at(i);
			logFile<<std::endl;
		}
	} else {std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;}
	logFile.close();
}


std::string Console::getLine(int num){
	int tempIndex=lines.size()-num-1;

	if (tempIndex>0 || Console::lines.size()>tempIndex){
		return ">> "+(Console::lines).at(tempIndex);
	}else{return "";}
	return "";
}
void Console::writeTo(std::string line){
	Console::lines.push_back(line);
}


