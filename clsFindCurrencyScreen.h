#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include <iomanip>
class clsFindCurrencyScreen : protected clsScreen
{
	static void _printCurrencyCard(clsCurrency c)
	{
		cout << "\nCurrency card:" << endl;
		cout << "-------------------------------------" << endl;
		cout << "Country: " << c.Country() << endl;
		cout << "Code: " << c.CurrencyCode() << endl;
		cout << "Name: " << c.CurrencyName() << endl;
		cout << "Rate(1$): " << c.Rate() << endl;
		cout << "-------------------------------------" << endl;
	}
public:
	static void showFindCurrencyScreen() {
		_DrawScreenHeader("Find Currency Screen");

		clsCurrency currency = clsCurrency::FindByCode("DZD");
		int choice = 1;
		cout << "Find by [1] Code - [2] Country: ";
		choice = clsInputValidate::ReadIntNumberBetween(1,2,"Not an option enter again: ");
		if (choice == 1) {
			string code = "";
			cout << "Enter currency code (XXX): ";
			code = clsInputValidate::ReadString();
			currency = clsCurrency::FindByCode(code);
			while (currency.IsEmpty()) {
				cout << "Currency code does not exist, Enter a different one: ";
				code = clsInputValidate::ReadString();
				currency = clsCurrency::FindByCode(code);
			}
		}
		else {
			string country = "";
			cout << "Enter currency country: ";
			country = clsInputValidate::ReadString();
			currency = clsCurrency::FindByCountry(country);
			while (currency.IsEmpty()) {
				cout << "Currency country does not exist, Enter a different one: ";
				country = clsInputValidate::ReadString();
				currency = clsCurrency::FindByCountry(country);
			}
		}
		cout << "\n\n\t- Currency found! -" << endl;
		_printCurrencyCard(currency);
	}
};

