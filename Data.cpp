#include "Data.h"

Data::Data()
{
}



Data::Data(string filename)
{
	float line[3];
	city = new Point[52];
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
	float line[3];
	city = new Point[n];
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
			for (int i = 1; i < 52; i++) {
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

void Data::showData(int n){
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		city[i].showData();
	}
}

float Data::calculateRoute() {
	

}
