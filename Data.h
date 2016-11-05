#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "Point.h"
using namespace std;
class Data
{
private:
	int number;
	Point* city;

public:
	Data();
	~Data();
	Data(string);
	Data(string, int);
	void showData(int);
	float calculateRoute();
};

