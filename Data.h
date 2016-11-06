#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <cmath>
#define M_E        2.71828182845904523536
#include "Point.h"
using namespace std;
class Data
{
private:
	int number;
	Point* city;
	int* route;
	int* bestRoute; //nie jestem pewien

public:
	Data();
	~Data();
	Data(string);
	int getNumber();
	void showData();
	void randomRoute();
	double calculateRoute();//przepisac
	double calculateRoute(int*);//przepisac

	double calculateBestRoute();
	void swap(int*, int*);
	void search();

	double loadBest(string);

	double setT();
};

