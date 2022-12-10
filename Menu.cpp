//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "Menu.h"
#include <cstring>
using namespace std;
namespace sdds
{
    Menu::Menu(const char* MenuContent, int NoOfSelections)
    {
        m_text = new char[strlen(MenuContent) + 1];
        strcpy(m_text, MenuContent);
        m_noOfSel = NoOfSelections;
    }
    Menu::~Menu()
    {
        delete[] m_text;
        m_text = nullptr;
    }
    std::ostream& Menu::display(std::ostream& ostr) const
    {
        ostr << m_text << endl;
        ostr << "0- Exit" << endl;
        return ostr;
    }
    int& Menu ::operator>>(int& Selection)
    {
        display();
        Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
        return Selection;
    }
    Menu::Menu(const Menu& RA)
    {
        m_text = new char[strlen(RA.m_text) + 1];
        strcpy(m_text, RA.m_text);
        m_noOfSel = RA.m_noOfSel;
    }
}
