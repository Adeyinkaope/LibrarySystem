#include <iostream>
#include <string> 
#include <limits> // for input validation
#include <ctime> // to get current time
#include <fstream> // header file to read the CSV files
#include <sstream> // For string stream
#include <iomanip> // For formatting

// including the header files for custom classes
#include "Book.hpp"
#include "Member.hpp"
#include "Library.hpp"
#include "library_books.csv"  // Include additional book types as needed

int main() {
    // Create an instance of the Library class
    Library library;

    // Welcome message for the user
    std::cout << "Welcome to the Library Management System!\n";

    int choice;
    do {
        // Display the main menu for user interaction
        std::cout << "\nMenu:\n"
                  << "1. Add a member\n"
                  << "2. Add a book\n"
                  << "3. Issue a book\n"
                  << "4. Return a book\n"
                  << "5. Display all books borrowed by a member\n"
                  << "6. Display available books\n"
                  << "7. Display all members\n"
                  << "8. Exit\n"
                  << "Enter your choice: ";

        // Read the user's choice
        std::cin >> choice;

        // Switch based on user's choice
        switch (choice) {
            case 1: {
                // Add a new member to the library
                Member newMember = library.createMember();
                library.addMember(newMember);
                break;
            }
            case 2: {
                // Add a new book to the library
                Book* newBook = library.createBook();
                library.addBook(newBook);
                break;
            }
            case 3: {
                // Issue a book to a member
                library.issueBook();
                break;
            }
            case 4: {
                // Return a book to the library
                library.returnBook();
                break;
            }
            case 5: {
                // Display all books borrowed by a specific member
                library.displayBorrowedBooks();
                break;
            }
            case 6: {
                // Display all available books in the library
                library.displayAvailableBooks();
                break;
            }
            case 7: {
                // Display details of all library members
                library.displayAllMembers();
                break;
            }
            case 8: {
                // Exit the program
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            }
            default: {
                // Handle invalid choices, clear input buffer
                std::cerr << "Invalid choice! Please try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

    } while (choice != 8);  // Continue the loop until the user chooses to exit

    return 0;
}
