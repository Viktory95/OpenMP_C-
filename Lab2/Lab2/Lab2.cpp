// OpenMpProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <windows.h> 
#include "PointsDownWithoutParallel.h"
#include "PointsDownWithParallel.h"
using namespace std;

int main()
{
	PointsDownWithParallel* withParallel = new PointsDownWithParallel();
	withParallel->run();	
	cout << "\n";
	PointsDownWithoutParallel* withoutParallel = new PointsDownWithoutParallel();
	withoutParallel->run();

	system("pause");
	return 0;
}
