#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<math.h>
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
	int cadence[4];
	Data data0 = Data(fileName[0]);
	int kadencja0[4] = { 10, sqrt(data0.getNumber()), data0.getNumber(), (data0.getNumber()*data0.getNumber()) / 3 };
	Data data1 = Data(fileName[1]);
	int kadencja1[4] = { 10, sqrt(data1.getNumber()), data1.getNumber(), (data1.getNumber()*data1.getNumber()) / 3 };
	Data data2 = Data(fileName[2]); 
	int kadencja2[4] = { 10, sqrt(data2.getNumber()), data2.getNumber(), (data2.getNumber()*data2.getNumber()) / 3 };
	Data data3 = Data(fileNameAsync[0]);
	int kadencja3[4] = { 10, sqrt(data3.getNumber()), data3.getNumber(), (data3.getNumber()*data3.getNumber()) / 3 };
	Data data4 = Data(fileNameAsync[1]);
	int kadencja4[4] = { 10, sqrt(data4.getNumber()), data4.getNumber(), (data4.getNumber()*data4.getNumber()) / 3 };
	Data data5 = Data(fileNameAsync[2]);
	int kadencja5[4] = { 10, sqrt(data5.getNumber()), data5.getNumber(), (data5.getNumber()*data5.getNumber()) / 3 };

	//Data testcase = Data("test.tsp");
	cout << menu << endl;
	cin >> switch_on;
	switch (switch_on)
	{
	case(1):
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
		break;
	case(2):
		data0.search("test.tsp",dT[4]);

		data0.tabuSearch("test.tsp");

		break;
	case(3):

		
		for (int i = 0; i < 4; i++) {
			data3.tabuSearch(fileNameAsync[0], kadencja3[i]);
		}
		
		for (int i = 0; i < 4; i++) {
			data4.tabuSearch(fileNameAsync[1], kadencja4[i]);
		}

		for (int i = 0; i < 4; i++) {
			data5.tabuSearch(fileNameAsync[2], kadencja5[i]);
		}

		for (int i = 0; i < 4; i++) {
			data0.tabuSearch(fileName[0], kadencja0[i]);

		}
		for (int i = 0; i < 4; i++) {
			data1.tabuSearch(fileName[1], kadencja1[i]);

		}
		for (int i = 0; i < 4; i++) {
			data2.tabuSearch(fileName[2], kadencja2[i]);
		}
		break;

	case 4:
		data0.GA(100, 100, 0.7, 0.01);

		break;
	default:
		break;
	}

	system("pause");
}
