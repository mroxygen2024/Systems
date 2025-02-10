#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/*THIS PROJECT CODE IMPLEMENTS A HOTEL MANAGEMENT SYSTEM THAT ALLOWS USERS TO PERFORM SEVERAL OPERATIONS.
YOU CAN ADD NEW RESERVATIONS TO A FILE, REMOVE EXISTING RESERVATIONS BY ROOM NUMBER, CHECK-IN GUESTS TO AVAILABLE ROOMS,
CHECK-OUT GUESTS AND DELETE THEIR RESERVATIONS, AND DISPLAY THE CURRENT AVAILABILITY OF ROOMS ALONG WITH GUEST DETAILS.
USERS INTERACT THROUGH A MENU SYSTEM WHERE THEY SELECT OPERATIONS USING NUMERICAL OPTIONS. THE SYSTEM READS AND WRITES
RESERVATION DATA TO A BINARY FILE NAMED "reservations.txt".



WE USED BINARY FILES SINCE BINARY FILES STORE DATA IN A RAW FORMAT, RETAINING THE EXACT STRUCTURE OF THE Reservation STRUCT,
INCLUDING ALL DATA MEMBERS WITHOUT ANY CONVERSIONS OR EXTRA FORMATTING.

NAME OF STUDENTS             GROUP                        ID NUMBER

NATNAEL TESHOME                21                         UGR/35146/16
ABEL DEME                      21                         UGR/33799/16
MIKIAS GURMESA                 21                         UGR/34964/16
EZEDIN MOHAMMED                22                         UGR/34389/16
IBISA LETA                     21                         UGR/34651/16

*/

const char *FILENAME = "reservations.txt";
const int MAX_ROOMS = 100;

// STRUCTURE TO HOLD RESERVATION INFORMATION
struct Reservation
{
    int roomNumber;
    char guestName[50];
    char checkInDate[20];
    char checkOutDate[20];
};

// FUNCTION PROTOTYPES
void addReservation();
void removeReservation();
void checkIn();
void checkOut();
void displayRoomAvailability();

// MAIN FUNCTION
int main()
{

    cout << left << setw(30) << "NAME OF STUDENTS"
         << left << setw(20) << "GROUP"
         << left << setw(20) << "ID NUMBER" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    cout << left << setw(30) << "NATNAEL TESHOME"
         << left << setw(20) << "21"
         << left << setw(20) << "UGR/35146/16" << endl;

    cout << left << setw(30) << "ABEL DEME"
         << left << setw(20) << "21"
         << left << setw(20) << "UGR/33799/16" << endl;

    cout << left << setw(30) << "MIKIAS GURMESA"
         << left << setw(20) << "21"
         << left << setw(20) << "UGR/34964/16" << endl;

    cout << left << setw(30) << "EZEDIN MOHAMMMED"
         << left << setw(20) << "22"
         << left << setw(20) << "UGR/34389/16" << endl;

    cout << left << setw(30) << "IBISA LETA"
         << left << setw(20) << "21"
         << left << setw(20) << "UGR/34651/16" << endl
         << endl
         << endl;

    int choice;

    do
    {
        cout << "Hotel Management System\n";
        cout << "1. Add Reservation\n";
        cout << "2. Remove Reservation\n";
        cout << "3. Check-In\n";
        cout << "4. Check-Out\n";
        cout << "5. Display Room Availability\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addReservation();
            break;
        case 2:
            removeReservation();
            break;
        case 3:
            checkIn();
            break;
        case 4:
            checkOut();
            break;
        case 5:
            displayRoomAvailability();
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 6.\n";
            break;
        }

    } while (choice != 6);

    return 0;
}

// ************************************************
// FUNCTION TO ADD A RESERVATION
// ************************************************

void addReservation()
{
    Reservation res;
    ofstream file(FILENAME, ios::app | ios::binary);

    // INPUT RESERVATION DETAILS
    cout << "Enter Room Number: ";
    cin >> res.roomNumber;
    cin.ignore();

    cout << "Enter Guest Name: ";
    cin.getline(res.guestName, 50);

    cout << "Enter Check-In Date (DD/MM/YYYY): ";
    cin.getline(res.checkInDate, 20);

    cout << "Enter Check-Out Date (DD/MM/YYYY): ";
    cin.getline(res.checkOutDate, 20);

    // WRITE RESERVATION TO FILE
    file.write((char *)&res, sizeof(res));
    file.close();

    // CONFIRMATION MESSAGE
    cout << "Reservation added successfully.\n";
}

// ************************************************
// FUNCTION TO REMOVE A RESERVATION
// ************************************************

void removeReservation()
{
    int roomNum;
    bool found = false;
    ifstream inFile(FILENAME, ios::binary);
    ofstream outFile("temp.txt", ios::out | ios::binary);

    // INPUT ROOM NUMBER TO CANCEL RESERVATION
    cout << "Enter Room Number to cancel reservation: ";
    cin >> roomNum;

    Reservation res;
    while (inFile.read((char *)&res, sizeof(res)))
    {
        if (res.roomNumber == roomNum)
        {
            found = true;
            // RESERVATION FOUND AND REMOVED
            cout << "Reservation for Room " << roomNum << " removed.\n";
        }
        else
        {
            // COPY OTHER RESERVATIONS TO TEMP FILE
            outFile.write((char *)&res, sizeof(res));
        }
    }

    inFile.close();
    outFile.close();
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    // IF RESERVATION NOT FOUND
    if (!found)
        cout << "Reservation not found.\n";
}

// ************************************************
// FUNCTION TO CHECK-IN A GUEST
// ************************************************

void checkIn()
{
    int roomNum;
    bool found = false;
    fstream file(FILENAME, ios::in | ios::out | ios::binary);

    // INPUT ROOM NUMBER FOR CHECK-IN
    cout << "Enter Room Number for Check-In: ";
    cin >> roomNum;

    Reservation res;
    while (file.read((char *)&res, sizeof(res)))
    {
        if (res.roomNumber == roomNum)
        {
            found = true;
            // IF ROOM ALREADY CONTAINS A GUEST
            if (res.roomNumber != 0)
            {
                cout << "Room already contains a guest.\n";
            }
            else
            {
                // GUEST CHECKED IN SUCCESSFULLY
                cout << "Guest checked in for Room " << roomNum << ".\n";
                // UPDATE CHECK-IN STATUS OR PERFORM NECESSARY OPERATIONS
            }
        }
    }

    file.close();

    // IF ROOM NOT FOUND
    if (!found)
        cout << "Room not found.\n";
}

// ************************************************
// FUNCTION TO CHECK-OUT A GUEST AND DELETE RESERVATION
// ************************************************

void checkOut()
{
    int roomNum;
    bool found = false;
    ifstream inFile(FILENAME, ios::binary);
    ofstream outFile("temp.txt", ios::out | ios::binary);

    // INPUT ROOM NUMBER FOR CHECK-OUT
    cout << "Enter Room Number for Check-Out: ";
    cin >> roomNum;

    Reservation res;
    while (inFile.read((char *)&res, sizeof(res)))
    {
        if (res.roomNumber == roomNum)
        {
            found = true;
            // GUEST CHECKED OUT SUCCESSFULLY
            cout << "Guest checked out from Room " << roomNum << ".\n";
            // DO NOT WRITE THIS RESERVATION TO TEMP FILE, EFFECTIVELY DELETING IT
        }
        else
        {
            // COPY OTHER RESERVATIONS TO TEMP FILE
            outFile.write((char *)&res, sizeof(res));
        }
    }

    inFile.close();
    outFile.close();
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    // IF ROOM NOT FOUND OR ALREADY CHECKED OUT
    if (!found)
        cout << "Room not found or already checked out.\n";
}

// ************************************************
// FUNCTION TO DISPLAY ROOM AVAILABILITY
// ************************************************

void displayRoomAvailability()
{
    ifstream inFile(FILENAME, ios::binary);
    Reservation res;
    bool anyReservation = false;

    // DISPLAY HEADER FOR ROOM AVAILABILITY
    cout << "Room Availability:\n";

    // READ EACH RESERVATION FROM FILE
    while (inFile.read((char *)&res, sizeof(res)))
    {
        if (res.roomNumber != 0)
        { // CHECK IF ROOM NUMBER IS VALID
            // DISPLAY RESERVATION DETAILS
            cout << "Room Number: " << res.roomNumber << ", Guest Name: " << res.guestName
                 << ", Check-In Date: " << res.checkInDate << ", Check-Out Date: " << res.checkOutDate << "\n";
            anyReservation = true;
        }
    }

    inFile.close();

    // IF NO RESERVATIONS FOUND
    if (!anyReservation)
        cout << "No reservations found.\n";
}
