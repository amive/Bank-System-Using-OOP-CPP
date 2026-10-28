#pragma once
#include <iostream>
#include <iomanip>
class clsAccessDeniedScreen
{
public:
	static void showAccessDeniedScreen() {
		system("cls");
        cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
        cout << "\n\t" << "Access Denied.\n   You cannot access this page.";
        cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
	}
};

