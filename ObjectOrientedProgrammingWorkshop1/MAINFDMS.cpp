#include "FDMS.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	
    int chooseUserType; //declare variable

    FoodDonation fdms; //create class's object

	fdms.databaseConnection(); // connection to database

    system("cls"); // clear all output on cmd

    cout << "Food Donation Management System\n";
    cout << "Please Select Type of User Login !\n";
    cout << "1. Managers\n";
    cout << "2. Donors\n";
    cout << "3. Volunteers\n";
    cout << "4. Register New\n";
    cout << "Your Choice :\t";
    cin >> chooseUserType;
    if (chooseUserType < 1 || chooseUserType > 4) {
        cout << "You have enter wrong option, please try again.\t";
        _getch();
        fdms.loginSelection();
    }
    else {
        fdms.setUserLogin(chooseUserType);
        if (fdms.getUserLogin() == 1) {
            fdms.managerLogin();
        }
        else if (fdms.getUserLogin() == 2) {
            fdms.donorLogin();
        }
        else if (fdms.getUserLogin() == 3) {
            fdms.volunteerLogin();
        }
        else if (fdms.getUserLogin() == 4) {
            fdms.Registration();            
        }
    }
}