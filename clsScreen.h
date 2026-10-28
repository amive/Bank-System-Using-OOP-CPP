#pragma once
#include <iostream>
#include "Global.h"
#include "clsAccessDeniedScreen.h"
#include "clsDate.h"
using namespace std;



class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << ":::===:::===:::===:::===:::===:::===:::" << endl;
        cout << "\n\t" << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t" << SubTitle;
        }
        cout << "\n\n:::===:::===:::===:::===:::===:::===:::\n" << endl;
        cout <<" User: " << currentUser.UserName << endl;
        cout <<" Date: " << clsDate::DateToString(clsDate()) << endl << endl;
    }

    static bool checkAccessRights(clsUser::enPermissions permission) {
        if (!currentUser.checkPermission(permission)) {
            clsAccessDeniedScreen::showAccessDeniedScreen();
            return false;
        }
        else return true;
    }

};

