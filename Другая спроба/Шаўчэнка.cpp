#include "Header1.h"

shared_ptr<User> Create_User()
{
	shared_ptr<User> user(new User);
	user->Set_User();
	return user;
}

shared_ptr<User> From_file_to_massiv(string log, string pas, bool role)
{
	shared_ptr<User> user(new User);
	user->From_file_to_massiv(log, pas, role);
	return user;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("cls");
	cout << "________________________________________________________________________________________________________________\n";
	cout << "|                  Вітаю! Вы карыстаецеся дадаткам па ўліку фармаўцептычнай вытворчасці.                       |\n";
	cout << "|               Каб працягнуць працу вам трэба прайсці аўтарызацыю. Прытрымлівайцеся інструкцый                |\n";
	cout << "|______________________________________________________________________________________________________________|\n";
	authorisation();
}

void authorisation()
{
	ifstream file;
	file.open("UserFile.txt");
	if (!file.is_open())
	{
		cout << "памылка";
	}
	else
	{
		string login, password;
		char str[256];
		User user;
		int check = 0;

		cout << "Калі ласка ўвядзіце свае асабістыя лагін ды пароль\nлагін: ";
		cin >> login;
		cout << "\nпароль";
		char c;
		int i = 0;
		while ((c = _getch()) != '\r')
		{
			str[i++] = c;
			_putch('*');
		}
		str[i] = '\0';
		password = str;
		if (login == "admin" && password == "1111")
		{
			check = 1;
			Adm_menu1();
		}
		for (int i = 0; password[i] != '\0'; i++) { password[i] = password[i] + 3; }

		while (file)
		{
			string str;
			string loginf;
			string passwordf;
			bool role = 0;
			getline(file, str);
			if (str == "") break;

			int j = 0;
			for (; str[j] != ' '; j++)loginf.push_back(str[j]);
			j++;
			for (; str[j] != ' '; j++) passwordf.push_back(str[j]);
			j++;
			if (str[j] == '1') role = 1;
			else role = 0;
			if (passwordf == password && loginf == login)
			{
				check = 1;
				if (role == 0) /*User_menu()*/;
				else
				{
					int switc = -1;
					while (switc != 0)
					{
						system("cls");
						cout << "________________________________________________________________________________________________________________\n";
						cout << "|У якое меню вы хочаце патрапіць:                                                                              |\n";
						cout << "|1. Працы з уліковымі запісамі                                                                                +|\n";
						cout << "|2. Працы са складам                                                                                          +|\n";
						cout << "|3. Меню карыстальніка                                                                                         |\n";
						cout << "|0. Cкончыць працу                                                                                            +|\n";
						cout << "|______________________________________________________________________________________________________________|\n";
						switc = input_and_check(0, 3);
						switch (switc)
						{
						case 1:
							Adm_menu1();
							break;
						case 2:
							/*Adm_menu2();*/
							break;
						case 3:
							/*User_menu();*/
							break;
						default:
							break;
						}
					}
				}
			}
		}
		if (check == 0)
		{
			//system("cls");
			cout << "Прабачце, але вы не здолелі прайсці аўтарызацыю\n";
		}

		file.close();
	}
}

void Adm_menu1()
{

	int switcher = -1;
	int size_of_mas = 0;
	shared_ptr<shared_ptr<User>[]> mas(new shared_ptr<User>[100]);
	//char a;

	ifstream file;
	file.open("UserFile.txt");
	if (!file.is_open())cout << "памылка";
	system("cls");

	while (file)
	{
		string str;
		string login;
		string password;
		bool role = 0;
		getline(file, str);
		if (str == "") break;

		int j = 0;
		for (; str[j] != ' '; j++)login.push_back(str[j]);
		j++;
		for (; str[j] != ' '; j++) password.push_back(str[j]);
		j++;
		if (str[j] == '1') role = 1;
		else role = 0;
		for (int i = 0; password[i] != '\0'; i++) { password[i] = password[i] - 3; }

		mas[size_of_mas] = From_file_to_massiv(login, password, role);
		size_of_mas++;
	}
	while (switcher != 0 && switcher != 5)
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                             Меню адміністратара 1                                            |\n";
		cout << "|1. стварыць новыя ўліковыя запісы                                                                            +|\n";
		cout << "|2. праглядзець існуючыя ўліковыя запісы                                                                      +|\n";
		cout << "|3. адрэдагаваць уліковы запіс                                                                                +|\n";
		cout << "|4. выдаліць уліковы запіс                                                                                    +|\n";
		cout << "|5. выдаліць усе уліковыя запісы (і выйсці)                                                                   +|\n";
		cout << "|0. выхад (захоўвае змены ў файл, не ігнаруйце яго)                                                           +|\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		cin.clear();
		switcher = input_and_check(0, 5);
		switch (switcher)
		{
		case 1:
		{
			system("cls");
			cout << "Увядзіце колькасць ствараемых запісаў: ";
			int size;
			cin >> size;
			for (int i = 0; i < size; i++)
			{

				mas[size_of_mas] = Create_User();
				size_of_mas++;
			}
			break;
		}
		case 2:
		{

			Show_ac(&mas, size_of_mas);
			break;
		}
		case 3:
		{
			redact_user(&mas, size_of_mas);
			break;
		}
		case 4:
		{
			delete_s(&mas, size_of_mas);
			break;
		}
		case 5:
		{
			ofstream file;
			file.open("UserFile.txt", ofstream::trunc);
			file.close();
			break;
		}
		case 0:
		{
			ofstream file;
			file.open("UserFile.txt", ofstream::out);
			file.close();
			ofstream fole;
			fole.open("Add.txt", ofstream::out);
			fole.close();
			for (int i = 0; i < size_of_mas; i++)
			{
				mas[i]->Save_to_file();
			}
			break;
		}
		default:
		{break; }
		}
	}
}



void Show_ac(shared_ptr<shared_ptr<User>[]>* mas, int size_of_mas)
{
	char a;
	system("cls");
	cout << "_____________________________________\n";
	cout << "|        Спіс уліковых запісаў      |\n";
	cout << "|___________________________________|\n";
	cout << "|    Лагін   | Пароль |   Роля      |\n";


	for (int i = 0; i < size_of_mas; i++)
	{
		cout << "|" << i + 1 << ".";
		(*mas)[i]->show();
	}
	cout << "|___________________________________|\n";
	if (size_of_mas == 0)
		cout << "каб паглядзець уліковыя запісы, патрэбныя ўліковыя запісы\n";
	cout << "націсніне нешта";
	a = _getch();
}

void redact_user(shared_ptr<shared_ptr<User>[]>* mas, int& size_of_mas)
{
	Show_ac(mas, size_of_mas);
	cout << "\nАбярыце нумар рэдаруемага запісу: ";
	int num = input_and_check(1, size_of_mas) - 1;
	(*mas)[num] = Create_User();
}

void delete_s(shared_ptr<shared_ptr<User>[]>* mas, int& size_of_mas)
{
	Show_ac(mas, size_of_mas);
	cout << "\nАбярыце нумар выдаляемага запісу: ";
	int num = input_and_check(1, size_of_mas) - 1;
	int counter;
	for (counter = num; counter < size_of_mas; counter++)
	{
		(*mas)[counter] = (*mas)[counter + 1];
	}
	size_of_mas--;
}

void User::show()
{
	if (!cout.good()) cout << "паток памёр";
	cout.setf(ios::left);
	cout << setw(10) << login << "|" << setw(8) << password << "|" << setw(13);
	if (role == 0) cout << "карыстальнік" << "|" << endl;
	else cout << "адміністратар" << "|" << endl;
	cout.unsetf(ios::right);
}

void create_list()
{
	ofstream new_file;
	new_file.open("ListFile.txt");
	if (!new_file.is_open())
		cout << "памылка";
	else cout << "файл створан\n";
	new_file.close();
}

