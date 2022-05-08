#pragma once
#include <string>
#include <time.h>

using namespace std;
string ltrim(string&);
string rtrim(string&);
string trim(string&);
int RemoveTheFirstChar(string);

struct tm GetCurrentTime();
string CorrectWeekDayTime(int);
string CorrectMonthTime(int);

string GetUniqueTutorID(Tutor**);
bool UniqueTutorIDChecker(Tutor**, string);

bool isLeapYear(int);
bool isValidDate(int, int, int);
bool checkFutureDate(int, int, int);
int countLeapYear(int, int, int);
int getDifferenceDate(int, int, int, int, int, int);

const int MaxValidYear = 9999;
const int MinValidYear = 1800;

//To trim the left of the string
string ltrim(string& s) {
	size_t start = s.find_first_not_of(" ");
	return (start == string::npos) ? "" : s.substr(start);
}

//To trim the right of the string
string rtrim(string& s) {
	size_t end = s.find_last_not_of(" ");
	return(end == string::npos) ? "" : s.substr(0, end + 1);
}

//Combine the left and right string
string trim(string& s) {
	string S = ltrim(s);
	return rtrim(S);
}

//
int RemoveTheFirstChar(string word) {
	string NewWord = word.substr(1);
	int New = stoi(NewWord);
	return New;
}

//To get the current time
struct tm GetCurrentTime() {
	struct tm NewTime;
	time_t CurrentTime = time(0);
	errno_t err;
	err = localtime_s(&NewTime, &CurrentTime);

	return NewTime;
}

//To convert the numeric day to string format
string CorrectWeekDayTime(int num) {
	if (num == 1)
		return "Mon";
	else if (num == 2)
		return "Tues";
	else if (num == 3)
		return "Wed";
	else if (num == 4)
		return "Thur";
	else if (num == 5)
		return "Fri";
	else if (num == 6)
		return "Sat";
	else
		return "Sun";
}

//To convert the numeric month to string format
string CorrectMonthTime(int num) {
	if (num == 0)
		return "Jan";
	else if (num == 1)
		return "Feb";
	else if (num == 2)
		return "Mar";
	else if (num == 3)
		return "Apr";
	else if (num == 4)
		return "May";
	else if (num == 5)
		return "Jun";
	else if (num == 6)
		return "Jul";
	else if (num == 7)
		return "Aug";
	else if (num == 8)
		return "Sep";
	else if (num == 9)
		return "Oct";
	else if (num == 10)
		return "Nov";
	else
		return "Dec";
}

//Function to check if Tutor ID is unique
bool UniqueTutorIDChecker(Tutor** head_ref, string id) {
	Tutor* check = *head_ref;
	bool unique = true;
	//Check if tutor ID is unique
	while (check != NULL) {
		if (trim(check->TutorID) == trim(id)) {
			unique = false;
		}
		check = check->next;
	}
	return unique;
}

//Function that returns a unique Tutor ID
string GetUniqueTutorID(Tutor** head_ref) {
	Tutor* ptr = *head_ref;

	int count = 1;
	string id;

	//get a number for Tutor ID
	while (ptr != NULL) {
		count += 1;
		ptr = ptr->next;
	}

	//Create tutor ID
	id = "T" + to_string(count);

	//If ID is not unique, add number to count
	while (!UniqueTutorIDChecker(head_ref, id)) {
		count += 1;
		id = "T" + to_string(count);
	}
	
	return id;
}

//Function to check if given year is leap year and is valid, returns true if year is valid
bool isLeapYear(int year) {

	return (((year % 4 == 0) && //is a multiple of 4
		(year % 100 != 0)) || //not a multiple of 100 OR
		(year % 400 == 0)); //is a Multiple of 400
}

bool isValidDate(int d, int m, int y) {
	// If year, month and day are not in given range
	if (y > MaxValidYear ||
		y < MinValidYear)
		return false;
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > 31)
		return false;

	// Handle February month
	// with leap year
	if (m == 2)
	{
		if (isLeapYear(y))
			return (d <= 29);
		else
			return (d <= 28);
	}

	// Months of April, June, Sept and Nov must have number of days less than or equal to 30.
	if (m == 4 || m == 6 ||
		m == 9 || m == 11)
		return (d <= 30);

	return true;
}

// Function to check whether given date is in future, returns true if date is in future
bool checkFutureDate(int d, int m, int y) {
	struct tm time = GetCurrentTime();
	//Year later than current year, return true
	if (y > 1900 + time.tm_year) {
		return true;
	}
	//Same year with current year
	else if (y == 1900 + time.tm_year) {
		//Month later than current month, return true
		if (m > 1 + time.tm_mon) {
			return true;
		}
		//Day later than current day
		else if (m == 1 + time.tm_mon) {
			if (d > time.tm_mday) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//
int countLeapYear(int d, int m, int y)
{
	int years = y;

	// Check if the current year needs to be considered for the count of leap years or not
	if (m <= 2) //Before february, do not need to be counted
		years--;

	return years / 4 //Leap year is a leap year if it is a multiple of 4
		- years / 100 //not a multiple of 100 OR
		+ years / 400; //is a Multiple of 400
}

// Function returns number of days between two given dates
int getDifferenceDate(int d, int m, int y, int dNow, int mNow, int yNow){
	//Number of Days for each month (not applicable for Leap year)
	const int monthDays[12]
		= { 31, 28, 31, 30, 31, 30,
		   31, 31, 30, 31, 30, 31 };

	// COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE
	// initialize count using years and day
	long int n1 = y * 365 + d;

	// Add days for months in given date
	for (int i = 0; i < m - 1; i++)
		n1 += monthDays[i];

	// Since every leap year is of 366 days,
	// Add a day for every leap year
	n1 += countLeapYear(d, m, y);

	// SIMILARLY, COUNT TOTAL NUMBER OF
	// DAYS BEFORE 'dt2'

	long int n2 = yNow * 365 + dNow;
	for (int i = 0; i < mNow - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYear(dNow, mNow, yNow);

	// return difference between two counts
	return (n2 - n1);
}