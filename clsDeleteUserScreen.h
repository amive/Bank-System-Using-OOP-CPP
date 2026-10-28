#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsUser.h"
#include <iomanip>
class clsDeleteUserScreen : protected clsScreen
{
	static void _printClient(clsUser u)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << u.FirstName;
		cout << "\nLastName    : " << u.LastName;
		cout << "\nFull Name   : " << u.FullName();
		cout << "\nEmail       : " << u.Email;
		cout << "\nPhone       : " << u.Phone;
		cout << "\nUsername    : " << u.UserName;
		cout << "\nPassword    : " << u.Password;
		cout << "\nPermissions : " << u.Permissions;
		cout << "\n___________________\n";

	}
public:
	static void deleteUser() {

		string title = "Delete User Screen";
		_DrawScreenHeader(title);

		string username = "";
		cout << "Enter username: ";
		username = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(username)) {
			cout << "Username doesn't exist, Enter a different one: ";
			username = clsInputValidate::ReadString();
		}

		cout << "\n--Delete User--" << endl;
		clsUser user = clsUser::Find(username);
		_printClient(user);

		cout << "\nAre you sure (Y/N)? ";
		if (!clsInputValidate::yesNo()) {
			return;
		}
		else {

			user = clsUser::getDeleteUserObject(username);
			clsUser::enSaveResults saveResult = user.Save();

			switch (saveResult) {
			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "Error: Failed to delete user";
				break;
			case clsUser::enSaveResults::svSucceeded:
				cout << "User deleted successfully!";
				break;
			}
		}
	}
};

