#include "stdafx.h"
#include "FileWorker.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*В конструктор передаем файл, содержащий входные данные и файл для сохранения выходных данных*/
FileWorker::FileWorker(string pFileForRead, string pFileForWrite)
{
	fileForRead = pFileForRead;
	fileForWrite = pFileForWrite;
}


FileWorker::~FileWorker()
{
	//очистка динамического массива
	for (int i = 0; i < width; i++){
		delete[] charMass[i];
	}
	delete[]charMass;
}

void FileWorker::cleanResultFile(){
	ofstream myfile;

	myfile.open(fileForWrite);

	if (myfile.is_open()){
		myfile << "";
		myfile.close();
	}
}

/*Возвращает количество символов, содержащихся в файле*/
int FileWorker::getFileCharactersCount(){
	int count = 0;
	ifstream myfile;
	char c;
	myfile.open(fileForRead);
	if (myfile.is_open())
	{
		while (myfile.get(c))
		{
			count ++;
		}
		myfile.close();
	}
	return count;
}

/*Чтение файла и сохранение всех данных в массив символов*/
char** FileWorker::getMassFromFile(int pWidth, int pHeight){
	width = pWidth;
	height = pHeight;
	ifstream myfile;
	char c;
	charMass = new char *[width];
	for (int i = 0; i < width; i++)
	{
		charMass[i] = new char[height];
	}

	myfile.open(fileForRead);
	if (myfile.is_open())
	{
		for (int i = 0; i < width; i++){
			for (int j = 0; j < height; j++){
				if (myfile.get(c))
				{
					charMass[i][j] = c;
				}
				else {
					charMass[i][j] = NULL;
				}
			}
		}
		myfile.close();
	}
	myfile.close();
	return charMass;
}

/*Запись результатов в файл*/
void FileWorker::setResults(string parallelTypeString, int parallelType, double time, int shedule, char** newCharMass){
	string prevData = "";
	string result;
	string line;
	ofstream myfile;
	ifstream myfile1;
	string parallelTypeString1 = parallelTypeString;

	switch (parallelType)
	{
	case 1:
		parallelTypeString1 += ", rows";
		break;
	case 2:
		parallelTypeString1 += ", columns";
		break;
	case 3:
		parallelTypeString1 += ", blocks";
		break;
	default:
		break;
	}

	result = "Parallel type - " + parallelTypeString1
		+ "\n Schedule = " + (shedule == -1 ? "1 (Main thred)" : to_string(shedule))
		+ "\n Work time = " + to_string(time) + " millisecons"
		+ "\n Work result: \n";

	/*for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if (newCharMass[i][j] != NULL){
				result += newCharMass[i][j];
			}
		}
		result += "\n";
	}*/
	result += "---------------------------------------------\n";

	myfile1.open(fileForWrite);

	if (myfile1.is_open()){
		while (getline(myfile1, line)){
			prevData += line + "\n";
		}
		myfile1.close();
	}

	myfile.open(fileForWrite);

	if (myfile.is_open()){
		myfile << prevData + result;
		myfile.close();
	}
}