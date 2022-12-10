//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include "Patient.h"
#include "utils.h"
namespace sdds
{
    Patient::Patient(int number, bool flag) : m_ticket(number)
    {
        fileIO(flag);
        m_name = nullptr;
        m_ohip = 0;
    }
    Patient::~Patient()
    {
        delete[] m_name;
        m_name = nullptr;
    }
    bool Patient::fileIO() const
    {
        return m_ioFlag;
    }
    void Patient::fileIO(bool flag)
    {
        m_ioFlag = flag;
    }
    bool Patient::operator==(char character) const
    {
        return type() == character;
    }
    bool Patient::operator==(const Patient &RA) const
    {
        return type() == RA.type();
    }
    void Patient::setArrivalTime()
    {
        m_ticket.resetTime();
    }
    Patient::operator Time() const
    {
        return Time(m_ticket);
    }
    int Patient::number() const
    {
        return m_ticket.number();
    }
    std::ostream &Patient::csvWrite(std::ostream &ostr) const
    {
        ostr << type() << "," << m_name << "," << m_ohip << ",";
        return m_ticket.csvWrite(ostr);
    }
    std::istream &Patient::csvRead(std::istream &istr)
    {
        char str[100];
        istr.get(str, 100, ',');
        delete[] m_name;
        m_name = new char[strlen(str) + 1];
        strcpy(m_name, str);
        istr.ignore(1000, ',');
        istr >> m_ohip;
        istr.ignore();
        return m_ticket.csvRead(istr);
    }
    std::ostream &Patient::write(std::ostream &ostr) const
    {
        ostr << m_ticket << std::endl;
        showString(ostr, m_name, 25) << ", OHIP: " << m_ohip;
        return ostr;
    }
    std::istream &Patient::read(std::istream &istr)
    {
        char *str = getcstr("Name: ", istr);
        delete[] m_name;
        m_name = new char[strlen(str) + 1];
        strcpy(m_name, str);
        delete[] str;
        m_ohip = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ");
        return istr;
    }
}

