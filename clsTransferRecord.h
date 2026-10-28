#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"


class clsTransferRecord : protected clsScreen
{
	string _date, _sAcc, _rAcc, _sBal, _rBal, _username;
	double _amount;

	static clsTransferRecord _ConvertLinetoTransferLogObject(string Line, string Seperator = "#//#")
	{
		vector <string> vLogData;
		vLogData = clsString::Split(Line, Seperator);

		return clsTransferRecord(vLogData[0], vLogData[1], vLogData[2], stod(vLogData[3]), vLogData[4], vLogData[5], vLogData[6]);


	}

	static  vector <clsTransferRecord> _LoadTransferLogDataFromFile()
	{

		vector <clsTransferRecord> vLogData1;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsTransferRecord logRecord = _ConvertLinetoTransferLogObject(Line);

				vLogData1.push_back(logRecord);
			}

			MyFile.close();

		}

		return vLogData1;

	}

	static void _printLogTableHeader() {
		cout << "\n______________________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(24) << "Date & time" << "| " << left << setw(14) << "s.Acc" << "| "
			<< left << setw(14) << "r.Acc" << "| " << left << setw(14) << "Amount" << "| " << left << setw(14) << "s.Balance" <<
			"| " << left << setw(14) << "r.Balance" << "| " << left << setw(14) << "User" << endl;
		cout << "______________________________________________________________________________________________________________________\n\n";
	}

	static void _printLogRecordLine(clsTransferRecord r) {
		cout << "| " << left << setw(24) << r._date << "| " << left << setw(14) << r._sAcc << "| "
			<< left << setw(14) << r._rAcc << "| " << left << setw(14) << r._amount << "| " << left << setw(14) << r._sBal <<
			"| " << left << setw(14) << r._rBal << "| " << left << setw(14) << r._username << endl;
	}

	static void _printAllLogRecords() {
		vector <clsTransferRecord> vLogData = _LoadTransferLogDataFromFile();
		if (vLogData.size() > 0) {
			for (clsTransferRecord& r : vLogData) {
				_printLogRecordLine(r);
			}
		}
		else cout << clsString::tabs(6) << "No Transfer Log Available." << endl;
		cout << "______________________________________________________________________________________________________________________";

	}

public:
	clsTransferRecord(string date, string sAcc, string rAcc, double amount, string sBal, string rBal, string username) {
		_date = date;
		_sAcc = sAcc;
		_rAcc = rAcc;
		_amount = amount;
		_sBal = sBal;
		_rBal = rBal;
		_username = username;
	};

	static void displayTransferRecordScreen() {
		vector <clsTransferRecord> vLogData = _LoadTransferLogDataFromFile();
		string title = "   Transfer Record";
		string subTitle = to_string(vLogData.size()) + " Record(s).";
		_DrawScreenHeader(title, subTitle);
		_printLogTableHeader();
		_printAllLogRecords();
	};

};