//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include"Patient.h"
namespace sdds {
    class TriagePatient : public Patient
    {
        char* m_symptoms;
    private:
        
    public:
        TriagePatient();
        char type() const;
        std::ostream &csvWrite(std::ostream &ostr) const;
        std::istream &csvRead(std::istream &istr);
        std::ostream &write(std::ostream &ostr) const;
        std::istream &read(std::istream &istr);
        ~TriagePatient();
    };
    
    
    
}
#endif // !SDDS_TRIAGEPATIENT_H


