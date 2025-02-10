
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // For formatting account number

using namespace std;

class Customer {
public:
    string name;
    int accountNumber;
    double balance;

    void input(int newAccountNumber) {
        cout << "\nEnter full name: ";
        cin.ignore(); // To ignore the newline character left in the input buffer
        getline(cin, name);
        accountNumber = newAccountNumber;
        cout << "Enter balance (in Birr): ";
        cin >> balance;
    }

    void display() {
        cout << "\nFull Name: " << name << endl;
        cout << "Account Number: " << setw(6) << setfill('0') << accountNumber << endl;
        cout << "Balance: " << balance << " Birr" << endl;
    }

    void save(ofstream &file) {
        file << name << "\n" << accountNumber << " " << balance << endl;
    }

    void load(ifstream &file) {
        getline(file, name); // Read the full name including spaces
        file >> accountNumber >> balance;
        file.ignore(); // To ignore the newline character after balance
    }

    void deposit(double amount) {
        balance += amount;
        cout << "\nAmount deposited successfully. New balance: " << balance << " Birr" << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "\nInsufficient balance." << endl;
            return false;
        }
        balance -= amount;
        cout << "\nAmount withdrawn successfully. New balance: " << balance << " Birr" << endl;
        return true;
    }
};

int getNextAccountNumber() {
    ifstream inFile("customers.txt");
    int accountNumber = 0;
    if (inFile.is_open()) {
        string name;
        double balance;
        while (!inFile.eof()) {
            getline(inFile, name); // Read the full name including spaces
            inFile >> accountNumber >> balance;
            inFile.ignore(); // To ignore the newline character after balance
        }
        inFile.close();
    }
    return accountNumber + 1;
}

void addCustomer() {
    int newAccountNumber = getNextAccountNumber();
    Customer customer;
    customer.input(newAccountNumber);

    ofstream outFile("customers.txt", ios::app);
    if (outFile.is_open()) {
        cout << "\nCustomer account number: " << setw(6) << setfill('0') << newAccountNumber << endl;
        customer.save(outFile);
        outFile.close();
        cout << "Customer information saved successfully." << endl;
    } else {
        cout << "\nUnable to open file for writing." << endl;
    }
}

void displayCustomer() {
    int accountNumber;
    cout << "\nEnter account number to display: ";
    cin >> accountNumber;

    ifstream inFile("customers.txt");
    if (inFile.is_open()) {
        Customer customer;
        bool found = false;
        while (!inFile.eof()) {
            customer.load(inFile);
            if (inFile.eof()) break;
            if (customer.accountNumber == accountNumber) {
                found = true;
                customer.display();
                break;
            }
        }
        inFile.close();
        if (!found) {
            cout << "\nCustomer with account number " << setw(6) << setfill('0') << accountNumber << " not found." << endl;
        }
    } else {
        cout << "\nUnable to open file for reading." << endl;
    }
}

void updateCustomerInfo(Customer &customer) {
    ifstream inFile("customers.txt");
    ofstream tempFile("temp.txt");
    if (inFile.is_open() && tempFile.is_open()) {
        Customer tempCustomer;
        while (!inFile.eof()) {
            tempCustomer.load(inFile);
            if (inFile.eof()) break;
            if (tempCustomer.accountNumber == customer.accountNumber) {
                customer.save(tempFile);
            } else {
                tempCustomer.save(tempFile);
            }
        }
        inFile.close();
        tempFile.close();
        remove("customers.txt");
        rename("temp.txt", "customers.txt");
    } else {
        cout << "\nUnable to open file for updating." << endl;
    }
}

void performTransaction(bool isDeposit) {
    int accountNumber;
    double amount;
    cout << "\nEnter account number: ";
    cin >> accountNumber;
    cout << "Enter amount (in Birr): ";
    cin >> amount;

    ifstream inFile("customers.txt");
    if (inFile.is_open()) {
        Customer customer;
        bool found = false;
        while (!inFile.eof()) {
            customer.load(inFile);
            if (inFile.eof()) break;
            if (customer.accountNumber == accountNumber) {
                found = true;
                if (isDeposit) {
                    customer.deposit(amount);
                } else {
                    if (!customer.withdraw(amount)) {
                        cout << "\nTransaction failed." << endl;
                        return;
                    }
                }
                updateCustomerInfo(customer);
                break;
            }
        }
        inFile.close();
        if (!found) {
            cout << "\nCustomer with account number " << setw(6) << setfill('0') << accountNumber << " not found." << endl;
        }
    } else {
        cout << "\nUnable to open file for reading." << endl;
    }
}

void closeAccount() {
    int accountNumber;
    cout << "\nEnter account number to close: ";
    cin >> accountNumber;

    ifstream inFile("customers.txt");
    ofstream tempFile("temp.txt");
    if (inFile.is_open() && tempFile.is_open()) {
        Customer customer;
        bool found = false;
        while (!inFile.eof()) {
            customer.load(inFile);
            if (inFile.eof()) break;
            if (customer.accountNumber == accountNumber) {
                found = true;
                cout << "\nAccount closed successfully." << endl;
            } else {
                customer.save(tempFile);
            }
        }
        inFile.close();
        tempFile.close();
        if (found) {
            remove("customers.txt");
            rename("temp.txt", "customers.txt");
        } else {
            cout << "\nCustomer with account number " << setw(6) << setfill('0') << accountNumber << " not found." << endl;
        }
    } else {
        cout << "\nUnable to open file for updating." << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nWelcome to Commercial Bank of Ethiopia" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Display Customer" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Close Account" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addCustomer();
            break;
        case 2:
            displayCustomer();
            break;
        case 3:
            performTransaction(true);
            break;
        case 4:
            performTransaction(false);
            break;
        case 5:
            closeAccount();
            break;
        case 6:
            return 0;
        default:
            cout << "\nInvalid choice. Please try again." << endl;
        }
    }
    return 0;
}
