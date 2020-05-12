// Food Donation Management System developed by Akmal Sab

#include <iostream> //Standard Input Output Streams Library
#include <cstdio> //C Standard Input and Output Library 
#include <fstream> //File streams
#include <sstream> //String streams
#include <string> //This header introduces string types, character traits and a set of converting functions
#include <cstdlib> //C Standard General Utilities Library
#include <conio.h> //compilers to provide console input/output
#include <windows.h> //contains declarations for all of the functions in the Windows API
#include <mysql.h> // The mysql.h is the most important header file for MySQL function calls
#include <iomanip>
#include "libxl.h"
using namespace libxl;
using namespace std;
#ifndef FDMS_H //checks whether the given token has been defined earlier in the file or in an included file
#define FDMS_H

class FoodDonation{
private:
	string username, password;
	int chooseUserType, registers, choice, select;
	char choose;
public:
	MYSQL* conn; // Define a pointer variable to a MYSQL connection data structure
	MYSQL_ROW row; // the data structure used to store one row (= one tuple) of the result data
	MYSQL_ROW countrow;
	MYSQL_RES* res; //a data structure used to represents the result of a query
	MYSQL_RES* countres;
	int qstate; //query state

	string profileIdentifier, selectQuery, insertQuery, updateQuery, deleteQuery, countQuery;
	const char* constantChar;
	
	FoodDonation(); //constructor
	~FoodDonation(); //destructor
	void databaseConnection();
	void loginSelection();
	void setUserLogin(int chooseUserType);
	int getUserLogin();
	void setUsername(string username);
	void setPassword(string password);
	string getUsername();
	string getPassword();	
	void managerLogin();
	void managerProfile();
	void donorLogin();
	void donorProfile();
	void volunteerLogin();
	void volunteerProfile();
	void Registration();
	void managerRegistration();
	void donorRegistration();
	void volunteerRegistration();
	void createEvent();
	void showEvent();
	void showEventClient();
	void deleteEvent();
	void updateEvent();
	void createFoodbank();
	void updateFoodbank();
	void deleteFoodbank();
	void showFoodbank();
	void showFoodbankClient();
	void makeDonation();
	void showDonation();
	void showDonationClient();
	void joinEvent();
	void showJoinedEvent();
	int reportGeneration();
};
#endif
