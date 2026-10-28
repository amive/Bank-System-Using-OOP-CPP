#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
class clsAddNewClientScreen : protected clsScreen
{
	static void _readNewClientInfo(clsBankClient& c) {
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
	static void addNewClient() {
		if (!checkAccessRights(clsUser::enPermissions::AddNewClient)) return;

		string title = "Add New Client Screen";
		_DrawScreenHeader(title);

		string accNum = "";
		cout << "Enter account number: ";
		accNum = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(accNum)) {
			cout << "Account number already exists, Enter a different one: ";
			accNum = clsInputValidate::ReadString();
		}

		cout << "\n---New client info---\n";
		clsBankClient client = clsBankClient::getAddNewClientObject(accNum);
		_readNewClientInfo(client);

		clsBankClient::enSaveResults saveResult = client.Save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "Error: Failed to add new client";
			break;
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "New client added successfully!";
			break;
		case clsBankClient::enSaveResults::svFaildAccNumExists:
			cout << "Error: Account number already exists.";
			break;
		}

		_printClient(client);
	}
};

