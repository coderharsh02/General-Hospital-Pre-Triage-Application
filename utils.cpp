//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
	bool debug = false; // made global in utils.h
	int getTime()
	{
		int mins = -1;
		if (debug)
		{
			Time t(0);
			cout << "Enter current time: ";
			do
			{
				cin.clear();
				cin >> t; // needs extraction operator overloaded for Time
				if (!cin)
				{
					cout << "Invlid time, try agian (HH:MM): ";
					cin.clear();
				}
				else
				{
					mins = int(t);
				}
				cin.ignore(1000, '\n');
			} while (mins < 0);
		}
		else
		{
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			mins = lt.tm_hour * 60 + lt.tm_min;
		}
		return mins;
	}
	int getInt(const char* prompt)
	{
		if (prompt)
			cout << prompt;
		int x;
		cin >> x;
		while (cin.fail() || cin.get() != '\n')
		{
			if (cin.fail())
				cout << "Bad integer value, try again: ";
			else
				cout << "Enter only an integer, try again: ";
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> x;
		}
		return x;
	}
	int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
	{
		int x = getInt(prompt);
		while (x < min || x > max)
		{
			cout << errorMessage;
			if (showRangeAtError)
				cout << "[" << min << " <= value <= " << max << "]: ";
			x = getInt();
		}
		return x;
	}
	char *getcstr(const char *prompt, std::istream &istr, char delimiter)
	{
	   if (prompt)
		  cout << prompt;
	   char *inpStr = new char[1023];
	   char c;
	   int count = 0;
	   while ((c = istr.get()) != '\n' && (c != delimiter) && c!=-1)
	   {
		  inpStr[count++] = c;
	   }
	   inpStr[count] = '\0';
	   return inpStr;
	}
	int stringToInt(const char* s)
	{
		int integer = 0, i = 0;
		if (s[0] == '-')
			i = 1;

		for (; s[i] != '\0'; i++)
		{
			integer = integer * 10 + (s[i] - '0');
		}
		if (s[0] == '-')
			integer = -integer;

		return integer;
	}
	std::ostream& showString(std::ostream& ostr, const char* str, int limit)
	{
		for (int i = 0; i < limit && str[i] != '\0'; i++)
		{
			cout << str[i];
		}
		return ostr;
	}
}