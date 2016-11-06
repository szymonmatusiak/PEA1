#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<math.h>
#include "Point.h"
using namespace std;
class Data
{
private:
	int number;
	Point* city;
	int* route;
	//int* bestRoute; //nie jestem pewien

public:
	Data();
	~Data();
	Data(string);
	Data(string, int);

	int getNumber();
	void showData();
	void randomRoute();
	float calculateRoute();

	void swap();
};

