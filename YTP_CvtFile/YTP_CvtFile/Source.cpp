#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;
inline string i2s(int x) {
	string s;
	if (x == 0) return "0";
	while (x > 0) {
		s.push_back((x % 10) + '0');
		x /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}
string dic[100];
int main() {
	srand(time(NULL));
	string dir = "D:\\allYTPData\\80\\output";
	string dir2 = "D:\\allYTPData\\80\\cvt";
	string dir3 = "D:\\allYTPData\\80\\cvt2";
	int pc, rc;
	pc = 1;
	rc = 80;
	for (int i = 1;i<=80; i++) dic[i] = i2s(i);
	sort(dic+1, dic + 81);
	for (int i = 1; i <= 80; i++) {
		string nowFile = (dir + "\\" + i2s(i) + ".txt");
		string outFile = (dir + "\\cvt" + i2s(i) + ".txt");
		string outFile2 = (dir3 + "\\cvt", i2s(i) + ".txt");
		fstream fs;
		fstream fout,fout2;
		string s;
		fs.open(nowFile.c_str(), ios::in);
		int cnt = 0;
		while (fs >> s) {
			double d;
			fs >> d;
			if (cnt > 1) {
				fout << ",";
				fout2 << ",";
			}

			if (cnt == 0) {
				if (d > 0) {
					outFile = (dir2 + "\\cvt" + dic[rc] + ".txt");
					outFile2 = (dir3 + "\\cvt" + dic[rc] + "_cvt.txt");
					rc--;
				}
				else {
					outFile = (dir2 + "\\cvt" + dic[pc] + ".txt");
					outFile2 = (dir3 + "\\cvt" + dic[pc] + ".txt");
					pc++;
				}
				cout << "outFile = " << outFile << endl;
				fout.open(outFile.c_str(), ios::out);
				fout2.open(outFile2.c_str(), ios::out);
				fout2 << d << ",";
			}
			else {
				if (cnt <= 2) {
					if (cnt == 2) {
						int age = rand() % 60 + 30;
						fout << (int)(age * 100);
						fout2 << (int)(age * 100);
					}
					else {
						fout << (int)(d * 100);
						fout2 << (int)(d * 100);
					}
				}
				else {
					fout << (int)(d * 100000);
					fout2 << (int)(d * 100000);
				}
			}
			cnt++;
			
		}
		cout << "dim " << i << " = " << cnt << endl;
		fs.close();
		fout.close();
	}
	return 0;
}