// OpenMpProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <windows.h>  
#include <iostream>
#include "FileWorker.h"
#include "MassWorker.h"
#include <time.h>
using namespace std;

void massShow(char** mass, int width, int height){
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			cout << mass[i][j];
		}
		cout << "\n";
	}
}

void main()
{
	FileWorker* fileWorker = new FileWorker("inFile.txt", "outFile.txt");
	MassWorker* massWorker = new MassWorker();
	char** newCharMass;
	clock_t start;
	int charCount = fileWorker->getFileCharactersCount();
	int width, height;
	for (int i = 0; i < sqrt(charCount) + 1; i++){
		for (int j = 0; j < sqrt(charCount)+1; j++){
			if (i*j >= charCount){
				width = i;
				height = j;
				break;
			}
		}
	}
	width = width * 2;
	height = height / 2;
	char** charMass = fileWorker->getMassFromFile(width, height);

	//massShow(charMass, width, height);

	fileWorker->cleanResultFile();

	for (int i = 1; i < 4; i++){
		start = clock();
		newCharMass = massWorker->massSortWithoutParallel(i, charMass, width, height);
		fileWorker->setResults("Without parallel", i, (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, -1, newCharMass);

		for (int i = 0; i < width; i++){
			delete[] newCharMass[i];
		}
		delete[]newCharMass;

		start = clock();
		newCharMass = massWorker->massSortWithParallel(i, charMass, width, height, 1);
		fileWorker->setResults("With parallel", i, (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, 1, newCharMass);

		for (int i = 0; i < width; i++){
			delete[] newCharMass[i];
		}
		delete[]newCharMass;

		for (int j = 5; j < 30; j += 10){
			start = clock();
			newCharMass = massWorker->massSortWithParallel(i, charMass, width, height, j);
			fileWorker->setResults("With parallel", i, (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, j, newCharMass);

			for (int i = 0; i < width; i++){
				delete[] newCharMass[i];
			}
			delete[]newCharMass;
		}
	}
	for (int i = 0; i < width; i++){
		delete[] charMass[i];
	}
	delete[]charMass;
	system("pause");
}


