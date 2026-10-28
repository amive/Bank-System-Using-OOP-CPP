#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

using namespace std; 
class clsInputValidate
{
	template <typename t> static bool _IsNumberBetween(t Number, t From, t To) {
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	template <typename t> static t _readNumber(string errorMsg) {
		t Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMsg;
		}
		return Number;
	}

	template <typename t> static t _readNumberBetween(t From, t To, string errorMsg) {
		t Number = _readNumber<t>(errorMsg);

		while (!_IsNumberBetween<t>(Number, From, To))
		{
			cout << errorMsg;
			Number = _readNumber<t>(errorMsg);
		}
		return Number;
	}
public:


	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		return _readNumber<int>(ErrorMessage);
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		return _readNumberBetween<int>(From, To, ErrorMessage);
	}

	static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again: ")
	{
		return _readNumber<float>(ErrorMessage);
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		return _readNumberBetween<float>(From, To, ErrorMessage);
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		return _readNumber<double>(ErrorMessage);
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		return _readNumberBetween<double>(From, To, ErrorMessage);
	}

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract all the whitespace characters
		getline(cin >> ws, S1);
		return S1;
	}

	static bool yesNo() {
		char choice = 'Y';
		cin >> choice;
		return (choice == 'Y' || choice == 'y') ? true : false;
	}
};

