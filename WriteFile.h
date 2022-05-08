#pragma once
#include <iostream>
#include <fstream>
#include "ReadFile.h"

using namespace std;

bool WriteTutorFile(Tutor*);
bool WriteStudentFile(Student*);
void WriteFilesBeforeEnd(Tutor*, Student*);

//WRITE DATA INTO Tutor.txt FILE
bool WriteTutorFile(Tutor* TutorHead) {
	ofstream writeData;
	writeData.open("Tutor.txt");

	if (writeData.is_open()) {
		while (TutorHead != NULL) {
			writeData << TutorHead->TutorID << ", ";
			writeData << TutorHead->Name << ", ";
			writeData << TutorHead->DateJoin << ", ";
			writeData << TutorHead->DateTerminate << ", ";
			writeData << TutorHead->HourlyRate << ", ";
			writeData << TutorHead->PhoneNumber << ", ";
			writeData << TutorHead->Address << ", ";
			writeData << TutorHead->CenterCode << ", ";
			writeData << TutorHead->CenterName << ", ";
			writeData << TutorHead->SubjectCode << ", ";
			writeData << TutorHead->SubjectName << ", ";
			writeData << TutorHead->TotalRatings << ", ";
			writeData << TutorHead->NoOfRatings << ", ";
			writeData << TutorHead->AverageRating << endl;

			TutorHead=TutorHead->next;
		}
		return true;
	}
	else
		cout << "Tutor.txt cannot be written." << endl;
	return false;
}

//WRITE DATA INTO Student.txt FILE
bool WriteStudentFile(Student* StudentHead) {
	bool done = false;
	ofstream writeData;
	writeData.open("Student.txt");

	if (writeData.is_open()) {
		while (StudentHead != NULL) {
			writeData << StudentHead->StudentID << ", ";
			writeData << StudentHead->Name << ", ";
			writeData << StudentHead->PhoneNumber << ", ";
			writeData << StudentHead->Password << ", ";
			writeData << StudentHead->CenterCode << ", ";
			writeData << StudentHead->CenterName << ", ";
			writeData << StudentHead->TutorID[0] << ", ";
			writeData << StudentHead->TutorID[1] << ", ";
			writeData << StudentHead->TutorID[2] << ", ";
			writeData << StudentHead->TutorID[3] << ", ";
			writeData << StudentHead->TutorID[4] << ", ";
			writeData << StudentHead->NoOfTutors << endl;
			
			StudentHead = StudentHead->next;
		}
		done = true;
	}
	else
		cout << "Student.txt cannot be written." << endl;
	return done;
}

//WRITE DATA INTO Student.txt and Tutor.txt FILE BEFORE EXITING SYSTEM
void WriteFilesBeforeEnd(Tutor* TutorHead, Student* StudentHead) {
	WriteTutorFile(TutorHead);
	WriteStudentFile(StudentHead);
}