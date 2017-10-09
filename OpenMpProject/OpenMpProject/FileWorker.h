#pragma once
#include <string>

class FileWorker
{
public:
	FileWorker(std::string pFileForRead, std::string pFileForWrite);
	~FileWorker();
	int getFileCharactersCount();
	char** getMassFromFile(int pWidth, int pHeight);
	void setResults(std::string parallelTypeString, int parallelType, double time, int shedule, char** newCharMass);
	void cleanResultFile();
private:
	std::string fileForRead;
	std::string fileForWrite;
	char** charMass;
	int width;
	int height;
};

