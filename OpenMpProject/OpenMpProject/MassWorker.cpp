#include "stdafx.h"
#include "MassWorker.h"
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <omp.h>
using namespace std;


MassWorker::MassWorker()
{
}


MassWorker::~MassWorker()
{
}

/*���������� � ������� ������*/
char** MassWorker::massSortWithoutParallel(int sortType, char** charMass, int width, int height){
	char** newCharMass = new char *[width];
	for (int i = 0; i < width; i++)
	{
		newCharMass[i] = new char[height];
	}

	switch (sortType)
	{
		case 1:
			//�� �������
			for (int i = 0; i < width; i++){
				for (int j = 0; j < height; j++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9' ){
						newCharMass[i][j] = charMass[i][j];
					}
					else{
						newCharMass[i][j] = NULL;
					}
				}
			}
			break;
		case 2:
			//�� ��������
			for (int j = 0; j < height; j++){
				for (int i = 0; i < width; i++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9'){
						newCharMass[i][j] = charMass[i][j];
					}
					else {
						newCharMass[i][j] = NULL;
					}
				}
			}
			break;
		case 3:
			//�� ������
			for (int i = 0; i < width/2; i++){
				for (int j = 0; j < height; j++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9'){
						newCharMass[i][j] = charMass[i][j];
					}
					else{
						newCharMass[i][j] = NULL;
					}
				}
			}
			for (int i = width / 2; i < width; i++){
				for (int j = 0; j < height; j++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9'){
						newCharMass[i][j] = charMass[i][j];
					}
					else{
						newCharMass[i][j] = NULL;
					}
				}
			}
			break;
		default:
			break;
	}
	
	return newCharMass;
}

/*���������� � ������������������*/
char** MassWorker::massSortWithParallel(int sortType, char** charMass, int width, int height, int schedule){
	char** newCharMass = new char *[width];
	for (int i = 0; i < width; i++)
	{
		newCharMass[i] = new char[height];
	}
	int i, j;

	switch (sortType)
	{
	case 1:
		//�� �������
		#pragma omp parallel for private(i, j) schedule(dynamic, schedule)
			for (i = 0; i < width; i++){
				for (j = 0; j < height; j++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9'){
						newCharMass[i][j] = charMass[i][j];
					}
					else {
						newCharMass[i][j] = NULL;
					}
				}
			}
		break;
	case 2:
		//�� ��������
		for (int i = 0; i < width; i++){
		#pragma omp parallel for private(j) schedule(dynamic, schedule)
			for (j = 0; j < height; j++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9'){
						newCharMass[i][j] = charMass[i][j];
					}
					else {
						newCharMass[i][j] = NULL;
					}
				}
			}
		break;
	case 3:
		//�� ������
		omp_set_nested(true);
		#pragma omp parallel for private(i,j) schedule(dynamic, schedule)
			for (i = 0; i < width; i++){
				#pragma omp parallel for private(j) schedule(dynamic, schedule)
				for (j = 0; j < height; j++){
					if ('0' > charMass[i][j] || charMass[i][j] > '9'){
						newCharMass[i][j] = charMass[i][j];
					}
					else{
						newCharMass[i][j] = NULL;
					}
				}
			}
		break;
	default:
		break;
	}

	return newCharMass;
}
