#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "Struct.h"
#include "ExtraFunction.h"

using namespace std;

void CountTutors(Tutor**);

//Count tutors in each center for each subject and generate report
void CountTutors(Tutor** head_ref) {
	int BEng = 0, BMath = 0, BChem = 0, BPhy = 0, BBio = 0; //Bukit Jalil Tutors
	int PEng = 0, PMath = 0, PChem = 0, PPhy = 0, PBio = 0; //Puchong Tutors
	int IEng = 0, IMath = 0, IChem = 0, IPhy = 0, IBio = 0; //Ipoh Tutors

	struct tm date = GetCurrentTime();

	int year = 1900 + date.tm_year;
	int month = 1 + date.tm_mon;
	int day = date.tm_mday;
	char dash = '-';
	string CurrentDate = to_string(year) + dash + to_string(month) + dash + to_string(day);

	Tutor* ptr = *head_ref;

	if (ptr == NULL) {
		cout << "TUTOR Linked List does not exist." << endl;
		return;
	}

	while (ptr != NULL) {
		if (ptr->DateTerminate > CurrentDate) {
			if (ptr->CenterName == "Bukit Jalil") {
				if (ptr->SubjectName == "English")
					BEng = BEng + 1;
				else if (ptr->SubjectName == "Math")
					BMath = BMath + 1;
				else if (ptr->SubjectName == "Chemistry")
					BChem = BChem + 1;
				else if (ptr->SubjectName == "Physics")
					BPhy = BPhy + 1;
				else
					BBio = BBio + 1;
			}
			else if (ptr->CenterName == "Puchong") {
				if (ptr->SubjectName == "English")
					PEng = PEng + 1;
				else if (ptr->SubjectName == "Math")
					PMath = PMath + 1;
				else if (ptr->SubjectName == "Chemistry")
					PChem = PChem + 1;
				else if (ptr->SubjectName == "Physics")
					PPhy = PPhy + 1;
				else
					PBio = PBio + 1;
			}
			else {
				if (ptr->SubjectName == "English")
					IEng = IEng + 1;
				else if (ptr->SubjectName == "Math")
					IMath = IMath + 1;
				else if (ptr->SubjectName == "Chemistry")
					IChem = IChem + 1;
				else if (ptr->SubjectName == "Physics")
					IPhy = IPhy + 1;
				else
					IBio = IBio + 1;
			}
		}

		ptr = ptr->next;
	}
	//Print Report
	cout << "Report of " << CurrentDate << endl;
	cout << "Bukit Jalil: " << endl;
	cout << "Number of English tutor: " << BEng << endl;
	cout << "Number of Math tutor: " << BMath << endl;
	cout << "Number of Chemistry tutor: " << BChem << endl;
	cout << "Number of Physics tutor: " << BPhy << endl;
	cout << "Number of Biology tutor: " << BBio << endl;
	cout << endl;

	cout << "Puchong: " << endl;
	cout << "Number of English tutor: " << PEng << endl;
	cout << "Number of Math tutor: " << PMath << endl;
	cout << "Number of Chemistry tutor: " << PChem << endl;
	cout << "Number of Physics tutor: " << PPhy << endl;
	cout << "Number of Biology tutor: " << PBio << endl;
	cout << endl;

	cout << "Ipoh: " << endl;
	cout << "Number of English tutor: " << IEng << endl;
	cout << "Number of Math tutor: " << IEng << endl;
	cout << "Number of Chemistry tutor: " << IChem << endl;
	cout << "Number of Physics tutor: " << IPhy << endl;
	cout << "Number of Biology tutor: " << IBio << endl;
	cout << endl;
}