#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>

using namespace std;

class Book
{
public:
    string name;
    string author;
    string serialNo;
    bool isAvailable;

    Book(string n, string a, string s)
        : name(n), author(a), serialNo(s), isAvailable(true) {}
};

class User
{
public:
    string name;
    string membershipNumber;
    string password;

    User(string n, string m, string p)
        : name(n), membershipNumber(m), password(p) {}
};

class Membership
{
public:
    string membershipNumber;
    int duration; // Duration in months (6, 12, or 24)

    Membership(string m, int d)
        : membershipNumber(m), duration(d) {}
};

class Transaction
{
public:
    string userName;
    string serialNo;
    string transactionType; // "issue" or "return"
    time_t transactionDate;

    Transaction(string u, string s, string type)
        : userName(u), serialNo(s), transactionType(type)
    {
        transactionDate = time(nullptr); // Store the current time
    }
};

class Fine
{
public:
    string userName;
    string serialNo;
    double amount;
    time_t fineDate;

    Fine(string u, string s, double amt)
        : userName(u), serialNo(s), amount(amt)
    {
        fineDate = time(nullptr); // Store the current time
    }
};

class Library
{
private:
    vector<Book> books;
    vector<User> users;
    vector<Membership> memberships;
    vector<Transaction> transactions;
    vector<Fine> fines;

    const double finePerDay = 2.0; // Define fine per day for late return

public:
    void addBook(const string &name, const string &author, const string &serialNo)
    {
        books.emplace_back(name, author, serialNo);
        cout << "Book added: " << name << " by " << author << endl;
    }

    void removeBook(const string &serialNo)
    {
        for (auto it = books.begin(); it != books.end(); ++it)
        {
            if (it->serialNo == serialNo)
            {
                cout << "Book removed: " << it->name << endl;
                books.erase(it);
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void updateBook(const string &serialNo, const string &newName, const string &newAuthor)
    {
        for (auto &book : books)
        {
            if (book.serialNo == serialNo)
            {
                book.name = newName;
                book.author = newAuthor;
                cout << "Book updated: " << newName << " by " << newAuthor << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void issueBook(const string &serialNo, const string &userName)
    {
        for (auto &book : books)
        {
            if (book.serialNo == serialNo && book.isAvailable)
            {
                book.isAvailable = false;
                transactions.emplace_back(userName, serialNo, "issue");
                cout << "Book issued to " << userName << endl;
                return;
            }
        }
        cout << "Book is not available for issue." << endl;
    }

    void returnBook(const string &serialNo, const string &userName)
    {
        for (auto &book : books)
        {
            if (book.serialNo == serialNo && !book.isAvailable)
            {
                book.isAvailable = true;
                transactions.emplace_back(userName, serialNo, "return");
                cout << "Book returned: " << book.name << endl;
                return;
            }
        }
        cout << "Book not found or already available." << endl;
    }

    void addUser(const string &name, const string &membershipNumber, const string &password)
    {
        users.emplace_back(name, membershipNumber, password);
        cout << "User added: " << name << endl;
    }

    void removeUser(const string &membershipNumber)
    {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (it->membershipNumber == membershipNumber)
            {
                cout << "User removed: " << it->name << endl;
                users.erase(it);
                return;
            }
        }
        cout << "User not found." << endl;
    }

    void addMembership(const string &membershipNumber, int duration)
    {
        memberships.emplace_back(membershipNumber, duration);
        cout << "Membership added for: " << membershipNumber << " with duration " << duration << " months" << endl;
    }

    void displayBooks()
    {
        cout << "\nAvailable Books:\n";
        for (const auto &book : books)
        {
            if (book.isAvailable)
            {
                cout << "Name: " << book.name << ", Author: " << book.author << ", Serial No: " << book.serialNo << endl;
            }
        }
    }

    bool validateMembership(const string &membershipNumber)
    {
        for (const auto &member : memberships)
        {
            if (member.membershipNumber == membershipNumber)
            {
                return true;
            }
        }
        return false;
    }

    bool isBookAvailable(const string &serialNo)
    {
        for (const auto &book : books)
        {
            if (book.serialNo == serialNo)
            {
                return book.isAvailable;
            }
        }
        return false;
    }

    void displayUsers()
    {
        cout << "\nUsers:\n";
        for (const auto &user : users)
        {
            cout << "Name: " << user.name << ", Membership No: " << user.membershipNumber << endl;
        }
    }

    void displayTransactions()
    {
        cout << "\nTransactions:\n";
        for (const auto &transaction : transactions)
        {
            tm *transactionTime = localtime(&transaction.transactionDate);
            cout << "User: " << transaction.userName << ", Book Serial: " << transaction.serialNo
                 << ", Type: " << transaction.transactionType
                 << ", Date: " << put_time(transactionTime, "%Y-%m-%d %H:%M:%S") << endl;
        }
    }

    void displayFines()
    {
        cout << "\nFines Paid:\n";
        for (const auto &fine : fines)
        {
            tm *fineTime = localtime(&fine.fineDate);
            cout << "User: " << fine.userName << ", Book Serial: " << fine.serialNo
                 << ", Fine Amount: $" << fine.amount
                 << ", Date: " << put_time(fineTime, "%Y-%m-%d %H:%M:%S") << endl;
        }
    }

    double payFine(const string &serialNo, const string &userName)
    {
        time_t now = time(nullptr);
        for (const auto &transaction : transactions)
        {
            if (transaction.serialNo == serialNo && transaction.userName == userName && transaction.transactionType == "issue")
            {
                double daysOverdue = difftime(now, transaction.transactionDate) / (60 * 60 * 24) - 14;
                if (daysOverdue > 0)
                {
                    double fineAmount = daysOverdue * finePerDay;
                    fines.emplace_back(userName, serialNo, fineAmount);
                    cout << "Fine paid: $" << fineAmount << endl;
                    return fineAmount;
                }
                else
                {
                    cout << "No fine. Book is not overdue." << endl;
                    return 0.0;
                }
            }
        }
        cout << "No matching transaction found." << endl;
        return 0.0;
    }

    // Added method to access users
    const vector<User> &getUsers() const
    {
        return users;
    }
};

class LibrarySystem
{
private:
    Library library;
    string adminUsername = "admin";
    string adminPassword = "admin";

    bool adminLogin()
    {
        string username, password;
        cout << "Admin Login\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        return username == adminUsername && password == adminPassword;
    }

    bool userLogin(string &loggedInUser)
    {
        string membershipNumber, password;
        cout << "User Login\n";
        cout << "Enter Membership Number: ";
        cin >> membershipNumber;
        cout << "Enter Password: ";
        cin >> password;

        for (const auto &user : library.getUsers()) // Accessing users through the new method
        {
            if (user.membershipNumber == membershipNumber && user.password == password)
            {
                loggedInUser = user.name;
                return true;
            }
        }
        return false;
    }

public:
    void start()
    {
        int choice;
        do
        {
            cout << "\nLibrary Management System\n";
            cout << "1. Admin Login\n";
            cout << "2. User Login\n";
            cout << "0. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                if (adminLogin())
                {
                    adminMenu();
                }
                else
                {
                    cout << "Invalid admin credentials." << endl;
                }
                break;
            case 2:
            {
                string loggedInUser;
                if (userLogin(loggedInUser))
                {
                    userMenu(loggedInUser);
                }
                else
                {
                    cout << "Invalid user credentials." << endl;
                }
                break;
            }
            case 0:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
            }
        } while (choice != 0);
    }

    void adminMenu()
    {
        int choice;
        do
        {
            cout << "\nAdmin Menu\n";
            cout << "1. Add User\n";
            cout << "2. Add Book\n";
            cout << "3. Add Membership\n";
            cout << "4. Remove Book\n";
            cout << "5. Update Book\n";
            cout << "6. Remove User\n";
            cout << "7. View All Transactions\n";
            cout << "8. View All Fines\n";
            cout << "0. Logout\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string name, membershipNumber, password;
                cout << "Enter user name: ";
                cin >> name;
                cout << "Enter membership number: ";
                cin >> membershipNumber;
                cout << "Enter password: ";
                cin >> password;
                library.addUser(name, membershipNumber, password);
                break;
            }
            case 2:
            {
                string name, author, serialNo;
                cout << "Enter book name: ";
                cin >> name;
                cout << "Enter author name: ";
                cin >> author;
                cout << "Enter serial number: ";
                cin >> serialNo;
                library.addBook(name, author, serialNo);
                break;
            }
            case 3:
            {
                string membershipNumber;
                int duration;
                cout << "Enter membership number: ";
                cin >> membershipNumber;
                cout << "Enter duration (6, 12, or 24 months): ";
                cin >> duration;
                library.addMembership(membershipNumber, duration);
                break;
            }
            case 4:
            {
                string serialNo;
                cout << "Enter serial number of the book to remove: ";
                cin >> serialNo;
                library.removeBook(serialNo);
                break;
            }
            case 5:
            {
                string serialNo, newName, newAuthor;
                cout << "Enter serial number of the book to update: ";
                cin >> serialNo;
                cout << "Enter new book name: ";
                cin >> newName;
                cout << "Enter new author name: ";
                cin >> newAuthor;
                library.updateBook(serialNo, newName, newAuthor);
                break;
            }
            case 6:
            {
                string membershipNumber;
                cout << "Enter membership number of the user to remove: ";
                cin >> membershipNumber;
                library.removeUser(membershipNumber);
                break;
            }
            case 7:
                library.displayTransactions();
                break;
            case 8:
                library.displayFines();
                break;
            case 0:
                cout << "Admin logged out." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
            }
        } while (choice != 0);
    }

    void userMenu(const string &loggedInUser)
    {
        int choice;
        do
        {
            cout << "\nUser Menu\n";
            cout << "1. Issue Book\n";
            cout << "2. Return Book\n";
            cout << "3. Display Available Books\n";
            cout << "4. Pay Fine\n";
            cout << "5. View Transactions (Issued/Returned)\n";
            cout << "6. View Fines Paid\n";
            cout << "0. Logout\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string serialNo;
                cout << "Enter serial number of the book to issue: ";
                cin >> serialNo;
                library.issueBook(serialNo, loggedInUser);
                break;
            }
            case 2:
            {
                string serialNo;
                cout << "Enter serial number of the book to return: ";
                cin >> serialNo;
                library.returnBook(serialNo, loggedInUser);
                break;
            }
            case 3:
                library.displayBooks();
                break;
            case 4:
            {
                string serialNo;
                cout << "Enter serial number of the book for which you want to pay fine: ";
                cin >> serialNo;
                library.payFine(serialNo, loggedInUser);
                break;
            }
            case 5:
                library.displayTransactions();
                break;
            case 6:
                library.displayFines();
                break;
            case 0:
                cout << "User logged out." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
            }
        } while (choice != 0);
    }
};

int main()
{
    LibrarySystem system;
    system.start();
    return 0;
}
