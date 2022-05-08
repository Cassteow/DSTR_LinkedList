#pragma once
#include <string>

using namespace std;

struct Tutor {
	string TutorID;
	string Name;
	string DateJoin;
	string DateTerminate;
	int HourlyRate;
	string PhoneNumber;
	string Address;
	string CenterCode;
	string CenterName;
	string SubjectCode;
	string SubjectName;
	int TotalRatings;
	int NoOfRatings;
	int AverageRating;
	struct Tutor* next, * prev;
};

struct Student {
	string StudentID;
	string Name;
	string PhoneNumber;
	string Password;
	string CenterCode;
	string CenterName;
	string TutorID[5];
	int NoOfTutors;
	struct Student* next, * prev;
};

struct Admin {
	string AdminID;
	string Password;
	struct Admin* next, * prev;
};