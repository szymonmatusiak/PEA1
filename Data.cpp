#include "Data.h"
//domyœlny tylko do testów
Data::Data()
{
	city = new Point[10];
	route = new int[10];
	number = 10;
	*matrix = new float[number];
	for (int i = 0; i < number; i++)
	{
		matrix[i] = new float[number];
	}
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
		matrix = new float*[number];
		for (int i = 0; i < number; i++)
		{
			matrix[i] = new float[number];
		}
		while (temp != "NODE_COORD_SECTION")
		{
			fin >> temp;
		}

		for (int i = 0; i < number; i++) {
			bestRoute[i] = i;
			fin >> line[0] >> line[1] >> line[2];
			city[i].put(line[1], line[2]);
			city[i].showData();
		}
	fin.close();
	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < number; j++) {
			if(i!=j)
				matrix[i][j] = sqrt(pow(city[i].getX() - city[j].getX(), 2) + pow(city[i].getY() - city[j].getY(), 2));
			cout <<i<<":"<<j<<": "<< matrix[i][j]<<" ";
		}
		cout << endl;
	}
	system("pause");

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
		if (matrix != NULL) {
			cost += matrix[i][(i + 1) % number];
		}
		else
		cost += sqrt( pow(city[route[i]].getX() - city[(route[(i + 1) % number])].getX(), 2) + pow(city[route[i]].getY() - city[(route[(i + 1) % number])].getY(), 2));
		//cost1 += sqrt(pow(city[i].getX() - city[(i + 1) % number].getX(), 2) + pow(city[i].getY() - city[(i + 1) % number].getY(), 2));
		//cout<< i << ":" << cost << "	" << cost1 << endl;
		//cout << i << ":" << (i + 1) % number << "	" << (route[(i + 1) % number]) << endl;

	}
	return cost;
}

double Data::calculateRoute(int* route) {
	float cost = 0;
	float cost1 = 0;
	for (int i = 0; i<number; i++)
	{
		cost += matrix[route[i]][route[(i + 1) % number]];

		//cost += sqrt(pow(city[route[i]].getX() - city[(route[(i + 1) % number])].getX(), 2) + pow(city[route[i]].getY() - city[(route[(i + 1) % number])].getY(), 2));

	}
	return cost;
}

void Data::swap(int* temp1, int* temp2)
{
	int a =1, b=1;

	while (a==b)
	{
		a = (int)rand() % (number - 1) + 1;
		b = (int)rand() % (number - 1) + 1;
	}

	for (int i = 0; i < number; i++)
		temp2[i] = temp1[i];

	temp2[a] = temp1[b];
	temp2[b] = temp1[a];
}

void Data::search() {
	int* route2 = new int[number];
	double cost = 0;
	double cost2 = 0;
	double lowestCost = 0;
	double T = 0;
	T = setT();
	double minT = 0.00001;
	double dT = 0.9999;
	randomRoute();
	for (int i = 0; i < number; i++) {
		route2[i] = route[i];
	}

	lowestCost = cost = calculateRoute();

	while(T > minT)
	{
		swap(route, route2);
		cost2 = calculateRoute(route2);

		if (cost > cost2) {
			for (int i = 0; i < number; i++)
				route[i] = route2[i];
			cost = cost2;
			if (lowestCost > cost2)
			{
				lowestCost = cost;
				for (int i = 0; i < number; i++)
					bestRoute[i] = route[i];
				cout << "		" << lowestCost << endl;
			}
		}
		else {
			if ( (double)rand()/RAND_MAX < exp((cost - cost2) / T)){
				for (int i = 0; i < number; i++)
					route[i] = route2[i];
				cost = cost2;

			}
		}

		cout << ": " << cost << endl;

		T *= dT;
	}
	cout <<"asd"<< lowestCost << endl;
}
void Data::search(string name, double dT) {
	int* route2 = new int[number];
	double cost = 0;
	double cost2 = 0;
	double time = 0 ;
	double lowestCost = 0 ;
	double T = 0;
	double minT = 0.00001;

		T = setT();
		randomRoute();
		for (int i = 0; i < number; i++) {
			route2[i] = route[i];
		}

		lowestCost = cost = calculateRoute();
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		while (T > minT)
		{
			swap(route, route2);
			cost2 = calculateRoute(route2);

			if (cost > cost2) {
				for (int i = 0; i < number; i++)
					route[i] = route2[i];
				cost = cost2;
				if (lowestCost > cost2)
				{
					lowestCost = cost;
					for (int i = 0; i < number; i++)
						bestRoute[i] = route[i];
					cout << "		" << lowestCost << endl;
				}
			}
			else {
				if ((double)rand() / RAND_MAX < exp((cost - cost2) / T)) {
					for (int i = 0; i < number; i++)
						route[i] = route2[i];
					cost = cost2;

				}
			}

			cout << ": " << cost << endl;

			T *= dT;
		}
		end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		time = (double)elapsed_seconds.count();
	
	
	
	fstream fout;
	fout.open(name + "res" + ".txt", ios::app);
	fout << dT << "	" << lowestCost << "	" << time<< endl;
	fout.close();

	cout << "Najlepsza:" << lowestCost << endl;

}
void Data::search100(string name, double dT) {
	int* route2 = new int[number];
	double cost = 0;
	double cost2 = 0;
	double time[100] = { 0 };
	double timeSum = 0;
	double lowestCost[100] = {0};
	double lowestCostSum = 0;
	double T = 0;
	double minT = 0.00001;

	for (int rep = 0; rep < 100; rep++) {
		T = setT();
		randomRoute();
		for (int i = 0; i < number; i++) {
			route2[i] = route[i];
		}

		lowestCost[rep] = cost = calculateRoute();
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		while (T > minT)
		{
			swap(route, route2);
			cost2 = calculateRoute(route2);
			cout << "cost2" << cost2;
			if (cost > cost2) {
				for (int i = 0; i < number; i++)
					route[i] = route2[i];
				cost = cost2;
				if (lowestCost[rep] > cost2)
				{
					lowestCost[rep] = cost;
					for (int i = 0; i < number; i++)
						bestRoute[i] = route[i];
					cout << "		" << lowestCost[rep] << endl;
				}
			}
			else {
				if ((double)rand() / RAND_MAX < exp((cost - cost2) / T)) {
					for (int i = 0; i < number; i++)
						route[i] = route2[i];
					cost = cost2;

				}
			}

			cout << ": " << cost << endl;

			T *= dT;
		}
		end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		time[rep] = (double)elapsed_seconds.count();
	}
	timeSum = 0;
	lowestCostSum = 0;
	for (int i = 0; i < 100; i++) {
		timeSum += time[i];
		lowestCostSum += lowestCost[i];
	}
	timeSum /= 100;
	lowestCostSum /= 100;
	fstream fout;
	fout.open(name + "res"+".txt", ios::app);
	fout << dT<<"	"<< lowestCostSum <<"	"<< timeSum <<endl;
	fout.close();

	cout << "Srednia ze 100: " << lowestCostSum << endl;
	system("pause");
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
	cout << maxCost;
	for (int i = 0; i < number*number; i++) {

		randomRoute();
		currentCost = calculateRoute(route);
		if (currentCost > maxCost)
			maxCost = currentCost;
		else if(currentCost < minCost)
			minCost = currentCost;
	}
	T = -(maxCost - minCost) / log(0.9);
	cout <<"temp: " <<T << endl;
	return T;
}