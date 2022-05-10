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

void DisplayAllTutorsForAdmin(Tutor* head) {
	int count = 1;
	while (head != NULL) {
		//Display Date of Termination, if Date is 1900-01-01, Date of Termination is unavailable
		string checkDateTermination;
		if (head->DateTerminate == "1900-01-01") {
			checkDateTermination = "NONE";
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
		cout << head->StudentID << ", " << head->Name << ", " << head->PhoneNumber << ", " << head->Password << ", ";
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
	Tutor* temp = TutorHead;
	MergeSortForID(&TutorHead);
	cout << "\n";
	DisplayIndividualTutor(temp, TutorHead, StudentHead, AdminHead);
}
//Function to Display Sorted Linked List (Rating)
void DisplaySortedRating(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	Tutor* temp = TutorHead;
	MergeSortForRating(&TutorHead);
	cout << "\n";
	DisplayIndividualTutor(temp, TutorHead, StudentHead, AdminHead);
}
//Function to Display Sorted Linked List (Hourly Rate)
void DisplaySortedHourlyRate(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	Tutor* temp = TutorHead;
	MergeSortForHourlyRate(&TutorHead);
	cout << "\n";
	DisplayIndividualTutor(temp, TutorHead, StudentHead, AdminHead);
}

//Function to display record individually and allow transversal of record back and forth
void DisplayIndividualTutor(Tutor* DisplayHead, Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int option;
	cout << "\n";
	DisplayOneTutorForAdmin(DisplayHead);
	cout << "\n1- Next Tutor Record\n2- Previous Tutor Record\n";
	cout <<	"3- Back to Admin Sub Menu for Tutor Records\nEnter your choice: ";
	while (!(cin >> option)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;

		cout << "\n1- Next Tutor Record\n2- Previous Tutor Record\n";
		cout << "3- Back to Admin Sub Menu for Tutor Records\nEnter your choice: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');
	}

	switch (option) {
	case 1: //NEXT RECORD
		if (DisplayHead->next != NULL) {
			DisplayHead = DisplayHead->next;
			DisplayIndividualTutor(DisplayHead, TutorHead, StudentHead, AdminHead);
		}
		else {
			cout << "ERROR: no next record!\n\n";
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		}
	case 2: //PREVIOUS RECORD
		if (DisplayHead->prev != NULL) {
			DisplayHead = DisplayHead->prev;
			DisplayIndividualTutor(DisplayHead, TutorHead, StudentHead, AdminHead);
		}
		else {
			cout << "ERROR: no previous record!\n\n";
			TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
		}
	case 3: //RETURN TO TUTOR RECORDS ADMIN SUB MENU
		TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
	}
}

