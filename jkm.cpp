#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>

class Book {
public:
    std::string name;
    std::string author;
    std::string serialNo;
    bool isAvailable;

    Book(std::string n, std::string a, std::string s)
        : name(n), author(a), serialNo(s), isAvailable(true) {}
};

class User {
public:
    std::string name;
    std::string membershipNumber;

    User(std::string n, std::string m)
        : name(n), membershipNumber(m) {}
};

class Membership {
public:
    std::string membershipNumber;
    int duration; // Duration in months (6, 12, or 24)

    Membership(std::string m, int d)
        : membershipNumber(m), duration(d) {}
};

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::vector<Membership> memberships;

public:
    void addBook(const std::string& name, const std::string& author, const std::string& serialNo) {
        books.emplace_back(name, author, serialNo);
        std::cout << "Book added: " << name << " by " << author << std::endl;
    }

    void issueBook(const std::string& serialNo, const std::string& userName) {
        for (auto& book : books) {
            if (book.serialNo == serialNo && book.isAvailable) {
                book.isAvailable = false;
                std::cout << "Book issued to " << userName << std::endl;
                return;
            }
        }
        std::cout << "Book is not available for issue." << std::endl;
    }

    void returnBook(const std::string& serialNo) {
        for (auto& book : books) {
            if (book.serialNo == serialNo && !book.isAvailable) {
                book.isAvailable = true;
                std::cout << "Book returned: " << book.name << std::endl;
                return;
            }
        }
        std::cout << "Book not found or already available." << std::endl;
    }

    void addUser(const std::string& name, const std::string& membershipNumber) {
        users.emplace_back(name, membershipNumber);
        std::cout << "User added: " << name << std::endl;
    }

    void addMembership(const std::string& membershipNumber, int duration) {
        memberships.emplace_back(membershipNumber, duration);
        std::cout << "Membership added for: " << membershipNumber << " with duration " << duration << " months" << std::endl;
    }

    void displayBooks() {
        std::cout << "\nAvailable Books:\n";
        for (const auto& book : books) {
            if (book.isAvailable) {
                std::cout << "Name: " << book.name << ", Author: " << book.author << ", Serial No: " << book.serialNo << std::endl;
            }
        }
    }

    bool validateMembership(const std::string& membershipNumber) {
        for (const auto& member : memberships) {
            if (member.membershipNumber == membershipNumber) {
                return true;
            }
        }
        return false;
    }

    bool isBookAvailable(const std::string& serialNo) {
        for (const auto& book : books) {
            if (book.serialNo == serialNo) {
                return book.isAvailable;
            }
        }
        return false;
    }

    void displayUsers() {
        std::cout << "\nUsers:\n";
        for (const auto& user : users) {
            std::cout << "Name: " << user.name << ", Membership No: " << user.membershipNumber << std::endl;
        }
    }
};

class LibrarySystem {
private:
    Library library;

public:
    void start() {
        int choice;
        do {
            std::cout << "\nLibrary Management System\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. Issue Book\n";
            std::cout << "3. Return Book\n";
            std::cout << "4. Add User\n";
            std::cout << "5. Add Membership\n";
            std::cout << "6. Display Books\n";
            std::cout << "7. Display Users\n";
            std::cout << "0. Exit\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string name, author, serialNo;
                    std::cout << "Enter Book Name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Enter Author Name: ";
                    std::getline(std::cin, author);
                    std::cout << "Enter Serial No: ";
                    std::getline(std::cin, serialNo);
                    library.addBook(name, author, serialNo);
                    break;
                }
                case 2: {
                    std::string serialNo, userName;
                    std::cout << "Enter Serial No: ";
                    std::cin.ignore();
                    std::getline(std::cin, serialNo);
                    std::cout << "Enter User Name: ";
                    std::getline(std::cin, userName);
                    if (library.isBookAvailable(serialNo)) {
                        library.issueBook(serialNo, userName);
                    } else {
                        std::cout << "Book is not available for issue." << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::string serialNo;
                    std::cout << "Enter Serial No: ";
                    std::cin.ignore();
                    std::getline(std::cin, serialNo);
                    library.returnBook(serialNo);
                    break;
                }
                case 4: {
                    std::string name, membershipNumber;
                    std::cout << "Enter User Name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Enter Membership Number: ";
                    std::getline(std::cin, membershipNumber);
                    library.addUser(name, membershipNumber);
                    break;
                }
                case 5: {
                    std::string membershipNumber;
                    int duration;
                    std::cout << "Enter Membership Number: ";
                    std::cin.ignore();
                    std::getline(std::cin, membershipNumber);
                    std::cout << "Enter Duration (6, 12, or 24 months): ";
                    std::cin >> duration;
                    if (duration == 6 || duration == 12 || duration == 24) {
                        library.addMembership(membershipNumber, duration);
                    } else {
                        std::cout << "Invalid duration. Please enter 6, 12, or 24." << std::endl;
                    }
                    break;
                }
                case 6:
                    library.displayBooks();
                    break;
                case 7:
                    library.displayUsers();
                    break;
                case 0:
                    std::cout << "Exiting system." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
            }
        } while (choice != 0);
    }
};

int main() {
    LibrarySystem system;
    system.start();
    return 0;
}
