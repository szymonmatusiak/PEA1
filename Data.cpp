#include "Data.h"
//domy�lny tylko do test�w
Data::Data()
{
	city = new Point[10];
	route = new int[10];
	number = 10;
}



Data::Data(string filename)
{
	float line[3];
	city = new Point[52];
	route = new int[52];
	char test[1];
	for (int i = 0; i < number; i++) {
		route[i] = 0;
	}
	fstream fin;
	fin.open(filename, ios::in);
	while (!fin.eof()) {
		fin >> test[0];
		//cout << test[0];
		if (test[0] == '1') {
			line[0] = test[0];
			fin >> line[1] >> line[2];
			city[0].put(line[1], line[2]);
			for (int i = 1; i < 52; i++) {
				fin >> line[0] >> line[1] >> line[2];
				city[i].put(line[1], line[2]);
			}
			break;
		}
	}
	fin.close();
	for (int i = 0; i < 52; i++) {
		cout << i << ": ";
		city[i].showData();
	}
}
Data::Data(string filename, int n)
{
	number = n;
	float line[3];
	city = new Point[n];
	route = new int[n];
	for (int i = 0; i < number; i++) {
		route[i] = 0;
	}
	char test[1];
	fstream fin;
	fin.open(filename, ios::in);
	while (!fin.eof()) {
		fin >> test[0];
		//cout << test[0];
		if (test[0] == '1') {
			line[0] = test[0];
			fin >> line[1] >> line[2];
			city[0].put(line[1], line[2]);
			for (int i = 1; i < number; i++) {
				fin >> line[0] >> line[1] >> line[2];
				city[i].put(line[1], line[2]);
			}
			break;
		}
	}
	fin.close();
	/*for (int i = 0; i < n; i++) {
		cout << i << ": ";
		city[i].showData();
	}*/
}

Data::~Data()
{
}

int Data::getNumber()
{
	return number;
}

void Data::showData(int n){
	for (int i = 0; i < n; i++) {
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
		cout << route[i] << endl;
	}
}

float Data::calculateRoute() {
	float cost = 0;
	for(int i=0;i<number;i++)
	{ 
		cost += sqrt(pow(city[i].getX() - city[(i+1) % number].getX(),2) + pow(city[i].getY() - city[(i + 1) % number].getY(), 2));
	}
	return cost;
}
