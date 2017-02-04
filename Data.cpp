#include "Data.h"
#include <algorithm>

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
	float *tempTab;
	fstream fin;
	fin.open(filename, ios::in);
	while (temp != "TYPE:")
	{
		fin >> temp;
	}
	fin >> temp;
	if(temp == "TSP")
	{
		//cout << filename;
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

		for (int i = 0; i < number; i++) 
		{
			bestRoute[i] = i;
			fin >> line[0] >> line[1] >> line[2];
			city[i].put(line[1], line[2]);
			//city[i].showData();
		}
		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < number; j++) {
				if (i != j)
					matrix[i][j] = sqrt(pow(city[i].getX() - city[j].getX(), 2) + pow(city[i].getY() - city[j].getY(), 2));
				//	cout <<":"<<i<<":"<<j<<": "<< matrix[i][j]<<" ";
			}
			cout << endl;
		}
	}
	else if(temp == "ATSP")
	{
		//cout << "atsp"<< filename;
		while (temp != "DIMENSION:")
		{

			
			fin >> temp;
		}
		fin >> number;
		cout << number;
		city = new Point[number];
		route = new int[number];
		bestRoute = new int[number];
		matrix = new float*[number];
		tempTab = new float[number];
		for (int i = 0; i < number; i++)
		{
			matrix[i] = new float[number];
		}
		while (temp != "EDGE_WEIGHT_SECTION")
		{
			fin >> temp;
		}

		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < number; j++) {
				fin >> tempTab[j];
				//cout << j << ": " << tempTab[j]<<" ";

			}
			for (int j = 0; j < number; j++) {
				matrix[i][j] = tempTab[j];
			}
		}
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
		cout << route[i] << endl;
	}
}

void Data::randomRoute(int *route2)
{
	bool* table;
	table = new bool[number];
	fill_n(table, number, 0);

	for (int i = 0; i < number; i++)
	{
		route2[i] = (int)rand() % number;
		while (table[route2[i]])
		{
			route2[i] = (int)rand() % number;
		}
		table[route2[i]] = 1;
		//cout << route2[i] << endl;
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
void Data::swap(int* temp1, int* temp2, int** tabu, int cadence)
{
	int a = 1, b = 1;
	int cost1 = 0;
	int cost2 = 0;
	a = (int)rand() % (number);
	b = (int)rand() % (number);
	while (a == b)
	{
		a = (int)rand() % (number);
		b = (int)rand() % (number);
		if (tabu[a][b]) 
		{
			cost1 = calculateRoute(temp1);
			cost2 = calculateRoute(temp2);
			if (cost2 - cost1 > cost1 * 0.03)
			{
				break;
			}
		}
	}
 	tabu[a][b] = cadence;
	
	for (int i = 0; i < number; i++)
		temp2[i] = temp1[i];

	temp2[a] = temp1[b];
	temp2[b] = temp1[a];
	
}
void Data::tabuListDecrease( int** tabu)
{
	for (int i = 0; i < number; i++) 
	{
		for (int j = 0; j < number; j++) 
		{
			if(tabu[i][j]!=0)
			{
				tabu[i][j] -= 1;
			}
		}
	}
}
void Data::tabuShow(int **tabu) {
	cout << endl;
	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < number; j++)
		{
			cout.width(3);
			cout << tabu[i][j];
		}
		cout << endl;
	}
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
	cout <<"lowestCost"<< lowestCost << endl;
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



void Data::tabuSearch(string name, int cadence) {
	double cost = 0;
	double cost2 = 0;
	double lowestcost = 0;
	int round = 0;
	double time[100] = { 0 };
	double timeSum = 0;
	double lowestCost[100] = { 0 };
	double lowestCostSum = 0;
	int notImproved = 0;


	int* route2 = new int[number];
	int** tabu = new int*[number];
	allocateTabu(tabu);
	tabuFill(tabu); 

	randomRoute(route);
	cost = calculateRoute();
	lowestcost = cost;
	//cout << "lowestcost" << cost;
	for (int rep = 0; rep < 100; rep++) {
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		for (int i = 0; i < number; i++) {
			route2[i] = route[i];
		}
		while (round != 20000)
		{
			round++;
			swap(route, route2, tabu, cadence);
			//tabuShow(tabu);
			tabuListDecrease(tabu);
			cost = calculateRoute(route);
			cost2 = calculateRoute(route2);
			if (cost > cost2)
			{
				for (int i = 0; i < number; i++)
					route[i] = route2[i];
				cost = cost2;
				cout << cost << " " << round << endl;
				notImproved = 0;
			}
			else notImproved++;
			if (notImproved > number*number)
				randomRoute();
			//cout << round << endl;

		}
		lowestCost[rep] = cost;
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
	fout.open(name + "res" + ".txt", ios::app);
	fout << "FTabu	"<< cadence <<"	"<< lowestCostSum << "	" << timeSum << endl;
	fout.close();

	cout << "Srednia ze 100: " << lowestCostSum << endl;
	//cout << "best" << cost << endl;
}
void Data::allocateTabu(int ** tabu)
{
	for (int i = 0; i < number; i++) {
		tabu[i] = new int[number];
	}
}
void Data::tabuFill(int ** tabu)
{
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			tabu[i][j] = 0;
		}
	}
}
void Data::tabuSearch(string name)
{

	double kadencja[4] = { 10, sqrt(number), number, (number*number) / 3 };
	int noImprovment = 0;
	int newRandom=0;
	int test = 0;
	int* route2 = new int[number];
	int** tabu = new int*[number];
	for (int i = 0; i < number; i++) {
		tabu[i] = new int[number];
	}
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			tabu[i][j] = 0;
		}
	}
	double cost = 0;
	double cost2 = 0;

	double time[100] = { 0 };
	double timeSum = 0;
	double lowestCost[100] = { 0 };
	double lowestCostSum = 0;
	
	
	
	for (int rep = 0; rep < 100; rep++) {
		randomRoute(route);
		randomRoute(route2);
		for (int i = 0; i < number; i++) {
			route2[i] = route[i];
		}
		if(lowestCost[rep] == 0)lowestCost[rep] = cost = calculateRoute();

		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();



		while (noImprovment != 1000)
		{
			swap(route, route2, tabu, kadencja[3]);
			
			cost2 = calculateRoute(route2);
			cout << cost2;
			if (cost > cost2) 
			{
				cout << "tetetetetetetee";
				system("pause");
				for (int i = 0; i < number; i++)
					route[i] = route2[i];
				cost = cost2;
				noImprovment = 0;

				if (lowestCost[rep]  > cost2)
				{
					lowestCost[rep] = cost;
					for (int i = 0; i < number; i++)
						bestRoute[i] = route[i];
					cout << "		"<< lowestCost << endl;
				}
			}

			else 
			{
				noImprovment++;
			}
			if (noImprovment == 100) {
				randomRoute();
				newRandom++;
				if (newRandom < 100) {
					noImprovment = 0;
				}
			}
			tabuListDecrease(tabu);
			//tabuShow(tabu);
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
	fout.open(name + "res" + ".txt", ios::app);
	fout << "tabu	" << lowestCostSum << "	" << timeSum << endl;
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

void Data::TestGA(string name, int populationSize, int stagnationLimit, float mutationProbability, float crossoverProbability) {
	double time[100] = { 0 };
	double timeSum = 0;
	double lowestCost[100] = { 0 };
	double lowestCostSum = 0; 
	
	for (int rep = 0; rep < 10; rep++) {
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();

		lowestCost[rep] = this->GA(populationSize, stagnationLimit, mutationProbability, crossoverProbability);

		end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		time[rep] = (double)elapsed_seconds.count();
	}
	timeSum = 0;
	lowestCostSum = 0;
	for (int i = 0; i < 10; i++) {
		timeSum += time[i];
		lowestCostSum += lowestCost[i];
	}
	timeSum /= 10;
	lowestCostSum /= 10;
	fstream fout;
	fout.open(name + "res" + ".txt", ios::app);
	fout << crossoverProbability << "	" << mutationProbability << "	" << lowestCostSum << "	" << timeSum << endl;
	fout.close();

	cout << "Srednia ze 100: " << lowestCostSum << endl;
}

int Data::GA(int populationSize, int stagnationLimit, float mutationProbability, float crossoverProbability) {
	int stagnation = 0;
	int bestFitness = -1;
	int newFitness =0;
	int fitnessVariable = 0;
	int bigPopulation = populationSize * 2;
	int **population = new int*[bigPopulation];
	int *fitness = new int[bigPopulation];

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < number; j++) {
			if (fitnessVariable < matrix[i][j])
				fitnessVariable = matrix[i][j];
		}
	}
	if (fitnessVariable > (INT_MAX) / number)fitnessVariable /= 4;
	fitnessVariable *= number;
	cout << "testy" << fitnessVariable << endl;
	//system("pause");
	for (auto i = 0; i < bigPopulation; i++) 
	{
		population[i] = new int[number];

		randomRoute(population[i]);
		fitness[i] = getFitness(population[i], fitnessVariable);
	}
	

	while (stagnation < stagnationLimit) {
		newFitness = evolve(population, bigPopulation, fitnessVariable, crossoverProbability, mutationProbability);  
		if (newFitness > bestFitness)
		{
			bestFitness = newFitness;
			stagnation = 0;
			continue;
		}
		++stagnation;

	}
	
	for (auto i = 0; i < populationSize; ++i)
	{
		delete[] population[i];
	}
	population = nullptr;
	delete[] population;
	return fitnessVariable - bestFitness;
}
int Data::evolve(int **population, int bigPopulation,int fitnessVariable, float crossoverProbability, float mutationProbability) {
	int elite = 0;
	int populationSize = bigPopulation / 2;
	int *fitness = new int[bigPopulation];
	for (int i = 0; i < bigPopulation; i++)
	{
		fitness[i] = getFitness(population[i], fitnessVariable);
	}
	int childrenCount = 0;
	while (childrenCount < populationSize)
	{
		int *parentA, *parentB, *child;
		child = new int[number];
		parentA = RandomSelection(fitness, population, populationSize);
		parentB = RandomSelection(fitness, population, populationSize);

		Cross(parentA, parentB, child, crossoverProbability);
		Mutate(child, mutationProbability);
		for (int i = 0; i < number; i++)
		{
			population[childrenCount+populationSize][i] = child[i];
		}
		

		delete child;
		childrenCount++;
	}

	for (int i = 0; i < bigPopulation; i++)
	{
		fitness[i] = getFitness(population[i], fitnessVariable);
	}
	quicksort(fitness, population,0, bigPopulation - 1);



	elite = getFitness(population[0], fitnessVariable);

	cout << "elite: " << elite << endl;
	delete[] fitness;

	return elite;
}


int Data::getFitness(int *temp, int fitnessVariable) {
	int fitness = fitnessVariable - (int)calculateRoute(temp);
	return fitness;
}
int* Data::RandomSelection(int *fitness, int **population,int populationSize) const
{
	int totalFitness = 0;
	for (auto i = 0; i < populationSize; i++)
	{
		totalFitness += fitness[i];
	}
	int stopAt = abs((rand()* rand()* rand()) % totalFitness);

	totalFitness = 0;
	for (int i = 0; i < populationSize; i++)
	{
		totalFitness += fitness[i];
		if (totalFitness >= stopAt)
		{
			return population[i];
		}
	}
	return nullptr;
}
bool Data::Equals(int *parentA, int *parentB) {

	return false;
}
void Data::Cross(const int *parentA, const int *parentB, int *child, float crossoverProbability)
{
	if (rand() / static_cast<double>(RAND_MAX) > crossoverProbability)
	{
		for (auto i = 0; i < number; i++)
			child[i] = parentA[i];
			return;
	}
	int crossing = rand() % number;

	for (auto i = 0; i < number; i++)
		child[i] = parentB[i];

	auto citiesFromParentA = 0;
	for (auto i = 0; i < number; ++i)
	{
		auto found = false;
		for (auto j = 0; j <= crossing; ++j)
		{
			if (child[j] == parentA[i])
			{
				found = true;
				break;
			}
		}
		if (found) continue;
		++citiesFromParentA;
		child[crossing + citiesFromParentA] = parentA[i];
	}
}
void Data::Mutate(int *t,float mutationProbability)
{
	if (rand() / static_cast<double>(RAND_MAX) > mutationProbability)
		return;
	int a = rand() % number;
	int b = a;
	while (a == b)
		b = rand() % number;
	if (a > b) {
		int buf = a;
		a = b;
		b = buf;
	}

	int invertRange = b - a + 1;
	int *invertBuf= new int[invertRange];

	for (int i = 0; i < invertRange; ++i)
		invertBuf[i] = t[b - i];
	for (int i = 0; i < invertRange; ++i)
		t[a + i] = invertBuf[i];
}
bool Data::Exists(int *child, int **population, size_t childrenCount)
{
	for (size_t i = 0; i < childrenCount; ++i)
	{
		if (Equals(child,population[i]))
			return true;
	}
	return false;
}
void Data::quicksort(int* costsArray, int** population, int left, int right) {
	double v = costsArray[(left + right) / 2];
	int i = left;
	int j = right;
	double costBuf;
	int* buf;
	do {
		while (costsArray[i]>v) i++;
		while (costsArray[j]<v) j--;
		if (i <= j) {
			costBuf = costsArray[i];
			buf = population[i];

			costsArray[i] = costsArray[j];
			population[i] = population[j];

			costsArray[j] = costBuf;
			population[j] = buf;

			i++; j--;
		}
	} while (i <= j);

	if (j>left)
		quicksort(costsArray, population, left, j);
	if (i<right)
		quicksort(costsArray, population, i, right);
}

