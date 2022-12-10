//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<string>
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds
{
	Time& Time::setToNow()
	{
		m_min = getTime();
		return *this;
	}
	Time::Time(unsigned int min)
	{
		m_min = min;
	}
	std::ostream& Time::write(std::ostream& ostr) const
	{
		unsigned int hrs = m_min / 60;
		unsigned int mins = m_min % 60;
		ostr.width(2);
		ostr.fill('0');
		ostr << hrs << ":";
		ostr.width(2);
		ostr << mins;
		ostr.fill(' ');
		return ostr;
	}
	bool Time::timeMaker(const char* inpStr)
	{
		bool flag = true;
		char sHrs[5], sMins[5];
		int ind = 0;
		bool colonFound = false;
		bool allValid = true;
		for (int i = 0; inpStr[i] != '\0' && allValid; i++)
		{
			if (!(inpStr[i] >= '0' && inpStr[i] <= '9') && inpStr[i] != ':')
			{
				allValid = false;
			}
			if (inpStr[i] == ':')
			{
				if (colonFound || i == 0)
					allValid = false;

				colonFound = true;
				sHrs[ind] = '\0';
				ind = 0;
			}
			else if (!colonFound)
			{
				sHrs[ind++] = inpStr[i];
			}
			else
			{
				sMins[ind++] = inpStr[i];
			}
		}
		sMins[ind] = '\0';
		flag = allValid && colonFound;
		if (flag)
		{
			int hrs = stringToInt(sHrs);
			int mins = stringToInt(sMins);
			m_min = hrs * 60 + mins;
		}
		return flag;
	}
	std::istream& Time::csvRead(std::istream& istr)
	{
		char* inpStr = getcstr(nullptr, istr, ',');
		if (!timeMaker(inpStr)) {
			istr.setstate(ios::failbit);
		}
		delete[] inpStr;
		return istr;
	}
	std::istream& Time::read(std::istream& istr)
	{
		string inpStr;
		getline(istr, inpStr);
		if (!timeMaker(inpStr.c_str()))
		{
			istr.setstate(ios::failbit);
		}
		istr.putback('\n');
		return istr;
	}
	Time& Time::operator-=(const Time& D)
	{
		int lMins = m_min;
		int rMins = D.m_min;
		int dif = lMins - rMins;
		int i = 1;
		while (dif < 0)
		{
			dif = lMins + 24 * 60 * i - rMins;
			i++;
		}
		m_min = dif;
		return *this;
	}
	Time Time::operator-(const Time& D) const
	{
		Time temp;
		int lMins = m_min;
		int rMins = D.m_min;
		int dif = lMins - rMins;
		int i = 1;
		while (dif < 0)
		{
			dif = lMins + 24 * 60 * i - rMins;
			i++;
		}
		temp.m_min = dif;
		return temp;
	}
	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;
		return *this;
	}
	Time Time::operator+(const Time& D) const
	{
		Time temp;
		temp.m_min = m_min + D.m_min;
		return temp;
	}
	Time& Time::operator=(unsigned int val)
	{
		m_min = val;
		return *this;
	}
	Time& Time::operator*=(unsigned int val)
	{
		m_min *= val;
		return *this;
	}
	Time Time::operator*(unsigned int val) const
	{
		Time temp;
		temp.m_min = m_min * val;
		return temp;
	}
	Time& Time::operator/=(unsigned int val)
	{
		m_min /= val;
		return *this;
	}
	Time Time::operator/(unsigned int val) const
	{
		Time temp;
		temp.m_min = m_min / val;
		return temp;
	}
	Time::operator int() const
	{
		return m_min;
	}
	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		D.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Time& D)
	{
		D.read(istr);
		return istr;
	}
}