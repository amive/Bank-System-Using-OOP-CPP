#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "clsString.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t:::===:::===:::===:::===:::===:::===:::" << endl;
		cout << "\n\t\t\t\t\t\t\t" << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t" << SubTitle;
		}
		cout << "\n\n\t\t\t\t\t:::===:::===:::===:::===:::===:::===:::\n" << endl;
		cout << "\t\t\t\t\tUser: " << currentUser.UserName << endl;
		cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl << endl;
	}

	static bool _login() {
		system("cls");
		_DrawScreenHeader("Login Screen");

		bool loginStatus = false;
		vector <clsUser> vUsers = clsUser::GetUsersList();
		cout << "\t\t\t\t\tUsername: ";
		string username = clsString::Trim(clsInputValidate::ReadString());
		cout << "\t\t\t\t\tPassword: ";
		string password = clsString::Trim(clsInputValidate::ReadString());
		currentUser = clsUser::Find(username, password);
		loginStatus = !currentUser.IsEmpty();

		short trials = 3;
		while (!loginStatus) {
			system("cls");
			_DrawScreenHeader("Login Screen");
			trials--;

			if (trials > 0) {
				cout << "\t\t\t\t\t\tInvalid Credentials, " << trials << " attempts left." << endl;
				cout << "\t\t\t\t\tUsername: ";
				username = clsString::Trim(clsInputValidate::ReadString());
				cout << "\t\t\t\t\tPassword: ";
				password = clsString::Trim(clsInputValidate::ReadString());
				currentUser = clsUser::Find(username, password);
				loginStatus = !currentUser.IsEmpty();
			}
			else {
				cout << "\n\n [!] Too many incorrect attempts. System locked.\n" << endl;
				return false;
			}
		}
		if (loginStatus && trials > 0) {
			currentUser.AddLogDataToFile();
			clsMainScreen::displayMainMenuScreen();
			return true;
		}
	}
public:


	static bool showLoginScreen() {
		_DrawScreenHeader("Login Screen");
		return _login();
	}

};