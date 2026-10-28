#pragma once
#include <iostream>
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
class clsClientListScreen : protected clsScreen
{
private:
	static void _printTableHeader() {
		cout << "\n______________________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(21) << "Account Number" << "| " << left << setw(15) <<
			"Pin Code" << "| " << left << setw(32) << "Client Name" << "| " << left << setw(20) <<
			"Phone Number" << "| " << left << setw(15) << "Balance" << left << endl;
		cout << "______________________________________________________________________________________________________________________\n\n";
	}

	static void _printClientRecordLine(clsBankClient client) {
		cout << "| " << left << setw(21) << client.AccountNumber() << "| " << left << setw(15) <<
			client.PinCode << "| " << left << setw(32) << client.FullName() << "| " << left << setw(20) <<
			client.Phone << "| " << left << setw(15) << to_string(client.AccountBalance) << left << endl;
	}

	static void _printAllClients() {
		vector <clsBankClient> vClients = clsBankClient::getClientsList();
		if (vClients.size() > 0) {
			for (clsBankClient& c : vClients) {
				_printClientRecordLine(c);
			}
		}
		else cout << clsString::tabs(6) << "No clients available." << endl;
		cout << "______________________________________________________________________________________________________________________";

	}

public:
	static void showClientsList() {
		if (!checkAccessRights(clsUser::enPermissions::ShowClientList)) return;

		vector <clsBankClient> vClients = clsBankClient::getClientsList();
		string title = "   Clients List Screen";
		string subTitle = to_string(vClients.size()) + " Client(s).";
		_DrawScreenHeader(title, subTitle);
		_printTableHeader();
		_printAllClients();
	}
};

