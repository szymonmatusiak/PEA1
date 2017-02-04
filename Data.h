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
	float** matrix;
	

public:
	Data();
	~Data();
	Data(string);
	int getNumber();
	void showData();
	void search(string, double);
	void search100(string, double);
	void tabuSearch(string name, int cadence);
	void allocateTabu(int ** tabu);
	void tabuFill(int ** tabu);
	void tabuSearch(string);



	void randomRoute();
	void randomRoute(int*);

	double calculateRoute();
	double calculateRoute(int*);

	double calculateBestRoute();
	void swap(int*, int*);
	void swap(int*, int*, int**, int);

	void tabuListDecrease(int **);
	void tabuShow(int **);

	void search();
	double loadBest(string);

	double setT();
	void TestGA(string name, int populationSize, int stagnationLimit, float mutationProbability, float crossoverProbability);
	int GA(int , int , float , float );
	int evolve(int**, int, int,float , float);
	int getFitness(int*,int);
	int * RandomSelection(int * fitness, int ** population, int populationSize) const;
	void Cross(const int * parentA, const int * parentB, int * child, float);
	void Mutate(int * t, float);
	bool Exists(int * child, int ** population, size_t childrenCount);
	void quicksort(int * bigfitness, int ** population, int left, int right);
	bool Equals(int *parentA, int *parentB);
};

