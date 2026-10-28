#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include <iomanip>
class clsCurrencyCalculatorScreen : protected clsScreen
{
	static float _readAmount() {
		cout << "\n~Enter amount to exchange: ";
		float amount = clsInputValidate::ReadFloatNumber();
		return amount;
	}

	static clsCurrency _getCurrency(string message) {
		cout << message;
		string c = clsInputValidate::ReadString();
		clsCurrency currency = clsCurrency::FindByCode(c);
		while (currency.IsEmpty()) {
			cout << "Currency code does not exist, Enter a different one: ";
			c = clsInputValidate::ReadString();
			currency = clsCurrency::FindByCode(c);
		}

		return currency;
	}

public:
	static void showCurrencyCalculatorScreen() {

		string title = "Currency Calculator Screen";
		_DrawScreenHeader(title);

		clsCurrency currency1 = _getCurrency("\n~Enter the first currency code: ");

		clsCurrency currency2 = _getCurrency("\n~Enter the second currency code: ");

		float amount = _readAmount();

		float exchangedAmount = currency1.convertToAnotherCurrency(amount, currency2);

		cout << "\n---------------------------------------------------" << endl;
		cout << clsString::tabs(2) << amount << currency1.CurrencyCode() << " = " << exchangedAmount << currency2.CurrencyCode() << endl;
		cout << "---------------------------------------------------" << endl;

		cout << "\nPerform another operation (Y/n)? ";
		if (clsInputValidate::yesNo()) {
			system("cls");
			showCurrencyCalculatorScreen();
		}
	}
};

