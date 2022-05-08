#pragma once
#include <iostream>
#include <string>
#include "Struct.h"
#include "SubMenu.h"
#include "Search.h"
#include "ReadFile.h"
#include "WriteFile.h"

using namespace std;

bool AddNewTutor(Tutor*);
void DeleteTutor(Tutor*);
void ModifyTutor(Tutor*, Student*, Admin*);
void TerminateTutor(Tutor*, Student*, Admin*);
void SearchStudentToModify(Tutor*, Student*, Admin*);
void ModifyStudentPage(Tutor*, Student*, Admin*, Student*, string);
void AddATutorForStudent(Tutor*, Student*, Admin*, Student*, string);
void RemoveATutorForStudent(Tutor*, Student*, Admin*, Student*, string);

//Function for System to Automatically Delete Tutor Record if Termination Date >= 180 days
void DeleteTutor(Tutor* TutorHead) {
	Tutor* updated = NULL;
	struct tm time = GetCurrentTime();
	bool updateSuccess = false;
	//Get Current Date
	int currentDay = time.tm_mday;
	int currentMonth = time.tm_mon + 1;
	int currentYear = 1900 + time.tm_year;
	int day = 0, month = 0, year = 0, dayDifferences;
	string yearString, monthString, dayString;

	if (TutorHead == NULL)
		return;
	while (TutorHead != NULL) {
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
		if (TermDate == "1900-01-01") {
			InsertAtEndForReadTutorFile(&updated, TutorHead->TutorID, TutorHead->Name,
				TutorHead->DateJoin, TutorHead->DateTerminate, TutorHead->HourlyRate,
				TutorHead->PhoneNumber, TutorHead->Address, TutorHead->CenterCode,
				TutorHead->CenterName, TutorHead->SubjectCode, TutorHead->SubjectName,
				TutorHead->TotalRatings, TutorHead->NoOfRatings, TutorHead->AverageRating);
			
		}
		//TermDate is valid
		else {
			//termination date is in future, do not delete
			if (checkFutureDate(day, month, year)) {
				InsertAtEndForReadTutorFile(&updated, TutorHead->TutorID, TutorHead->Name,
					TutorHead->DateJoin, TutorHead->DateTerminate, TutorHead->HourlyRate,
					TutorHead->PhoneNumber, TutorHead->Address, TutorHead->CenterCode,
					TutorHead->CenterName, TutorHead->SubjectCode, TutorHead->SubjectName,
					TutorHead->TotalRatings, TutorHead->NoOfRatings, TutorHead->AverageRating);		
			}
			//termination date in the past
			else {
				dayDifferences = getDifferenceDate(day, month, year, currentDay, currentMonth, currentYear);
				//Check if TermDate is more than 180 days, if yes, delete by skipping the node
				if (dayDifferences >= 180) {
					 //Skip current node to delete
				}
				//less than 180 days, remain record
				else {
					InsertAtEndForReadTutorFile(&updated, TutorHead->TutorID, TutorHead->Name,
						TutorHead->DateJoin, TutorHead->DateTerminate, TutorHead->HourlyRate,
						TutorHead->PhoneNumber, TutorHead->Address, TutorHead->CenterCode,
						TutorHead->CenterName, TutorHead->SubjectCode, TutorHead->SubjectName,
						TutorHead->TotalRatings, TutorHead->NoOfRatings, TutorHead->AverageRating);
					
				}
			}
		}
		TutorHead = TutorHead->next;
	}
	WriteTutorFile(updated);
}
//Function to Add New Tutor Record
bool AddNewTutor(Tutor* TutorHead) {
	int valid;
	bool addSuccess = false;
	string tutorID, name, dateJoin, dateTerminate, phone, address, centerCode, centerName, subjectCode, subjectName;
	int hourlyRate;

	//Get unique ID for new tutor
	tutorID = GetUniqueTutorID(&TutorHead);

	//Get details of new tutor
	cout << "\n==========Add New Tutor Record==========" << endl;
	cout << "Tutor ID for New Tutor: " << tutorID << endl;
	cout << "Enter new tutor name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Tutor Join Date (YYYY-MM-DD)";
	getline(cin, dateJoin);
	dateTerminate = "1900-01-01";
	cout << "Enter Tutor Phone Number: ";
	getline(cin, phone);
	cout << "Enter Tutor Address: ";
	getline(cin, address);

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
		cout << "Enter subject name here (Choices: English, Math, Chemistry, Physics, Biology): << endl";
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
		}
	} while (valid == 0);

	cout << "Enter hourly rate (in RM) for tutor: RM";
	cin >> hourlyRate;
	
	TutorHead = InsertAtBeginningForReadTutorFile(&TutorHead, tutorID, name, dateJoin, dateTerminate, hourlyRate, phone, address, centerCode, centerName, subjectCode, subjectName, 0, 0, 0);
	addSuccess = WriteTutorFile(TutorHead);
	return addSuccess;
}

//Function to Modify Tutor Records
void ModifyTutor(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int option, ValidChoice;
	char repeat;
	string TutorID, modification;

	cout << "\n==========Modify a Tutor Record==========" << endl;
	cout << "Enter the tutor ID to modify: ";
	cin >> TutorID;
	cout << endl;
	cout << "Tutor's Record: " << endl;
	//Search for tutor ID to be modified
	if (BinarySearchAlgorithmForTutor(TutorHead, TutorID) == NULL) { //If ID cannot be found
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
		cout << "Please try again." << endl << endl;
		ModifyTutor(TutorHead, StudentHead, AdminHead);
	}
	else { //ID Found and display
		Tutor* target = BinarySearchAlgorithmForTutor(TutorHead, TutorID);
		DisplayOneTutorForAdmin(target);

		do {
			//Select choice to modify which specific information
			ValidChoice = 0;
			cout << "Enter '1' to modify tutor's phone" << endl;
			cout << "Enter '2' to modify tutor's address" << endl;
			cout << "Enter '3' to return to Tutor Record Page" << endl;
			cout << "Enter your choice here: ";
			while (!(cin >> option)) {
				cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
				cout << "Enter '1' to modify tutor's phone" << endl;
				cout << "Enter '2' to modify tutor's address" << endl;
				cout << "Enter '3' to return to Tutor Record Page" << endl;
				cout << "Enter your choice here: ";

				//Clear previous input
				cin.clear();
				//Discard previous input
				cin.ignore(100, '\n');
			}

			switch (option) {
			case 1: //Modify Phone Number
				ValidChoice = 1;
				cout << "Enter new phone number: ";
				cin.ignore();
				getline(cin, modification);
				target->PhoneNumber = modification;
				WriteTutorFile(TutorHead); //Modify and update tutor record in text file
				cout << TutorID << "'s phone number is updated." << endl;
				cout << "Enter 'Y' to continue the modification for Tutor " << TutorID << " or Press any key to return to Tutor Records Page : ";
				cin >> repeat;
				if (repeat == 'Y' || repeat == 'y') {
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
				cin.ignore();
				getline(cin, modification);
				target->Address = modification;
				WriteTutorFile(TutorHead); //Modify and update tutor record in text file
				cout << TutorID << "'s address is updated." << endl;
				cout << "Enter 'Y' to continue the modification for Tutor " << TutorID << " or Press any key to return to Tutor Records Page : ";
				cin >> repeat;
				if (repeat == 'Y' || repeat == 'y') {
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
}

//Function to Termination Date for Tutor
void TerminateTutor(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	string TutorID, DateTerminate;
	char ch1 = NULL, ch2 = NULL;
	int option, ValidChoice, day, month, year;
	string dayString, monthString, yearString;
	bool valid = true;
	cout << "\n==========Terminate a Tutor==========" << endl;
	cout << "Enter the tutor ID to terminate: ";
	cin >> TutorID;
	cout << endl;
	cout << "Tutor's Record: " << endl;

	if (BinarySearchAlgorithmForTutor(TutorHead, TutorID) == NULL) {
		cout << "Tutor ID " << TutorID << " does not exist in Tutor.txt." << endl;
		cout << "Please try again." << endl << endl;
		TerminateTutor(TutorHead,StudentHead,AdminHead);
	}
	else {
		Tutor* target = BinarySearchAlgorithmForTutor(TutorHead, TutorID);
		DisplayOneTutorForAdmin(target);

		do {
			ValidChoice = 0;
			cout << "Enter '1' to continue or '2' to return to Tutor Records Page: ";
			cin >> option;
			switch (option) {
			case 1: //User confirm termination date
				ValidChoice = 1;
				do {
					//Get Termination  Date - Year
					cout << "Enter year of termination date for tutor (format - YYYY): "; 
					while (!(cin >> year)) {
						cout << "\nWrong Year Format Input! Please try again with integers only.\n";
						cout << "Enter year of termination date for tutor (format - YYYY): ";
						//Clear previous input
						cin.clear();
						//Discard previous input
						cin.ignore(100, '\n');
					}
					//Get Termination  Date - Month
					cout << "Enter month of termination date for tutor (format - MM): "; 
					while (!(cin >> month)) {
						cout << "\nWrong Month Format Input! Please try again with integers only.\n";
						cout << "Enter month of termination date for tutor (format - MM): ";
						//Clear previous input
						cin.clear();
						//Discard previous input
						cin.ignore(100, '\n');
					}

					//Get Termination  Date - Day
					cout << "Enter day of termination date for tutor (format - DD): "; 
					while (!(cin >> day)) {
						cout << "\nWrong Day Format Input! Please try again with integers only.\n";
						cout << "Enter day of termination date for tutor (format - DD): ";
						//Clear previous input
						cin.clear();
						//Discard previous input
						cin.ignore(100, '\n');
					}

					//Invalid Date
					if (!(isValidDate(day, month, year))) {
						cout << "\nInvalid Date Input! Please try again with a valid date.\n";
						valid = false;
						
					}
					//Valid Date
					else if (isValidDate(day, month, year)){
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
						cout << DateTerminate << endl;
					}
					else {
						cout << "Invalid Date Input! Please try again with a valid date.\n ";
						valid = false;
					}
				} while (!valid);
				
				target->DateTerminate = DateTerminate;
				WriteTutorFile(TutorHead); //Modify and Update records in text file
				cout << TutorID << "'s date of termination is updated." << endl;
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
}

//Admin search student to modify details
void SearchStudentToModify(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead) {
	int repeat;
	string StudentID;

	do {
		cout << "==========Search a Student to Modify==========" << endl;
		cout << "Enter the student ID to modify: ";
		cin >> StudentID;
		//Trim Input
		StudentID = trim(StudentID);
		//Change small letter to capital letter if there are any
		for_each(StudentID.begin(), StudentID.end(), [](char& c)
			{
				c = toupper(c);
			});
		cout << endl;
		cout << "Student's Record: " << endl;

		//Invalid ID or No search results
		if (BinarySearchAlgorithmForStudent(StudentHead, StudentID) == NULL) {
			cout << "Tutor ID " << StudentID << " does not exist in Tutor.txt." << endl;
			cout << "Please try again." << endl << endl;
			repeat = 1;
		}
		//Student ID found and calls modify function
		else {
			Student* target = BinarySearchAlgorithmForStudent(StudentHead, StudentID);
			repeat = 0;
			DisplayOneStudent(target);
			ModifyStudentPage(TutorHead, StudentHead, AdminHead, target, StudentID);
		}
	} while (repeat == 1);
}

//Modify Student Record
void ModifyStudentPage(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead, Student* target, string id) {
	int option, ValidChoice;
	char REPEAT;
	string modification;

	do {
		ValidChoice = 0;

		cout << "\n==========Modify Student " << id << "'s Record==========" << endl;
		cout << "1. To modify student's phone" << endl << "2. To modify student's center" << endl;
		cout << "3. To add a new tutor for the student" << endl << "4. To remove a tutor for the student" << endl;
		cout << "5. Exit to Student Records Page" << endl;
		cout << "Enter your choice here: ";
		while (!(cin >> option)) {
			cout << "********INVALID INPUT********\nPlease try again.\n" << endl;
			cout << "\n==========Modify Student " << id << "'s Record==========" << endl;
			cout << "1. To modify student's phone" << endl << "2. To modify student's center" << endl;
			cout << "3. To add a new tutor for the student" << endl << "4. To remove a tutor for the student" << endl;
			cout << "5. Exit to Student Records Page" << endl;
			cout << "Enter your choice here: ";
			//Clear previous input
			cin.clear();
			//Discard previous input
			cin.ignore(100, '\n');
		}

		switch (option) {
		case 1://Modify Phone Number
			cout << "Enter new phone number for Student " << id << ": ";
			cin.ignore();
			getline(cin, modification);
			target->PhoneNumber = modification;
			WriteStudentFile(StudentHead); //Modify and update student record in text file
			cout << "Student " << id << "'s new phone number is updated." << endl;
			cout << "Enter 'Y' to continue the modification for Student " << id << " or Press any key to return to Student Records Page : ";
			cin >> REPEAT;
			if (REPEAT == 'Y' || REPEAT == 'y') {
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
			cin >> REPEAT;
			if (REPEAT == 'Y' || REPEAT == 'y') {
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
	int ValidTutor;
	string TutorID;

	do {
		ValidTutor = 0;
		cout << "Enter the tutor ID to add for Student " << id << " or Enter 'Y' to return to previous page: ";
		cin.ignore();
		getline(cin, TutorID);

		if (TutorID == "Y" || TutorID == "y") {
			ModifyStudentPage(TutorHead, StudentHead, AdminHead,target, id);
			return;
		}

		while (TutorHead != NULL) {
			if (TutorHead->TutorID == TutorID) {
				ValidTutor = 1;
				target->TutorID[target->NoOfTutors] = TutorID;
				cout << "Tutor " << TutorID << " is added for Student " << id << "." << endl << endl;
				AddATutorForStudent(TutorHead, StudentHead, AdminHead, target, id);
				break;
			}

			TutorHead = TutorHead->next;
		}

		if (ValidTutor == 0) {
			cout << "Invalid tutor ID entered." << endl << "Please try again." << endl << endl;
		}

	} while (ValidTutor == 0);

}

//Allow Admin to remove tutor for student
void RemoveATutorForStudent(Tutor* TutorHead, Student* StudentHead, Admin* AdminHead, Student* target, string id) {
	int found;
	string TutorID;

	do {
		found = 0;
		cout << "Enter the tutor ID to remove for Student " << id << " or Enter 'Y' to return to previous page: ";
		cin.ignore();
		getline(cin, TutorID);

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