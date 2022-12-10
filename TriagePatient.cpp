//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include "TriagePatient.h"
#include "Patient.h"
#include "utils.h"

namespace sdds
{
   int nextTriageTicket = 1;

   TriagePatient::TriagePatient() : Patient(nextTriageTicket)
   {
      m_symptoms = nullptr;
      nextTriageTicket++;
   }
   char TriagePatient::type() const
   {
      return 'T';
   }
   std::ostream &TriagePatient::csvWrite(std::ostream &ostr) const
   {
      Patient::csvWrite(ostr);
      ostr << ","<<m_symptoms;
      return ostr;
   }
   std::istream &TriagePatient::csvRead(std::istream &istr)
   {
      delete[] m_symptoms;
      Patient::csvRead(istr);
      char *str = new char[500];
      istr.get(str, 500, '\n');
      istr.ignore(1000, '\n');
      m_symptoms = str;
      nextTriageTicket = number() + 1;
      return istr;
   }
   std::ostream &TriagePatient::write(std::ostream &ostr) const
   {
      if (fileIO())
      {
         csvWrite(ostr);
      }
      else
      {
         ostr << "TRIAGE\n";
         Patient::write(ostr);
         ostr << "\nSymptoms: " << m_symptoms << "\n";
      }
      return ostr;
   }
   std::istream &TriagePatient::read(std::istream &istr)
   {
      if(fileIO())
      {
         csvRead(istr);
      }
      else
      {
         delete[] m_symptoms;
         Patient::read(istr);
         char* str = getcstr("Symptoms: ",istr,'\n');
         m_symptoms = new char[strlen(str) + 1];
         strcpy(m_symptoms, str);
         delete[] str;
      }
      return istr;
   }
   TriagePatient::~TriagePatient()
   {
      delete[] m_symptoms;
   }
}