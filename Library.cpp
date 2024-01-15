// Library.cpp
// this includes the header file for the library class
#include "Library.hpp"
#include <algorithm> //alogrithm header


/*this is a constructor to initialise the library object
the function to add new member 
to the library by adding it to the vector */
void Library::addMember(const Member& member) {
    members.push_back(member);
    std::cout << "New member added:\n"; 
    member.displayDetails();  
    /* the code above call the displayDetails 
    method of the member class to show member detail*/
}


/* a function to add a book 
to the library and to push books vector*/
void Library::addBook(Book* book) {
    books.push_back(book);
    std::cout << "New book added:\n";
    book->displayDetails();
    /* the code above call the displayDetails 
    method of the book class to show member detail*/

}


//issue a book to a member
void Library::issueBook(int bookID, int memberID) {
    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookID](const Book* book) { return book->getBookID() == bookID && book->getMemberID() == 0; });

    auto memberIt = std::find_if(members.begin(), members.end(),
        [memberID](const Member& member) { return member.getMemberID() == memberID; });

    if (bookIt != books.end() && memberIt != members.end()) {
        time_t now = time(0);
        struct tm dueDateStruct = *localtime(&now);
        dueDateStruct.tm_mday += 3; // make it due in  3 days from now
        char dueDate[11];
        strftime(dueDate, sizeof(dueDate), "%Y-%m-%d", &dueDateStruct);
        //issue the book to the member with the calculated due date
        (*bookIt)->borrowBook(memberID, dueDate);
        std::cout << "Book issued to member ID: " << memberID << " with due date: " << dueDate << std::endl;
    } else {
        //display an error message if the book or member is not found or the book is already borrowed
        std::cerr << "Book or member not found or book already borrowed." << std::endl;
    }
}
//return book
void Library::returnBook(int bookID) {
    //find the book using bookid and ensure it borrowed
    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookID](const Book* book) { return book->getBookID() == bookID && book->getMemberID() != 0; });

      // check if the book is borrowed
    if (bookIt != books.end()) {
        (*bookIt)->returnBook(); // return bool and calculate any overdue fine
        int fine = (*bookIt)->calculateFine();
        if (fine > 0) {
            std::cout << "Fine for overdue book: £" << fine << std::endl;
        }
        std::cout << "Book returned." << std::endl;
    } else {
        std::cerr << "Book not found or not borrowed." << std::endl;
    }
}


//function to display books borrowed by specific member
void Library::displayBorrowedBooks(int memberID) const {
    std::cout << "Books borrowed by member ID: " << memberID << std::endl;
    //it iterate through the books and display details of borrowed books by specific member
    for (const Book* book : books) {
        if (book->getMemberID() == memberID) {
            book->displayDetails();
            std::cout << "---------------------" << std::endl;
        }
    }
}


// it displays members
void Library::displayAllMembers() const {
    std::cout << "All Members:" << std::endl;
    // iterate through the members and display detail of each member
    for (const Member& member : members) {
        member.displayDetails();
        std::cout << "---------------------" << std::endl;
    }
}

void Library::displayAvailableBooks() const {
    std::cout << "Available Books:" << std::endl;
    for (const Book* book : books) {
        if (book->getMemberID() == 0) {
            book->displayDetails();
            std::cout << "---------------------" << std::endl;
        }
    }
}

// this display the main menu for library operations
void Library::displayMenu() {
    int choice;
    do {
        std::cout << "\nMenu:\n"
            << "1. Add a member\n"
            << "2. Add a book\n"
            << "3. Issue a book\n"
            << "4. Return a book\n"
            << "5. Display all books borrowed by a member\n"
            << "6. Display available books\n"
            << "7. Display all members\n"
            << "0. Exit\n"
            << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
        case 1:
            addMember(createMember());
            break;
        case 2:
            addBook(createBook());
            break;
        case 3:
            issueBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            displayBorrowedBooks();
            break;
        case 6:
            displayAvailableBooks();
            break;
        case 7:
            displayAllMembers();
            break;
        case 0:
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            std::cerr << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
}

Member Library::createMember() {
    std::string name, address, email;
    std::cout << "Enter member name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter member address: ";
    std::getline(std::cin, address);
    std::cout << "Enter member email: ";
    std::getline(std::cin, email);
    return Member(name, address, email);
}

Book* Library::createBook() {
    std::string name, author, type;
    int pageCount;
    std::cout << "Enter book name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter book author: ";
    std::getline(std::cin, author);
    std::cout << "Enter book type: ";
    std::getline(std::cin, type);
    std::cout << "Enter book page count: ";
    std::cin >> pageCount;
    return createBookByType(type, name, author, pageCount);
}

//function to create a new book based on the specified type
Book* Library::createBookByType(const std::string& type, const std::string& name, const std::string& author, int pageCount) {
    if (type == "Science Fiction") {
        return new library_books.csv(name, author, pageCount);
    }
    // Add more conditions for other book types...

    std::cerr << "Invalid book type. Creating a default book." << std::endl;
    return new Book(name, author, "Default", pageCount);
}


// Function to issue a book with user input
void Library::issueBook() {
    int bookID, memberID;
    std::cout << "Enter Book ID to issue: "; // Function to issue a book with user input
    std::cin >> bookID;
    std::cout << "Enter Member ID to issue to: ";
    std::cin >> memberID;
    issueBook(bookID, memberID);
}


// Function to return a book with user input
void Library::returnBook() {
    int bookID;
    std::cout << "Enter Book ID to return: "; // Get book ID from user input
    std::cin >> bookID;
    returnBook(bookID);
}

// Function to display books borrowed by a member with user input
void Library::displayBorrowedBooks() {
    int memberID;
    std::cout << "Enter Member ID: ";
    std::cin >> memberID;
    displayBorrowedBooks(memberID);
}
