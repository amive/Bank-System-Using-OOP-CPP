#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
class clsFindClientScreen : protected clsScreen
{
	static void _printClient(clsBankClient c)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << c.FirstName;
		cout << "\nLastName    : " << c.LastName;
		cout << "\nFull Name   : " << c.FullName();
		cout << "\nEmail       : " << c.Email;
		cout << "\nPhone       : " << c.Phone;
		cout << "\nAcc. Number : " << c.AccountNumber();
		cout << "\nPassword    : " << c.PinCode;
		cout << "\nBalance     : " << c.AccountBalance;
		cout << "\n___________________\n";

	}
public:
	static void showFindClientScreen() {
		if (!checkAccessRights(clsUser::enPermissions::FindClient)) return;

		_DrawScreenHeader("Find Client Screen");


		string accNum = "";
		cout << "Enter account number: ";
		accNum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accNum)) {
			cout << "Account number does not exist, Enter a different one: ";
			accNum = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accNum);
		cout << "\n\n\t<| Client found! |>" << endl;
		_printClient(client);
	}
};

