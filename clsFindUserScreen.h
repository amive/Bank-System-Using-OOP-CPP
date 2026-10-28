#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsUser.h"
#include <iomanip>
class clsFindUserScreen : protected clsScreen
{
	static void _printUser(clsUser user)
	{
		cout << "\nUser's details:" << endl;
		cout << "-------------------------------------" << endl;
		cout << "Username: " << user.UserName << endl;
		cout << "FullName: " << user.FullName() << endl;
		cout << "Email: " << user.Email << endl;
		cout << "Phone: " << user.Phone << endl;
		cout << "Password: " << user.Password << endl;
		cout << "Permissions: " << user.Permissions << endl;
		cout << "-------------------------------------" << endl;

	}
public:
	static void showFindUserScreen() {

		_DrawScreenHeader("Find User Screen");


		string username = "";
		cout << "Enter username: ";
		username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(username)) {
			cout << "Username does not exist, Enter a different one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::Find(username);
		cout << "\n\n\t<| User found! |>" << endl;
		_printUser(user);
	}
};

