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

public:
	Data();
	~Data();
	Data(string);
	Data(string, int);

	int getNumber();
	void showData(int);
	void randomRoute();
	float calculateRoute();
	float calculateRoute1();
};

