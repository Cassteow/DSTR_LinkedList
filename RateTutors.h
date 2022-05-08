#pragma once

using namespace std;

void DisplayTutorsAndRate(Tutor*, Student*, Student*);
void StudentSubMenu(Tutor*, Student*, Student*);//the function definition is at SubMenu.h

void DisplayTutorsAndRate(Tutor* TutorHead, Student* StudentHead, Student* wantedstudent) {
	int found, rating;
	string TutorID;
	Tutor* ptr, * TargetTutor;

	cout << "==========View Own Tutors and Rate Them==========" << endl;
	cout << "Your Tutors' Records: " << endl;
	for (int i = 0; i < wantedstudent->NoOfTutors; i++) {
		ptr = TutorHead;
		TargetTutor = BinarySearchAlgorithmForTutor(ptr, wantedstudent->TutorID[i]);
		DisplayOneTutorForStudent(TargetTutor);
		cout << endl;
	}

	do {
		found = 0;
		ptr = TutorHead;
		cout << "Enter the tutor ID to rate or Enter 'Y' to return to previous page: ";
		cin.ignore();
		getline(cin, TutorID);

		if (TutorID == "Y" || TutorID == "y") {
			StudentSubMenu(TutorHead, StudentHead, wantedstudent);
		}

		for (int j = 0; j < wantedstudent->NoOfTutors; j++) {
			if (wantedstudent->TutorID[j] == TutorID) {
				found = 1;
				cout << "Please rate for Tutor " << TutorID << "(rating from 1-5, where 1 is 'very poor performance' and 5 is 'excellent performance'): ";
				cin >> rating;

				while (ptr != NULL) {
					if (ptr->TutorID == TutorID) {
						ptr->TotalRatings = ptr->TotalRatings + rating;
						ptr->NoOfRatings++;
						ptr->AverageRating = ptr->TotalRatings / ptr->NoOfRatings;
						cout << "Rating for Tutor " << TutorID << " successfully." << endl;
						DisplayTutorsAndRate(TutorHead, StudentHead, wantedstudent);
						break;
					}
					ptr = ptr->next;
				}
			}
		}

		if (found == 0) {
			cout << "Invalid tutor ID entered for rating." << endl << "Please try again." << endl << endl;
		}
	} while (found == 0);

}