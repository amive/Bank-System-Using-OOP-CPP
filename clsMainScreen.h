#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsLogout.h"
#include "clsLoginRecord.h"
#include "clsCurrencyExchange.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	static void _showClientListScreen() {
		clsClientListScreen::showClientsList();
	}

	static void _addNewClientScreen() {
		clsAddNewClientScreen::addNewClient();

	}

	static void _deleteClientScreen() {
		clsDeleteClientScreen::deleteClient();

	}

	static void _updateClientScreen() {
		clsUpdateClientScreen::updateClient();
	}

	static void _findClientScreen() {
		clsFindClientScreen::showFindClientScreen();
	}

	static void _transactionsScreen() {
		clsTransactionsScreen::displayTransactionsMenuScreen();
	}

	static void _manageUsersScreen() {
		clsManageUsers::displayManageUsersScreen();
	}

	static void _loginRecordScreen() {
		clsLoginRecord::displayLoginRecordScreen();
	}

	static void _currencyExchangeScreen() {
		clsCurrencyExchange::displayCurrencyExchangeScreen();
	}

	static void _logout() {
		clsLogout::logout();
	}




	static void _goBackToMainMenu() {
		cout << "\nPress any key to go back to main menu..." << endl;
		system("pause>0");
		displayMainMenuScreen();
	}

	static void _goBackToMainMenuNoPause() {
		displayMainMenuScreen();
	}

	enum enMainMenuOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eLoginRecord = 8 ,eCurrencyExchange = 9, eExit = 0
	};
	static short _readMenuChoice() {
		short choice;
		cout << "\nChoose an option [0-9]: ";
		choice = clsInputValidate::ReadIntNumberBetween(0,9,"Not a menu option, Enter again: ");
		return choice;
	}
	
	static void _menuNavigation(enMainMenuOptions option) {
		switch (option) {
		case eListClients:
			system("cls");
			_showClientListScreen();
			_goBackToMainMenu();
			break;
		case eAddNewClient:
			system("cls");
			_addNewClientScreen();
			_goBackToMainMenu();
			break;
		case eDeleteClient:
			system("cls");
			_deleteClientScreen();
			_goBackToMainMenu();
			break;
		case eUpdateClient:
			system("cls");
			 _updateClientScreen();
			_goBackToMainMenu();
			break;
		case eFindClient:
			system("cls");
			_findClientScreen();
			_goBackToMainMenu();
			break;
		case eShowTransactionsMenue:
			system("cls");
			_transactionsScreen();
			_goBackToMainMenu();
			break;
		case eManageUsers:
			system("cls");
			_manageUsersScreen();
			_goBackToMainMenu();
			break;
		case eLoginRecord:
			system("cls");
			_loginRecordScreen();
			_goBackToMainMenu();
			break;
		case eCurrencyExchange:
			system("cls");
			_currencyExchangeScreen();
			_goBackToMainMenu();
			break;
		case eExit:
			system("cls");
			_logout();

		}
	}


public:
	static void displayMainMenuScreen() {

		system("cls");
		_DrawScreenHeader("\tMain Menu");
		cout << "   [1] Show Client List" << endl;
		cout << "   [2] Add New Client" << endl;
		cout << "   [3] Delete Client" << endl;
		cout << "   [4] Update Client Info" << endl;
		cout << "   [5] Find Client" << endl;
		cout << "   [6] Transactions" << endl;
		cout << "   [7] Manage Users" << endl;
		cout << "   [8] Login Record" << endl;
		cout << "   [9] Currency Exchange" << endl;
		cout << "   [0] Logout" << endl;
		cout << "======================================" << endl;
		_menuNavigation((enMainMenuOptions) _readMenuChoice());

	}

	
};

