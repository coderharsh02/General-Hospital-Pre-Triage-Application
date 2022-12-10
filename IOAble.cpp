//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#include<iostream>
#include"IOAble.h"
namespace sdds
{
    IOAble::~IOAble() { }
    std::istream& operator>>(std::istream& istr, IOAble& I)
    {
        return I.read(istr);
    }
    std::ostream& operator<<(std::ostream& ostr, const IOAble& I)
    {
        return I.write(ostr);
    }
}