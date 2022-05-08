#pragma once
#include <iostream>
#include "Search.h"
#include "Report.h"
#include "RateTutors.h"

using namespace std;

void TutorRecordsForAdminSubMenu(Tutor*, Student*, Admin*);
void StudentRecordsForAdminSubMenu(Tutor*, Student*, Admin*);
void ReportForAdminSubMenu(Tutor*, Student*, Admin*);
void AdminSubMenu(Tutor*, Student*, Admin*);
void StudentSubMenu(Tutor*, Student*, Student*);
void SearchTutorsPage(Tutor*, Student*, Admin*);
void MainLandingPage();

void WriteFilesBeforeEnd(Tutor*, Student*);
//the function definition is at WriteFile.h
//the function definitions of three function prototype below are at Edit.h
void ModifyTutor(Tutor*, Student*, Admin*);
void TerminateTutor(Tutor*, Student*, Admin*);
void SearchStudentToModify(Tutor*, Student*, Admin*);
bool AddNewTutor(Tutor*);
struct Tutor* ReadTutorFile();
void MergeSortStudentID(Student**);
void DeleteTutor(Tutor*);

//TUTOR RECORDS FOR ADMINS
void TutorRecordsForAdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int option;
	char repeat;
	bool newTutorAdded = false;

	//Update Tutor Records and Delete Records with Termination Date more than 180 days ago
	DeleteTutor(TutorHead);
	TutorHead = ReadTutorFile();

	cout << "\n====================Tutor Records====================" << endl;
	cout << "1. Add New Tutor Record" << endl << "2. Display All Tutor Records" << endl << "3. Search Tutors(by Tutor ID or Rating)" << endl;
	cout << "4. Sort and Display(by Tutors ID or Tutors Hourly Pay Rate or Tutors Rating)" << endl;
	cout << "5. Modify a Tutor Record" << endl << "6. Terminate a Tutor Record" << endl << "7. Exit to Admin Menu" << endl;
	cout << "Enter your choice here: ";
	//Input Validation 
	while (!(cin >> option)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
		cout << "====================Tutor Records====================" << endl;
		cout << "1. Add New Tutor Record" << endl << "2. Display All Tutor Records" << endl << "3. Search Tutors(by Tutor ID or Rating)" << endl;
		cout << "4. Sort and Display(by Tutors ID or Tutors Hourly Pay Rate or Tutors Rating)" << endl;
		cout << "5. Modify a Tutor Record" << endl << "6. Terminate a Tutor Record" << endl << "7. Exit to Admin Menu" << endl;
		cout << "Enter your choice here: ";
		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');
	}

	switch (option) {
	case 1: //ADD NEW TUTOR RECORD
		//Call Add new tutor function and return boolean to check whether operation is successful
		newTutorAdded = AddNewTutor(TutorHead);
		//Read new updated linked list into TutorHead from Tutor.txt file
		TutorHead = ReadTutorFile();

		if (newTutorAdded)
			cout << "\nNew tutor successfully added!" << endl;
		else
			cout << "\nNew tutor not added due to system error, please try again later." << endl;

		cout << "Enter 'Y' to exit the entire program or Press any key to return to Tutor Records Page: ";
		cin >> repeat;

		if (repeat == 'Y' || repeat == 'y') {
			WriteFilesBeforeEnd(TutorHead, StudentHead);
			exit(0);
		}
		else
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);

		break;
	case 2: //DISPLAY ALL TUTOR RECORD
		//Read new updated linked list into TutorHead from Tutor.txt file
		TutorHead = ReadTutorFile();
		cout << "\n====================Display All Tutor Records====================" << endl;
		DisplayAllTutorsForAdmin(TutorHead);
		cout << "Enter 'Y' to exit the entire program or Press any key to return to Tutor Records Page: ";
		cin >> repeat;

		if (repeat == 'Y' || repeat == 'y') {
			WriteFilesBeforeEnd(TutorHead, StudentHead);
			exit(0);
		}
		else
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);

		break;
	case 3: //SEARCH TUTOR SUBMENU
		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
		break;
	case 4: //SORT AND DISPLAY TUTOR RECORD
		//Read new updated linked list into TutorHead from Tutor.txt file
		TutorHead = ReadTutorFile();
		cout << "\n====================Sort and Display Tutor Record====================" << endl;
		cout << "1. Sort via Tutor ID" << endl << "2. Sort via Tutor Hourly Pay Rate" << endl << "3. Sort via Tutor Ratings" << endl;
		cout << "Enter your choice here: ";
		//Input Validation
		while (!(cin >> option)) {
			cout << "********INVALID INPUT********\nPlease try again.\n" << endl;

			cout << "\n====================Sort and Display Tutor Record====================" << endl;
			cout << "1. Sort via Tutor ID" << endl << "2. Sort via Tutor Hourly Pay Rate" << endl << "3. Sort via Tutor Ratings" << endl;
			cout << "Enter your choice here: ";

			//Clear previous input
			cin.clear();
			//Discard previous input
			cin.ignore(100, '\n');
		}

		switch (option) {
		case 1: //Sort via Tutor ID
			DisplaySortedID(TutorHead, StudentHead, AdminHead);
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		case 2: //Sort via Hourly Pay Rate
			DisplaySortedHourlyRate(TutorHead, StudentHead, AdminHead);
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		case 3: //Sort via Ratings 
			DisplaySortedRating(TutorHead, StudentHead, AdminHead);
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		default:
			cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		}		
		break;
	case 5: //MODIFY TUTOR RECORD
		ModifyTutor(TutorHead, StudentHead, AdminHead);
		break;
	case 6: //TERMINATE TUTOR
		do {
			TerminateTutor(TutorHead, StudentHead, AdminHead);
			cout << "Enter 'Y' to continue deleting or Press any key to return to Tutor Records Page: ";
			cin >> repeat;
		} while (repeat == 'Y' || repeat == 'y');
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	case 7: //
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	
	default:
		cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
	}

}

void StudentRecordsForAdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int option;
	cout << "\n====================Student Records====================" << endl;
	cout << "1. Sort by Students ID and Display" << endl << "2. Search a Student by Student ID and Modify" << endl;
	cout << "3. Exit to Admin Sub-Menu" << endl;
	cout << "Enter your choice here: ";
	//Input Validation
	while (!(cin >> option)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
		cout << "\n====================Student Records====================" << endl;
		cout << "1. Sort by Students ID and Display" << endl << "2. Search a Student by Student ID and Modify" << endl;
		cout << "3. Exit to Tutor Sub-Menu" << endl;
		cout << "Enter your choice here: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');
	}

	switch (option) {
	case 1:
		MergeSortStudentID(&StudentHead);
		DisplayAllStudents(StudentHead);
		StudentRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
	case 2:
		SearchStudentToModify(TutorHead, StudentHead, AdminHead);
		break;
	case 3:
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	default:
		cout << "Invalid number entered." << endl << "Please try again." << endl << endl;
		StudentRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
	}
}

void ReportForAdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	char option;
	cout << "\n====================Report====================" << endl;
	CountTutors(&TutorHead);
	
	cout << "Enter 'Y' to exit the entire program or Press any key to return to Tutor Sub-Menu: ";
	cin >> option;
	if (option == 'Y' || option == 'y') {
		WriteFilesBeforeEnd(TutorHead, StudentHead);
		exit(0);
	}
	else
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
}

void AdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int submenu;

	cout << "\nAdmin Sub-Menu: " << endl;
	cout << "1. Tutor Records" << endl;
	cout << "2. Student Records" << endl;
	cout << "3. Report" << endl;
	cout << "4. Logout to Main Menu" << endl;
	cout << "5. Exit the system" << endl;
	cout << "Enter your choice here: ";
	//Input validation
	while (!(cin >> submenu)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
		cout << "\nAdmin Sub-Menu: " << endl;
		cout << "1. Tutor Records" << endl;
		cout << "2. Student Records" << endl;
		cout << "3. Report" << endl;
		cout << "4. Logout to Main Menu" << endl;
		cout << "5. Exit the system" << endl;
		cout << "Enter your choice here: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');
	}
	cout << endl;

	switch (submenu) {
	case 1:
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	case 2:
		StudentRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	case 3:
		ReportForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	case 4:
		MainLandingPage();
		break;
	case 5:
		WriteFilesBeforeEnd(TutorHead, StudentHead);
		exit(0);
		break;
	default:
		cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
	}
}

void StudentSubMenu(Tutor* TutorHead, Student* StudentHead, Student* wantedstudent) {
	int submenu;
	char repeat;

	cout << "\nStudent Sub-Menu: " << endl;
	cout << "1. View My Profile" << endl;
	cout << "2. View All The Tutors in Your Center" << endl;
	cout << "3. View Your Own Tutors and Rate" << endl;
	cout << "4. Logout to Main Menu" << endl;
	cout << "5. Exit the system" << endl;
	cout << "Enter your choice here: ";
	while (!(cin >> submenu)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
		cout << "\nStudent Sub-Menu: " << endl;
		cout << "1. View My Profile" << endl;
		cout << "2. View All The Tutors in Your Center" << endl;
		cout << "3. View Your Own Tutors and Rate" << endl;
		cout << "4. Logout to Main Menu" << endl;
		cout << "5. Exit the system" << endl;
		cout << "Enter your choice here: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');

	}

	switch (submenu) {
	case 1:
		cout << endl;
		cout << "\n====================My Profile====================" << endl;
		DisplayOneStudent(wantedstudent);
		cout << "Enter 'Y' to exit the entire program or Press any key to return to Student Sub-Menu: ";
		cin >> repeat;
		if (repeat == 'Y' || repeat == 'y') {
			WriteFilesBeforeEnd(TutorHead, StudentHead);
			exit(0);
		}
		else
			StudentSubMenu(TutorHead, StudentHead, wantedstudent);
		break;
	case 2:
		cout << endl;
		cout << "\n====================Display All The Tutors in Your Center====================" << endl;
		DisplayTutorsForStudent(TutorHead, wantedstudent->CenterCode);
		cout << "Enter 'Y' to exit the entire program or Press any key to return to Student Sub-Menu: ";
		cin >> repeat;
		if (repeat == 'Y' || repeat == 'y') {
			WriteFilesBeforeEnd(TutorHead, StudentHead);
			exit(0);
		}
		else
			StudentSubMenu(TutorHead, StudentHead, wantedstudent);
		break;
	case 3:
		cout << endl;
		DisplayTutorsAndRate(TutorHead, StudentHead, wantedstudent);
		break;
	case 4:
		MainLandingPage();
		break;
	case 5:
		WriteFilesBeforeEnd(TutorHead, StudentHead);
		exit(0);
		break;
	default:
		cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;
		StudentSubMenu(TutorHead, StudentHead, wantedstudent);
	}
}

void SearchTutorsPage(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int search;
	char repeat;
	cout << "\n====================Search Tutors====================" << endl;
	cout << "1. Search a tutor by tutor ID" << endl << "2. Search tutors by rating" << endl << "3. Exit to Tutor Records Page" << endl;
	cout << "Enter your choice here: ";
	while (!(cin >> search)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
		cout << "\n====================Search Tutors====================" << endl;
		cout << "1. Search a tutor by tutor ID" << endl << "2. Search tutors by rating" << endl << "3. Exit to Tutor Records Page" << endl;
		cout << "Enter your choice here: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');
	}
	switch (search) {
	case 1:
		do {
			SearchTutorByTutorID(&TutorHead);
			cout << endl;
			cout << "Enter 'Y' to continue searching via tutor ID or Press any key to return to Search Tutors Page: ";
			cin >> repeat;
		} while (repeat == 'Y' || repeat == 'y');

		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
		break;
	case 2:
		do {
			SearchTutorByRating(&TutorHead);
			cout << endl;
			cout << "Enter 'Y' to continue searching via rating or Press any key to return to Search Tutors Page: ";
			cin >> repeat;
		} while (repeat == 'Y' || repeat == 'y');

		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
		break;
	case 3:
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	default:
		cout << "\nInvalid number entered." << endl << "Please try again." << endl << endl << endl;
		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
	}
}