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
	int _shift, _coef;
	string _key;
	vector<vector<string>> _subs;
	bool isShiftSet, isCoefSet, isKeySet, isSubsSet;

public:

	EncryptingInterraction();

	int getShift();
	void setShift(int shift);
	int getCoef();
	void setCoef(int coef);

	string getKey();
	void setKey(string key);
	vector<vector<string>> getSubs();
	void setSubs(vector<vector<string>> subs);

	string getEncryptCaesar(string text, int shift);
	string getEncryptCaesar(string text);
	void getDecryptCaesar(string text);
	string getDecryptCaesarLargeText(string text);

	string getEncryptCaesarGeneralized(string text, int shift);
	string getEncryptCaesarGeneralized(string text);
	int modInverse(int a, int m);
	string getDecryptCaesarGeneralized(string text);

	string getEncryptVigenereKey(string text);
	string getDecryptVigenereKey(string text);
	string getEncryptVigenereSubs(string text);
	string getDecryptVigenereSubs(string text);

	vector<string> getReverseSub(vector<string> sub);
};

int gcd(int a, int b);
void printQuit();