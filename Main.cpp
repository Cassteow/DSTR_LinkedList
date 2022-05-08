#include <iostream>
#include "Display.h"
#include "Edit.h"
#include "ExtraFunction.h"
#include "RateTutors.h"
#include "ReadFile.h"
#include "Report.h"
#include "Search.h"
#include "Struct.h"
#include "SubMenu.h"
#include "WriteFile.h"
#include "Sort.h"

using namespace std;

//Function Prototype Declaration
bool AdminLogin(Admin*, string, string);
struct Student* StudentLogin(Student*, string, string);
void MainLandingPage();

int main() {
	//Call Main Landing Page Function
	MainLandingPage();
	return 0;
}

//Function for Main Landing Page (displayed when system starts or when user logout)
void MainLandingPage() {
	int login;
	char repeat;
	bool registered = false;
	string id, password, name, phone, NewStudentID = "S" + to_string(rand()), centercode, centername;
	struct tm time = GetCurrentTime();

	//Read all Tutor, Student, and Admin records into linked list
	Tutor* TUTOR = ReadTutorFile();
	Student* STUDENT = ReadStudentFile();
	Admin* ADMIN = ReadAdminFile();
	//Update Tutor Records and Delete Records with Termination Date more than 180 days ago
	DeleteTutor(TUTOR);
	TUTOR = ReadTutorFile();

	//MAIN LANDING PAGE FOR TUTOR MANAGEMENT SYSTEM
	cout << "\n====================Tutors Management System====================" << endl;
	cout << "===================" << CorrectWeekDayTime(time.tm_wday) << " " << CorrectMonthTime(time.tm_mon) << " " << time.tm_mday << " " << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << " " << 1900 + time.tm_year << "====================" << endl;
	cout << "Main Menu: " << endl;
	cout << "1. Login as Admin" << endl << "2. Login as Student" << endl;
	cout << "3. Register as New Student" << endl << "4. Exit the system" << endl;
	cout << "Enter your choice here: ";
	//Input Validation (ensure input is integer)
	while (!(cin >> login)) {
		cout << "********INVALID INPUT********\nPlease try again.\n" << endl;

		cout << "====================Tutors Management System====================" << endl;
		cout << "===================" << CorrectWeekDayTime(time.tm_wday) << " " << CorrectMonthTime(time.tm_mon) << " " << time.tm_mday << " " << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << " " << 1900 + time.tm_year << "====================" << endl;
		cout << "Main Menu: " << endl;
		cout << "1. Login as Admin" << endl << "2. Login as Student" << endl;
		cout << "3. Register as New Student" << endl << "4. Exit the system" << endl;
		cout << "Enter your choice here: ";
		//Clear previous input
		cin.clear();
		//Discard previous input
		cin.ignore(100, '\n');
	}

	switch (login) {
	case 1: //ADMIN LOGIN
		do {
			cout << endl;
			cout << "----------Login as Admin----------" << endl;
			cout << "Enter your admin ID here: ";
			cin >> id;
			cout << "Enter your password here: ";
			cin >> password;
			//Check admin login credentials wiht function that returns boolean value
			if (AdminLogin(ADMIN, id, password)) {
				repeat = 'A';
				//Call Admin Sub Menu Function if credentials are correct
				AdminSubMenu(TUTOR, STUDENT, ADMIN);
			}
			else {
				cout << "Enter 'Y' to try again or Press any key to return to main menu: ";
				cin >> repeat;
			}
		} while (repeat == 'Y' || repeat == 'y');

		if (repeat != 'Y' || repeat != 'y') {
			cout << endl << endl;
			main();
		}

		break;

	case 2: //STUDENT LOGIN
		Student * WantedStudent;
		do {
			cout << endl;
			cout << "----------Login as Student----------" << endl;
			cout << "Enter your student ID here: ";
			cin >> id;
			cout << "Enter your password here: ";
			cin >> password;
			//Check student login credentials wiht function that returns boolean value
			if (StudentLogin(STUDENT, id, password) != NULL) {
				WantedStudent = StudentLogin(STUDENT, id, password);
				repeat = 'A';
				cout << endl;
				cout << "Dear Student " << id << ", welcome back." << endl;
				//Call Admin Sub Menu Function if credentials are correct
				StudentSubMenu(TUTOR, STUDENT, WantedStudent);
				break;
			}
			else {
				cout << "Enter 'Y' to try again or Press any key to return to main menu: ";
				cin >> repeat;
			}
		} while (repeat == 'Y' || repeat == 'y');

		if (repeat != 'Y' || repeat != 'y')
			main();
		break;
	case 3: //STUDENT REGISTRATION
		int valid;

		cout << endl;
		cout << "----------Register New Student----------" << endl;
		cout << "Enter your name here: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter your phone number here: "; //**** ADD VALIDATE PHONE NUMBER
		getline(cin, phone);

		//Choose tuition center for student registration
		do {
			valid = 0;
			cout << "Enter your center name here ('Bukit Jalil' or 'Puchong' or 'Ipoh'): ";
			getline(cin, centername);
			if (trim(centername) == "Bukit Jalil") {
				centercode = "B001C";
				valid = 1;
			}
			else if (trim(centername) == "Puchong") {
				centercode = "P001C";
				valid = 1;
			}
			else if (trim(centername) == "Ipoh") {
				centercode = "I001C";
				valid = 1;
			}
			else {
				cout << "Invalid center name entered." << endl << "Please enter again." << endl << endl;
				valid = 0;
			}
		} while (valid == 0);

		cout << "Your assigned student ID: " << NewStudentID << endl; //Display System Assigned student ID
		cout << "Enter your password here: ";
		getline(cin, password);

		//Insert New Student record at the end of the linked list
		InsertAtEndForReadStudentFile(&STUDENT, NewStudentID, trim(name), trim(phone), password, centercode, trim(centername), "Nope", "Nope", "Nope", "Nope", "Nope", 0);
		//Write Updated Linked List into student file
		registered = WriteStudentFile(STUDENT);
		//Registration Successful
		if (registered) {
			cout << endl << "Registered successfully!" << endl << "Your Student ID is: " << NewStudentID << endl << "Please login as a student using the assigned Student ID.\n\n" << endl;
		}
		//Registration Unsucessful
		else {
			cout << endl << "Registration Unsuccessful!\n Please try again later.\n\n";
		}
		main();
		break;
	case 4: //EXIT SYSTEM (Update latest data into text file before exit system)
		WriteFilesBeforeEnd(TUTOR, STUDENT);
		break;
	default:
		//INVALID USER INPUT CHOICE
		cout << "Invalid number entered." << endl << "Please try again." << endl << endl << endl;
		main();
	}
}

//FUNCTION TO CHECK ADMIN LOGIN CREDENTIAL
bool AdminLogin(Admin* head, string id, string password) { 
	while (head != NULL) {
		if (head->AdminID == id) {
			if (head->Password == password) {
				cout << endl << "Dear Admin " << id << ", welcome back." << endl;
				return true;
			}
			else {
				cout << "Incorrect password for Admin " << id << "." << endl;
				return false;
			}
		}

		head = head->next;
	}

	cout << id << " is an invalid admin ID." << endl;
	return false;
}

//FUNCTION TO CHECK STUDENT LOGIN CREDENTIAL
struct Student* StudentLogin(Student* head, string id, string password) {
	while (head != NULL) {
		if (head->StudentID == id) {
			if (head->Password == password) {
				return head;
			}
			else {
				cout << "Incorrect password for Student " << id << "." << endl;
				return NULL;
			}
		}
		head = head->next;
	}

	return NULL;
}