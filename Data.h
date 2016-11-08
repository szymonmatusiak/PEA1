#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <cmath>
#include<chrono>
#define M_E        2.71828182845904523536
#include "Point.h"
using namespace std;
class Data
{
private:
	int number;
	Point* city;
	int* route;
	int* bestRoute;

public:
	Data();
	~Data();
	Data(string);
	int getNumber();
	void showData();
	void search(string, double);
	void search100(string, double);

	void randomRoute();
	double calculateRoute();
	double calculateRoute(int*);

	double calculateBestRoute();
	void swap(int*, int*);
	void search();

	double loadBest(string);

	double setT();
};

