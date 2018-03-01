#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sys/types.h>
#include "dirent.h"
#include <errno.h>
#include <Windows.h>
#include <wchar.h>
#include <sstream>
#include <codecvt>
using namespace std;
std::string /*ofDewarServer::*/s2u(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
std::string u2s(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}
inline string i2s(int x) {
	if (x == 0) return "0";
	string s;
	s.clear();
	while (x) {
		s.push_back(x % 10 + '0');
		x /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}
int getdir(string dir, vector<string> &vs) {
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}
	while ((dirp = readdir(dp)) != NULL) {
		vs.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}
inline int firstNum(string s) {
	int x = 0, i = 0;
	while (i<s.size() && s[i] >= '0' && s[i] <= '9') {
		x = x * 10 + s[i] - '0';
		i++;
	}
	return x;
}
inline string fileNameNum(string s) {
	for (int i = 0; i < (int)s.size();i++) {
		if (s[i] == ' ') {
			return s.substr(i + 1, 13);
		}
	}
}	
char ret[1000];
inline string fileNameBack(string s) {
	

	int cnt = 0;
	string ans;
	
}


#include <sstream>
#include <fstream>
#include <codecvt>

std::wstring readFile(const char* filename)
{
	std::wifstream wif(filename);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();
}
std::string wstring_to_utf8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

vector<string> vf[200];
int main() {
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	string dir = "D:\\allYTPData\\\\chgOut_all";
	string cmdS;
	vector<string> v_file;
	getdir(dir, v_file);
	int cnt = 0;
	for (auto f : v_file) {
		if ((int)(f.size()) > 4 && f.substr((int)(f.size()) - 4, 4) == ".txt") {
			cnt++;
			//cout << f << " is belongs to " << firstNum(f) << endl;
			vf[firstNum(f)].push_back(f);
		}
	}
	for (int i = 1; i <= 124; i++) {
		cout << "i = " << i << endl;
		for (auto f : vf[i]) {
			string fs = "D:\\allYTPData\\chgOut_all2";
			string sufS = "_all.txt";
			string lastS = fs + "\\" + i2s(i) + sufS;
			string nowF;
			fstream fp;
			nowF = dir + "\\" + f;
			wstring ws = readFile(nowF.c_str());
			//cout << "nowF = " << nowF << endl;
			//cout << "ws = " << wstring_to_utf8(ws) << endl;
			

			fp.open(lastS.c_str(), ios::out | ios::app);
			if (!fp) {//如果開啟檔案失敗，fp為0；成功，fp為非0
				cout << "Fail to open file: " << lastS << endl;
			}
			/*fp << u8"\n[[[" << s2u(fileNameNum(f)) << u8"]]]\n{{{";
			for (int i = 0; i < (int)f.size(); i++) {
				if (f[i] == ' ') {
					strcpy(ret, f.c_str() + i + 15);
					fp << s2u(ret);
					break;
				}
			} 
			fp << u8"}}}\n";*/

			fp << wstring_to_utf8(ws) <<endl;
			fp.close();
			// freopen fs+i2s(i)+sufS and print [[[fileName number]]] {{{fileName back}}} 
			/*cmdS.clear();
			cmdS = "type \"" + lastS + "\" \"" + dir + "\\" + f + "\" > " + "\"" + fs + "temp.txt" + "\"";
			system(cmdS.c_str());
			// type fs+i2s(i)+sufS nowFile temp
			cmdS.clear();
			cmdS = "type \"" + fs + "temp.txt" + "\"" + " > \"" + lastS + "\"";
			system(cmdS.c_str());*/
			// type temp fs+i2s(i)+sufS
		}
	}
	cout << "cnt = " << cnt << endl;

	return 0;
}