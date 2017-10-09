#pragma once
class MassWorker
{
public:
	MassWorker();
	~MassWorker();
	char** massSortWithParallel(int sortType, char** charMass, int width, int height, int schedule);
	char** massSortWithoutParallel(int sortType, char** charMass, int width, int height);
};

