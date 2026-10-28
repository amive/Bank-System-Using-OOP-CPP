#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"
class clsListUsersScreen : clsScreen
{
	static void _printUsersTableHeader() {
		cout << "\n______________________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(14) << "Username" << "| " << left << setw(21) << "FullName" << "| " << left << setw(12) << "Phone" 
			<< "| " << left << setw(32) << "Email" << "| " << left << setw(15)
			<< "Password" << "| " << left << setw(22) << "Permissions" << endl;
		cout << "______________________________________________________________________________________________________________________\n\n";
	}

	static void _printUserRecordLine(clsUser user) {
		cout << "| " << left << setw(14) << user.UserName << "| " << left << setw(21) << user.FullName() << "| " << left << setw(12) << user.Phone
			<< "| " << left << setw(32) << user.Email << "| " << left << setw(15)
			<< user.Password << "| " << left << setw(22) << user.Permissions << endl;
	}

	static void _printAllUsers() {
		vector <clsUser> vUsers = clsUser::GetUsersList();
		if (vUsers.size() > 0) {
			for (clsUser& u : vUsers) {
				_printUserRecordLine(u);
			}
		}
		else cout << clsString::tabs(6) << "No users available." << endl;
		cout << "______________________________________________________________________________________________________________________";

	}
public:
	static void listUsers() {
		vector <clsUser> vUsers = clsUser::GetUsersList();
		string title = "   List Users Screen";
		string subTitle = to_string(vUsers.size()) + " User(s).";
		_DrawScreenHeader(title, subTitle);
		_printUsersTableHeader();
		_printAllUsers();
	}
};

