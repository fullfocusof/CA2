#pragma once
#include <iostream>
#include <sstream>

#include <Windows.h>
#include <conio.h>
#include <cstdlib>

#include <vector>
#include <string>
#include <unordered_map>

#define ENG 26
#define RUS 33

using namespace std;

class EncryptingInterraction
{
	int _shift;
	string _key;
	vector<vector<string>> _subs;
	bool isShiftSet, isKeySet, isSubsSet;

public:

	EncryptingInterraction();

	int getShift();
	void setShift(int shift);
	string getKey();
	void setKey(string key);
	vector<vector<string>> getSubs();
	void setSubs(vector<vector<string>> subs);

	string getEncryptCaesar(string text, int shift);
	string getEncryptCaesar(string text);

	void getDecryptCaesar(string text);
	string getDecryptCaesarLargeText(string text);

	string getEncryptVigenereKey(string text);
	string getDecryptVigenereKey(string text);

	string getEncryptVigenereSubs(string text);
	string getDecryptVigenereSubs(string text);

	vector<string> getReverseSub(vector<string> sub);
};

void printQuit();