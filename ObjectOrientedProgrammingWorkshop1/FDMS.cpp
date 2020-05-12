#include "FDMS.h"

FoodDonation::FoodDonation() {
    choice = 0;
    select = 0;
    choose;
    username = "";
    password = "";
    chooseUserType = 0;
    registers = 0;
    selectQuery = "";
    updateQuery = "";
    deleteQuery = "";
    insertQuery = "";
    countQuery = "";
    profileIdentifier = "";
}

FoodDonation::~FoodDonation() {

}

void FoodDonation::databaseConnection() {
    conn = mysql_init(0); 
    // Initialize the MYSQL connection data structure 

    conn = mysql_real_connect(conn, "localhost", "root", "", "workshop2", 3306, NULL, 0); 
    //establish a connection to a MySQL database engine on host

    if (conn)
        cout << "Database Connected To MySql" << conn << endl;
    else
        cout << "Failed To Connect ! " << mysql_errno(conn) << endl; // Returns the numerical value of the error message from previous MySQL operation
}

void FoodDonation::setUserLogin(int chooseUserType) {
    this->chooseUserType = chooseUserType;
}

int FoodDonation::getUserLogin() {
    return chooseUserType;
}

void FoodDonation::loginSelection() {
    system("cls");

    cout << "Please Select Type of User Login !\n";
    cout << "1. Managers\n";
    cout << "2. Donors\n";
    cout << "3. Volunteers\n";
    cout << "4. Register New\n";
    cout << "Your Choice:\t";
    cin >> select;
    if (select < 1 || select > 4) {
        cout << "You have enter wrong option, press any key to retry\t";
        _getch();
        loginSelection();
    }
    else {
        setUserLogin(select);
        if (getUserLogin() == 1) {
            managerLogin();
        }
        else if (getUserLogin() == 2) {
            donorLogin();
        }
        else if (getUserLogin() == 3) {
            volunteerLogin();
        }
        else if (getUserLogin() == 4) {
            Registration();            
        }
    }
        

}

void FoodDonation::setUsername(string uname) {
    username = uname;
}

void FoodDonation::setPassword(string pass) {
    password = pass;
}

string FoodDonation::getUsername() {
    return username;
}

string FoodDonation::getPassword() {
    return password;
}

void FoodDonation::Registration() {

    system("cls");

    cout << "Please Select Type of User to Register !\n";
    cout << "1. Register Managers\n";
    cout << "2. Register Donors\n";
    cout << "3. Register Volunteers\n";
    cout << "4. Cancel Register\n";
    cout << "Your Choice :\t";
    cin >> registers;
    switch (registers)
    {
    case 1:
        managerRegistration();
        break;
    case 2:
        donorRegistration();
        break;
    case 3:
        volunteerRegistration();
        break;
    case 4:
        loginSelection();
        break;
    default:
        cout << "You have enter wrong option, please try again.\t";
        _getch();
        Registration();
        break;
    }
}

void FoodDonation::managerLogin() {

    system("cls");

    string uname, pass = "";

    cout << "Insert Manager's credential !\n";
    cin.ignore(1, '\n'); //clear the unwanted buffer, so when next input is taken, it stores into the desired container, but not in the buffer of previous variable
    cout << "Enter Your Username:\t";
    getline(cin, uname);       

    cout << "Enter Your Password:\t";
    getline(cin, pass);

    setUsername(uname);
    setPassword(pass);

    selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str(); 
    /*c_str converts string to constant char and this is required
    pass the contents of an string to a function that expects to work with a C-style string.*/
    qstate = mysql_query(conn, constantChar); //executes a query on a MySQL database
    if (qstate == 0) //Return Values = Zero for success. Nonzero if an error occurred.
    {
        res = mysql_store_result(conn); //must call mysql_store_result() for every statement that successfully produces a result set
        row = mysql_fetch_row(res);        
        if (row)
        {
            //cout << "IC: " << row[0] << "\nName: " << row[1] << "\nTelephone Number: " << row[2] << "\nLocation: " << row[3] << "\nUsername: " << row[4] << "\nPassword: " << row[5] << endl << endl;    
            //cout << "row = " << row << " res = " << res << endl;
            system("cls");
            profileIdentifier = "manager";
            cout << "Welcome Back Manager " << row[1] << "\n";
            cout << "Press any key to continue\n";
            _getch();
            managerProfile();
        }
        else
        {
            cout << "Username or Password may wrong, Press any key to continue.\t";
            //cout << "row = " << row << " res = " << res << endl;
            _getch();
            loginSelection();            
        }        
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch(); 
        loginSelection();
    }
    mysql_free_result(res); // frees the memory allocated for a result set by mysql_store_result()
}

void FoodDonation::donorLogin() {
    system("cls");

    string uname, pass;

    cout << "Insert Donor's credential !" << endl;
    cin.ignore(1, '\n');

    cout << "Enter Your Username:\t";
    getline(cin, uname);

    cout << "Enter Your Password:\t";
    getline(cin, pass);

    setUsername(uname);
    setPassword(pass);

    selectQuery = "select * from donor where donorUsername = '" + getUsername() + "' and donorPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str(); // c_str converts string to constant char and this is required
    qstate = mysql_query(conn, constantChar); //executes a query on a MySQL database
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (row)
        {
            system("cls");
            profileIdentifier = "donor";
            cout << "Welcome Back Donor " << row[1] << "\n";
            cout << "Press any key to continue\n";
            _getch();
            donorProfile();
        }
        else
        {
            cout << "Username or Password may wrong. Press any key to continue.\n";
            _getch();
            loginSelection();
        }
    }
    else
    {
        cout << "Query Execution Problem! -> " << mysql_errno(conn) << endl;
    }
    mysql_free_result(res);
}

void FoodDonation::volunteerLogin() {
    system("cls");

    string uname, pass;

    cout << "Insert Volunteer's credential !" << endl;
    cin.ignore(1, '\n');

    cout << "Enter Your Username:\t";
    getline(cin, uname);

    cout << "Enter Your Password:\t";
    getline(cin, pass);

    setUsername(uname);
    setPassword(pass);

    selectQuery = "select * from volunteer where volunteerUsername = '" + getUsername() + "' and volunteerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (row)
        {
            system("cls");
            profileIdentifier = "volunteer";
            cout << "Welcome Back Volunteer " << row[1] << "\n";
            cout << "Press any key to continue\n";
            _getch();
            volunteerProfile();
        }
        else
        {
            cout << "Username or Password may wrong. Press any key to continue.\n";
            _getch();
            loginSelection();
        }
    }
    else
    {
        cout << "Query Execution Problem! -> " << mysql_errno(conn) << endl;
        _getch();
        loginSelection();
    }
    mysql_free_result(res);
}

void FoodDonation::managerRegistration() {
    system("cls");
    string managerIc = "";
    string managerName = "";
    string managerTelNum = "";
    string managerLocation = "";
    string managerUsername = "";
    string managerPassword = "";

    cout << "Insert new Manager's information !" << endl << endl;
    cin.ignore(1, '\n');
    cout << "Enter Your IC: ";
    getline(cin, managerIc); //Get line from stream into string
    cout << "Enter Your Name: ";
    getline(cin, managerName);
    cout << "Enter Your Telephone Number: ";
    getline(cin, managerTelNum);
    cout << "Enter Your Location: ";
    getline(cin, managerLocation);
    cout << "Enter Your Username: ";
    getline(cin, managerUsername);
    cout << "Enter Your Password: ";
    getline(cin, managerPassword);

    insertQuery = "insert into manager (managerIc, managerName, managerTelNum, managerLocation, managerUsername, managerPassword) values ('" + managerIc + "','" + managerName + "','" + managerTelNum + "','" + managerLocation + "','" + managerUsername + "','" + managerPassword + "')";
    constantChar = insertQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        cout << "\nThe manager has been successfully registered, press any key to continue!" << endl;
        _getch();
        loginSelection();
    }
    else
    {
        cout << "Query Execution Problem! " << mysql_errno(conn) << " press any key to continue!" << endl;
        _getch();
        Registration();
    }
}

void FoodDonation::donorRegistration() {
    system("cls");
    string donorIc = "";
    string donorName = "";
    string donorTelNum = "";
    string donorLocation = "";
    string donorUsername = "";
    string donorPassword = "";


    cout << "Insert new Donor's information !" << endl << endl;
    cin.ignore(1, '\n');
    cout << "Enter Your IC: ";
    getline(cin, donorIc); //Get line from stream into string
    cout << "Enter Your Name: ";
    getline(cin, donorName);
    cout << "Enter Your Telephone Number: ";
    getline(cin, donorTelNum);
    cout << "Enter Your Location: ";
    getline(cin, donorLocation);
    cout << "Enter Your Username: ";
    getline(cin, donorUsername);
    cout << "Enter Your Password: ";
    getline(cin, donorPassword);

    insertQuery = "insert into donor (donorIc, donorName, donorTelNum, donorLocation, donorUsername, donorPassword) values ('" + donorIc + "','" + donorName + "','" + donorTelNum + "','" + donorLocation + "','" + donorUsername + "','" + donorPassword + "')";
    constantChar = insertQuery.c_str();
    qstate = mysql_query(conn, constantChar);

    if (qstate == 0)
    {
        cout << endl << "\nThe donor has been successfully registered, press any key to continue!" << endl;
        _getch();
        loginSelection();
    }
    else
    {
        cout << "Query Execution Problem! " << mysql_errno(conn) << " press any key to continue!" << endl;
        _getch();
        Registration();
    }
}

void FoodDonation::volunteerRegistration() {
    system("cls");
    string volunteerIc = "";
    string volunteerName = "";
    string volunteerTelNum = "";
    string volunteerLocation = "";
    string volunteerUsername = "";
    string volunteerPassword = "";

    cout << "Insert new Volunteer's information !" << endl << endl;
    cin.ignore(1, '\n');
    cout << "Enter Your IC: ";
    getline(cin, volunteerIc); //Get line from stream into string
    cout << "Enter Your Name: ";
    getline(cin, volunteerName);
    cout << "Enter Your Telephone Number: ";
    getline(cin, volunteerTelNum);
    cout << "Enter Your Location: ";
    getline(cin, volunteerLocation);
    cout << "Enter Your Username: ";
    getline(cin, volunteerUsername);
    cout << "Enter Your Password: ";
    getline(cin, volunteerPassword);

    insertQuery = "insert into volunteer (volunteerIc, volunteerName, volunteerTelNum, volunteerLocation, volunteerUsername, volunteerPassword) values ('" + volunteerIc + "','" + volunteerName + "','" + volunteerTelNum + "','" + volunteerLocation + "','" + volunteerUsername + "','" + volunteerPassword + "')";
    constantChar = insertQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        cout << "\nThe volunteer has been successfully registered, press any key to continue!\n";
        _getch();
        loginSelection();
    }
    else
    {
        cout << "Query Execution Problem! " << mysql_errno(conn) << " press any key to continue!" << endl;
        _getch();
        Registration();
    }
}

void FoodDonation::managerProfile() {

    system("cls");
    cout << "Welcome to Manager Profiles !" << endl;
    cout << "1. Create Event\n";
    cout << "2. Show All Event\n";
    cout << "3. Delete Event\n";
    cout << "4. Update Event\n";
    cout << "5. Create Food Bank\n";
    cout << "6. Show All Food Bank\n";
    cout << "7. Update Food Bank\n";
    cout << "8. Delete Food Bank\n";
    cout << "9. Show All Donation\n";
    cout << "10. Generate Report\n";
    cout << "11. Log Out\n";
    cout << "Your Choice:\t";
    cin >> choice;
    switch (choice)
    {
    case 1:
        createEvent();
        break;
    case 2:
        showEvent();
        break;
    case 3:
        deleteEvent();
        break;
    case 4:
        updateEvent();
        break;
    case 5:
        createFoodbank();
        break;
    case 6:
        showFoodbank();
        break;
    case 7:
        updateFoodbank();
        break;
    case 8:
        deleteFoodbank();
        break;
    case 9:
        showDonation();
        break;
    case 10:
        reportGeneration();
        break;
    case 11:
        loginSelection();
        break;
    default:
        cout << "You have enter wrong option, please try again.\t";
        _getch();       
        managerProfile();
        break;
    }        
}

void FoodDonation::donorProfile() {
    system("cls");
    cout << "Welcome to Donor Profiles !" << endl;
    cout << "1. Show All Foodbank\n";
    cout << "2. Show All Event\n";
    cout << "3. Show All Donation\n";
    cout << "4. Make A Donation\n";      
    cout << "5. Log Out\n";
    cout << "Your Choice:\t";
    cin >> choice;
    switch (choice)
    {
    case 1:
        showFoodbankClient();
        break;
    case 2:
        showEventClient();
        break;
    case 3:
        showDonationClient();        
        break;
    case 4:
        makeDonation();        
        break;
    case 5:
        loginSelection();
        break;        
    default:
        cout << "You have enter wrong option, please try again.\t";
        _getch();
        donorProfile();
        break;
    }
}

void FoodDonation::volunteerProfile() {
    system("cls");
    cout << "Welcome to Volunteer Profiles !" << endl;
    cout << "1. Show All Event\n";
    cout << "2. Join An Event\n";
    cout << "3. Show All Joined Event\n";
    cout << "4. Log Out\n";
    cout << "Your Choice:\t";
    cin >> choice;
    switch (choice)
    {
    case 1:
        showEventClient();
        break;
    case 2:
        joinEvent();
        break;
    case 3:
        showJoinedEvent();
        break;
    case 4:
        loginSelection();
        break;
    default:
        cout << "You have enter wrong option, please try again.\t";
        _getch();
        volunteerProfile();
        break;
    }
}

void FoodDonation::createEvent() {

    system("cls");
    string eventName = "";
    string eventLocation = "";
    string eventType = "";
    string eventDate = "";
    string eventTime = "";
    string managerIc = "";
    string foodbankId = "";
    string foodbankCurrentQuantity = "";
    string eventTargetQuantity = "";
    int foodbankQuantity, targetQuantity = 0;

    countQuery = "select count(*) from foodbank where foodbankStatus = 'available' and foodbankCurrentQuantity > 0;";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);        
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        if (stoi(row[0]) == 0) {
            cout << "No foodbank are available, press any key to back.\n";
            _getch();
            managerProfile();
        }
        else {

            cout << "Event Creation !\n";
            cin.ignore(1, '\n');
            cout << "Enter Event Name: ";
            getline(cin, eventName);
            cout << "Enter Event Location: ";
            getline(cin, eventLocation);
            cout << "Enter Event Type: ";
            getline(cin, eventType);
            cout << "Enter Event Date [YYYY-MM-DD]: ";
            getline(cin, eventDate);
            cout << "Enter Event Time [HH:MM:SS]: ";
            getline(cin, eventTime);
            cout << "\n";    
            
            qstate = mysql_query(conn, "select f.*, m.managerName from foodbank f join manager m where f.managerIc = m.managerIc and f.foodbankStatus = 'available' and f.foodbankCurrentQuantity > 0;");
            if (qstate == 0) {
                cout << "All Foodbank:\n";
                cout << "=============\n";
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Foodbank ID: " << row[0] << "\nFoodbak Name: " << row[1] << "\nFoodbank Capacity: " << row[2] << "\nFoodbank Location: " << row[3] << "\nFoodbank Current Capacity: " << row[4] << "\nFoodbank Status: " << row[5] << "\nHandled By: " << row[7] << "(" << row[6] << ")" << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

            do {
                cout << "Enter Foodbank Id: ";
                getline(cin, foodbankId);

                countQuery = "select count(*) from foodbank where foodbankId = '" + foodbankId + "' and foodbankStatus = 'available' and foodbankCurrentQuantity > 0";
                constantChar = countQuery.c_str();
                qstate = mysql_query(conn, constantChar);
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (qstate == 0)
                {
                    if (stoi(row[0]) == 0)
                        cout << "Foodbank Id does not exist.\n";
                }
                else
                {
                    cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                    _getch();
                    managerProfile();
                }
            } while (stoi(row[0]) == 0);

            do {
                cout << "Enter Event Target Quantity: ";
                getline(cin, eventTargetQuantity);

                selectQuery = "select foodbankCurrentQuantity from foodbank where foodbankId = '" + foodbankId + "'";
                constantChar = selectQuery.c_str();
                qstate = mysql_query(conn, constantChar);                
                if (qstate == 0)
                {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    foodbankCurrentQuantity = row[0];
                    foodbankQuantity = stoi(foodbankCurrentQuantity);
                    targetQuantity = stoi(eventTargetQuantity);
                    if (foodbankQuantity < targetQuantity)
                        cout << "Selected foodbank Current Quantity (" << foodbankCurrentQuantity << ") is not sufficient to support the event target quantity\n ";
                    else
                        cout << "foodbank Current Quantity is sufficient to support the event\n ";
                }
                else
                {
                    cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                    _getch();
                    managerProfile();
                }
            } while (foodbankQuantity < targetQuantity);


            selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    managerIc = row[0];
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }


            insertQuery = "insert into events (managerIc, foodbankId, eventName, eventLocation, eventType, eventTargetQuantity, eventDate, eventTime) values ('" + managerIc + "','" + foodbankId + "','" + eventName + "','" + eventLocation + "','" + eventType + "','" + eventTargetQuantity + "','" + eventDate + "','" + eventTime + "')";
            constantChar = insertQuery.c_str();
            qstate = mysql_query(conn, constantChar); 
            if (qstate == 0)
            {
                cout << endl << "The event was successfully created";
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

            cout << "Press 'A' to create another event Or Any Other key to exit: ";
            cin >> choose;
            if (choose == 'a' || choose == 'A')
            {
                createEvent();
            }
            else
            {
                managerProfile();
            }                   
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }
    mysql_free_result(res);
}

void FoodDonation::showEvent() {

    system("cls");
    countQuery = "select count(*) from events";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No Event are available, Press any key to return Main Menu \t";
            _getch();
            if (profileIdentifier == "manager") {
                managerProfile();
            }
            else if (profileIdentifier == "donor") {
                donorProfile();
            }
            else if (profileIdentifier == "volunteer") {
                volunteerProfile();
            }
        }
        else {
            cout << "All Event:\n";
            cout << "==========\n";
            qstate = mysql_query(conn, "select e.*, m.managerName from events e join manager m on e.managerIc = m.managerIc order by eventId; ");
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Event ID: " << row[0] << "\nCreated By: " << row[10] << "(" << row[1] << ")" << "\nFoodbank Source: " << row[2] << "\nEvent Name: " << row[3] << "\nEvent Location: " << row[4] << "\nEvent Type: " << row[5] << "\nEvent Target Quantity: " << row[6] << "\nEvent Date: " << row[7] << "\nEvent Time: " << row[8] << "\nEvent Status: " << row[9] << endl << endl;
                    cout << "=====================================\n";
                }                
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                if (profileIdentifier == "manager") {
                    managerProfile();
                }
                else if (profileIdentifier == "donor") {
                    donorProfile();
                }
                else if (profileIdentifier == "volunteer") {
                    volunteerProfile();
                }
            }
        }
        cout << "Press any key to continue.\t";
        _getch();
        if (profileIdentifier == "manager") {
            managerProfile();
        }
        else if (profileIdentifier == "donor") {
            donorProfile();
        }
        else if (profileIdentifier == "volunteer") {
            volunteerProfile();
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }        
}

void FoodDonation::showEventClient() {

    system("cls");
    countQuery = "select count(*) from events where eventStatus = 'available'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No Event are available, Press any key to return Main Menu \t";
            _getch();
            if (profileIdentifier == "manager") {
                managerProfile();
            }
            else if (profileIdentifier == "donor") {
                donorProfile();
            }
            else if (profileIdentifier == "volunteer") {
                volunteerProfile();
            }
        }
        else {
            
            qstate = mysql_query(conn, "select e.*, m.managerName from events e join manager m on e.managerIc = m.managerIc where eventStatus = 'available' order by eventId; ");
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                cout << "All Event:\n";
                cout << "==========\n";
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Event ID: " << row[0] << "\nCreated By: " << row[10] << "(" << row[1] << ")" << "\nFoodbank Source: " << row[2] << "\nEvent Name: " << row[3] << "\nEvent Location: " << row[4] << "\nEvent Type: " << row[5] << "\nEvent Target Quantity: " << row[6] << "\nEvent Date: " << row[7] << "\nEvent Time: " << row[8] << "\nEvent Status: " << row[9] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                if (profileIdentifier == "manager") {
                    managerProfile();
                }
                else if (profileIdentifier == "donor") {
                    donorProfile();
                }
                else if (profileIdentifier == "volunteer") {
                    volunteerProfile();
                }
            }
        }
        cout << "Press any key to continue.\t";
        _getch();
        if (profileIdentifier == "manager") {
            managerProfile();
        }
        else if (profileIdentifier == "donor") {
            donorProfile();
        }
        else if (profileIdentifier == "volunteer") {
            volunteerProfile();
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }
}

void FoodDonation::deleteEvent() {

    system("cls");    
    string eventid;
    string managerIc = "";
    string status = "deleted";    

    selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            managerIc = row[0];
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

    countQuery = "select count(*) from events where eventStatus = 'AVAILABLE' and managerIc = '" + managerIc + "'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No Event are available, Press any key to return Main Menu \t";
            _getch();
            managerProfile();
        }
        else {            

            selectQuery = "select * from events where eventStatus = 'available' and managerIc = '" + managerIc + "'";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Event ID: " << row[0] << "\nCreated By: " << row[1] << "\nFoodbank Source: " << row[2] << "\nEvent Name: " << row[3] << "\nEvent Location: " << row[4] << "\nEvent Type: " << row[5] << "\nEvent Target Quantity: " << row[6] << "\nEvent Date: " << row[7] << "\nEvent Time: " << row[8] << "\nEvent Status: " << row[9] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

            cout << "Choose Event ID to be delete: ";
            cin >> eventid;

            countQuery = "select count(*) from events where eventId = '" + eventid + "' and eventStatus = 'available' and managerIc = '" + managerIc + "'";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);    
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) != 0) {
                    
                    updateQuery = "update events set eventStatus = '" + status + "' where eventId = " + eventid;
                    constantChar = updateQuery.c_str();
                    qstate = mysql_query(conn, constantChar);
                    if (qstate == 0)
                    {
                        cout << "The event was successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        managerProfile();
                    }

                    cout << "Press 'd' to delete another event or any other key to Exit: ";
                    cin >> choose;
                    if (choose == 'd' || choose == 'D')
                    {
                        deleteEvent();
                    }
                    else
                    {
                        managerProfile();
                    }

                }
                else {
                    cout << "Event's ID does not exist, press any key to back"<< endl;
                    _getch();
                    deleteEvent();
                }
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }               
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }
    

    
}

void FoodDonation::updateEvent() {

    system("cls");
    string eventid = "";
    string managerIc = "";

    selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            managerIc = row[0];
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

    countQuery = "select count(*) from events where eventStatus = 'AVAILABLE' and managerIc = '" + managerIc + "'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No Event are available, Press any key to return Main Menu ";
            _getch();
            managerProfile();
        }
        else {
            selectQuery = "select * from events where eventStatus = 'available' and managerIc = '" + managerIc + "'";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Event ID: " << row[0] << "\nCreated By: " << row[1] << "\nFoodbank Source: " << row[2] << "\nEvent Name: " << row[3] << "\nEvent Location: " << row[4] << "\nEvent Type: " << row[5] << "\nEvent Target Quantity: " << row[6] << "\nEvent Date: " << row[7] << "\nEvent Time: " << row[8] << "\nEvent Status: " << row[9] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

            cout << "Choose Event ID to be update: ";
            cin >> eventid;

            countQuery = "select count(*) from events where eventId = '" + eventid + "' and eventStatus = 'AVAILABLE'";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);       
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) != 0) {

                    string eventName = "";
                    string eventLocation = "";
                    string eventType = "";
                    string eventDate = "";
                    string eventTime = "";

                    cout << "Event Update !\n";
                    cin.ignore(1, '\n');
                    cout << "Enter New Event Name: ";
                    getline(cin, eventName); 
                    cout << "Enter New Event Location: ";
                    getline(cin, eventLocation);
                    cout << "Enter New Event Type: ";
                    getline(cin, eventType);
                    cout << "Enter New Event Date [YYYY-MM-DD]: ";
                    getline(cin, eventDate);
                    cout << "Enter New Event Time [HH:MM:SS]: ";
                    getline(cin, eventTime);
                    
                    updateQuery = "update events set eventName = '" + eventName + "', eventLocation = '"+ eventLocation +"', eventType = '"+ eventType +"', eventDate = '"+ eventDate +"', eventTime = '"+ eventTime +"' where eventid = '" + eventid + "'";
                    constantChar = updateQuery.c_str();
                    qstate = mysql_query(conn, constantChar);
                    if (qstate == 0)
                    {
                        cout << "The event was successfully updated" << endl;
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        managerProfile();
                    }
                    cout << "Press 'U' to update another event or any other key to Exit: ";
                    cin >> choose;
                    if (choose == 'u' || choose == 'U')
                    {
                        updateEvent();
                    }
                    else
                    {
                        managerProfile();
                    }
                }
                else {
                    cout << "Event's ID does not exist, press any key to back" << endl;
                    _getch();
                    updateEvent();
                }
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }
    
}

void FoodDonation::createFoodbank() {

    // create event
    system("cls");
    string foodbankName = "";
    string foodbankCapacity = "";    
    string foodbankLocation = "";
    string foodbankCurrentQuantity = "";
    string managerIc = "";

    cout << "FoodBank Creation !\n";
    cin.ignore(1, '\n');
    cout << "Enter FoodBank Name: ";
    getline(cin, foodbankName); 
    cout << "Enter FoodBank Capacity: ";
    getline(cin, foodbankCapacity);
    cout << "Enter FoodBank Location: ";
    getline(cin, foodbankLocation);
    cout << "Enter FoodBank Current Quantity: ";
    getline(cin, foodbankCurrentQuantity);


    selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            managerIc = row[0];
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

    insertQuery = "insert into foodbank (foodbankName,foodbankCapacity,foodbankLocation,foodbankCurrentQuantity,managerIc) values ('" + foodbankName + "','" + foodbankCapacity + "','" + foodbankLocation + "','" + foodbankCurrentQuantity + "','" + managerIc + "')";
    constantChar = insertQuery.c_str(); 
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        cout << endl << "The foodbank was successfully created" << endl;
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

    cout << "Press 'C' to create another foodbank Or Any Other key to exit: ";
    cin >> choose;        
    if (choose == 'c' || choose == 'C')
    {
        createFoodbank();
    }
    else
    {
        managerProfile();
    }
}

void FoodDonation::updateFoodbank() {
    system("cls");
    string fbid, managerIc;
    char choose;

    selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            managerIc = row[0];
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

    countQuery = "select count(*) from foodbank where foodbankStatus = 'AVAILABLE' and managerIc = '" + managerIc + "'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        
        if (stoi(row[0]) == 0) {
            cout << "No foodbank are available, Press any key to return Main Menu ";
            _getch();
            managerProfile();
        }
        else {
            selectQuery = "select * from foodbank where foodbankStatus = 'available' and managerIc = '" + managerIc + "'";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);            
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Foodbank ID: " << row[0] << "\nFoodbak Name: " << row[1] << "\nFoodbank Capacity: " << row[2] << "\nFoodbank Location: " << row[3] << "\nFoodbank Current Capacity: " << row[4] << "\nFoodbank Status: " << row[5] << "\nHandled By: " << row[6] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

            cout << "Choose Foodbank ID to be update:\t";
            cin >> fbid;

            countQuery = "select count(*) from foodbank where foodbankId = '" + fbid + "' and foodbankStatus = 'AVAILABLE' and managerIc = '" + managerIc + "'";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);                        
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) != 0) {

                    string foodbankName = "";
                    string foodbankCapacity = "";
                    string foodbankLocation = "";
                    string foodbankCurrentQuantity = "";

                    cout << "FoodBank Update !\n";
                    cin.ignore(1, '\n');
                    cout << "Enter FoodBank Name: ";
                    getline(cin, foodbankName);
                    cout << "Enter FoodBank Capacity: ";
                    getline(cin, foodbankCapacity);
                    cout << "Enter FoodBank Location: ";
                    getline(cin, foodbankLocation);
                    cout << "Enter FoodBank Current Quantity: ";
                    getline(cin, foodbankCurrentQuantity);

                    updateQuery = "update foodbank set foodbankName = '" + foodbankName + "', foodbankCapacity = '" + foodbankCapacity + "', foodbankLocation = '" + foodbankLocation + "' , foodbankCurrentQuantity = '" + foodbankCurrentQuantity + "' where foodbankId = '" + fbid + "'";
                    constantChar = updateQuery.c_str();
                    qstate = mysql_query(conn, constantChar);
                    if (qstate == 0)
                    {
                        cout << "The foodbank was successfully updated" << endl;
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        managerProfile();
                    }
                    cout << "Press 'U' to update another foodbank and any other key to Exit: ";
                    cin >> choose;
                    if (choose == 'u' || choose == 'u')
                    {
                        updateFoodbank();
                    }
                    else
                    {
                        managerProfile();
                    }
                }
                else {
                    cout << "Foodbank's ID does not exist, press any key to back" << endl;
                    _getch();
                    updateFoodbank();
                }
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

}

void FoodDonation::deleteFoodbank() {
    system("cls");
    string fbid, managerIc;
    char choose;

    selectQuery = "select * from manager where managerUsername = '" + getUsername() + "' and managerPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            managerIc = row[0];
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

    countQuery = "select count(*) from foodbank where foodbankStatus = 'AVAILABLE' and managerIc = '" + managerIc + "'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);        
        if (stoi(row[0]) == 0) {
            cout << "No foodbank are available, Press any key to return Main Menu ";
            _getch();
            managerProfile();
        }
        else {
            countQuery = "select * from foodbank where foodbankStatus = 'available' and managerIc = '" + managerIc + "'";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Foodbank ID: " << row[0] << "\nFoodbak Name: " << row[1] << "\nFoodbank Capacity: " << row[2] << "\nFoodbank Location: " << row[3] << "\nFoodbank Current Capacity: " << row[4] << "\nFoodbank Status: " << row[5] << "\nHandled By: " << row[6] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

            cout << "Choose Foodbank ID to be delete:\t";
            cin >> fbid;

            countQuery = "select count(*) from foodbank where foodbankId = '" + fbid + "' and foodbankStatus = 'AVAILABLE'";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);                        
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) != 0) {

                    updateQuery = "update foodbank set foodbankStatus = 'deleted' where foodbankId = " + fbid;
                    constantChar = updateQuery.c_str();
                    qstate = mysql_query(conn, constantChar);
                    if (qstate == 0)
                    {
                        cout << "The foodbank was successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        managerProfile();
                    }

                   
                    cout << "Press 'D' to delete another foodbank and any other key to Exit: ";
                    cin >> choose;
                    if (choose == 'd' || choose == 'D')
                    {
                        deleteFoodbank();
                    }
                    else
                    {
                        managerProfile();
                    }
                }
                else {
                    cout << "Foodbank's ID does not exist, press any key to back" << endl;
                    _getch();
                    deleteFoodbank();
                }
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }

        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        managerProfile();
    }

}

void FoodDonation::showFoodbank() {

    system("cls");
    countQuery = "select count(*) from foodbank";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);        
        if (stoi(row[0]) == 0) {
            cout << "No foodbank are created yet, press any key to continue\n";
            _getch();
            if (profileIdentifier == "manager") {
                managerProfile();
            }
            else if (profileIdentifier == "donor") {
                donorProfile();
            }
            else if (profileIdentifier == "volunteer") {
                volunteerProfile();
            }
        }
        else {

            countQuery = "select count(*) from foodbank where foodbankStatus = 'available';";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);                
                if (stoi(row[0]) == 0) {
                    cout << "There is no available foodbank, press any key to continue\n";
                    _getch();
                    if (profileIdentifier == "manager") {
                        managerProfile();
                    }
                    else if (profileIdentifier == "donor") {
                        donorProfile();
                    }
                    else if (profileIdentifier == "volunteer") {
                        volunteerProfile();
                    }
                }
                else {
                    //char choose;
                    cout << "All Foodbank:\n";
                    cout << "==========\n";
                    cout << endl;
                    qstate = mysql_query(conn, "select f.*, m.managerName from foodbank f join manager m where f.managerIc = m.managerIc order by f.foodbankId;");
                    if (qstate == 0)
                    {
                        res = mysql_store_result(conn);
                        while ((row = mysql_fetch_row(res)))
                        {
                            cout << "Foodbank ID: " << row[0] << "\nFoodbak Name: " << row[1] << "\nFoodbank Capacity: " << row[2] << "\nFoodbank Location: " << row[3] << "\nFoodbank Current Capacity: " << row[4] << "\nFoodbank Status: " << row[5] << "\nHandled By: " << row[7] << "(" << row[6] << ")" << endl << endl;
                            cout << "=====================================\n";
                        }
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        if (profileIdentifier == "manager") {
                            managerProfile();
                        }
                        else if (profileIdentifier == "donor") {
                            donorProfile();
                        }
                        else if (profileIdentifier == "volunteer") {
                            volunteerProfile();
                        }
                    }

                    cout << "Press any other key to Exit: ";
                    _getch();
                    if (profileIdentifier == "manager") {
                       managerProfile();
                    }
                    else if (profileIdentifier == "donor") {
                       donorProfile();
                    }
                    else if (profileIdentifier == "volunteer") {
                       volunteerProfile();
                    }
                }
            }            
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        if (profileIdentifier == "manager") {
            managerProfile();
        }
        else if (profileIdentifier == "donor") {
            donorProfile();
        }
        else if (profileIdentifier == "volunteer") {
            volunteerProfile();
        }
    }
    
}

void FoodDonation::showFoodbankClient() {

    system("cls");
    countQuery = "select count(*) from foodbank where foodbankStatus = 'available'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No foodbank are available yet, press any key to continue\n";
            _getch();
            if (profileIdentifier == "manager") {
                managerProfile();
            }
            else if (profileIdentifier == "donor") {
                donorProfile();
            }
            else if (profileIdentifier == "volunteer") {
                volunteerProfile();
            }
        }
        else {            
            qstate = mysql_query(conn, "select f.foodbankId,f.foodbankName,f.foodbankCapacity,f.foodbankLocation,f.foodbankCurrentQuantity,f.foodbankStatus,m.managerName,m.managerIc from foodbank f join manager m on f.managerIc = m.managerIc where foodbankStatus = 'available'");            
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                cout << "All Foodbank:\n";
                cout << "==========\n";
                cout << endl;
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Foodbank ID: " << row[0] << "\nFoodbak Name: " << row[1] << "\nFoodbank Capacity: " << row[2] << "\nFoodbank Location: " << row[3] << "\nFoodbank Current Capacity: " << row[4] << "\nFoodbank Status: " << row[5] << "\nHandled By: " << row[6] << "("<< row[7] << ")" << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                if (profileIdentifier == "manager") {
                    managerProfile();
                }
                else if (profileIdentifier == "donor") {
                    donorProfile();
                }
                else if (profileIdentifier == "volunteer") {
                    volunteerProfile();
                }
            }

            cout << "Press any other key to Exit: ";
            _getch();
            if (profileIdentifier == "manager") {
                managerProfile();
            }
            else if (profileIdentifier == "donor") {
                donorProfile();
            }
            else if (profileIdentifier == "volunteer") {
                volunteerProfile();
            }
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        if (profileIdentifier == "manager") {
            managerProfile();
        }
        else if (profileIdentifier == "donor") {
            donorProfile();
        }
        else if (profileIdentifier == "volunteer") {
            volunteerProfile();
        }
    }
}

void FoodDonation::makeDonation() {

    // create event
    system("cls");
    string foodbankId = "";
    string donationType = "";
    string donationQuantity = "";
    string donorIc = "";
    string availablequantity;
    int myint1, myint2;


    countQuery = "select count(*) from foodbank";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);        
        if (stoi(row[0]) == 0) {
            cout << "No foodbank are created yet, press any key to back.\n";
            _getch();
           donorProfile();
        }
        else {
            countQuery = "select count(*) from foodbank where foodbankStatus = 'available';";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) == 0) {
                    cout << "There is no available foodbank, press any key to back.\n";
                    _getch();
                    donorProfile();
                }
                else {
                    cout << "All Foodbank:\n";
                    cout << "=============\n";
                    cout << endl;
                    qstate = mysql_query(conn, "select * from foodbank where foodbankStatus = 'available';");
                    if (qstate == 0)
                    {
                        res = mysql_store_result(conn);
                        while ((row = mysql_fetch_row(res)))
                        {
                            cout << "Foodbank ID: " << row[0] << "\nFoodbak Name: " << row[1] << "\nFoodbank Capacity: " << row[2] << "\nFoodbank Location: " << row[3] << "\nFoodbank Current Capacity: " << row[4] << "\nFoodbank Status: " << row[5] << "\nHandled By: " << row[6] << endl << endl;
                            cout << "=====================================\n";
                        }
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        donorProfile();
                    }

                    cout << "Insert which FoodBank Id to donate:\t";
                    cin >> foodbankId;

                    countQuery = "select count(*) from foodbank where foodbankId = '" + foodbankId + "' and foodbankStatus = 'AVAILABLE'";
                    constantChar = countQuery.c_str();
                    qstate = mysql_query(conn, constantChar);
                    if (qstate == 0) {
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);
                        if (stoi(row[0]) != 0) {

                            selectQuery = "select foodbankCapacity - foodbankCurrentQuantity from foodbank where foodbankId = '" + foodbankId + "'";
                            constantChar = selectQuery.c_str();
                            qstate = mysql_query(conn, constantChar);
                            if (qstate == 0)
                            {
                                res = mysql_store_result(conn);
                                while ((row = mysql_fetch_row(res)))
                                {
                                    availablequantity = row[0];
                                }
                            }
                            else
                            {
                                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                                _getch();
                                donorProfile();
                            }
                            cout << "Maximum quantity item that you are able to donate is:\t" << availablequantity << "\n";
                            cout << "State your donation type:\t";
                            cin >> donationType;

                            myint1 = stoi(availablequantity);   //convert string to int                                 

                            do
                            {
                                cout << "state your donation quantity:\t";
                                cin >> donationQuantity;
                                myint2 = stoi(donationQuantity);
                            } while (myint2 > myint1);

                            selectQuery = "select * from donor where donorUsername = '" + getUsername() + "' and donorPassword = '" + getPassword() + "'";
                            constantChar = selectQuery.c_str();
                            qstate = mysql_query(conn, constantChar);
                            if (qstate == 0)
                            {
                                res = mysql_store_result(conn);
                                while ((row = mysql_fetch_row(res)))
                                {
                                    donorIc = row[0];
                                }
                            }
                            else
                            {
                                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                                _getch();
                                donorProfile();
                            }

                            insertQuery = "insert into donation (donorIc,foodbankId,donationDate,donationType,donationQuantity) values ('" + donorIc + "','" + foodbankId + "', Now() ,'" + donationType + "','" + donationQuantity + "')";
                            constantChar = insertQuery.c_str();
                            qstate = mysql_query(conn, constantChar);
                            if (qstate == 0)
                            {
                                cout << "\ndonations has been made successfully.\n";
                            }
                            else
                            {
                                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                                _getch();
                                donorProfile();
                            }

                            cout << "Press 'D' to Donate Again Or Any Other key to back: ";
                            cin >> choose;
                            if (choose == 'd' || choose == 'D')
                            {
                                makeDonation();
                            }
                            else
                            {
                                donorProfile();
                            }
                        }
                        else {
                            cout << "Foodbank's ID does not exist, press any key to back" << endl;
                            _getch();
                            makeDonation();
                        }
                    }
                    else {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        donorProfile();
                    }
                }
            }
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();        
        donorProfile();
    }
}
 
void FoodDonation::showDonation() {

    countQuery = "select count(*) from donation d join donor dd join foodbank f on d.donorIc = dd.donorIc and d.foodbankId = f.foodbankId";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No donation has been made, press any key to back.\n";
            _getch();
            managerProfile();
        }
        else 
        {
            cout << "All Donation:\n";
            cout << "=============\n";
            cout << endl;
            qstate = mysql_query(conn, "select dd.donorName,dd.donorIc,d.foodbankId,d.donationDate,d.donationType,d.donationQuantity from donation d join donor dd join foodbank f on d.donorIc = dd.donorIc and d.foodbankId = f.foodbankId");
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Donor Name: " << row[0] << "("<< row[1] <<")"<<"\nFoodbank ID: " << row[2] << "\nDonation Date: " << row[3] << "\nDonation Type: " << row[4] << "\nDonation QUantity: " << row[5] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();                
                managerProfile();
            }
            cout << "Press any other key to Exit: ";
            _getch();
            managerProfile();
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        donorProfile();
    }
}

void FoodDonation::showDonationClient() {

    system("cls");
    string donorIc;
    selectQuery = "select * from donor where donorUsername = '" + getUsername() + "' and donorPassword = '" + getPassword() + "'";
    constantChar = selectQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            donorIc = row[0];
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        donorProfile();
    }

    countQuery = "select count(*) from donation where donorIc = '" + donorIc + "'";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);        
        if (stoi(row[0]) == 0) {
            cout << "No donation has been made, press any key to back.\n";
            _getch();
            donorProfile();
        }
        else {
            cout << "All Donation:\n";
            cout << "=============\n";
            cout << endl;
            selectQuery = "select * from donation where donorIc = '" + donorIc + "'";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Donor Ic: " << row[0] << "\nFoodbank ID: " << row[1] << "\nDonation Date: " << row[2] << "\nDonation Type: " << row[3] << "\nDonation QUantity: " << row[4] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                if (profileIdentifier == "manager") {
                    managerProfile();
                }
                else if (profileIdentifier == "donor") {
                    donorProfile();
                }
                else if (profileIdentifier == "volunteer") {
                    volunteerProfile();
                }
            }
            cout << "Press any other key to Exit: ";
            _getch();
            if (profileIdentifier == "manager") {
                managerProfile();
            }
            else if (profileIdentifier == "donor") {
               donorProfile();
            }
            else if (profileIdentifier == "volunteer") {
               volunteerProfile();
            }
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
       donorProfile();
    }
}

void FoodDonation::joinEvent() {
    system("cls");
    string eventid, volunteerIc, eventid2;    

    countQuery = "select count(*) from events where eventStatus = 'AVAILABLE';";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No Event are available, Press any key to return Main Menu \t";
            _getch();
            volunteerProfile();
        }
        else {
            qstate = mysql_query(conn, "select * from events where eventStatus = 'available'");
            if (qstate == 0)
            {                
                res = mysql_store_result(conn);
                cout << "All Event:\n";
                cout << "==========\n";
                cout << endl;
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Event ID: " << row[0] << "\nCreated By: " << row[1] << "\nFoodbank Source: " << row[2] << "\nEvent Name: " << row[3] << "\nEvent Location: " << row[4] << "\nEvent Type: " << row[5] << "\nEvent Target Quantity: " << row[6] << "\nEvent Date: " << row[7] << "\nEvent Time: " << row[8] << "\nEvent Status: " << row[9] << endl << endl;
                    cout << "=====================================\n";
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                volunteerProfile();
            }

            cout << "Choose which Event's Id do you want to contribute:\t";
            cin >> eventid;

            countQuery = "select count(*) from events where eventId = '" + eventid + "' and eventStatus = 'AVAILABLE'";
            constantChar = countQuery.c_str();
            qstate = mysql_query(conn, constantChar);            
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) != 0) {

                    selectQuery = "select * from volunteer where volunteerUsername = '" + getUsername() + "' and volunteerPassword = '" + getPassword() + "'";
                    constantChar = selectQuery.c_str();
                    qstate = mysql_query(conn, constantChar);
                    if (qstate == 0)
                    {
                        res = mysql_store_result(conn);
                        while ((row = mysql_fetch_row(res)))
                        {
                            volunteerIc = row[0];
                        }
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        volunteerProfile();
                    }

                    selectQuery = "select count(*) from distribution where eventId = '" + eventid + "' and volunteerIc = '" + volunteerIc + "'";
                    constantChar = selectQuery.c_str();
                    qstate = mysql_query(conn, constantChar);                    
                    if (qstate == 0)
                    {
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);
                        if (stoi(row[0]) != 0)
                        {
                            cout << "You have already registered for the Events\n";
                        }
                        else
                        {
                            insertQuery = "insert into distribution (eventId,volunteerIc) values ('" + eventid + "','" + volunteerIc + "')";
                            constantChar = insertQuery.c_str();
                            qstate = mysql_query(conn, constantChar);
                            if (qstate == 0)
                            {
                                cout << "Event participation have been saved successfully\n";
                            }
                            else
                            {
                                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                                _getch();
                                volunteerProfile();
                            }
                        }
                    }
                    else
                    {
                        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                        _getch();
                        volunteerProfile();
                    }



                    cout << "Press 'A' to participate another event or any other key to Exit: ";
                    cin >> choose;                    
                    if (choose == 'a' || choose == 'A')
                    {
                        joinEvent();
                    }
                    else
                    {
                        volunteerProfile();
                    }
                }
                else {
                    cout << "Event's ID does not exist, press any key to back" << endl;
                    _getch();
                    joinEvent();
                }
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                volunteerProfile();
            }
        }
    }
    else
    {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        donorProfile();
    }
}

void FoodDonation::showJoinedEvent() {
    system("cls");

    string volunteerIc;

    countQuery = "select count(*) from distribution;";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);    
    if (qstate == 0)
    {        
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No event's registration record, press any key to return Main Menu \t";
            _getch();
            volunteerProfile();
        }
        else {
            selectQuery = "select volunteerIc from volunteer where volunteerUsername = '" + getUsername() + "' and volunteerPassword = '" + getPassword() + "';";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);            
            if (qstate == 0) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                volunteerIc = row[0];
            }
            else {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                volunteerProfile();
            }

            selectQuery = "select d.eventId,d.volunteerIc,e.eventName,e.eventLocation,e.eventType,e.eventDate,e.eventTime,e.eventStatus,e.managerIc,m.managerName from distribution d join events e join manager m on d.eventId = e.eventId and e.managerIc = m.managerIc where volunteerIc = '" + volunteerIc + "' order by eventId";
            constantChar = selectQuery.c_str();
            qstate = mysql_query(conn, constantChar);
            if (qstate == 0)
            {
                cout << "All Joined Events:\n";
                cout << "==================\n";
                cout << endl;
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "Event ID: " << row[0] << "\nVolunteer Ic: " << row[1] << "\nEvent Name: " << row[2] << "\nEvent Location: " << row[3] << "\nEvent Type: " << row[4] << "\nEvent Date: " << row[5] << "\nEvent Time: " << row[6] << "\nEvent Status: " << row[7] << "\nManager Ic: " << row[8] << "\nManager Name: " << row[9] << endl << endl;
                }
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                volunteerProfile();
            }
            cout << "Press any other key to Exit: ";
            _getch();
            volunteerProfile();
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        volunteerProfile();
     }
}

//verification and validation is until here 1/5/2020 4:38 PM

int FoodDonation::reportGeneration() {

    ofstream outData;
    countQuery = "select count(*) from donation d join donor dd join foodbank f on d.donorIc = dd.donorIc and d.foodbankId = f.foodbankId";
    constantChar = countQuery.c_str();
    qstate = mysql_query(conn, constantChar);
    if (qstate == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (stoi(row[0]) == 0) {
            cout << "No donation has been made, press any key to back.\n";
            _getch();
            managerProfile();
        }
        else
        {
            qstate = mysql_query(conn, "select dd.donorName,dd.donorIc,d.foodbankId,f.foodbankName,d.donationDate,d.donationType,d.donationQuantity from donation d join donor dd join foodbank f on d.donorIc = dd.donorIc and d.foodbankId = f.foodbankId");
            if (qstate == 0)
            {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                outData.open("C:/Users/akmal/Desktop/Report1.txt", ios::app);
                outData << "Donor Name" << "," << "Donor Ic" << "," << "Foodbank Id" << "," << "Foodbank Name" << "," << "Donation Date" << "," << "Donation Type" << "," << "Donation Quantity" << endl;
                while ((row = mysql_fetch_row(res)))
                {                 
                    outData << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << "," << row[6] << endl;
                }                         
            }
            else
            {
                cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
                _getch();
                managerProfile();
            }
            cout << "Report Generation has been made.";      
            _getch();
            managerProfile();
            return 0;
        }
    }
    else {
        cout << "Query Execution Problem! [" << mysql_errno(conn) << "], press any key to continue.\t";
        _getch();
        donorProfile();
    }
}