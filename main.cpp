#include <iostream>
#include <string>
#include <vector>
#include <cctype>   
#include <limits>
#include <iomanip>

using namespace std;

// STORE CATEGORY DATA
struct Category {
    string name;
    int amount;
};

// SPECIAL CHARACTER CHECK
bool isValidName(string name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!isalnum(c) && !isspace(c)) return false;
    }
    return true;
}

// ENTER
void waitEnter() {
    string dummy;
    getline(cin, dummy);
}

int main() {
    // WELCOME MESSAGE
    cout << "Welcome to Allocoint!" << endl;
    cout << "Where every coin finds its allocated purpose." << endl;
    cout << "|| Press ENTER to start...";
    waitEnter();

    // INSTRUCTIONS
    cout << "\nNOTE:" << endl;
    cout << "Press ENTER after every input." << endl;
    cout << "Enter whole numbers only for amounts." << endl;
    cout << "Category names must not contain special characters." << endl;
    cout << "|| Press ENTER to proceed...";
    waitEnter();

    // INPUT TOTAL BALANCE
    cout << "\nSETUP" << endl;
    cout << "Enter TOTAL BALANCE for this month: ";
    int total_balance;
    while (!(cin >> total_balance) || total_balance < 0) {
        cout << "Invalid input. Enter a positive whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); 

    int remaining_balance = total_balance;
    int total_allocated = 0;
    vector<Category> categories;

    cout << "TOTAL BALANCE: Php " << total_balance << endl;

    // CREATE CATEGORIES
    cout << "\nCATEGORY SETUP" << endl;
    while (true) {
        cout << "Add a category (type DONE to finish): ";
        string inputName;
        getline(cin, inputName);

        for (int i = 0; i < inputName.length(); i++) {
            inputName[i] = toupper(inputName[i]);
        }

        if (inputName == "DONE") break;

        if (isValidName(inputName)) {
            Category newCat;
            newCat.name = inputName;
            newCat.amount = 0;
            categories.push_back(newCat);

            cout << "\nCURRENT CATEGORIES:" << endl;
            for (int i = 0; i < categories.size(); i++) {
                cout << i + 1 << ". " << categories[i].name << endl;
            }
        } else {
            cout << "Invalid name! No special characters allowed." << endl;
        }
        cout << endl;
    }

    // ALLOCATE BUDGET
    cout << "\nBUDGET ALLOCATION" << endl;
    cout << "TOTAL BALANCE: Php " << total_balance << endl;
    cout << "Enter allocated budget for each category:" << endl;

    for (int i = 0; i < categories.size(); i++) {
        int amount;
        while (true) {
            cout << i + 1 << ". " << categories[i].name << ": ";
            if (cin >> amount && amount >= 0 && amount <= remaining_balance) {
                categories[i].amount = amount;
                remaining_balance -= amount;
                total_allocated += amount;
                cout << "   Remaining Balance: Php " << remaining_balance << endl;
                break;
            } else {
                cout << "   Invalid amount. Must be <= " << remaining_balance << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    // DISPLAY SUMMARY
    cout << "\nSUMMARY" << endl;
    cout << "-------------------------------" << endl;
    cout << "Total Budget    : Php " << total_balance << endl;
    cout << "Total Allocated : Php " << total_allocated << endl;
    cout << "Remaining       : Php " << remaining_balance << endl;
    cout << "\nCategory Breakdown:" << endl;

    for (int i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << left << setw(15) << categories[i].name << ": Php " << categories[i].amount << endl;
    }

    // STATUS CHECK
    cout << "\nStatus: ";
    if (remaining_balance == 0) {
        cout << "Successful - Budget Fully Allocated" << endl;
    } else if (remaining_balance > 0) {
        cout << "Incomplete" << endl;
        cout << "Warning: You still have Php " << remaining_balance << " unallocated." << endl;
    } else {
        cout << "Error - Over Allocated" << endl;
        cout << "Warning: You exceeded budget by Php " << abs(remaining_balance) << endl;
    }

    cout << "\nThank you for using Allocoint!" << endl;

    return 0;
}
