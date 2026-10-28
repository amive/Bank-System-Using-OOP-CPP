#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsCurrency.h"
class clsListCurrenciesScreen : protected clsScreen
{
	static void _printCurrenciesTableHeader() {
		cout << "\n\t_____________________________________________________________________________________________________\n\n";
		cout << "\t| " << left << setw(32) << "Country" << "| " << left << setw(6) << "Code" << "| " << left << setw(45) << "Name"
			<< "| " << left << setw(8) << "Rate(1$)" << " |" << endl;
		cout << "\t_____________________________________________________________________________________________________\n\n";
	}

	static void _printCurrencyLine(clsCurrency c) {
		cout << "\t| " << left << setw(32) << c.Country() << "| " << left << setw(6) << c.CurrencyCode() << "| " << left << setw(45) << c.CurrencyName()
			<< "| " << left << setw(8) << c.Rate() << " |" << endl;
	}

	static void _printAllCurrencies() {
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		if (vCurrencies.size() > 0) {
			for (clsCurrency& c : vCurrencies) {
				_printCurrencyLine(c);
			}
		}
		else cout << clsString::tabs(6) << "No currencies available." << endl;
		cout << "\t_____________________________________________________________________________________________________";

	}
public:
	static void listCurrencies() {
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string title = "   List Currencies Screen";
		string subTitle = to_string(vCurrencies.size()) + " Currencies(s).";
		_DrawScreenHeader(title, subTitle);
		_printCurrenciesTableHeader();
		_printAllCurrencies();
	}
};

