#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
class clsUpdateClientScreen : protected clsScreen
{
	static void _readClientInfo(clsBankClient& c) {
		cout << "First name: ";
		c.FirstName = clsInputValidate::ReadString();
		cout << "Last name: ";
		c.LastName = clsInputValidate::ReadString();
		cout << "Email: ";
		c.Email = clsInputValidate::ReadString();
		cout << "Phone: ";
		c.Phone = clsInputValidate::ReadString();
		cout << "Pin: ";
		c.PinCode = clsInputValidate::ReadString();
		cout << "Account balance: ";
		c.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

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
	static void updateClient() {
		if (!checkAccessRights(clsUser::enPermissions::UpdateClient)) return;

		string title = "Update Client Screen";
		_DrawScreenHeader(title);

		string accNum = "";
		cout << "Enter account number: ";
		accNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(accNum)) {
			cout << "Account number does not exist, Enter a different one: ";
			accNum = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accNum);
		_printClient(client);

		cout << "\n---Update client info---\n";
		_readClientInfo(client);
		client.Save();
	}
};

