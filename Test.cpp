// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "Member.hpp"
#include "Book.hpp"
#include "Library.hpp"

TEST_CASE("Member Class Tests") {
    SECTION("Member Initialization") {
        Member member("John Doe", "123 Main St", "john@example.com");
        REQUIRE(member.getMemberID() > 0);
        REQUIRE(member.getName() == "John Doe");
        REQUIRE(member.getAddress() == "123 Main St");
        REQUIRE(member.getEmail() == "john@example.com");
    }
}

TEST_CASE("Book Class Tests") {
    SECTION("Book Initialization") {
        Book book("The Catcher in the Rye", "J.D. Salinger", "Fiction", 234);
        REQUIRE(book.getBookID() > 0);
        REQUIRE(book.getBookName() == "The Catcher in the Rye");
        REQUIRE(book.getAuthor() == "J.D. Salinger");
        REQUIRE(book.getType() == "Fiction");
        REQUIRE(book.getPageCount() == 234);
        REQUIRE(book.getMemberID() == 0);
        REQUIRE(book.getDueDate() == "");
    }

    SECTION("Book Borrowing and Returning") {
        Book book("The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", 1200);

        // Borrow the book
        book.borrowBook(1, "2024-01-20");
        REQUIRE(book.getMemberID() == 1);
        REQUIRE(book.getDueDate() == "2024-01-20");

        // Return the book
        book.returnBook();
        REQUIRE(book.getMemberID() == 0);
        REQUIRE(book.getDueDate() == "");
    }

    SECTION("Book Display Details") {
        Book book("The Hitchhiker's Guide to the Galaxy", "Douglas Adams", "Science Fiction", 200);

        // Display book details
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout to a stringstream
        book.displayDetails();
        std::cout.rdbuf(old); // Restore cout

        std::string details = buffer.str();
        REQUIRE(details.find("Book ID:") != std::string::npos);
        REQUIRE(details.find("Name: The Hitchhiker's Guide to the Galaxy") != std::string::npos);
        REQUIRE(details.find("Author: Douglas Adams") != std::string::npos);
        REQUIRE(details.find("Type: Science Fiction") != std::string::npos);
        REQUIRE(details.find("Page Count: 200") != std::string::npos);
        REQUIRE(details.find("Member ID: 0") != std::string::npos);
        REQUIRE(details.find("Due Date: ") != std::string::npos);
    }
}

TEST_CASE("Library Class Tests") {
    SECTION("Add Members and Books") {
        Library library;

        // Add members
        Member member1("John Doe", "123 Main St", "john@example.com");
        Member member2("Jane Smith", "456 Oak St", "jane@example.com");
        library.addMember(member1);
        library.addMember(member2);

        // Add books
        Book* book1 = library.createBookByType("Fiction", "The Catcher in the Rye", "J.D. Salinger", 234);
        Book* book2 = library.createBookByType("Fantasy", "The Lord of the Rings", "J.R.R. Tolkien", 1200);
        library.addBook(book1);
        library.addBook(book2);

        REQUIRE(library.displayAllMembers() == "All Members:\nMember ID: 22\nName: Blake Fox\nAddress: 99 IDK St\nEmail: balkie@example.com\n---------------------\nMember ID: 2\nName: John Tay\nAddress: 419 Oak St\nEmail: tayiiee@example.com\n---------------------\n");

        REQUIRE(library.displayAvailableBooks() == "Available Books:\nBook ID: 16\nName: A Touch of Sun and Other Stories\nAuthor: Mary Hallock Foote\nType: Guide\nPage Count: 141\nMember ID: 22\nDue Date: 3 days \n---------------------\nBook ID: 26\nName: The Unlived Life of Little Mary Ellen\nAuthor: Ruth Stuart\nType: Mystery\nPage Count: 99\nMember ID: 2\nDue Date: 1 day\n---------------------\n");
    }

    SECTION("Issue and Return Books") {
        Library library;

        // Add members
        Member member("John Doe", "123 Main St", "john@example.com");
        library.addMember(member);

        // Add books
        Book* book = library.createBookByType("Fiction", "The Catcher in the Rye", "J.D. Salinger", 234);
        library.addBook(book);

        // Issue a book
        library.issueBook(book->getBookID(), member.getMemberID());
        REQUIRE(book->getMemberID() == member.getMemberID());
        REQUIRE(library.displayBorrowedBooks(member.getMemberID()) == "Books borrowed by member ID: 1\nBook ID: 1\nName: The Catcher in the Rye\nAuthor: J.D. Salinger\nType: Fiction\nPage Count: 234\nMember ID: 1\nDue Date: \n---------------------\n");

        // Return the book
        library.returnBook(book->getBookID());
        REQUIRE(book->getMemberID() == 0);
    }

    SECTION("Display Menu") {
        // Test the menu-driven interaction (you may need to simulate user input or refactor your code for easier testing)
    }
}
