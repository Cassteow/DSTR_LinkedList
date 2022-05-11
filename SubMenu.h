#pragma once
#include <iostream>
#include "Search.h"
#include "Report.h"
#include "RateTutors.h"

using namespace std;

//Function Prototype Declaration
void TutorRecordsForAdminSubMenu(Tutor*, Student*, Admin*);
void StudentRecordsForAdminSubMenu(Tutor*, Student*, Admin*);
void ReportForAdminSubMenu(Tutor*, Student*, Admin*);

void AdminSubMenu(Tutor*, Student*, Admin*);
void StudentSubMenu(Tutor*, Student*, Student*);

void SearchTutorsPage(Tutor*, Student*, Admin*);

//the function definition is at Main.cpp
void MainLandingPage();

//the function definition is at WriteFile.h
void WriteFilesBeforeEnd(Tutor*, Student*);

//the function definitions of three function prototype below are at Edit.h
void ModifyTutor(Tutor*, Student*, Admin*);
void TerminateTutor(Tutor*, Student*, Admin*);
void SearchStudentToModify(Tutor*, Student*, Admin*);
bool AddNewTutor(Tutor**);
struct Tutor* ReadTutorFile();
struct Tutor* ReadTutorFile();
void DeleteTutor(Tutor**);

//the function definition is at Sort.h
void MergeSortForStudentID(Student**);

//TUTOR RECORDS MENU FOR ADMINS
void TutorRecordsForAdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	string userInput;
	int option;
	string repeat;
	bool newTutorAdded = false;
	//MergeSortForID(&TutorHead);
	cout << "\n====================Tutor Records====================" << endl;
	cout << "1. Add New Tutor Record" << endl << "2. Display All Tutor Records" << endl << "3. Search Tutors(by Tutor ID or Rating)" << endl;
	cout << "4. Sort and Display(by Tutors ID or Tutors Hourly Pay Rate or Tutors Rating)" << endl;
	cout << "5. Modify a Tutor Record" << endl << "6. Terminate a Tutor Record" << endl << "7. Exit to Admin Menu" << endl;
	cout << "Enter your choice here: ";
	getline(cin, userInput);
	//Input Validation (ensure input is integer)
	while (!(checkIntInput(userInput))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "====================Tutor Records====================" << endl;
		cout << "1. Add New Tutor Record" << endl << "2. Display All Tutor Records" << endl << "3. Search Tutors(by Tutor ID or Rating)" << endl;
		cout << "4. Sort and Display(by Tutors ID or Tutors Hourly Pay Rate or Tutors Rating)" << endl;
		cout << "5. Modify a Tutor Record" << endl << "6. Terminate a Tutor Record" << endl << "7. Exit to Admin Menu" << endl;
		cout << "Enter your choice here: ";
		//Clear previous input
		cin.clear();
		//Discard previous input
		userInput.clear();
		getline(cin, userInput);
	}
	option = stoi(userInput);

	switch (option) {
	case 1: //ADD NEW TUTOR RECORD
		//Call Add new tutor function and return boolean to check whether operation is successful
		newTutorAdded = AddNewTutor(&TutorHead);

		if (newTutorAdded)
			cout << "\nNew tutor successfully added!" << endl;
		else
			cout << "\nNew tutor not added due to system error, please try again later." << endl;

		cout << "Enter 'Y' to exit the entire program or Press any key to return to Tutor Records Page: ";
		getline(cin, repeat);
		repeat = trim(repeat);
		if (repeat == "Y" || repeat == "y") {
			WriteFilesBeforeEnd(TutorHead, StudentHead);
			exit(0);
		}
		else
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);

		break;
	case 2: //DISPLAY ALL TUTOR RECORD
		//Read new updated linked list into TutorHead from Tutor.txt file
		
		cout << "\n====================Display All Tutor Records====================" << endl;
		DisplayAllTutorsForAdmin(TutorHead);
		cout << "Enter 'Y' to exit the entire program or Press any key to return to Tutor Records Page: ";
		getline(cin, repeat);
		repeat = trim(repeat);
		if (repeat == "Y" || repeat == "y") {
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
		cout << "\n====================Sort and Display Tutor Record====================" << endl;
		cout << "1. Sort via Tutor ID" << endl << "2. Sort via Tutor Hourly Pay Rate" << endl << "3. Sort via Tutor Ratings" << endl 
			<< "4. Exit to Tutor Records page" << endl;
		cout << "Enter your choice here: ";
		userInput.clear();
		getline(cin, userInput);
		//Input Validation (ensure input is integer)
		while (!(checkIntInput(userInput))) {
			cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;

			cout << "\n====================Sort and Display Tutor Record====================" << endl;
			cout << "1. Sort via Tutor ID" << endl << "2. Sort via Tutor Hourly Pay Rate" << endl << "3. Sort via Tutor Ratings" 
				<< endl << "4. Exit to Tutor Records page" << endl;
			cout << "Enter your choice here: ";
			//Clear previous input
			cin.clear();
			//Discard previous input
			userInput.clear();
			getline(cin, userInput);
		}
		option = stoi(userInput);

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
		case 4: 
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
		TerminateTutor(TutorHead, StudentHead, AdminHead);
		break;
	case 7: //
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	
	default:
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
	}

}

//STUDENT RECORDS MENU FOR ADMINS
void StudentRecordsForAdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	string userInput;
	int option;
	cout << "\n====================Student Records====================" << endl;
	cout << "1. Sort by Students ID and Display" << endl << "2. Search a Student by Student ID and Modify" << endl;
	cout << "3. Exit to Admin Sub-Menu" << endl;
	cout << "Enter your choice here: ";
	userInput.clear();
	getline(cin, userInput);
	//Input Validation (ensure input is integer)
	while (!(checkIntInput(userInput))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "\n====================Student Records====================" << endl;
		cout << "1. Sort by Students ID and Display" << endl << "2. Search a Student by Student ID and Modify" << endl;
		cout << "3. Exit to Tutor Sub-Menu" << endl;
		cout << "Enter your choice here: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		userInput.clear();
		getline(cin, userInput);
	}
	option = stoi(userInput);
	switch (option) {
	case 1:
		MergeSortForStudentID(&StudentHead);
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

//REPORT MENU FOR ADMINS
void ReportForAdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	string option;
	cout << "\n====================Report====================" << endl;
	CountTutors(&TutorHead);
	
	cout << "Enter 'Y' to exit the entire program or Press any key to return to Tutor Sub-Menu: ";
	getline(cin, option);
	option = trim(option);
	if (option == "Y" || option == "y") {
		WriteFilesBeforeEnd(TutorHead, StudentHead);
		exit(0);
	}
	else
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
}

//MAIN PAGE FOR ADMINS
void AdminSubMenu(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int submenu;
	string userInput;
	cout << "\nAdmin Sub-Menu: " << endl;
	cout << "1. Tutor Records" << endl;
	cout << "2. Student Records" << endl;
	cout << "3. Report" << endl;
	cout << "4. Logout to Main Menu" << endl;
	cout << "5. Exit the system" << endl;
	cout << "Enter your choice here: ";
	getline(cin, userInput);
	//Input Validation (ensure input is integer)
	while (!(checkIntInput(userInput))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
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
		userInput.clear();
		getline(cin, userInput);
	}
	submenu = stoi(userInput);

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
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		AdminSubMenu(TutorHead, StudentHead, AdminHead);
	}
}

//MAIN PAGE FOR STUDENTS
void StudentSubMenu(Tutor* TutorHead, Student* StudentHead, Student* wantedstudent) {
	int submenu;
	string repeat;
	string userInput;
	cout << "\nStudent Sub-Menu: " << endl;
	cout << "1. View My Profile" << endl;
	cout << "2. View All The Tutors in Your Center" << endl;
	cout << "3. View Your Own Tutors and Rate" << endl;
	cout << "4. Logout to Main Menu" << endl;
	cout << "5. Exit the system" << endl;
	cout << "Enter your choice here: ";
	userInput.clear();
	getline(cin, userInput);
	//Input Validation (ensure input is integer)
	while (!(checkIntInput(userInput))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
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
		userInput.clear();
		getline(cin, userInput);
	}
	submenu = stoi(userInput);

	switch (submenu) {
	case 1:
		cout << endl;
		cout << "\n====================My Profile====================" << endl;
		DisplayOneStudent(wantedstudent);
		cout << "Enter 'Y' to exit the entire program or Press any key to return to Student Sub-Menu: ";
		getline(cin, repeat);
		repeat = trim(repeat);
		if (repeat == "Y" || repeat == "y") {
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
		getline(cin, repeat);
		repeat = trim(repeat);
		if (repeat == "Y" || repeat == "y") {
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

//SEARCHING PAGE (TUTOR RECORDS) FOR ADMINS
void SearchTutorsPage(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int search;
	string repeat;
	string userInput;
	cout << "\n====================Search Tutors====================" << endl;
	cout << "1. Search a tutor by tutor ID" << endl << "2. Search tutors by rating" << endl << "3. Exit to Tutor Records Page" << endl;
	cout << "Enter your choice here: ";
	userInput.clear();
	getline(cin, userInput);
	//Input Validation (ensure input is integer)
	while (!(checkIntInput(userInput))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "\n====================Search Tutors====================" << endl;
		cout << "1. Search a tutor by tutor ID" << endl << "2. Search tutors by rating" << endl << "3. Exit to Tutor Records Page" << endl;
		cout << "Enter your choice here: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		userInput.clear();
		getline(cin, userInput);
	}
	search = stoi(userInput);

	switch (search) {
	case 1:
		do {
			SearchTutorByTutorID(TutorHead);
			cout << endl;
			cout << "Enter 'Y' to continue searching via tutor ID or Press any key to return to Search Tutors Page: ";
			getline(cin, repeat);
			repeat = trim(repeat);
		} while (repeat == "Y" || repeat == "y");

		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
		break;
	case 2:
		do {
			SearchTutorByRating(TutorHead);
			cout << endl;
			cout << "Enter 'Y' to continue searching via rating or Press any key to return to Search Tutors Page: ";
			getline(cin, repeat);
			repeat = trim(repeat);
		} while (repeat == "Y" || repeat == "y");

		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
		break;
	case 3:
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		break;
	default:
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		SearchTutorsPage(TutorHead, StudentHead, AdminHead);
	}
}