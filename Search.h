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

//the function definition is at ExtraFunction.h
string trim(string&);
int RemoveTheFirstChar(string);

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
	int idInt = RemoveTheFirstChar(id);
	do {
		Tutor* mid = GetMiddleForTutor(&start, &last);


		//No more MID, return START or LAST node, or NULL if no matches
		if (mid == NULL) {
			if (RemoveTheFirstChar(start->TutorID) == idInt)
				return start;
			
			else
				return NULL;
		}
		//Return MID if it is a match
		if (RemoveTheFirstChar(mid->TutorID) == idInt)
			return mid;
		//MID ID is valued less than given search ID
		else if (RemoveTheFirstChar(mid->TutorID) < idInt)
			start = mid->next; //Set Start as the next node of MID
		else
			last = mid;
	} while (last == NULL || last != start);

	return NULL;
}

void SearchTutorByTutorID(Tutor** head_ref) {
	string TutorID;
	Tutor* found;
	cout << "\n==========Search a Tutor by Tutor ID==========" << endl;
	cout << "Enter the tutor ID to search: ";
	cin >> TutorID;
	cout << endl;
	cout << "\nSearch Result: " << endl;
	//Trim Input
	TutorID = trim(TutorID);

	found = BinarySearchAlgorithmForTutor(*head_ref, TutorID);
	if (found == NULL)
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
	else {
		Tutor* target = found;
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
	int idInt = RemoveTheFirstChar(id);
	do {
		Student* mid = GetMiddleForStudent(&start, &last);

		if (mid == NULL) {
			if (RemoveTheFirstChar(start->StudentID) == idInt)
				return start;
			
			else
				return NULL;
		}

		if (RemoveTheFirstChar(mid->StudentID) == idInt)
			return mid;
		else if (RemoveTheFirstChar(mid->StudentID) < idInt)
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