#include "Data.h"
//domyœlny tylko do testów
Data::Data()
{
	city = new Point[10];
	route = new int[10];
	number = 10;
}

Data::Data(string filename)
{
	string temp;
	float line[3];

	fstream fin;
	fin.open(filename, ios::in);
		while (temp != "DIMENSION:")
		{
			fin >> temp;
		}
		fin >> number;
		city = new Point[number];
		route = new int[number];
		bestRoute = new int[number];

		while (temp != "NODE_COORD_SECTION")
		{
			fin >> temp;
		}

		for (int i = 0; i < number; i++) {
			bestRoute[i] = i;
			fin >> line[0] >> line[1] >> line[2];
			city[i].put(line[1], line[2]);
			//city[i].showData();
		}
	fin.close();
}
Data::~Data()
{
}
int Data::getNumber()
{
	return number;
}

void Data::showData(){
	for (int i = 0; i < number; i++) {
		cout << i << ": ";
		city[i].showData();
	}
}

void Data::randomRoute()
{
	bool* table;
	table = new bool[number];
	fill_n(table, number, 0);

	for (int i = 0; i < number; i++)
	{
		route[i] = (int)rand() % number;
		while (table[route[i]])
		{
			route[i] = (int)rand() % number;
		}
		table[route[i]] = 1;
		//cout << route[i] << endl;
	}
}

double Data::calculateRoute() {
	float cost = 0;
	float cost1 = 0;
	for(int i=0;i<number;i++)
	{ 
		cost += sqrt( pow(city[route[i]].getX() - city[(route[(i + 1) % number])].getX(), 2) + pow(city[route[i]].getY() - city[(route[(i + 1) % number])].getY(), 2));
		//cost1 += sqrt(pow(city[i].getX() - city[(i + 1) % number].getX(), 2) + pow(city[i].getY() - city[(i + 1) % number].getY(), 2));
		//cout<< i << ":" << cost << "	" << cost1 << endl;
		//cout << i << ":" << (i + 1) % number << "	" << (route[(i + 1) % number]) << endl;

	}
	return cost;
}

void Data::swap()
{
	int a =1, b=1;
	int temp=0;

	while (a==b)
	{
		a = (int)rand() % number;
		b = (int)rand() % number;
	}
	temp = route[a];
	route[a] = route[b];
	route[b] = temp;
}

void Data::search() {
	int notImprovment = 0;
	int* route2 = new int[number];
	double cost = 0;
	double cost2 = 0;
	double lowestCost = 0;
	double T = 0;
	T = setT();

	randomRoute();
	lowestCost = cost = calculateRoute();

	for (int i = 0; i < 10000; i++)
	{
		if (notImprovment > 200) {
			randomRoute();
			notImprovment = 0;
		}
		cost = calculateRoute();
		cost2 = calculateRoute();

		if (cost > cost2) {
			for (int i = 0; i < number; i++)
				route[i] = route2[i];
			cost = cost2;
			if (lowestCost > cost)
			{
				lowestCost = cost;
				for (int i = 0; i < number; i++)
					bestRoute[i] = route[i];
				cout << "		" << lowestCost << endl;
			}
		}
		else {
			if ( ( 1 / ( 1 + pow( M_E, (cost-cost2)/T)))>(pow(M_E, (cost - cost2) / T))){
				for (int i = 0; i < number; i++)
					route[i] = route2[i];
				cost = cost2;
			}
		}
		cout << cost << endl;
		swap();
	}
	cout <<"asd"<< lowestCost << endl;
}
double Data::loadBest(string filename) {
	string temp;

	fstream fin;
	fin.open(filename, ios::in);
	while (temp != "TOUR_SECTION")
	{
		fin >> temp;
	}

	for (int i = 0; i < number; i++) {
		fin >> bestRoute[i];
		bestRoute[i]--;
		cout <<i<<": "<< bestRoute[i]<<endl;
	}
	fin.close();
	cout<<"Najlepsza: "<<calculateBestRoute();
	return calculateBestRoute();
}
double Data::calculateBestRoute() {
	double cost = 0;
	for (int i = 0; i<number; i++)
	{
		cout << i << ": " << bestRoute[i] << " " << bestRoute[(i + 1) % number]<<endl;
		cost += sqrt(pow(city[bestRoute[i]].getX() - city[(bestRoute[(i + 1) % number])].getX(), 2) + pow(city[bestRoute[i]].getY() - city[(bestRoute[(i + 1) % number])].getY(), 2));
		cout << cost<<endl;
	}
	return cost;
}
double Data::setT() {
	double maxCost = 0;
	double minCost = 0;
	double currentCost = 0;
	double T;

	randomRoute();
	maxCost = minCost = calculateRoute();
	for (int i = 0; i < number*number; i++) {

		randomRoute();
		currentCost = calculateRoute();
		if (currentCost > maxCost)
			maxCost = currentCost;
		else if(currentCost < minCost)
			minCost = currentCost;
	}
	T = -(maxCost - minCost) / log(0.9);
	return 0;
}