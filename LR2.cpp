#include "EncryptingInterraction.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleTitle(L"Шифрование");
	ConsoleCursorVisible(false, 100);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	EncryptingInterraction test;

	int active_menu = 0;
	int keyInput;
	bool exitProg = false;

	system("cls");
	while (!exitProg)
	{
		int x = 35, y = 8;
		GoToXY(x, y);

		vector<string> menu =
		{
			"Перезапустить программу",
			"Установить сдвиг для простого шифра Цезаря",
			"Установить сдвиг для обобщенного шифра Цезаря",
			"Установить ключ для шифра Виженера",
			"Установить систему подстановок для шифра Виженера",
			"Ввод текста для зашифровки простым шифром Цезаря",
			"Ввод текста для расшифровки простым шифром Цезаря",
			"Ввод текста для зашифровки обобщенным шифром Цезаря",
			"Ввод текста для расшифровки обобщенным шифром Цезаря",
			"Ввод текста для расшифровки шифром Цезаря (большой текст)",
			"Ввод текста для зашифровки шифром Виженера (ключевое слово)",
			"Ввод текста для расшифровки шифром Виженера (ключевое слово)",
			"Ввод текста для зашифровки шифром Виженера (система подстановок)",
			"Ввод текста для расшифровки шифром Виженера (система подстановок)",
			"Выход"
		};

		for (int i = 0; i < menu.size(); i++)
		{
			if (i == active_menu)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
		}

		keyInput = _getch();
		switch (keyInput)
		{
			case KEY_ESC:
				exit(0);

			case KEY_UP:
			{
				if (active_menu > 0)
				{
					active_menu--;
				}
			}
			break;

			case KEY_DOWN:
			{
				if (active_menu < menu.size() - 1)
				{
					active_menu++;
				}
			}
			break;

			case KEY_ENTER:
			{
				switch (active_menu)
				{
					case 0:
					{
						system("cls");

						exitProg = true;
						string command = "start /B \"\" \"" + string(__argv[0]) + "\"";
						system(command.c_str());
					}
					break;

					case 1:
					{
						system("cls");

						string shiftInput;
						int shiftINT;
						bool isCorrInput = false;
						while (!isCorrInput)
						{
							system("cls");
							cout << "Введите натуральное число (сдвиг): ";
							getline(cin, shiftInput);

							try
							{
								shiftINT = stoi(shiftInput);
							}
							catch (const exception& ex)
							{
								system("cls");
								cout << "Введите натуральное число (сдвиг): ";
								getline(cin, shiftInput);
							}

							if (shiftINT > 0) isCorrInput = true;
						}

						test.setShift(shiftINT);
						cout << endl << "Сдвиг успешно установлен";

						printQuit();
					}
					break;

					case 2:
					{
						system("cls");

						string input;
						istringstream iss;
						int a, b;
						bool isCorrInput = false;
						while (!isCorrInput)
						{
							system("cls");
							cout << "Введите параметры a и b через пробел: ";
							getline(cin, input);
							istringstream iss(input);
							iss >> a;
							iss >> b;

							if (gcd(a, b) == 1) isCorrInput = true;
						}

						test.setCoef(a);
						test.setShift(b);
						cout << endl << "Параметры успешно установлены";

						printQuit();
					}
					break;

					case 3:
					{
						system("cls");

						string keyInput;
						//bool isCorrInput = false;
						cout << "Введите ключ: ";
						getline(cin, keyInput);
						/*while (!isCorrInput)
						{
							try
							{
								shiftINT = stoi(shiftInput);
								isCorrInput = true;
								break;
							}
							catch (const exception& ex)
							{
								system("cls");
								cout << "Введите натуральное число (сдвиг): ";
								getline(cin, shiftInput);
							}
						}*/

						test.setKey(keyInput);
						cout << endl << "Ключ успешно установлен";

						printQuit();
					}
					break;

					case 4:
					{
						system("cls");

						vector<vector<string>> subsInput;
						vector<string> base, sub1, sub2;
						string input;
						cout << "Введите элементы базиса по очереди, для ввода пробела используйте /, в конце введите пустую строчку" << endl;
						while (true)
						{
							getline(cin, input);
							if (input.empty()) break;

							istringstream iss(input);
							string el;
							iss >> el;
							if (el == "/") base.push_back(" ");
							else base.push_back(el);
						}
						system("cls");
						cout << "Введите элементы первой подстановки по очереди, в конце введите пустую строчку" << endl;
						while (true)
						{
							getline(cin, input);
							if (input.empty()) break;

							istringstream iss(input);
							string el;
							iss >> el;
							if (el == "/") sub1.push_back(" ");
							else sub1.push_back(el);
						}
						system("cls");
						cout << "Введите элементы первой подстановки по очереди, в конце введите пустую строчку" << endl;
						while (true)
						{
							getline(cin, input);
							if (input.empty()) break;

							istringstream iss(input);
							string el;
							iss >> el;
							if (el == "/") sub2.push_back(" ");
							else sub2.push_back(el);
						}

						subsInput.push_back(base);
						subsInput.push_back(sub1);
						subsInput.push_back(sub2);

						try
						{
							test.setSubs(subsInput);
							cout << endl << "Система подстановок успешно установлена";
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}	

						printQuit();
					}
					break;

					case 5:
					{
						system("cls");

						try
						{
							int shift = test.getShift();

							string input, result;
							cout << "Введите текст для зашифровки" << endl;
							getline(cin, input);

							result = test.getEncryptCaesar(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Зашифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 6:
					{
						system("cls");
		
						try
						{
							int shift = test.getShift();

							string input;
							cout << "Введите текст для расшифровки" << endl;
							getline(cin, input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							test.getDecryptCaesar(input);
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 7:
					{
						system("cls");

						try
						{
							int shift = test.getShift();
							int coef = test.getCoef();

							string input, result;
							cout << "Введите текст для зашифровки" << endl;
							getline(cin, input);

							result = test.getEncryptCaesarGeneralized(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Зашифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 8:
					{
						system("cls");

						try
						{
							int shift = test.getShift();
							int coef = test.getCoef();

							string input, result;
							cout << "Введите текст для расшифровки" << endl;
							getline(cin, input);

							result = test.getDecryptCaesarGeneralized(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Зашифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 9:
					{
						system("cls");

						try
						{
							int shift = test.getShift();

							string input;
							cout << "Введите текст для расшифровки" << endl;
							getline(cin, input);

							string result = test.getDecryptCaesarLargeText(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Расшифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 10:
					{
						system("cls");

						try
						{
							string key = test.getKey();

							string input, result;
							cout << "Введите текст для зашифровки" << endl;
							getline(cin, input);

							result = test.getEncryptVigenereKey(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Зашифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 11:
					{
						system("cls");

						try
						{
							string key = test.getKey();

							string input, result;
							cout << "Введите текст для расшифровки" << endl;
							getline(cin, input);

							result = test.getDecryptVigenereKey(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Расшифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 12:
					{
						system("cls");

						try
						{
							vector<vector<string>> key = test.getSubs();

							string input, result;
							cout << "Введите текст для зашифровки" << endl;
							getline(cin, input);

							result = test.getEncryptVigenereSubs(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Зашифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 13:
					{
						system("cls");

						try
						{
							vector<vector<string>> key = test.getSubs();

							string input, result;
							cout << "Введите текст для расшифровки" << endl;
							getline(cin, input);

							result = test.getDecryptVigenereSubs(input);

							system("cls");
							cout << "Исходный текст:" << endl << input << endl << endl;
							cout << "Расшифрованный текст:" << endl << result;
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 14:
					{
						exitProg = true;
					}
					break;
				}
			}
			break;
		}
	}
}