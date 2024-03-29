#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Struct.h"
#include "ExtraFunction.h"

using namespace std;

//Function Prototype Declaration
void InsertAtBeginningForReadTutorFile(Tutor**, string, string, string, string, int, string, string, string, string, string, string, int, int, int);
struct Tutor* ReadTutorFile();
void InsertAtEndForReadStudentFile(Student**, string, string, string, string, string, string, string, string, string, string, string, int);
struct Student* ReadStudentFile();
void InsertAtEndForReadAdminFile(Admin**, string, string);
struct Admin* ReadAdminFile();

//Function to insert new node of tutor record to the beginning of the linked list
void InsertAtBeginningForReadTutorFile(Tutor** TutorHead_ref, string id, string name, string join, string terminate, int hourly, string phone, string address, string centercode, string centername, string subcode, string subname, int totalratings, int noofratings, int averagerating) {
	Tutor* ptr = *TutorHead_ref;
	//Allocate new node
	Tutor* NewNode = new Tutor();

	//Insert new data to node members
	NewNode->TutorID = id;
	NewNode->Name = name;
	NewNode->DateJoin = join;
	NewNode->DateTerminate = terminate;
	NewNode->HourlyRate = hourly;
	NewNode->PhoneNumber = phone;
	NewNode->Address = address;
	NewNode->CenterCode = centercode;
	NewNode->CenterName = centername;
	NewNode->SubjectCode = subcode;
	NewNode->SubjectName = subname;
	NewNode->TotalRatings = totalratings;
	NewNode->NoOfRatings = noofratings;
	NewNode->AverageRating = averagerating;
	//Make next node of new node as head of original linked list
	NewNode->next = *TutorHead_ref;
	//Make prev node of new node as NULL 
	NewNode->prev = NULL;
	if (ptr == NULL) {
		*TutorHead_ref = NewNode;
	}
	else {
		ptr->prev = NewNode;
		//Let head point to NewNode
		*TutorHead_ref = NewNode;

	}
	
}

//Read Tutor.txt file into linked list
struct Tutor* ReadTutorFile() {
	ifstream read("Tutor.txt");
	Tutor* FullRecord = NULL;//this is very important, cannot be 'Tutor* FullRecord = new Tutor;'

	if (read.is_open()) {
		string line;

		while (getline(read, line)) {
			stringstream ss(line);
			string id, name, join, terminate, hourly, phone, address, centercode, centername, subcode, subname, totalrating, noofrating, averagerating;

			getline(ss, id, ',');
			getline(ss, name, ',');
			getline(ss, join, ',');
			getline(ss, terminate, ',');
			getline(ss, hourly, ',');
			getline(ss, phone, ',');
			getline(ss, address, ',');
			getline(ss, centercode, ',');
			getline(ss, centername, ',');
			getline(ss, subcode, ',');
			getline(ss, subname, ',');
			getline(ss, totalrating, ',');
			getline(ss, noofrating, ',');
			getline(ss, averagerating, ',');

			InsertAtBeginningForReadTutorFile(&FullRecord, trim(id), trim(name), trim(join), trim(terminate), stoi(hourly), trim(phone), trim(address), trim(centercode), trim(centername), trim(subcode), trim(subname), stoi(totalrating), stoi(noofrating), stoi(averagerating));
		}
	}
	else
		cout << "Tutor.txt cannot be opened." << endl;

	return FullRecord;
}

//Function to insert new node of student record to the end of the linked list
void InsertAtEndForReadStudentFile(Student** head_ref, string id, string name, string phone, string password, string centercode, string centername, string tutor1, string tutor2, string tutor3, string tutor4, string tutor5, int nooftutors) {
	Student* NewNode = new Student();
	Student* ptr = new Student();

	NewNode->StudentID = id;
	NewNode->Name = name;
	NewNode->PhoneNumber = phone;
	NewNode->Password = password;
	NewNode->CenterCode = centercode;
	NewNode->CenterName = centername;
	NewNode->TutorID[0] = tutor1;
	NewNode->TutorID[1] = tutor2;
	NewNode->TutorID[2] = tutor3;
	NewNode->TutorID[3] = tutor4;
	NewNode->TutorID[4] = tutor5;
	NewNode->NoOfTutors = nooftutors;
	NewNode->next = NULL;

	ptr = *head_ref;

	if (*head_ref == NULL) {
		*head_ref = NewNode;
		NewNode->prev = NULL;
	}
	else {

		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = NewNode;
		NewNode->prev = ptr;
	}
}

//Read Student.txt file into linked list
struct Student* ReadStudentFile() {
	ifstream read("Student.txt");
	Student* FullRecord = NULL;//this is very important, cannot be 'Student* FullRecord = new Student;'

	if (read.is_open()) {
		string line;

		while (getline(read, line)) {
			stringstream ss(line);
			string id, name, phone, password, centercode, centername, tutor1, tutor2, tutor3, tutor4, tutor5, nooftutors;

			getline(ss, id, ',');
			getline(ss, name, ',');
			getline(ss, phone, ',');
			getline(ss, password, ',');
			getline(ss, centercode, ',');
			getline(ss, centername, ',');
			getline(ss, tutor1, ',');
			getline(ss, tutor2, ',');
			getline(ss, tutor3, ',');
			getline(ss, tutor4, ',');
			getline(ss, tutor5, ',');
			getline(ss, nooftutors, ',');

			InsertAtEndForReadStudentFile(&FullRecord, trim(id), trim(name), trim(phone), trim(password), trim(centercode), trim(centername), trim(tutor1), trim(tutor2), trim(tutor3), trim(tutor4), trim(tutor5), stoi(nooftutors));
		}
	}
	else
		cout << "Student.txt cannot be opened." << endl;

	return FullRecord;
}

//Function to insert new node of admin record to the end of the linked list
void InsertAtEndForReadAdminFile(Admin** head_ref, string id, string password) {
	Admin* NewNode = new Admin();
	Admin* ptr = new Admin();

	NewNode->AdminID = id;
	NewNode->Password = password;
	NewNode->next = NULL;

	ptr = *head_ref;

	if (*head_ref == NULL) {
		*head_ref = NewNode;
		NewNode->prev = NULL;
	}
	else {

		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = NewNode;
		NewNode->prev = ptr;
	}
}

//Read Admin.txt file into linked list
struct Admin* ReadAdminFile() {
	ifstream read("Admin.txt");
	Admin* FullRecord = NULL;//this is very important, cannot be 'Student* FullRecord = new Student;'

	if (read.is_open()) {
		string line;

		while (getline(read, line)) {
			stringstream ss(line);
			string id, password;

			getline(ss, id, ',');
			getline(ss, password, ',');

			InsertAtEndForReadAdminFile(&FullRecord, trim(id), trim(password));
		}
	}
	else
		cout << "Admin.txt cannot be opened." << endl;

	return FullRecord;
}