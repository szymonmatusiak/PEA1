#include<iostream>
#include<fstream>
#include<string>

#include"Point.h"
#include"Data.h"
using namespace std;

void main(){
	string fileName = "berlin52.tsp";
	Data data = Data(fileName, 52);

	data.showData(52);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*string test;
	float demention[52][3];
	fstream fin;
	fin.open("berlin52.tsp", ios::in);
	while (!fin.eof()) {
		fin >> test[0];
		//cout << test[0];
		if (test[0] == '1') {
			demention[0][0] = 1;
			fin >> demention[0][1] >> demention[0][2];
			for (int i = 1; i < 52; i++) {
				fin>> demention[i][0]>> demention[i][1]>> demention[i][2];
			}
			break;
		}
	}
	fin.close();
	for (int i = 0; i < 52; i++) {
		cout << demention[i][0] << " " << demention[i][1] << " " << demention[i][2] << endl;
	}
	*/
	system("pause");
}
