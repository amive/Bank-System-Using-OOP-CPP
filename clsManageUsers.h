#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsBankClient.h"
#include "clsUser.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsers : protected clsScreen
{
	static void _listUsers(){
		//cout << "List users";
		clsListUsersScreen::listUsers();
	}
	static void _addNewUser() {
		clsAddNewUserScreen::addNewUser();
	}
	static void _DeleteUser() {
		clsDeleteUserScreen::deleteUser();
	}
	static void _updateUser() {
		clsUpdateUserScreen::updateUser();
	}
	static void _findUser() {
		clsFindUserScreen::showFindUserScreen();
	}


	static void _goBackToManageUsersMenu() {
		cout << "\nPress any key to go back to manage users menu...";
		system("pause > 0");
		displayManageUsersScreen();
	}

	enum enManageUsersMenuOption { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6 };
	static short _readManageUsersMenuChoice() {
		short choice;
		cout << "\nChoose an option [1-6]: ";
		choice = clsInputValidate::ReadIntNumberBetween(1,6,"Not a menu option, enter again: ");
		return choice;
	}

	static void _manageUsersNavigation(enManageUsersMenuOption option) {
		switch (option) {
		case eListUsers:
			system("cls");
			_listUsers();
			_goBackToManageUsersMenu();
			break;
		case eAddNewUser:
			system("cls");
			_addNewUser();
			_goBackToManageUsersMenu();
			break;
		case eDeleteUser:
			system("cls");
			_DeleteUser();
			_goBackToManageUsersMenu();
			break;
		case eUpdateUser:
			system("cls");
			_updateUser();
			_goBackToManageUsersMenu();
			break;
		case eFindUser:
			system("cls");
			_findUser();
			_goBackToManageUsersMenu();
			break;
		case eMainMenu:
			return;
		}
	}

public:

	static void displayManageUsersScreen() {
		if (!checkAccessRights(clsUser::enPermissions::ManageUsers)) return;

		system("cls");
		_DrawScreenHeader("Manage Users Screen");
		cout << "   [1] List Users" << endl;
		cout << "   [2] Add New User" << endl;
		cout << "   [3] Delete User" << endl;
		cout << "   [4] Update User" << endl;
		cout << "   [5] Find User" << endl;
		cout << "   [6] Main Menu" << endl;
		cout << "======================================" << endl;
		_manageUsersNavigation((enManageUsersMenuOption)_readManageUsersMenuChoice());
	}
};

