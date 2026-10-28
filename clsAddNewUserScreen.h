#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"
class clsAddNewUserScreen : protected clsScreen
{

	static void _readNewUserInfo(clsUser& u) {
		cout << "First name: ";
		u.FirstName = clsInputValidate::ReadString();
		cout << "Last name: ";
		u.LastName = clsInputValidate::ReadString();
		cout << "Email: ";
		u.Email = clsInputValidate::ReadString();
		cout << "Phone: ";
		u.Phone = clsInputValidate::ReadString();
		cout << "Password: ";
		u.Password = clsInputValidate::ReadString();
		cout << "Permissions: ";
		u.Permissions = _readPermissions();
	}
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

	static int _readPermissions() {
		cout << "\nFull access (Y/N): ";
		//Full access
		if (clsInputValidate::yesNo()) return -1;
		int permissions = 0;

		cout << "\nAccess List:\n";

		cout << "Show clients list (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::ShowClientList;
		}

		cout << "Add new client (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::AddNewClient;
		}

		cout << "Delete client (Y/N): ";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::DeleteClient;
		}

		cout << "Update Client (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::UpdateClient;
		}

		cout << "Find Client (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::FindClient;
		}

		cout << "Transactions (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::Transactions;
		}

		cout << "Manage Users (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::ManageUsers;
		}

		cout << "Login Record (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::LoginRecord;
		}

		cout << "Currency Exchange (Y/N):";
		if (clsInputValidate::yesNo()) {
			permissions |= clsUser::enPermissions::CurrencyExchange;
		}

		if (permissions == 511) return -1;

		return permissions;
	}

public:
	static void addNewUser() {

		string title = "Add New User Screen";
		_DrawScreenHeader(title);

		string username = "";
		cout << "Enter Username: ";
		username = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(username)) {
			cout << "Username already exists, Enter a different one: ";
			username = clsInputValidate::ReadString();
		}

		cout << "\n---New client info---\n";
		clsUser user = clsUser::GetAddNewUserObject(username);
		_readNewUserInfo(user);

		clsUser::enSaveResults saveResult = user.Save();

		switch (saveResult) {
		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "Error: Failed to add new user";
			break;
		case clsUser::enSaveResults::svSucceeded:
			cout << "New user added successfully!";
			break;
		case clsUser::enSaveResults::svFaildUserExists:
			cout << "Error: Username already exists.";
			break;
		}

		_printUser(user);
	}
};

