//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#define _CRT_SECURE_NO_WARNINGS
#include "Ticket.h"
namespace sdds
{
    class Patient : public IOAble
    {
        char *m_name;
        int m_ohip;
        Ticket m_ticket;
        bool m_ioFlag;

    public:
        Patient(int number = 0, bool flag = false);
        ~Patient();
        Patient(const Patient &) = delete;
        Patient &operator=(const Patient &) = delete;
        virtual char type() const = 0;
        bool fileIO() const;
        void fileIO(bool flag);
        bool operator==(char character) const;
        bool operator==(const Patient &) const;
        void setArrivalTime();
        operator Time() const;
        int number() const;
        std::ostream &csvWrite(std::ostream &ostr) const;
        std::istream &csvRead(std::istream &istr);
        std::ostream &write(std::ostream &ostr) const;
        std::istream &read(std::istream &istr);
    };
}
#endif // !SDDS_PATIENT_H_

