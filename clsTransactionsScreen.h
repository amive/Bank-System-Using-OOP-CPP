#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsTransferRecord.h"
class clsTransactionsScreen : protected clsScreen
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

	static void _printMiniClientCard(clsBankClient c)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << c.FullName();
		cout << "\nAcc. Number : " << c.AccountNumber();
		cout << "\nBalance     : " << fixed << c.AccountBalance;
		cout << "\n___________________\n";

	}

	static void _printTableHeader() {
		cout << "\n______________________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(21) << "Account Number" << "| " << left << setw(47) << "Client Name" << "| " << left << setw(35) << "Balance" << left << endl;
		cout << "______________________________________________________________________________________________________________________\n\n";
	}

	static void _printClientBalanceRecordLine(clsBankClient client) {
		cout << "| " << left << setw(21) << client.AccountNumber() << "| " << left << setw(47) << client.FullName() << "| " << left << setw(35) << to_string(client.AccountBalance) << left << endl;
	}


	static void _deposit() {
		_DrawScreenHeader("Deposit Screen");

		string accNum = "";
		cout << "Enter account number: ";
		accNum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accNum)) {
			cout << "\nClient Not Found, Enter a different account number: ";
			accNum = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accNum);
		_printClient(client);

		float depositAmount = 0;
		cout << "Enter deposit amount: ";
		depositAmount = clsInputValidate::ReadDblNumber();

		cout << "Are you sure you want to perform this transaction (Y/N)? ";
		if (clsInputValidate::yesNo()) {
			client.Deposit(depositAmount);
			client.Save();
			cout << "\nDeposit successfully, New balance: " << client.AccountBalance << endl;
		}
		else cout << "\nOperation canceled." << endl;

	}

	static void _withdraw() {
		_DrawScreenHeader("Withdraw Screen");

		string accNum = "";
		cout << "Enter account number: ";
		accNum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accNum)) {
			cout << "\nClient Not Found, Enter a different account number: ";
			accNum = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accNum);
		_printClient(client);

		float withdrawAmount = 0;
		cout << "Enter withdraw amount: ";
		withdrawAmount = clsInputValidate::ReadDblNumber();
		while (withdrawAmount < 1) {
			cout << "Invalid amount, enter again: ";
			withdrawAmount = clsInputValidate::ReadDblNumber();
		}
		cout << "Are you sure you want to perform this transaction (Y/N)? ";
		if (clsInputValidate::yesNo()) {
			if (client.Withdraw(withdrawAmount)) {
				cout << "\nWithdraw successfully, New balance: " << client.AccountBalance << endl;
			}
			else cout << "\nWithdraw failed, insuffecient balance. \n(Balance: " << client.AccountBalance << ").";
			client.Save();
		}
		else cout << "\nOperation canceled." << endl;
	}

	static void _showTotalBalances() {

		vector <clsBankClient> vClients = clsBankClient::getClientsList();
		string title = "Balances List - " + to_string(vClients.size()) + " Client(s).";
		_DrawScreenHeader(title);
		_printTableHeader();

		double balances = clsBankClient::getTotalBalances();
		if (vClients.size() > 0) {
			for (clsBankClient& c : vClients) {
				_printClientBalanceRecordLine(c);
			}
		}
		else cout << clsString::tabs(6) << "No clients available." << endl;

		cout << "______________________________________________________________________________________________________________________";
		cout << "\n\n" << clsString::tabs(6) << "Total Balances: " << balances << "." << endl;
		cout << clsString::tabs(4) << "   " << "- " << clsUtil::NumberToText(balances) << "-";
	}

	static void _transfer() {
		_DrawScreenHeader("Transfer Screen");

		string senderAccNum = "", receiverAccNum = "";
		cout << "Sender's account number: ";
		senderAccNum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(senderAccNum)) {
			cout << "\nClient Not Found, Enter a different account number: ";
			senderAccNum = clsInputValidate::ReadString();
		}
		clsBankClient sender = clsBankClient::Find(senderAccNum);
		_printMiniClientCard(sender);

		cout << "\nReceiver's account number: ";
		receiverAccNum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(receiverAccNum) || receiverAccNum == senderAccNum) {
			cout << "\nClient Not Found (Can't Send Over to Sender's Account), Enter a different account number: ";
			receiverAccNum = clsInputValidate::ReadString();
		}
		clsBankClient receiver = clsBankClient::Find(receiverAccNum);
		_printMiniClientCard(receiver);

		cout << "\nEnter transfer amount: ";
		double amount = clsInputValidate::ReadDblNumber();
		while (!sender.Transfer(receiver, amount, currentUser.UserName)) {
			cout << "\nAmount exceeds sender's balance, Enter again: ";
			amount = clsInputValidate::ReadDblNumber();
		}
		cout << "\n\t*Transfer Successful*";
		

		cout << endl;
		_printMiniClientCard(sender);
		_printMiniClientCard(receiver);
		sender.Save();
		receiver.Save();

	}

	static void _showTransferLogScreen() {
		clsTransferRecord::displayTransferRecordScreen();
	}

	static void _goBackToTransactionsMenu() {
		cout << "\nPress any key to go back to the transactions menu...";
		system("pause > 0");
		displayTransactionsMenuScreen();
	}

	enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eMainMenu = 6 };
	static short _readTransactionsMenuChoice() {
		short choice;
		cout << "\nChoose an option [1-6]: ";
		choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Not a menu option, Enter again: ");
		return choice;
	}

	static void _transactionsNavigation(enTransactionsMenuOptions option) {
		switch (option) {
		case eDeposit:
			system("cls");
			_deposit();
			_goBackToTransactionsMenu();
			break;
		case eWithdraw:
			system("cls");
			_withdraw();
			_goBackToTransactionsMenu();
			break;
		case eTotalBalances:
			system("cls");
			_showTotalBalances();
			_goBackToTransactionsMenu();
			break;
		case eTransfer:
			system("cls");
			_transfer();
			_goBackToTransactionsMenu();
			break;
		case eTransferLog:
			system("cls");
			_showTransferLogScreen();
			_goBackToTransactionsMenu();
			break;
		case eMainMenu:
			return;
		}
	}
public:

	static void displayTransactionsMenuScreen() {
		if (!checkAccessRights(clsUser::enPermissions::Transactions)) return;

		system("cls");
		_DrawScreenHeader("\tTrasactions Menu");
		cout << "   [1] Deposit" << endl;
		cout << "   [2] Withdraw" << endl;
		cout << "   [3] Total balances" << endl;
		cout << "   [4] Transfer" << endl;
		cout << "   [5] Transfer log" << endl;
		cout << "   [6] Main menu" << endl;
		cout << "=================================" << endl;
		_transactionsNavigation((enTransactionsMenuOptions)_readTransactionsMenuChoice());
	}
};

