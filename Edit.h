#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Struct.h"
#include "SubMenu.h"
#include "Search.h"
#include "ReadFile.h"
#include "WriteFile.h"

using namespace std;

bool AddNewTutor(Tutor**);
void DeleteTutor(Tutor**); 
void ModifyTutor(Tutor*, Student*, Admin*);
void TerminateTutor(Tutor*, Student*, Admin*);
void SearchStudentToModify(Tutor*, Student*, Admin*);
void ModifyStudentPage(Tutor*, Student*, Admin*, Student*, string);
void AddATutorForStudent(Tutor*, Student*, Admin*, Student*, string);
void RemoveATutorForStudent(Tutor*, Student*, Admin*, Student*, string);
bool NoRepeatTutorForOneStudent(Tutor*, Student*, string);
bool AValidTutorForStudents(Tutor*, string);

//Function for System to Automatically Delete Tutor Record if Termination Date >= 180 days
void DeleteTutor(Tutor** TutorHead_ref) {
	Tutor* TutorHead = *TutorHead_ref;
	struct tm time = GetCurrentTime();
	
	//Get Current Date
	int currentDay = time.tm_mday;
	int currentMonth = time.tm_mon + 1;
	int currentYear = 1900 + time.tm_year;
	int day = 0, month = 0, year = 0, dayDifferences;
	string yearString, monthString, dayString;

	if (TutorHead == NULL)
		return;
	while (TutorHead != NULL) {
		//clear previous string data
		yearString.clear();
		monthString.clear();
		dayString.clear();
		//Get Termination Date of current node
		//Extract Year, Month, Day of Termination Date
		string TermDate = trim(TutorHead->DateTerminate);
		for(int i = 0; i < 4; i++) {
			yearString = yearString + TermDate.at(i);		
		}
		for(int i = 5; i < 7; i++) {
			monthString = monthString + TermDate.at(i);	
		}
		for (int i = 8; i < 10; i++) {
			dayString = dayString + TermDate.at(i);	
		}
		year = stoi(trim(yearString));
		month = stoi(trim(monthString));
		day = stoi(trim(dayString));

		//TermDate Invalid
		if (TermDate != "1900-01-01") {
			if (getDifferenceDate(day, month, year, currentDay, currentMonth, currentYear) >= 180) {
				if (TutorHead->prev == NULL) {
					*TutorHead_ref = TutorHead->next;
					TutorHead->next->prev = NULL;
				}
				else {
					TutorHead->prev->next = TutorHead->next;
				}
			}
		}
		TutorHead = TutorHead->next;
	}
}
//Function to Add New Tutor Record
bool AddNewTutor(Tutor** TutorHead_ref) {
	int valid, day, month, year;
	bool addSuccess = false, validDate = false;
	string tutorID, name, dateJoin, dateTerminate, phone, address, centerCode, centerName, subjectCode, subjectName;
	int hourlyRate;
	string dayString, monthString, yearString, hourlyRateString;

	//Get unique ID for new tutor
	tutorID = GetUniqueTutorID(*TutorHead_ref);

	//Get details of new tutor
	cout << "\n==========Add New Tutor Record==========" << endl;
	cout << "Tutor ID for New Tutor: " << tutorID << endl;
	cout << "Enter new tutor name: ";
	getline(cin, name);
	//Ensure name input is valid
	while (!checkStringInput(name)) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "Enter new tutor name: ";
		name.clear();
		cin.clear();
		getline(cin, name);
	}
	//Get Joining date of tutor
	do {
		//Get Joining Date - Year
		cout << "Enter year of joining date for tutor (format - YYYY): ";
		getline(cin, yearString);
		while (!checkIntInput(yearString)) {
			cout << "Invalid year input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "Enter year of joining date for tutor (format - YYYY): ";
			//Discard previous input
			yearString.clear();
			//Clear previous input
			cin.clear();
			getline(cin, yearString);
		}

		//Get Joining Date - Month
		cout << "Enter month of joining date for tutor (format - MM): ";
		getline(cin, monthString);
		while (!checkIntInput(monthString)) {
			cout << "Invalid month input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "Enter month of joining date for tutor (format - MM): ";
			//Clear previous input
			cin.clear();
			//Discard previous input
			monthString.clear();
			getline(cin, monthString);
		}

		//Get Joining Date - Day
		cout << "Enter day of joining date for tutor (format - DD): ";
		getline(cin, dayString);
		while (!checkIntInput(dayString)) {
			cout << "Invalid day input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "Enter day of joining date for tutor (format - DD): ";
			//Clear previous input
			cin.clear();
			//Discard previous input
			dayString.clear();
			getline(cin, dayString);
		}

		year = stoi(yearString);
		month = stoi(monthString);
		day = stoi(dayString);
		//Invalid Date
		if (!(isValidDate(day, month, year))) {
			cout << "Invalid date input entered." << endl << "Please try again." << endl << endl << endl;
			dayString.clear();
			monthString.clear();
			yearString.clear();
			day = 0, month = 0, year = 0;
			validDate = false;
		}
		//Valid Date
		else if (isValidDate(day, month, year)) {
			validDate = true;
			//ensure double digit format for Month and Day
			if (day < 10) {
				dayString = '0' + to_string(day);
			}
			else {
				dayString = to_string(day);
			}

			if (month < 10) {
				monthString = '0' + to_string(month);
			}
			else {
				monthString = to_string(month);
			}

			dateJoin = to_string(year) + '-' + monthString + '-' + dayString;
		}
		
	} while (!validDate);

	dateTerminate = "1900-01-01";

	cout << "Enter Tutor Phone Number: ";
	getline(cin, phone);
	while (!(checkIntInput(phone))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;;
		cout << "Enter Tutor Phone Number: ";
		//Clear previous input
		cin.clear();
		//Discard previous input
		phone.clear();
		getline(cin, phone);
	}

	cout << "Enter Tutor Address: ";
	getline(cin, address);
	while (address.empty()) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "Enter Tutor Address: ";
		//Clear previous input
		cin.clear();
		//Discard previous input
		address.clear();
		getline(cin, address);
	}

	//Choose tuition center name and code for tutor 
	do {
		valid = 0;
		cout << "Enter tutor center name here ('Bukit Jalil' or 'Puchong' or 'Ipoh'): ";
		getline(cin, centerName);
		if (trim(centerName) == "Bukit Jalil") {
			centerCode = "B001C";
			valid = 1;
		}
		else if (trim(centerName) == "Puchong") {
			centerCode = "P001C";
			valid = 1;
		}
		else if (trim(centerName) == "Ipoh") {
			centerCode = "I001C";
			valid = 1;
		}
		else {
			cout << "Invalid center name entered." << endl << "Please enter again." << endl << endl;
			valid = 0;
		}
	} while (valid == 0);

	//Choose subject name and codee for tutor 
	do {
		valid = 0;
		cout << "Enter subject name here (Choices: English, Math, Chemistry, Physics, Biology): ";
		getline(cin, subjectName);
		if (trim(subjectName) == "English" || trim(subjectName) == "english") {
			subjectCode = "E001S";
			valid = 1;
		}
		else if (trim(subjectName) == "Math" || trim(subjectName) == "math") {
			subjectCode = "M001S";
			valid = 1;
		}
		else if (trim(subjectName) == "Chemistry" || trim(subjectName) == "chemistry") {
			subjectCode = "C001S";
			valid = 1;
		}
		else if (trim(subjectName) == "Physics" || trim(subjectName) == "physics") {
			subjectCode = "P001S";
			valid = 1;
		}
		else if (trim(subjectName) == "Biology" || trim(subjectName) == "biology") {
			subjectCode = "B001S";
			valid = 1;
		}
		else {
			cout << "Invalid subject name entered." << endl << "Please enter again." << endl << endl;
			valid = 0;
			subjectName.clear();
		}
	} while (valid == 0);

	cout << "Enter hourly rate (in RM) for tutor: RM";
	getline(cin, hourlyRateString);
	while (!(checkIntInput(hourlyRateString))) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "Enter hourly rate (in RM) for tutor: RM";
		//Clear previous input
		cin.clear();
		//Discard previous input
		hourlyRateString.clear();
		getline(cin, hourlyRateString);
	}
	hourlyRate = stoi(hourlyRateString);
	
	InsertAtBeginningForReadTutorFile(TutorHead_ref, tutorID, name, dateJoin, dateTerminate, hourlyRate, phone, address, centerCode, centerName, subjectCode, subjectName, 0, 0, 0);
	addSuccess = true;
	return addSuccess;
}

//Function to Modify Tutor Records
void ModifyTutor(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int option, ValidChoice;
	string TutorID, modification, userInput, repeat;
	Tutor* found;

	cout << "\n==========Modify a Tutor Record==========" << endl;
	cout << "Enter the tutor ID to modify: ";
	getline(cin, TutorID);
	TutorID = trim(TutorID);
	while (TutorID.empty()) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "Enter the tutor ID to modify: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		TutorID.clear();
		getline(cin, TutorID);
		TutorID = trim(TutorID);
	}
	cout << endl;
	cout << "Tutor's Record: " << endl;
	found = BinarySearchAlgorithmForTutor(TutorHead, TutorID);
	//Search for tutor ID to be modified
	if (found == NULL) { //If ID cannot be found
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
		cout << "Please try again." << endl << endl;
		ModifyTutor(TutorHead, StudentHead, AdminHead);
	}
	else { //ID Found and display
		if (TutorID[0] == 'T' || TutorID[0] == 't') {
			do {
				Tutor* target = BinarySearchAlgorithmForTutor(TutorHead, TutorID);
				DisplayOneTutorForAdmin(target);
				//Select choice to modify which specific information
				ValidChoice = 0;
				cout << "Enter '1' to modify tutor's phone" << endl;
				cout << "Enter '2' to modify tutor's address" << endl;
				cout << "Enter '3' to return to Tutor Record Page" << endl;
				cout << "Enter your choice here: ";
				userInput.clear();
				getline(cin, userInput);
				//Input Validation (ensure input is integer)
				while (!(checkIntInput(userInput))) {
					cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
					cout << "Enter '1' to modify tutor's phone" << endl;
					cout << "Enter '2' to modify tutor's address" << endl;
					cout << "Enter '3' to return to Tutor Record Page" << endl;
					cout << "Enter your choice here: ";

					//Clear previous input
					cin.clear();
					//Discard previous input
					userInput.clear();
					getline(cin, userInput);
				}
				option = stoi(userInput);

				switch (option) {
				case 1: //Modify Phone Number
					ValidChoice = 1;
					cout << "Enter new phone number: ";
					getline(cin, modification);
					while (!(checkIntInput(modification))) {
						cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;;
						cout << "Enter new phone number: ";
						//Clear previous input
						cin.clear();
						//Discard previous input
						modification.clear();
						getline(cin, modification);
					}
					target->PhoneNumber = modification;
					WriteTutorFile(TutorHead); //Modify and update tutor record in text file
					cout << TutorID << "'s phone number is updated." << endl;
					cout << "Enter 'Y' to continue the modification for Tutor " << TutorID << " or Press any key to return to Tutor Records Page : ";
					getline(cin, repeat);
					if (repeat == "Y" || repeat == "y") {
						ValidChoice = 0;
					}
					else {
						cout << endl;
						TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
					}
					break;
				case 2: //Modify Address
					ValidChoice = 1;
					cout << "Enter new address: ";
					getline(cin, modification);
					modification = trim(modification);
					//Validate input
					while (modification.empty()) {
						cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
						cout << "Enter new address: ";

						//Clear previous input
						cin.clear();
						//Discard previous input
						modification.clear();
						getline(cin, modification);
						modification = trim(modification);
					}
					target->Address = modification;
					WriteTutorFile(TutorHead); //Modify and update tutor record in text file
					cout << TutorID << "'s address is updated." << endl;
					cout << "Enter 'Y' to continue the modification for Tutor " << TutorID << " or Press any key to return to Tutor Records Page : ";
					getline(cin, repeat);
					if (repeat == "Y" || repeat == "y") {
						ValidChoice = 0;
					}
					else {
						cout << endl;
						TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
					}
					break;
				case 3: //Return to Admin Sub Menu
					ValidChoice = 1;
					TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
					break;
				default:
					ValidChoice = 0;
					cout << "Invalid number entered." << endl;
					cout << "Please try again." << endl << endl;
				}
			} while (ValidChoice == 0);
		}
		//Invalid Tutor ID at the first character
		else {
			cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
			cout << "Please try again." << endl << endl;
			ModifyTutor(TutorHead, StudentHead, AdminHead);
		}
	}
}

//Function to Termination Date for Tutor
void TerminateTutor(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	string TutorID, DateTerminate, userInput;
	int option, ValidChoice, day, month, year;
	string dayString, monthString, yearString;
	bool valid = true;
	cout << "\n==========Terminate a Tutor==========" << endl;
	cout << "Enter the tutor ID to terminate: ";
	getline(cin, TutorID);
	TutorID = trim(TutorID);
	//Input validation
	while (TutorID.empty()) {
		cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
		cout << "Enter the tutor ID to terminate: ";

		//Clear previous input
		cin.clear();
		//Discard previous input
		TutorID.clear();
		getline(cin, TutorID);
		TutorID = trim(TutorID);
	}
	cout << endl;
	cout << "Tutor's Record: " << endl;
	Tutor* found = BinarySearchAlgorithmForTutor(TutorHead, TutorID);

	if (found == NULL) {
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
		cout << "Please try again." << endl << endl;
		TerminateTutor(TutorHead,StudentHead,AdminHead);
	}
	else {
		if (TutorID[0] == 'T' || TutorID[0] == 't') {
			Tutor* target = BinarySearchAlgorithmForTutor(TutorHead, TutorID);
			DisplayOneTutorForAdmin(target);

			do {
				ValidChoice = 0;
				cout << "Enter '1' to continue or '2' to return to Tutor Records Page: ";
				userInput.clear();
				getline(cin, userInput);
				//Input Validation (ensure input is integer)
				while (!(checkIntInput(userInput))) {
					cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
					cout << "Enter '1' to continue or '2' to return to Tutor Records Page: ";

					//Clear previous input
					cin.clear();
					//Discard previous input
					userInput.clear();
					getline(cin, userInput);
				}
				option = stoi(userInput);
				switch (option) {
				case 1: //User confirm termination date
					ValidChoice = 1;
					do {
						//Get Termination  Date - Year
						cout << "Enter year of termination date for tutor (format - YYYY): ";
						getline(cin, yearString);
						while (!checkIntInput(yearString)) {
							cout << "Invalid year input entered." << endl << "Please try again." << endl << endl << endl;
							cout << "Enter YEAR of termination date for tutor (format - YYYY): ";
							//Discard previous input
							yearString.clear();
							//Clear previous input
							cin.clear();
							getline(cin, yearString);
						}

						//Get Termination  Date - Month
						cout << "Enter month of termination date for tutor (format - MM): ";
						getline(cin, monthString);
						while (!checkIntInput(monthString)) {
							cout << "Invalid month input entered." << endl << "Please try again." << endl << endl << endl;
							cout << "Enter MONTH of termination date for tutor (format - MM): ";
							//Clear previous input
							cin.clear();
							//Discard previous input
							monthString.clear();
							getline(cin, monthString);
						}

						//Get Termination  Date - Day
						cout << "Enter day of termination date for tutor (format - DD): ";
						getline(cin, dayString);
						while (!checkIntInput(dayString)) {
							cout << "Invalid day input entered." << endl << "Please try again." << endl << endl << endl;
							cout << "Enter DAY of termination date for tutor (format - DD): ";
							//Clear previous input
							cin.clear();
							//Discard previous input
							dayString.clear();
							getline(cin, dayString);
						}

						year = stoi(yearString);
						month = stoi(monthString);
						day = stoi(dayString);
						//Invalid Date
						if (!(isValidDate(day, month, year))) {
							cout << "Invalid date input entered." << endl << "Please try again." << endl << endl << endl;
							valid = false;

						}
						//Valid Date
						else if (isValidDate(day, month, year)) {
							valid = true;
							//ensure double digit format for Month and Day
							if (day < 10) {
								dayString = '0' + to_string(day);
							}
							else {
								dayString = to_string(day);
							}

							if (month < 10) {
								monthString = '0' + to_string(month);
							}
							else {
								monthString = to_string(month);
							}

							DateTerminate = to_string(year) + '-' + monthString + '-' + dayString;
						}
						else {
							cout << "Invalid Date Input! Please try again with a valid date.\n ";
							valid = false;
						}
					} while (!valid);

					target->DateTerminate = DateTerminate;

					cout << TutorID << "'s date of termination is updated." << endl;
					
					DeleteTutor(&TutorHead);
					WriteTutorFile(TutorHead);
					TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
					break;
				case 2: //Return to Admin sub menu
					ValidChoice = 1;
					TutorRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
					break;
				default: //Entered invalid input
					ValidChoice = 0;
					cout << "Invalid number entered." << endl;
					cout << "Please try again." << endl;
				}
			} while (ValidChoice == 0);
		}
		else {
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
		cout << "Please try again." << endl << endl;
		TerminateTutor(TutorHead, StudentHead, AdminHead);
		}
	}
}

//Admin search student to modify details
void SearchStudentToModify(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int repeat;
	string StudentID;

	do {
		cout << "==========Search a Student to Modify==========" << endl;
		cout << "Enter the student ID to modify: ";
		getline(cin, StudentID);
		while (StudentID.empty()) {
			cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "Enter the student ID to modify: ";

			//Clear previous input
			cin.clear();
			//Discard previous input
			StudentID.clear();
			getline(cin, StudentID);
		}
		//Trim Input
		StudentID = trim(StudentID);
		
		cout << endl;
		cout << "Student's Record: " << endl;

		Student* found = BinarySearchAlgorithmForStudent(StudentHead, StudentID);
		//Invalid ID or No search results
		if (found == NULL) {
			cout << "Student ID " << StudentID << " does not exist in Student.txt." << endl;
			cout << "Please try again." << endl << endl;
			repeat = 1;
		}
		//Student ID found and calls modify function
		else {
			if (StudentID[0] == 'S' || StudentID[0] == 's') {
				Student* target = BinarySearchAlgorithmForStudent(StudentHead, StudentID);
				repeat = 0;
				DisplayOneStudent(target);
				ModifyStudentPage(TutorHead, StudentHead, AdminHead, target, StudentID);
			}
			else {
				cout << "Student ID " << StudentID << " does not exist in Student.txt." << endl;
				cout << "Please try again." << endl << endl;
				repeat = 1;
			}
		}
	} while (repeat == 1);
}

//Modify Student Record
void ModifyStudentPage(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead, Student* target, string id) {
	int option, ValidChoice;
	string REPEAT, userInput;
	string modification;

	do {
		ValidChoice = 0;

		cout << "\n==========Modify Student " << id << "'s Record==========" << endl;
		cout << "1. To modify student's phone" << endl << "2. To modify student's center" << endl;
		cout << "3. To add a new tutor for the student" << endl << "4. To remove a tutor for the student" << endl;
		cout << "5. Exit to Student Records Page" << endl;
		cout << "Enter your choice here: ";
		getline(cin, userInput);
		userInput = trim(userInput);
		while (!(checkIntInput(userInput))) {
			cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "\n==========Modify Student " << id << "'s Record==========" << endl;
			cout << "1. To modify student's phone" << endl << "2. To modify student's center" << endl;
			cout << "3. To add a new tutor for the student" << endl << "4. To remove a tutor for the student" << endl;
			cout << "5. Exit to Student Records Page" << endl;
			cout << "Enter your choice here: ";
			//Clear previous input
			cin.clear();
			//Discard previous input
			userInput.clear();
			getline(cin, userInput);
			userInput = trim(userInput);
		}
		option = stoi(userInput);
		switch (option) {
		case 1://Modify Phone Number
			cout << "Enter new phone number for Student " << id << ": ";
			getline(cin, modification);
			//Validate input
			while (!(checkIntInput(modification))) {
				cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;;
				cout << "Enter new phone number for Student " << id << ": ";
				//Clear previous input
				cin.clear();
				//Discard previous input
				modification.clear();
				getline(cin, modification);
			}
			
			target->PhoneNumber = modification;
			WriteStudentFile(StudentHead); //Modify and update student record in text file
			cout << "Student " << id << "'s new phone number is updated." << endl;
			cout << "Enter 'Y' to continue the modification for Student " << id << " or Press any key to return to Student Records Page : ";
			getline(cin, REPEAT);
			REPEAT = trim(REPEAT);
			if (REPEAT == "Y" || REPEAT == "y") {
				ValidChoice = 0;
			}
			else {
				cout << endl;
				ValidChoice = 1;
				StudentRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
			}
			break;
		case 2://Modify Center
			int repeat;

			do {
				repeat = 0;
				cout << "Enter new center code for Student " << id << ": ";
				cin.ignore();
				getline(cin, modification);

				if (modification == "B001C") {
					target->CenterCode = "B001C";
					target->CenterName = "Bukit Jalil";
				}
				else if (modification == "P001C") {
					target->CenterCode = "P001C";
					target->CenterName = "Puchong";
				}
				else if (modification == "I001C") {
					target->CenterCode == "I001C";
					target->CenterName == "Ipoh";
				}
				else {
					cout << "Invalid center code entered." << endl << "Please try again." << endl << endl;
					repeat = 1;
				}
			} while (repeat == 1);
			WriteStudentFile(StudentHead); //Modify and update student record in text file
			cout << id << "'s new center code is updated." << endl;
			cout << "Enter 'Y' to continue the modification for Student " << id << " or Press any key to return to Student Records Page : ";
			getline(cin, REPEAT);
			REPEAT = trim(REPEAT);
			if (REPEAT == "Y" || REPEAT == "y") {
				ValidChoice = 0;
			}
			else {
				cout << endl;
				ValidChoice = 1;
				StudentRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
			}
			break;
		case 3://Modify Number of Tutors (Add tutor)
			if (target->NoOfTutors == 5) {
				ValidChoice = 0;
				cout << "The number of tutors for Student " << id << " is maximized." << endl << "Please remove a tutor before adding." << endl << endl;
			}
			else {
				ValidChoice = 1;
				AddATutorForStudent(TutorHead, StudentHead, AdminHead, target, id);
			}
			break;
		case 4://Modify Number of tutors (Remove tutor)
			if (target->NoOfTutors == 0) {
				ValidChoice = 0;
				cout << "Student " << id << " has no tutor yet." << endl << "Please add a tutor before removing." << endl << endl;
			}
			else {
				ValidChoice = 1;
				RemoveATutorForStudent(TutorHead, StudentHead, AdminHead, target, id);
			}
			break;
		case 5: //Return to Student Sub Menu for Admins
			ValidChoice = 1;
			StudentRecordsForAdminSubMenu(TutorHead, StudentHead, AdminHead);
			break;
		default:
			ValidChoice = 0;
			cout << "Invalid number entered." << endl << "Please try again." << endl << endl;
		}
	} while (ValidChoice == 0);

}

//Allow Admin to Add New Tutor for Student
void AddATutorForStudent(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead, Student* target, string id) {
	int repeat;
	string TutorID;
	bool ValidTutor, NoRepeatTutor;

	do {
		cout << "Enter the tutor ID to add for Student " << id << " or Enter 'Y' to return to previous page: ";
		getline(cin, TutorID);
		TutorID = trim(TutorID);
		while (TutorID.empty()) {
			cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "Enter the tutor ID to add for Student " << id << " or Enter 'Y' to return to previous page: ";

			//Clear previous input
			cin.clear();
			//Discard previous input
			TutorID.clear();
			getline(cin, TutorID);
			TutorID = trim(TutorID);
		}
		

		if (TutorID == "Y" || TutorID == "y") {
			ModifyStudentPage(TutorHead, StudentHead, AdminHead, target, id);
			return;
		}

		ValidTutor = AValidTutorForStudents(TutorHead, TutorID);
		NoRepeatTutor = NoRepeatTutorForOneStudent(TutorHead, target, TutorID);
		if (ValidTutor && NoRepeatTutor && target->NoOfTutors < 5) {
			target->TutorID[target->NoOfTutors] = TutorID;
			target->NoOfTutors = target->NoOfTutors + 1;
			cout << "Tutor " << TutorID << " is added for Student " << id << "." << endl << endl;
			repeat = 1;
		}
		else if (!ValidTutor) {
			cout << "Invalid tutor ID entered." << endl << "Please try again." << endl << endl;
			repeat = 1;
		}
		else if (!NoRepeatTutor) {
			cout << "The tutor with ID " << TutorID << " already exists for Student " << id << "." << endl;
			cout << "Please enter other tutor ID." << endl << endl;
			repeat = 1;
		}
		else {
			cout << "The number of tutors for Student " << id << " is maximized." << endl << "Please remove a tutor before adding." << endl << endl;
			repeat = 0;
		}
	} while (repeat == 1);
	ModifyStudentPage(TutorHead, StudentHead, AdminHead, target, id);
}

bool AValidTutorForStudents(Tutor* TutorHead, string TutorID) {
	bool ValidTutor = false;

	while (TutorHead != NULL) {
		if (TutorHead->TutorID == TutorID) {
			ValidTutor = true;
			return ValidTutor;
		}

		TutorHead = TutorHead->next;
	}

	return ValidTutor;
}

bool NoRepeatTutorForOneStudent(Tutor* TutorHead, Student* wantedstudent, string TutorID) {
	bool NoRepeat = true;

	for (int i = 0; i < wantedstudent->NoOfTutors; i++) {
		if (wantedstudent->TutorID[i] == TutorID) {
			NoRepeat = false;
			return NoRepeat;
		}
	}

	return NoRepeat;
}

//Allow Admin to remove tutor for student
void RemoveATutorForStudent(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead, Student* target, string id) {
	int found;
	string TutorID;

	do {
		found = 0;
		cout << "Enter the tutor ID to remove for Student " << id << " or Enter 'Y' to return to previous page: ";
		
		getline(cin, TutorID);
		TutorID = trim(TutorID);
		while (TutorID.empty()) {
			cout << "Invalid input entered." << endl << "Please try again." << endl << endl << endl;
			cout << "Enter the tutor ID to remove for Student " << id << " or Enter 'Y' to return to previous page: ";

			//Clear previous input
			cin.clear();
			//Discard previous input
			TutorID.clear();
			getline(cin, TutorID);
			TutorID = trim(TutorID);
		}

		if (TutorID == "Y" || TutorID == "y") {
			ModifyStudentPage(TutorHead, StudentHead, AdminHead, target, id);
			return;
		}
		//Loop through list of tutors under student record
		for (int i = 0; i < target->NoOfTutors; i++) {
			if (target->TutorID[i] == TutorID) {
				found = 1;

				if (i + 1 == target->NoOfTutors) {
					target->TutorID[i] = "Nope";
					--target->NoOfTutors;
				}
				else {
					while (i < target->NoOfTutors) {
						if (i + 1 == target->NoOfTutors) {
							target->TutorID[i] = "Nope";
						}
						else {
							target->TutorID[i] = target->TutorID[i + 1];
							i++;
						}
					}
				}
				break;
			}
		}

		if (found == 0) {
			cout << "Tutor ID " << TutorID << " is an invalid tutor ID for Student " << id << "." << endl;
			cout << "Please try again." << endl << endl;
		}
		else {
			cout << "Tutor ID " << TutorID << " is removed for Student " << id << "." << endl;
			ModifyStudentPage(TutorHead, StudentHead, AdminHead, target, id);
		}
	} while (found == 0);

}