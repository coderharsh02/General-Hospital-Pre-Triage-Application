//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#include "CovidPatient.h"
#include "Ticket.h"
#include "Patient.h"
namespace sdds
{
   int nextCovidTicket = 1;
   CovidPatient::CovidPatient() : Patient(nextCovidTicket)
   {
      nextCovidTicket++;
   }
   char CovidPatient::type() const
   {
      return 'C';
   }
   std::istream &CovidPatient::csvRead(std::istream &istr)
   {
      Patient::csvRead(istr);
      nextCovidTicket = number() + 1;
      return istr;
   }
   std::ostream &CovidPatient::write(std::ostream &ostr) const
   {
      if (fileIO())
      {
         csvWrite(ostr);
      }
      else
      {
         ostr << "COVID TEST\n";
         Patient::write(ostr) << std::endl;
      }
      return ostr;
   }
   std::istream &CovidPatient::read(std::istream &istr)
   {
      if (fileIO())
      {
         csvRead(istr);
      }
      else
      {
         Patient::read(istr);
      }
      return istr;
   }
}

