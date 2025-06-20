#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BankAccount {
    static int nextAccountNumber;
    int accountNumber;
    string holderName;
    double balance;

public:
    BankAccount(string name, double initialBalance) {
        accountNumber = nextAccountNumber++;
        holderName = name;
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getHolderName() const {
        return holderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Invalid or insufficient funds.\n";
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << "\n"
             << "Holder Name: " << holderName << "\n"
             << "Balance: $" << balance << "\n";
    }
};

int BankAccount::nextAccountNumber = 1001;

class BankSystem {
    vector<BankAccount> accounts;

    BankAccount* findAccount(int accountNumber) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accountNumber)
                return &acc;
        }
        return nullptr;
    }

public:
    void createAccount() {
        string name;
        double initialBalance;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial deposit: ";
        cin >> initialBalance;

        accounts.emplace_back(name, initialBalance);
        cout << "Account created successfully. Account Number: "
             << accounts.back().getAccountNumber() << "\n";
    }

    void depositMoney() {
        int accNo;
        double amount;
        cout << "Enter account number: ";
        cin >> accNo;
        BankAccount* acc = findAccount(accNo);
        if (acc) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            acc->deposit(amount);
        } else {
            cout << "Account not found.\n";
        }
    }

    void withdrawMoney() {
        int accNo;
        double amount;
        cout << "Enter account number: ";
        cin >> accNo;
        BankAccount* acc = findAccount(accNo);
        if (acc) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            acc->withdraw(amount);
        } else {
            cout << "Account not found.\n";
        }
    }

    void transferMoney() {
        int fromAccNo, toAccNo;
        double amount;
        cout << "Enter sender's account number: ";
        cin >> fromAccNo;
        cout << "Enter receiver's account number: ";
        cin >> toAccNo;
        cout << "Enter amount to transfer: ";
        cin >> amount;

        BankAccount* fromAcc = findAccount(fromAccNo);
        BankAccount* toAcc = findAccount(toAccNo);

        if (fromAcc && toAcc && amount > 0 && fromAcc->getBalance() >= amount) {
            fromAcc->withdraw(amount);
            toAcc->deposit(amount);
            cout << "Transferred $" << amount << " from " << fromAccNo << " to " << toAccNo << "\n";
        } else {
            cout << "Transfer failed. Check accounts and balance.\n";
        }
    }

    void viewAccount() {
        int accNo;
        cout << "Enter account number: ";
        cin >> accNo;
        BankAccount* acc = findAccount(accNo);
        if (acc) {
            acc->display();
        } else {
            cout << "Account not found.\n";
        }
    }
};

int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n=== Online Banking System ===\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. View Account Details\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney(); break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.transferMoney(); break;
            case 5: bank.viewAccount(); break;
            case 0: cout << "Thank you for using the system.\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

