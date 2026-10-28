#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchange : protected clsScreen
{
	static void _listCurrencies(){
		clsListCurrenciesScreen::listCurrencies();
	}

	static void _findCurrencies(){
		clsFindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _updateRate(){
		clsUpdateCurrencyRateScreen::showUpdateCurrencyRateScreen();
	}
	
	static void _currencyCalculator(){
		clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
	}

	static void _goBackToCurrencyExchangeMenu() {
		cout << "\nPress any key to go back to manage users menu...";
		system("pause > 0");
		displayCurrencyExchangeScreen();
	}

	enum enCurrencyExchangeMenuOption { eListCurrencies = 1, eFindCurrencies = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5 };
	static short _readCurrencyExchangeMenuChoice() {
		short choice;
		cout << "\nChoose an option [1-5]: ";
		choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Not a menu option, enter again: ");
		return choice;
	}

	static void _CurrencyExchangeNavigation(enCurrencyExchangeMenuOption option) {
		switch (option) {
		case eListCurrencies:
			system("cls");
			_listCurrencies();
			_goBackToCurrencyExchangeMenu();
			break;
		case eFindCurrencies:
			system("cls");
			_findCurrencies();
			_goBackToCurrencyExchangeMenu();
			break;
		case eUpdateRate:
			system("cls");
			_updateRate();
			_goBackToCurrencyExchangeMenu();
			break;
		case eCurrencyCalculator:
			system("cls");
			_currencyCalculator();
			_goBackToCurrencyExchangeMenu();
			break;
		case eMainMenu:
			return;
		}
	}
public:
	static void displayCurrencyExchangeScreen() {
		if (!checkAccessRights(clsUser::enPermissions::CurrencyExchange)) return;

		system("cls");
		_DrawScreenHeader("Currency Exchange Screen");
		cout << "   [1] List Currencies" << endl;
		cout << "   [2] Find Currencies" << endl;
		cout << "   [3] Update Rate" << endl;
		cout << "   [4] Currency Calculator" << endl;
		cout << "   [5] Main Menu" << endl;
		cout << "======================================" << endl;
		_CurrencyExchangeNavigation((enCurrencyExchangeMenuOption)_readCurrencyExchangeMenuChoice());
	}
};

