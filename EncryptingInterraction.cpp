#include "EncryptingInterraction.h"

int gcd(int a, int b)
{
	while (b != 0) 
	{
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

void printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

EncryptingInterraction::EncryptingInterraction()
{
	_shift = -1;
	_coef = -1;
	_key = "";
	_subs = {};
	isShiftSet = false;
	isCoefSet = false;
	isKeySet = false;
	isSubsSet = false;
}

int EncryptingInterraction::getShift()
{
	if (!isShiftSet) throw exception("Сдвиг не установлен");
	return _shift;	
}

void EncryptingInterraction::setShift(int shift)
{
	_shift = shift;
	isShiftSet = true;
}

int EncryptingInterraction::getCoef()
{
	if (!isCoefSet) throw exception("Коэффициент не установлен");
	return _coef;
}

void EncryptingInterraction::setCoef(int coef)
{
	_coef = coef;
	isCoefSet = true;
}

string EncryptingInterraction::getKey()
{
	if (!isKeySet) throw exception("Ключ не установлен");
	return _key;
}

void EncryptingInterraction::setKey(string key)
{
	_key = key;
	isKeySet = true;
}

vector<vector<string>> EncryptingInterraction::getSubs()
{
	if (!isSubsSet) throw exception("Система подстановок не установлена");
	return _subs;
}

void EncryptingInterraction::setSubs(vector<vector<string>> subs)
{
	int baseSize = subs[0].size();
	int sub1Size = subs[1].size();
	int sub2Size = subs[2].size();
	if (baseSize != sub1Size || baseSize != sub2Size) throw exception("Система подстановок не может быть установлена");

	_subs = subs;
	isSubsSet = true;
}

string EncryptingInterraction::getEncryptCaesar(string text, int shift)
{
	string temp = text;
	string result;

	for (auto& letter : temp)
	{
		if (letter >= 'A' && letter <= 'Z') letter = 'A' + ((letter - 'A' + shift) % ENG);
		else if (letter >= 'a' && letter <= 'z') letter = 'a' + ((letter - 'a' + shift) % ENG);
		result += letter;
	}

	return result;
}

string EncryptingInterraction::getEncryptCaesar(string text)
{
	return getEncryptCaesar(text, _shift);
}

string EncryptingInterraction::getEncryptCaesarGeneralized(string text, int shift)
{
	string temp = text;
	string result;

	for (auto& letter : temp)
	{
		if (letter >= 'A' && letter <= 'Z') letter = 'A' + ((_coef * (letter - 'A') + shift) % ENG);
		else if (letter >= 'a' && letter <= 'z') letter = 'a' + ((_coef * (letter - 'a') + shift) % ENG);
		result += letter;
	}

	return result;
}

string EncryptingInterraction::getEncryptCaesarGeneralized(string text)
{
	return getEncryptCaesarGeneralized(text, _shift);
}

int EncryptingInterraction::modInverse(int a, int m) 
{
	a = a % m;
	for (int x = 1; x < m; x++) 
	{
		if ((a * x) % m == 1) return x;
	}
	return -1;
}

string EncryptingInterraction::getDecryptCaesarGeneralized(string text)
{
	int revCoef = modInverse(_coef, ENG);
	if (_coef == -1) throw exception("Обратного элемента не существует");

	string temp = text;
	string result;

	for (auto& letter : temp)
	{
		if (letter >= 'A' && letter <= 'Z') letter = 'A' + ((revCoef * ((letter - 'A') - _shift + ENG)) % ENG);
		else if (letter >= 'a' && letter <= 'z') letter = 'a' + ((revCoef * ((letter - 'a') - _shift + ENG)) % ENG);
		result += letter;
	}

	return result;
}

void EncryptingInterraction::getDecryptCaesar(string text)
{
	for (int i = 1; i < ENG; i++)
	{
		cout << i << ": " << getEncryptCaesar(text, ENG - i) << endl;
	}
}

string EncryptingInterraction::getDecryptCaesarLargeText(string text)
{
	vector<int> cntOfEntries(26);
	int maxID = 0, key;

	for (auto& letter : text)
	{
		if (letter >= 'A' && letter <= 'Z') cntOfEntries[letter - 'A']++;
		if (letter >= 'a' && letter <= 'z') cntOfEntries[letter - 'a']++;
	}

	for (int i = 1; i < ENG; i++)
	{
		if (cntOfEntries[i] > cntOfEntries[maxID]) maxID = i;
	}

	key = maxID - 4;
	while (key < 0) key += 26;

	return getEncryptCaesar(text, ENG - key);
}

string EncryptingInterraction::getEncryptVigenereKey(string text)
{
	string temp = text;
	string result;
	string newKey;
	int keyLen = _key.size(), textSize = text.size(), j = 0;

	for (auto& letter : text)
	{
		if (j == keyLen) j = 0;
		newKey += _key[j];
		j++;
	}

	for (int i = 0; i < textSize; i++)
	{
		char letter = temp[i];
		char start = isupper(letter) ? 'A' : 'a';
		int shift = (letter + newKey[i]) % ENG;
		result += start + shift;
	}

	/*for (auto& letter : text)
	{
		if (isalpha(letter))
		{
			char start = isupper(letter) ? 'A' : 'a';
			int ID = j % keyLength;
			char encryptSymb = isupper(_key[ID]) ? _key[ID] - 'A' : _key[ID] - 'a';
			result += char(start + (letter - start + encryptSymb) % 26);
		}
		else result += letter;
	}*/

	return result;
}

string EncryptingInterraction::getDecryptVigenereKey(string text)
{
	string temp = text;
	string result;
	string newKey;
	int keyLen = _key.size(), textSize = text.size(), j = 0;

	for (auto& letter : temp)
	{
		if (j == keyLen) j = 0;
		newKey += _key[j];
		j++;
	}

	for (int i = 0; i < textSize; i++)
	{
		char letter = temp[i];
		char start = isupper(letter) ? 'A' : 'a';
		int shift = ((letter - newKey[i]) + ENG) % ENG;
		result += start + shift;
	}

	return result;
}

string EncryptingInterraction::getEncryptVigenereSubs(string text)
{
	string temp = text;
	string result;

	vector<string> base = _subs[0];
	vector<string> sub1 = _subs[1];
	vector<string> sub2 = _subs[2];

	for (int i = 0; i < temp.size(); i++)
	{
		char curLetter = temp[i];
		string letter(1, curLetter);
		auto it = find(base.begin(), base.end(), letter);
		if (it != base.end())
		{
			int ID = distance(base.begin(), it);
			if (i % 2 == 1) result += sub2[ID];
			else result += sub1[ID];
		}
		else throw exception("Данный символ отсутствует в базисе подстановок");
	}

	return result;
}

string EncryptingInterraction::getDecryptVigenereSubs(string text)
{
	string temp = text;
	string result;

	vector<string> base = _subs[0];
	vector<string> sub1 = getReverseSub(_subs[1]);
	vector<string> sub2 = getReverseSub(_subs[2]);

	for (int i = 0; i < temp.size(); i++)
	{
		char curLetter = temp[i];
		string letter(1, curLetter);
		auto it = find(base.begin(), base.end(), letter);
		if (it != base.end())
		{
			int ID = distance(base.begin(), it);
			if (i % 2 == 1) result += sub2[ID];
			else result += sub1[ID];
		}
		else throw exception("Символ отсутствует в базисе подстановок");
	}

	return result;
}

vector<string> EncryptingInterraction::getReverseSub(vector<string> sub)
{
	int size = sub.size();
	vector<string> base = _subs[0];
	vector<string> result(size);

	for (int i = 0; i < size; i++)
	{
		auto it = find(base.begin(), base.end(), sub[i]);
		if (it != base.end())
		{
			int ID = distance(base.begin(), it);
			result[ID] = base[i];
		}
		else throw exception("Символ отсутствует в базисе подстановок");	
	}

	return result;
}