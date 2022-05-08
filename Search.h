#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "Struct.h"

using namespace std;

struct Tutor* GetMiddleForTutor(Tutor**, Tutor**);
struct Tutor* BinarySearchAlgorithmForTutor(Tutor*, string);

void SearchTutorByTutorID(Tutor**);
int LinearSearchAlgorithm(Tutor*, int);
void SearchTutorByRating(Tutor**);

struct Student* GetMiddleForStudent(Student**, Student**);
struct Student* BinarySearchAlgorithmForStudent(Student*, string);
void DisplayOneStudent(Student*);
string trim(string&);

struct Tutor* GetMiddleForTutor(Tutor** start_ref, Tutor** last_ref) {
	Tutor* start = *start_ref;
	if (start == NULL || start->next == *last_ref)
		return NULL;

	Tutor* slow = start;
	Tutor* fast = start->next;

	while (fast != *last_ref) {
		fast = fast->next;
		if (fast != *last_ref) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	return slow;
}

struct Tutor* BinarySearchAlgorithmForTutor(Tutor* head, string id) {
	
	Tutor* start = head;
	Tutor* last = NULL;

	do {
		Tutor* mid = GetMiddleForTutor(&start, &last);

		////Convert ID digit into Integer to compare
		//string convertMid = "0", convertID = "0";
		//int intMid = 0, intID = 0;
		//for (int i = 1; i < mid->TutorID.length(); i++) { //int i = 1 as we need to skip the first character
		//	convertMid = convertMid + mid->TutorID.at(i);
		//}
		//for (int i = 1; i < id.length(); i++) { //int i = 1 as we need to skip the first character
		//	convertID = convertID + id.at(i);
		//}

		//No more MID, return START or LAST node, or NULL if no matches
		if (mid == NULL) {
			if (start->TutorID == id)
				return start;
			else if (last->TutorID == id)
				return last;
			else
				return NULL;
		}
		//Return MID if it is a match
		if (mid->TutorID == id)
			return mid;
		//MID ID is valued less than given search ID
		else if (mid->TutorID < id)
			start = mid->next; //Set Start as the next node of MID
		else
			last = mid;
	} while (last == NULL || last != start);

	return NULL;
}

void SearchTutorByTutorID(Tutor** head_ref) {
	string TutorID;

	cout << "\n==========Search a Tutor by Tutor ID==========" << endl;
	cout << "Enter the tutor ID to search: ";
	cin >> TutorID;
	cout << endl;
	cout << "\nSearch Result: " << endl;
	//Trim Input
	TutorID = trim(TutorID);
	//Change small letter to capital letter if there are any
	for_each(TutorID.begin(), TutorID.end(), [](char& c)
	{
		c = toupper(c);
	});
	if (BinarySearchAlgorithmForTutor(*head_ref, TutorID) == NULL)
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
	else {
		Tutor* target = BinarySearchAlgorithmForTutor(*head_ref, TutorID);
		DisplayOneTutorForAdmin(target);
	}
}

int LinearSearchAlgorithm(Tutor* head, int rating) {
	int found = 0;

	if (head != NULL) {

		do {
			if (head->AverageRating == rating) {
				cout << head->TutorID << ", " << head->Name << ", " << head->DateJoin << ", " << head->DateTerminate << ", ";
				cout << head->HourlyRate << ", " << head->PhoneNumber << ", " << head->Address << ", " << head->CenterCode << ", ";
				cout << head->CenterName << ", " << head->SubjectCode << ", " << head->SubjectName << ", " << head->AverageRating << endl;
				found = 1;
			}
			head = head->next;
		} while (head != NULL);
	}
	else
		cout << "Cannot search tutors by rating." << endl;

	return found;
}

void SearchTutorByRating(Tutor** head_ref) {
	int Rating;

	cout << "\n==========Search Tutors by Rating==========" << endl;
	cout << "Enter the rating to search: ";
	cin >> Rating;
	cout << endl;

	cout << "\nSearch Result: " << endl;
	if (LinearSearchAlgorithm(*head_ref, Rating) == 0)
		cout << "No tutor has rating of " << Rating << "." << endl;

}

struct Student* GetMiddleForStudent(Student** start_ref, Student** last_ref) {
	Student* start = *start_ref;
	if (start == NULL || start->next == *last_ref)
		return NULL;
	
	Student* slow = start;
	Student* fast = start->next;

	while (fast != *last_ref) {
		fast = fast->next;
		if (fast != *last_ref) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	return slow;
}

struct Student* BinarySearchAlgorithmForStudent(Student* head, string id) {
	Student* start = head;
	Student* last = NULL;

	do {
		Student* mid = GetMiddleForStudent(&start, &last);

		if (mid == NULL) {
			if (start->StudentID == id)
				return start;
			else if (last->StudentID == id)
				return last;
			else
				return NULL;
		}

		if (mid->StudentID == id)
			return mid;
		else if (mid->StudentID < id)
			start = mid->next;
		else
			last = mid;
	} while (last == NULL || last != start);

	return NULL;
}

void DisplayOneStudent(Student* one) {

	cout << "Tutor ID: " << one->StudentID << endl;
	cout << "Name: " << one->Name << endl;
	cout << "Phone: " << one->PhoneNumber << endl;
	cout << "Tuition Center Code: " << one->CenterCode << endl;
	cout << "Tuition Center Name: " << one->CenterName << endl;
	cout << "Tutor ID 1: " << one->TutorID[0] << endl;
	cout << "Tutor ID 2: " << one->TutorID[1] << endl;
	cout << "Tutor ID 3: " << one->TutorID[2] << endl;
	cout << "Tutor ID 4: " << one->TutorID[3] << endl;
	cout << "Tutor ID 5: " << one->TutorID[4] << endl;
	cout << endl;
}