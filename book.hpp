// Book.h

// Header guards to prevent multiple inclusions of the same header file
#ifndef BOOK_HPP
#define BOOK_HPP

// Include necessary standard C++ headers
#include <iostream>
#include <vector>
#include <string>

// Declaration of the Book class
class Book {
private:
    // Static member to count and generate unique book IDs
    static int bookIDCounter;

    // Instance variables to store book information
    int bookID;         // Unique identifier for each book
    std::string bookName;   // Book's name
    std::string author;     // Book's author
    std::string type;       // Book's type or genre
    int pageCount;          // Number of pages in the book
    int memberID;           // Member ID to whom the book is currently borrowed (0 if not borrowed)
    std::string dueDate;    // Due date for the borrowed book (empty string if not borrowed)

public:
    // Constructor to initialize a Book object with provided details
    Book(const std::string& name, const std::string& author, const std::string& type, int pageCount);

    // Getter methods to retrieve book attributes
    int getBookID() const;     // Get the book's unique ID
    std::string getBookName() const; // Get the book's name
    std::string getAuthor() const;   // Get the book's author
    std::string getType() const;     // Get the book's type
    int getPageCount() const;        // Get the book's page count
    int getMemberID() const;         // Get the member ID to whom the book is currently borrowed
    std::string getDueDate() const;  // Get the due date for the borrowed book

    // Method to display details of the book
    void displayDetails() const;

    // Virtual method to calculate the fine for an overdue book
    virtual int calculateFine() const;

    // Method to borrow the book by assigning it to a member and setting the due date
    void borrowBook(int memberId, const std::string& dueDate);

    // Method to return the book by resetting the member ID and due date
    void returnBook();
};

// End of the header guard to prevent multiple inclusions
#endif // BOOK_HPP
