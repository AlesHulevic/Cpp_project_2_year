#pragma once



#include <iostream>
#include <fstream>
#include <Windows.h>
#include <memory>
#include <conio.h>
#include <string>
#include <iomanip>

using namespace std;

int input_and_check(int a, int b) //гэта шчасце--функцыя дзеля ўвода switchera, выклікаецца як switcher=input_and_check(a, b), дзе а і b гэта колькасць кейсаў
{
	int i;
	try
	{
		while (!(cin >> i) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
		}
		if (i < a || i > b) throw exception("Памылковая лічба\n");
		return i;
	}
	catch (const exception& ex)
	{
		cout << ex.what();
	}
	return 100;
}
void authorisation();
void Adm_menu1();


class User
{
	string login = "";
	string password = "";
	bool role = 0;
public:
	User() {};
	User(string login, string password, bool role)
	{
		this->login = login;
		this->password = password;
		this->role = role;
	}

	virtual void show();
	virtual void From_file_to_massiv(string log, string pas, bool role)
	{
		this->login = log;
		this->password = pas;
		this->role = role;
	}

	virtual void Set_User()
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                Увод дадзеных новага карыстальніка                                            |\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		cout << "увядзіце лагін: ";
		cin >> this->login;
		cout << "увядзіце пароль: ";
		cin >> this->password;
		cout << "увядзіце ролю (1-адміністратар, 0-карыстальнік): ";
		this->role = input_and_check(0, 1); //ахтунг, можа выклікаць памылку (bool=int)
	}

	virtual void Save_to_file()
	{
		ofstream file;
		file.open("UserFile.txt", ofstream::app);
		if (!file.is_open()) cout << "памылка";
		for (int i = 0; this->password[i] != '\0'; i++) { this->password[i] = this->password[i] + 3; }
		file << this->login << " " << this->password << " " << this->role << endl;
		file.close();
	}
};



void Show_ac(shared_ptr<shared_ptr<User>[]>* mas, int size_of_mas);
void delete_s(shared_ptr<shared_ptr<User>[]>* mas, int& size_of_mas);
void redact_user(shared_ptr<shared_ptr<User>[]>* mas, int& size_of_mas);

