#pragma once
#include <iostream>
#include "Struct.h"

using namespace std;
void DisplayAllTutorsForAdmin(Tutor*);
void DisplayAllStudents(Student*);
void DisplayAllAdmins(Admin*);
void DisplayTutorsForStudent(Tutor*, string);
void DisplayOneTutorForStudent(Tutor*);
void DisplayOneTutorForAdmin(Tutor*);

void DisplaySortedID(Tutor*, Student*, Admin*);
void DisplaySortedRating(Tutor*, Student*, Admin*);
void DisplaySortedHourlyRate(Tutor*, Student*, Admin*);
void DisplayIndividualTutor(Tutor*, Tutor*, Student*, Admin*);

//Function Definitions of the function prototypes below are included at Sort.h
void MergeSortForID(Tutor**);
void MergeSortForRating(Tutor**);
void MergeSortForHourlyRate(Tutor**);
//Function Definition of the function prototype below is included at SubMenu.h
void TutorRecordsForAdminSubMenu(Tutor*, Student*, Admin*);
//Function Definition of the function prototype below is included at ExtraFunction.h
bool checkIntInput(string);

void DisplayAllTutorsForAdmin(Tutor* head) {
	int count = 1;
	//Display Header
	cout << "No.--ID--Name-----Join Date---Terminate Date--Hourly Rate--Phone--Address--Center Code--Center Name--Subject Code--Subject Name--Ratings" << endl;
	while (head != NULL) {
		//Display Date of Termination, if Date is 1900-01-01, Date of Termination is unavailable
		string checkDateTermination;
		if (head->DateTerminate == "1900-01-01") {
			checkDateTermination = "NONE  ";
		}
		else {
			checkDateTermination = head->DateTerminate;
		}
		cout << count << ": " << head->TutorID << ", " << head->Name << ", " << head->DateJoin << ", " << checkDateTermination << ", ";
		cout << head->HourlyRate << ", " << head->PhoneNumber << ", " << head->Address << ", " << head->CenterCode << ", ";
		cout << head->CenterName << ", " << head->SubjectCode << ", " << head->SubjectName << ", " << head->AverageRating << endl;
		head = head->next;
		count += 1;
	}
}

void DisplayAllStudents(Student* head) {
	while (head != NULL) {
		//Display Header
		cout << "No.--ID--Name-----Phone----Tutor(s)" << endl;
		cout << head->StudentID << ", " << head->Name << ", " << head->PhoneNumber << ", " ;
		cout << head->TutorID[0] << ", " << head->TutorID[1] << ", " << head->TutorID[2] << ", " << head->TutorID[3] << ", ";
		cout << head->TutorID[4] << ", " << head->NoOfTutors << endl;
		head = head->next;
	}
}

void DisplayAllAdmins(Admin* head) {
	while (head != NULL) {
		cout << head->AdminID << ", " << head->Password << endl;
		head = head->next;
	}
}

void DisplayTutorsForStudent(Tutor* head, string centercode) {
	//Display Header
	cout << "No.--ID--Name---Hourly Rate---Center Code--Center Name--Subject Code--Subject Name--Ratings" << endl;
	while (head != NULL) {
		if (head->CenterCode == centercode) {
			cout << head->TutorID << ", " << head->Name << ", " << head->HourlyRate << ", " << head->CenterCode << ", ";
			cout << head->CenterName << ", " << head->SubjectCode << ", " << head->SubjectName << ", " << head->AverageRating << endl;
		}
		head = head->next;
	}
}

void DisplayOneTutorForStudent(Tutor* one) {

	cout << "Tutor ID: " << one->TutorID << endl;
	cout << "Name: " << one->Name << endl;
	cout << "Hourly Pay Rate: " << one->HourlyRate << endl;
	cout << "Tuition Center Code: " << one->CenterCode << endl;
	cout << "Tuition Center Name: " << one->CenterName << endl;
	cout << "Subject Code: " << one->SubjectCode << endl;
	cout << "Subject Name: " << one->SubjectName << endl;
	cout << "Rating: " << one->AverageRating << endl;
	cout << endl;
}

void DisplayOneTutorForAdmin(Tutor* one) {
	//Display Date of Termination, if Date is 1900-01-01, Date of Termination is unavailable
	string checkDateTermination;
	if (one->DateTerminate == "1900-01-01") {
		checkDateTermination = "NONE";
	}
	else {
		checkDateTermination = one->DateTerminate;
	}

	cout << "Tutor ID: " << one->TutorID << endl;
	cout << "Name: " << one->Name << endl;
	cout << "Date Joined: " << one->DateJoin << endl;
	cout << "Date Terminated: " << checkDateTermination << endl;
	cout << "Hourly Pay Rate: " << one->HourlyRate << endl;
	cout << "Phone: " << one->PhoneNumber << endl;
	cout << "Address: " << one->Address << endl;
	cout << "Tuition Center Code: " << one->CenterCode << endl;
	cout << "Tuition Center Name: " << one->CenterName << endl;
	cout << "Subject Code: " << one->SubjectCode << endl;
	cout << "Subject Name: " << one->SubjectName << endl;
	cout << "Rating: " << one->AverageRating << endl;
	cout << endl;
}


//Function to Display Sorted Linked List (ID)
void DisplaySortedID(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	MergeSortForID(&TutorHead);
	Tutor* temp = TutorHead;
	cout << "\n";
	DisplayIndividualTutor(temp, TutorHead, StudentHead, AdminHead);
}
//Function to Display Sorted Linked List (Rating)
void DisplaySortedRating(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	MergeSortForRating(&TutorHead);
	Tutor* temp = TutorHead;	
	cout << "\n";
	DisplayIndividualTutor(temp, TutorHead, StudentHead, AdminHead);
}
//Function to Display Sorted Linked List (Hourly Rate)
void DisplaySortedHourlyRate(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	MergeSortForHourlyRate(&TutorHead);
	Tutor* temp = TutorHead;
	cout << "\n";
	DisplayIndividualTutor(temp, TutorHead, StudentHead, AdminHead);
}

//Function to display record individually and allow transversal of record back and forth
void DisplayIndividualTutor(Tutor* DisplayHead, Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int option, valid;
	string userInput;
	cout << "\n";
	DisplayOneTutorForAdmin(DisplayHead);

	do {
		cout << "\n1- Next Tutor Record\n2- Previous Tutor Record\n";
		cout << "3- Back to Admin Sub Menu for Tutor Records\nEnter your choice: ";
		getline(cin, userInput);
		while (!checkIntInput(userInput)) {
			cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;

			cout << "\n1- Next Tutor Record\n2- Previous Tutor Record\n";
			cout << "3- Back to Admin Sub Menu for Tutor Records\nEnter your choice: ";
			userInput.clear();
			//Clear previous input
			cin.clear();
			getline(cin, userInput);
		}

		option = stoi(userInput);
		valid = 1;
		switch (option) {
		case 1: //NEXT RECORD
			valid = 1;
			if (DisplayHead->next != NULL) {
				DisplayHead = DisplayHead->next;
				DisplayIndividualTutor(DisplayHead, TutorHead, StudentHead, AdminHead);
				
			}
			else {
				cout << "ERROR: no next record!\n\n";
				TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
			}
			break;
		case 2: //PREVIOUS RECORD
			valid = 1;
			if (DisplayHead->prev != NULL) {
				DisplayHead = DisplayHead->prev;
				DisplayIndividualTutor(DisplayHead, TutorHead, StudentHead, AdminHead);
			}
			else {
				cout << "ERROR: no previous record!\n\n";
				TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
			}
			break;
		case 3: //RETURN TO TUTOR RECORDS ADMIN SUB MENU
			valid = 1;
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
			break;
		default:
			valid = 0;
			cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;
		}
	} while (valid == 0);
	
}

