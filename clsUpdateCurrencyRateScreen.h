#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include <iomanip>
class clsUpdateCurrencyRateScreen : protected clsScreen
{
	static float _readNewRate() {
		cout << "\nEnter new rate: ";
		float rate = clsInputValidate::ReadFloatNumber();
		return rate;
	}

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
	static void showUpdateCurrencyRateScreen() {
		string title = "Update Currency Rate Screen";
		_DrawScreenHeader(title);

		string code = "";
		cout << "Enter currency code: ";
		code = clsInputValidate::ReadString();
		clsCurrency currency = clsCurrency::FindByCode(code);
		while (currency.IsEmpty()) {
			cout << "Currency code does not exist, Enter a different one: ";
			code = clsInputValidate::ReadString();
			currency = clsCurrency::FindByCode(code);
		}


		_printCurrencyCard(currency);

		cout << "\n---Update currency rate---\n";

		cout << "~Confirm (Y/n): ";
		if (clsInputValidate::yesNo()) currency.UpdateRate(_readNewRate());
		else return;

		cout << "\n~Rate updated successfully!" << endl;
		_printCurrencyCard(currency);


	}
};

