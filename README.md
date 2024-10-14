# Library Management System

## Project Overview

This **Library Management System** is a C++ application designed to manage the core functionalities of a library. The system supports book management, user management, membership management, and transaction management (issue and return of books). The application features a simple interface with validations and multiple user roles (Admin and User), each having different access levels.

### Features Implemented

#### 1. **Books Management:**

- **Add New Book**: Admin can add books by providing the name, author, and serial number.
- **Issue Book**: Allows the issue of books to users, while ensuring the book is available.
- **Return Book**: Handles the return of books and updates availability status.
- **Validation**: Ensures that the book is available before issuing and that required fields are filled before submission.

#### 2. **User Management:**

- **Add New User**: Admin can add users with a unique membership number and name.
- **Manage User Access**: Users have restricted access to certain modules (e.g., cannot access the Maintenance module).

#### 3. **Membership Management:**

- **Add Membership**: Users can have memberships added for different durations (6, 12, or 24 months).
- **Update Membership**: Extend or cancel existing memberships.

#### 4. **Transaction Management:**

- **Issue and Return Books**: Admin and users can manage the issue and return of books, with automatic population of the author and return date.
- **Fine Payment**: If books are returned after the due date, a fine is calculated and payment is required before completing the return process.

#### 5. **Validation:**

- Validations are included in forms to ensure all required fields are filled before submission.
- Users must make valid selections before submitting forms to prevent errors.

#### 6. **Display Functionality:**

- **List Available Books**: Display books that are available for issue.
- **List Users**: Display all registered users and their membership details.
- **Transaction History**: Display a list of issued and returned books along with dates.

### Access Roles

- **Admin**: Has access to all modules including Maintenance, Reports, and Transactions.
- **User**: Limited to Reports and Transactions modules; cannot access the Maintenance module.

### Next Steps for Enhancement

1. **Input Validation**: Improve input validation across the application, such as checking if a user exists before issuing a book.
2. **Fine Management**: Fully implement fine management for overdue books.
3. **Persistent Storage**: Introduce file or database storage for persistence of data across sessions.
4. **Login System**: Add a simple login mechanism with role-based access (Admin and User).

### How to Run the Program

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/your-username/library-management-system.git
   ```

2. Navigate to the project directory:
   ```bash
   cd library-management-system
   ```

3. Compile the program :
   ```bash
   g++ main.cpp -o library_management
   ```

4. Run the application:
   ```bash
   ./library_management
   ```
