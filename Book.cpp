// Book.cpp
#include "Book.hpp"


// Include the corresponding header file for the Book class
#include "Book.hpp"


int Book::bookIDCounter = 0;

// Constructor to initialize a Book object with provided details
Book::Book(const std::string& name, const std::string& author, const std::string& type, int pageCount)
    : bookID(++bookIDCounter), bookName(name), author(author), type(type), pageCount(pageCount), memberID(0), dueDate("") {}

int Book::getBookID() const {
    return bookID;
}

std::string Book::getBookName() const {
    return bookName;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getType() const {
    return type;
}

int Book::getPageCount() const {
    return pageCount;
}

int Book::getMemberID() const {
    return memberID;
}

std::string Book::getDueDate() const {
    return dueDate;
}

void Book::displayDetails() const {
    std::cout << "Book ID: " << bookID << "\nName: " << bookName << "\nAuthor: " << author
        << "\nType: " << type << "\nPage Count: " << pageCount << "\nMember ID: " << memberID << "\nDue Date: " << dueDate << std::endl;
}

int Book::calculateFine() const {
    return 0; // Default implementation for the base class
}

void Book::borrowBook(int memberId, const std::string& dueDate) {
    this->memberID = memberId;
    this->dueDate = dueDate;
}

void Book::returnBook() {
    memberID = 0;
    dueDate = "";
}
