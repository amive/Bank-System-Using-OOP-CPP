#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsUtil.h"

class clsLoginRecord : protected clsScreen
{
	string _date, _username, _password;
	int _perms = 0;
	
	static clsLoginRecord _ConvertLinetoLogObject(string Line, string Seperator = "#//#")
	{
		vector <string> vLogData;
		vLogData = clsString::Split(Line, Seperator);

		return clsLoginRecord(vLogData[0], vLogData[1], vLogData[2], stoi(vLogData[3]));
		

	}

	static  vector <clsLoginRecord> _LoadLogDataFromFile()
	{

		vector <clsLoginRecord> vLogData1;

		fstream MyFile;
		MyFile.open("log.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsLoginRecord logRecord = _ConvertLinetoLogObject(Line);

				vLogData1.push_back(logRecord);
			}

			MyFile.close();

		}

		return vLogData1;

	}

	static void _printLogTableHeader() {
		cout << "\n______________________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(24) << "Date & time" << "| " << left << setw(28) << "Username" << "| " 
				     << left << setw(32) << "Password" << "| " << left << setw(18) << "Permissions" << endl;
		cout << "______________________________________________________________________________________________________________________\n\n";
	}

	static void _printLogRecordLine(clsLoginRecord r) {
		cout << "| " << left << setw(24) << r._date << "| " << left << setw(28) 
			<< r._username << "| " << left << setw(32) << clsUtil::decrypt(r._password) << "| " << left << setw(18) << r._perms << endl;
	}

	static void _printAllLogRecords() {
		vector <clsLoginRecord> vLogData = clsLoginRecord::_LoadLogDataFromFile();
		if (vLogData.size() > 0) {
			for (clsLoginRecord& r : vLogData) {
				_printLogRecordLine(r);
			}
		}
		else cout << clsString::tabs(6) << "No log available." << endl;
		cout << "______________________________________________________________________________________________________________________";

	}
public:
	clsLoginRecord(string date, string username, string password, int perms) {
		_date = date;
		_username = username;
		_password = password;
		_perms = perms;
	};

	static void displayLoginRecordScreen() {
		if (!checkAccessRights(clsUser::enPermissions::LoginRecord)) return;
			vector <clsLoginRecord> vLogData = _LoadLogDataFromFile();
			string title = "   Login Record";
			string subTitle = to_string(vLogData.size()) + " Record(s).";
			_DrawScreenHeader(title, subTitle);
			_printLogTableHeader();
			_printAllLogRecords();
	}
};

