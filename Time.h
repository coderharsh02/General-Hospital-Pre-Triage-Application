//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <iostream>
namespace sdds {
   class Time {
      unsigned int m_min;
   public:
      Time& setToNow();
      Time(unsigned int min = 0);
      std::ostream& write(std::ostream& ostr) const;
      bool timeMaker(const char* inpStr);
      std::istream& read(std::istream& istr);
      std::istream& csvRead(std::istream& istr);

      Time& operator-=(const Time& D);
      Time operator-(const Time& D)const;
      Time& operator+=(const Time& D);
      Time operator+(const Time& D)const;

      Time& operator=(unsigned int val);
      Time& operator *= (unsigned int val);
      Time& operator /= (unsigned int val);
      Time operator *(unsigned int val)const;
      Time operator /(unsigned int val)const;

      operator unsigned int()const;
      operator int()const;
   };
   std::ostream& operator<<(std::ostream& ostr, const Time& D);
   std::istream& operator>>(std::istream& istr, Time& D);
}

#endif // !SDDS_TIME_H

