#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
class clsDeleteClientScreen : protected clsScreen
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
	static void deleteClient() {
		if (!checkAccessRights(clsUser::enPermissions::DeleteClient)) return;

		string title = "Delete Client Screen";
		_DrawScreenHeader(title);

		string accNum = "";
		cout << "Enter account number: ";
		accNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(accNum)) {
			cout << "Account number doesn't exist, Enter a different one: ";
			accNum = clsInputValidate::ReadString();
		}

		cout << "\n--Delete Client--" << endl;
		clsBankClient client = clsBankClient::Find(accNum);
		_printClient(client);

		cout << "\nAre you sure (Y/N)? ";
		if (!clsInputValidate::yesNo()) {
			return;
		}
		else {

			client = clsBankClient::getDeleteClientObject(accNum);
			clsBankClient::enSaveResults saveResult = client.Save();

			switch (saveResult) {
			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "Error: Failed to delete client";
				break;
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "Client deleted successfully!";
				break;
			}
		}
	}
};

