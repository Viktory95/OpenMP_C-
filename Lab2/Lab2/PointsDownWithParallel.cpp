#include "stdafx.h"
#include "PointsDownWithParallel.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <windows.h> 
#include <vector>
#include <iostream>
#include <Math.h>
#include <string>
#include <sstream>
#include <conio.h>
#include <time.h>
#include <omp.h>
#include <iomanip>

using namespace std;

const int var_count_par = 3;
double function_par(double* variables);
typedef double(*func_ptr)(double*);
double golden_section_par(func_ptr f, double* vars, int var_index, double eps, double a, double b, int max_steps_count);
void descent_method_par(func_ptr f, double* vars, double eps, int max_steps_count);

PointsDownWithParallel::PointsDownWithParallel()
{
}


PointsDownWithParallel::~PointsDownWithParallel()
{
}

void PointsDownWithParallel::run()
{
	setlocale(LC_ALL, "RUSSIAN");
	clock_t start;
	start = clock();

	double eps = 0.001;
	int max_steps_count = 100;
	double variables[var_count_par] = { 0.1, 0.1, 0.1 };

	descent_method_par(function_par, variables, eps, max_steps_count);


	cout << "Время с распараллеливанием = " + to_string((double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC) + "\n";
}

double function_par(double* variables)
{
	return (pow(variables[0], 2) + pow((variables[1] - 50), 2) + pow((variables[2] + 30), 2)) - 100 * sin(variables[0]);
	//(x1^2+(x2-50)^2+(x3+30)^2)-100*sin(x1)
}

void descent_method_par(func_ptr f, double* vars, double eps, int max_steps_count)
{
	omp_set_nested(true);

	double B = f(vars), A = 0;
	bool was_counted = false;
	int stpes_ellapsed = 0;
	double delta = 0.0;
	bool flag = true;
#pragma omp for ordered 
		for (int i = 0; i < max_steps_count; i++){
			if (flag){
				A = B;

#pragma omp ordered 
				{
					for (int var_index = 0; var_index < var_count_par; var_index++)
						vars[var_index] = golden_section_par(f, vars, var_index, eps, -5000, 5000, max_steps_count);
				}

				B = f(vars);

				delta = fabs(A - B);

				if (delta <= eps)
				{
					stpes_ellapsed = i + 1;
					was_counted = true;
					flag = false;
				}
			}
		}
	

	std::cout << "Результат поиска минимума функции " << "(x1^2+(x2-50)^2+(x3+30)^2)-100*sin(x1)" << std::endl;

	if (!was_counted)
		std::cout << "За максимально указанное количество шагов ( " << max_steps_count << " ) минимум не был посчитан." << std::endl;
	else {
		std::cout << "Количество итераций: " << stpes_ellapsed << std::endl;
		std::cout << "Погрешность: " << delta << std::endl;
	}

	std::cout << "Точка: X(";
	for (int i = 0; i < var_count_par; i++){
		std::cout << vars[i] << ", ";

	}

	std::cout << "\b\b" << ")" << std::endl;
	std::cout << "Значение фукнции f(X): " << std::setprecision(10) << f(vars) << std::endl;
}

double golden_section_par(func_ptr f, double* vars, int var_index, double eps, double a, double b, int max_steps_count)
{

	double res = 0.0;
	double phi = (1 + sqrt(5.0)) / 2.0;
	double A = 0.0f, B = 0.0f;
	double x1, x2, flag = true;
//#pragma omp parallel
	//{
		x1 = a + phi * (b - a);
		x2 = b - phi * (b - a);
	//}

	int step = 0;

	while (flag)
	{
			x1 = b - ((b - a) / phi);
			vars[var_index] = x1;
//#pragma omp parallel
	//	{
			A = f(vars);
			x2 = a + ((b - a) / phi);
	//	}
		vars[var_index] = x2;

//#pragma omp parallel
	//	{
			B = f(vars);
//#pragma omp critical
	//		{
				if (A > B)
					a = x1;
				else
					b = x2;
		//	}
			flag = b - a > eps;
		//}
		step++;
		
		if (step > max_steps_count)
			break;
	}

	res = (a + b) / 2;
	return res;
}
