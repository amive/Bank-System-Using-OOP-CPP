#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
using namespace std;

class clsLogout
{
public:
	static void logout() {
		currentUser = clsUser::Find("", "");
	}
};

