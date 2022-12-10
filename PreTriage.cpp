//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include"utils.h"
#include"Menu.h"
#include"Patient.h"
#include"CovidPatient.h"
#include"TriagePatient.h"
#include"PreTriage.h"
using namespace std;
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename) :m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		delete m_dataFilename;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}
	PreTriage::~PreTriage()
	{
		ofstream fout(m_dataFilename);
		if (fout) {
			fout << m_averCovidWait << ',' << m_averTriageWait << endl;
			cout << "Saving Average Wait Times,\n";
			cout << "   COVID Test: " << m_averCovidWait << "\n";
			cout << "   Triage: " << m_averTriageWait << "\n";
			cout << "Saving m_lineup...\n";
			for (int i = 0; i < m_lineupSize; i++)
			{
				cout << i + 1 << "- ";
				m_lineup[i]->csvWrite(std::cout) << endl;
				m_lineup[i]->csvWrite(fout) << endl;
			}
			fout.close();
		}
		else {
			cout << "File is not open" << std::endl;
		}
		for (int i = 0; i < maxNoOfPatients; i++)
		{
			delete m_lineup[i];
		}
		delete[] m_dataFilename;
		cout << "done!" << endl;
	}
	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		int count = 0, waitTime = 0;
		for (int i = 0; i < m_lineupSize; i++)
		{
			if (m_lineup[i]->type() == p.type())
				count++;
		}
		waitTime = p.type() == 'C' ? m_averCovidWait : m_averTriageWait;
		waitTime *= count;
		return waitTime;
	}
	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		int CT = getTime(), PTT = Time(p);
		int AWT = p.type() == 'C' ? m_averCovidWait : m_averTriageWait;
		int PTN = p.number();
		AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
		p.type() == 'C' ? m_averCovidWait : m_averTriageWait = AWT;
	}
	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement<Patient>(m_lineup, index, m_lineupSize);
	}
	int PreTriage::indexOfFirstInLine(char type) const
	{
		bool notfound = true;
		int firstInLine = -1;
		for (int i = 0; i < m_lineupSize && notfound; i++)
		{
			if (m_lineup[i]->type() == type)
			{
				firstInLine = i;
				notfound = false;
			}
		}
		return firstInLine;
	}
	void PreTriage::load()
	{
		int i = 0;
		cout << "Loading data...\n";
		ifstream dataFile(m_dataFilename, ios::in);
		if (dataFile.is_open())
		{
			string tp;
			m_averCovidWait.csvRead(dataFile);
			m_averTriageWait.csvRead(dataFile);
			Patient* ptPtr = nullptr;
			for (; i < maxNoOfPatients && getline(dataFile, tp, ','); i++)
			{
				if (!tp.compare("C"))
				{
					ptPtr = new CovidPatient;
				}
				else
				{
					ptPtr = new TriagePatient;
				}
				if (ptPtr)
				{
					ptPtr->fileIO(true);
					ptPtr->csvRead(dataFile);
					ptPtr->fileIO(false);
					m_lineup[i] = ptPtr;
					m_lineupSize++;
				}
			}
			if (i >= maxNoOfPatients)
				cout << "Warning: number of records exceeded 100\n";
			if (i == 0)
				cout << "No data or bad data file!\n\n";
			else
				cout << i << " Records imported...\n\n";
		}
	}
	void PreTriage::reg()
	{
		if (m_lineupSize >= maxNoOfPatients)
			cout << "Line up full!\n";
		else
		{
			int choice = -1;
			Patient* ptPtr = nullptr;
			m_pMenu >> choice;
			switch (choice)
			{
			case 1:
				ptPtr = new CovidPatient;
				break;
			case 2:
				ptPtr = new TriagePatient;
				break;
			case 0:
				break;
			}
			if (choice > 0)
			{

				ptPtr->setArrivalTime();
				cout << "Please enter patient information: \n";
				ptPtr->fileIO(false);
				cin >> *ptPtr;
				cout << endl;
				cout.fill('*');
				cout.width(43);
				cout << "*\n";
				cout << *ptPtr;
				cout << "Estimated Wait Time: " << getWaitTime(*ptPtr) << endl;
				cout.fill('*');
				cout.width(44);
				cout << "*\n\n";
				m_lineup[m_lineupSize] = ptPtr;
				m_lineupSize++;
			}
		}
	}
	void PreTriage::admit()
	{
		int choice = -1, index = -1;
		m_pMenu >> choice;
		switch (choice)
		{
		case 1:
			index = indexOfFirstInLine('C');
			break;
		case 2:
			index = indexOfFirstInLine('T');
			break;
		case 0:
			break;
		}
		if (choice > 0 && index != -1)
		{
			Patient* ptPtr = m_lineup[index];
			cout << endl;
			cout.fill('*');
			cout.width(43);
			cout << "*\n";
			ptPtr->fileIO(false);
			cout << "Calling for ";
			cout << *ptPtr;
			cout.fill('*');
			cout.width(44);
			cout << "*\n\n";
			setAverageWaitTime(*ptPtr);
			removePatientFromLineup(index);
		}
	}
	void PreTriage::run(void)
	{
		int choice = -1;
		while (choice != 0)
		{
			m_appMenu >> choice;
			switch (choice)
			{
			case 1: 
				reg();
				break;
			case 2:
				admit();
				break;
			case 0:
				break;
			}
		}
	}
};