#pragma once
#include <iostream>
#include "Struct.h"

using namespace std;

struct Tutor* SortedMergeID(Tutor*, Tutor*);
struct Tutor* SortedMergeRating(Tutor*, Tutor*);
struct Tutor* SortedMergeHourlyRate(Tutor*, Tutor*);
struct Student* SortedMergeStudentID(Student*, Student*);

void SplitList(Tutor*);
void SplitListStudent(Student*);

void MergeSortForID(Tutor**);
void MergeSortForRating(Tutor**);
void MergeSortForHourlyRate(Tutor**);
void MergeSortForStudentID(Student**);

void TutorRecordsForAdminSubMenu(Tutor*, Student*, Admin*);

/* Split the nodes of the given list into front and back halves,
   and return the two lists using the reference parameters.
   Uses the fast/slow pointer strategy. */
void SplitList(Tutor* head, Tutor** a, Tutor** b) {
	Tutor* fast = head->next;
	Tutor* slow = head;
	/* Advance 'fast' two nodes, and
	   advance 'slow' one node */
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}

	}
	/* 'slow' is before the midpoint in the list,
		so split it in two at that point. */
	*b = slow->next;
	slow->next = NULL;
}

//Split a list into two
void SplitListStudent(Student* head, Student** a, Student** b) {
	Student* fast = head->next;
	Student* slow = head;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}

	}
	*b = slow->next;
	slow->next = NULL;
}

//Function to merge 2 sorted linked list (Rating)
struct Tutor* SortedMergeRating(Tutor* first, Tutor* second) {

	//If first linked list is empty, return second
	if (!first) {
		return second;
	}
	//If second linked list is empty, return first
	if (!second) {
		return first;
	}


	//pick either first or second and recur
	if (first->AverageRating <= second->AverageRating) {
		first->next = SortedMergeRating(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = SortedMergeRating(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}

//Function to merge 2 sorted linked list (hourly rate)
struct Tutor* SortedMergeHourlyRate(Tutor* first, Tutor* second) {

	//If first linked list is empty, return second
	if (!first) {
		return second;
	}
	//If second linked list is empty, return first
	if (!second) {
		return first;
	}

	
	//pick either first or second and recur
	if (first->HourlyRate <= second->HourlyRate) {
		first->next = SortedMergeHourlyRate(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = SortedMergeHourlyRate(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}

//Function to merge 2 sorted linked list (ID)
struct Tutor* SortedMergeID(Tutor* first, Tutor* second) {

	//If first linked list is empty, return second
	if (!first) {
		return second;
	}
	//If second linked list is empty, return first
	if (!second) {
		return first;
	}

	//Convert ID digit into Integer to compare
	int intID1 = RemoveTheFirstChar(first->TutorID);
	int intID2 = RemoveTheFirstChar(second->TutorID);
	//Select smaller value
	//pick either first or second and recur
	if (intID1 <= intID2) {
		first->next = SortedMergeID(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = SortedMergeID(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}
//Function to apply merge sort to a linked list based on Hourly Rate
void MergeSortForHourlyRate(Tutor** head) {

	if (*head == NULL || (*head)->next == NULL) {
		return;
	}
	struct Tutor* first = *head;
	struct Tutor* second = NULL;
	SplitList(*head, &first, &second);

	//Recur left and right halves
	MergeSortForHourlyRate(&first);
	MergeSortForHourlyRate(&second);
	//Merge two sorted halves
	*head = SortedMergeHourlyRate(first, second);
}

//Function to apply merge sort to a linked list based on Tutor ID
void MergeSortForID(Tutor** head) {

	if (*head == NULL || (*head)->next == NULL) {
		return;
	}
	struct Tutor* first = *head;
	struct Tutor* second = NULL;
	SplitList(*head, &first, &second);

	//Recur left and right halves
	MergeSortForID(&first);
	MergeSortForID(&second);
	//Merge two sorted halves
	*head = SortedMergeID(first, second);
}

//Function to apply merge sort to a linked list based on Average Ratings
void MergeSortForRating(Tutor** head) {

	if (*head == NULL || (*head)->next == NULL) {
		return;
	}
	struct Tutor* first = *head;
	struct Tutor* second = NULL;
	SplitList(*head, &first, &second);

	//Recur left and right halves
	MergeSortForRating(&first);
	MergeSortForRating(&second);
	//Merge two sorted halves
	*head = SortedMergeRating(first, second);
}

//Function to merge 2 sorted linked list (for Student ID)
struct Student* SortedMergeStudentID(Student* first, Student* second) {

	//If first linked list is empty, return second
	if (!first) {
		return second;
	}
	//If second linked list is empty, return first
	if (!second) {
		return first;
	}

	
	int intID1 = RemoveTheFirstChar(first->StudentID);
	int intID2 = RemoveTheFirstChar(second->StudentID);
	//pick either first or second and recur
	if (intID1 <= intID2) {
		first->next = SortedMergeStudentID(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = SortedMergeStudentID(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}

//Function to apply merge sort to a linked list based on Tutor ID
void MergeSortForStudentID(Student** head) {

	if (*head == NULL || (*head)->next == NULL) {
		return;
	}
	struct Student* first = *head;
	struct Student* second = NULL;
	SplitListStudent(*head, &first, &second);

	//Recur left and right halves
	MergeSortForStudentID(&first);
	MergeSortForStudentID(&second);
	//Merge two sorted halves
	*head = SortedMergeStudentID(first, second);
}