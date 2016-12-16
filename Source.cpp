#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include"Point.h"
#include"Data.h"
using namespace std;

void main(){
	srand(time(NULL));
	
	
	string menu = "test menu";
	int switch_on=0;
	string fileName[3] = { "berlin52.tsp", "eil76.tsp", "ch130.tsp"};
	string fileNameAsync[3] = { "br17.atsp", "ftv70.atsp", "ftv47.atsp" };
	string fileNameOpt[3] = { "berlin52.opt.tour", "gr24.opt.tour", "gr120.opt.tour" };
	double dT[5]={0.9,0.95,0.99,0.999,0.9999};
	Data data0 = Data("test.tsp");

	/*
	Data data0 = Data(fileName[0]);
	Data data1 = Data(fileName[1]);
	Data data2 = Data(fileName[2]); 
	Data data3 = Data(fileNameAsync[0]);
	Data data4 = Data(fileNameAsync[1]);
	Data data5 = Data(fileNameAsync[2]);
	*/
	Data testcase = Data("test.tsp");
	cout << menu << endl;
	cin >> switch_on;
	switch (switch_on)
	{
	/*case(1):
		for (int i = 0; i < 5; i++) {
			data3.search100(fileNameAsync[0], dT[i]);
		}
		for (int i = 0; i < 5; i++) {
			data4.search100(fileNameAsync[1], dT[i]);
		}
		for (int i = 0; i < 5; i++) {
			data4.search100(fileNameAsync[2], dT[i]);
		}

		for (int i = 0; i < 5; i++) {
			data0.search100(fileName[0], dT[i]);

		}
		for (int i = 0; i < 5; i++) {
			data1.search100(fileName[1], dT[i]);

		}
		for (int i = 0; i < 5; i++) {
			data2.search100(fileName[2], dT[i]);
		}
		data0.~Data();
		data1.~Data();
		data2.~Data();
		break;*/


	case(2):
		data0.tabuSearch("test.tsp");
		break;
	default:
		break;
	}

	system("pause");
}
