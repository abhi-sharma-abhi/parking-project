/***********************************************************************
// Utils Module
// File  utils.cpp
// Version 0.0
// Date
// Author
// Description
// Estra Classes and functions needed in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "Utils.h"

namespace sdds {
	int strlen(const char str[]) {
		if (str == nullptr) return 0;
	    int len = 0;
	    while (str[len] != '\0') len++;
	    return len;
	}

	char* strcpy(const char original[]) {
		if (original == nullptr) return nullptr;
	    int n = strlen(original);
	    char* copy = new char[n+1];
	    for (int i=0; i<n; i++) {
	      copy[i] = original[i];
	    }
	    copy[n] = '\0';
	    return copy;
	}

	bool strcmp(const char* str1, const char str2[]) {
		int n1 = strlen(str1);
		int n2 = strlen(str2);

		if (n1 != n2) return false;

		for (int i=0; i<n1; i++) {
			if (str1[i] != str2[i]) return false;
		}
		return true;
	}

	int ctoi(const char str[]) {
		int ans = 0;
		int len = strlen(str);
		for (int i=len-1; i>=0; i--) {
			int dig = str[i] - '0';
			ans *= 10;
			ans += dig;
		}
		return ans;
	}

	void toUpper(char str[]) {
		int len = strlen(str);
		for (int i=0; i<len; i++) {
			if (str[i]>= 97 && str[i] <= 122) str[i] -= 32;
		}
	}
}