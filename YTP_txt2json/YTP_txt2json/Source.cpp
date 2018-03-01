#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;


int main() {
	
	ifstream fin;
	fin.open(".\\newText.txt");
	ofstream fout;
	fout.open(".\\output.txt", ios::app);

	string s;

	while (getline(fin,s)) {
		cout << s << endl;
		fout << s << endl;
	}

	return 0;
}