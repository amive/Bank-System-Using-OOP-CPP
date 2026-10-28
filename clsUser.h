#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include <vector>
#include <fstream>
using namespace std;

class clsUser : public clsPerson
{
	enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2, deleteMode = 3 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::updateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::decrypt(vUserData[5]), stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::encrypt(User.Password) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    bool _Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::emptyMode, "", "", "", "", "", "", 0);
    }

    string _PrepareLogDataLine(string delimeter = "#//#") {
        return clsDate::GetSystemDateTimeString() + delimeter + this->_UserName + delimeter + clsUtil::encrypt(this->_Password)
            + delimeter + to_string(this->_Permissions);
    }

public:
    //Logs
    void AddLogDataToFile()
    {
        string logData = _PrepareLogDataLine();

        fstream MyFile;
        MyFile.open("log.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << logData << endl;

            MyFile.close();
        }

    }

    enum enPermissions {
        All = -1,
        ShowClientList = 1,
        AddNewClient = 2,
        DeleteClient = 4,
        UpdateClient = 8,
        FindClient = 16,
        Transactions = 32,
        ManageUsers = 64,
        LoginRecord = 128,
        CurrencyExchange = 256
    };

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, string username, string password, int permissions) : clsPerson(firstName, lastName, email, phone) {
        _Mode = mode;
        _UserName = username;
        _Password = password;
        _Permissions = permissions;
	}

    bool IsEmpty()
    {
        return (_Mode == enMode::emptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::emptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::updateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::addNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::updateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        case enMode::deleteMode:
            if (!clsUser::IsUserExist(_UserName)) {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _Delete();

                _Mode = enMode::updateMode;
                return enSaveResults::svSucceeded;
            }
        }

    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }


    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::addNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    static clsUser getDeleteUserObject(string username) {
        clsUser user = clsUser::Find(username);
        user._Mode = enMode::deleteMode;
        return user;
    }
    
    bool checkPermission(int perm) {
        if (this->Permissions == enPermissions::All) return true;
        return this -> Permissions & perm;
    }

};