// Library.h
#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Book.hpp"
#include "Member.hpp"

/* The code below is the collection of pointers to Book objects 
 representing the library's books. And
Collection of Member objects
representing the library's members.*/

class Library {
private:
    std::vector<Book*> books;
    std::vector<Member> members;



public:
    void addMember(const Member& member);
    void addBook(Book* book);
    void issueBook(int bookID, int memberID);
    void returnBook(int bookID);
    void displayBorrowedBooks(int memberID) const;
    void displayAllMembers() const;
    void displayAvailableBooks() const;
    void displayMenu();

   // Function to create a new Member object
    // by taking user input for name, address, and email.
    Member createMember();
    Book* createBook();
    Book* createBookByType(const std::string& type, const std::string& name, const std::string& author, int pageCount);

    void issueBook();
    void returnBook();
    void displayBorrowedBooks();
};

#endif  LIBRARY_H
