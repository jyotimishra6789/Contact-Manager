#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits> 
using namespace std;

class temp {
public:
    string phoneNo, name, address, description, search;
    fstream file;

    void addContact();
    void showAll();
    void searchContact();
};

void temp::addContact() {
    cout << "Enter the name of the contact: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, name);

    while (true) {
        cout << "Enter the Phone No. (10 digits): ";
        getline(cin, phoneNo);

        if (phoneNo.length() == 10 && all_of(phoneNo.begin(), phoneNo.end(), ::isdigit)) {
            break;
        } else {
            cout << "Invalid phone number. Please enter exactly 10 digits.\n";
        }
    }

    cout << "Enter the Address: ";
    getline(cin, address);
    cout << "Enter the Description: ";
    getline(cin, description);

    file.open("data.csv", ios::out | ios::app);
    if (file.is_open()) {
        file << phoneNo << "," << name << "," << address << "," << description << "\n";
        file.close();
        cout << "Contact added successfully!\n";
    } else {
        cout << "Error opening file.\n";
    }
}

void temp::showAll() {
    file.open("data.csv", ios::in);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, phoneNo, ',');
            getline(file, name, ',');
            getline(file, address, ',');
            getline(file, description, '\n');

            if (!file.eof()) {
                cout << "Phone No.: " << phoneNo << endl;
                cout << "Name: " << name << endl;
                cout << "Address: " << address << endl;
                cout << "Description: " << description << endl;
                cout << "------------------------\n";
            }
        }
        file.close();
    } else {
        cout << "Error opening file.\n";
    }
}

void temp::searchContact() {
    cout << "Enter Phone No. to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, search);

    bool found = false;
    file.open("data.csv", ios::in);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, phoneNo, ',');
            getline(file, name, ',');
            getline(file, address, ',');
            getline(file, description, '\n');

            if (phoneNo == search) {
                cout << "Phone No.: " << phoneNo << endl;
                cout << "Name: " << name << endl;
                cout << "Address: " << address << endl;
                cout << "Description: " << description << endl;
                found = true;
                break;
            }
        }
        file.close();
        if (!found) {
            cout << "Contact not found.\n";
        }
    } else {
        cout << "Error opening file.\n";
    }
}

int main() {
    temp obj;
    char choice;

    do {
        cout << "1 --> Add Contact\n";
        cout << "2 --> Show all Contacts\n";
        cout << "3 --> Search Contact\n";
        cout << "4 --> Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case '1':
            obj.addContact();
            break;
        case '2':
            obj.showAll();
            break;
        case '3':
            obj.searchContact();
            break;
        case '4':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != '4');

    return 0;
}