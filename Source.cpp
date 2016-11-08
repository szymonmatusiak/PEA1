#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include"Point.h"
#include"Data.h"
using namespace std;

void main(){
	srand(time(NULL));
	string fileName[3] = { "berlin52.tsp", "eil76.tsp", "ch130.tsp"};
	string fileNameOpt[3] = { "berlin52.opt.tour", "gr24.opt.tour", "gr120.opt.tour" };
	double dT[5]={0.9,0.95,0.99,0.999,0.9999};
	int number = 2;
	Data data0 = Data(fileName[0]);
	Data data1 = Data(fileName[1]);
	Data data2 = Data(fileName[2]);

	for (int i = 0; i < 5; i++) {
		data0.search100(fileName[0], dT[i]);
	
	}
	for (int i = 0; i < 5; i++) {
		data1.search100(fileName[1], dT[i]);

	}
	for (int i = 0; i < 5; i++) {
		data2.search100(fileName[2], dT[i]);
	}*/
	data0.~Data();
	data1.~Data();
	data2.~Data();

	system("pause");
}
