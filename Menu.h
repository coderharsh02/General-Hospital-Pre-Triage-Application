//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>
namespace sdds
{
    class Menu
    {
        char* m_text;  // holds the menu content dynamically
        int m_noOfSel; // holds the number of options displayed in menu content
        std::ostream& display(std::ostream& ostr = std::cout) const;

    public:
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        int& operator>>(int& Selection);
        // add safe copying logic
        Menu(const Menu&);
        Menu& operator=(const Menu& source) = delete;
    };
}
#endif // !SDDS_MENU_H_