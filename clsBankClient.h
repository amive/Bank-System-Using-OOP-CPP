#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode {
        EmptyMode = 0, UpdateMode = 1, AddNewMode = 2, deleteMode = 3
    };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient& C : vClients)
            {
                if (!C._MarkedForDelete) {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveClientsDataToFile(_vClients);

    }

    void _AddNew() {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _Delete() {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C._AccountNumber == _AccountNumber) {
                C._MarkedForDelete = true;
            }
        }
        _SaveClientsDataToFile(_vClients);
        *this = _GetEmptyClientObject();

    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _PrepareTransferLogDataLine(clsBankClient to, double amount, string username, string delimeter = "#//#") {
        return clsDate::GetSystemDateTimeString() + delimeter + this -> AccountNumber() + delimeter + to.AccountNumber()
            + delimeter + to_string(amount) + delimeter + to_string(this->AccountBalance) + delimeter + to_string(to.AccountBalance) + delimeter + username;
    }

public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults {
        svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccNumExists
        = 2
    };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
            if (clsBankClient::IsClientExist(_AccountNumber)) {
                return enSaveResults::svFaildAccNumExists;
            }
            else
            {
                _AddNew();

                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

        case enMode::deleteMode:
            if (!clsBankClient::IsClientExist(_AccountNumber)) {
                return enSaveResults::svFaildAccNumExists;
            }
            else
            {
                _Delete();

                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }



    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient getAddNewClientObject(string accNum) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", accNum, "", 0);
    }

    static clsBankClient getDeleteClientObject(string accNum) {
        clsBankClient client = clsBankClient::Find(accNum);
        client._Mode = enMode::deleteMode;
        return client;
    }

    static vector <clsBankClient> getClientsList() {
        vector <clsBankClient> clientsList = _LoadClientsDataFromFile();
        return clientsList;
    }

    static double getTotalBalances() {
        vector <clsBankClient> clientsList = _LoadClientsDataFromFile();
        double totalBal = 0;
        for (clsBankClient& c : clientsList) {
            totalBal += c.AccountBalance;
        }
        return totalBal;
    }

    void Deposit(double amount) {
        _AccountBalance += amount;
    }

    bool Withdraw(double amount) {
        if (amount <= _AccountBalance) {
            _AccountBalance -= amount;
            return true;
        }
        else return false;
    }

    bool Transfer(clsBankClient& receiver, double amount, string username) {
        if (!Withdraw(amount)) {
            return false;
        }

        receiver.Deposit(amount);
        AddTransferLogDataToFile(receiver, amount, username);
        return true;
    
    }

    void AddTransferLogDataToFile(clsBankClient to, double amount, string username)
    {
        string logData = _PrepareTransferLogDataLine(to, amount, username);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << logData << endl;

            MyFile.close();
        }

    }
};