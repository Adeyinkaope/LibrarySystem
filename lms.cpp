#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Member {
private:
    static int memberIDCounter;
    int memberID;
    string name;
    string address;
    string email;

public:
    Member(const string& n, const string& a, const string& e)
        : memberID(++memberIDCounter), name(n), address(a), email(e) {}

    int getMemberID() const { return memberID; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getEmail() const { return email; }

    void displayDetails() const {
        cout << "Member ID: " << memberID << "\nName: " << name << "\nAddress: " << address << "\nEmail: " << email << endl;
    }
};

int Member::memberIDCounter = 0;

class Book {
protected:
    static int bookIDCounter;
    int bookID;
    string bookName;
    string author;
    string type;
    int pageCount;
    int memberID;
    string dueDate;

public:
    Book(const string& name, const string& author, const string& type, int pageCount)
        : bookID(++bookIDCounter), bookName(name), author(author), type(type), pageCount(pageCount), memberID(0), dueDate("") {}

    int getBookID() const { return bookID; }
    string getBookName() const { return bookName; }
    string getAuthor() const { return author; }
    string getType() const { return type; }
    int getPageCount() const { return pageCount; }
    int getMemberID() const { return memberID; }
    string getDueDate() const { return dueDate; }

    void displayDetails() const {
        cout << "Book ID: " << bookID << "\nName: " << bookName << "\nAuthor: " << author
            << "\nType: " << type << "\nPage Count: " << pageCount << "\nMember ID: " << memberID << "\nDue Date: " << dueDate << endl;
    }

    virtual int calculateFine() const {
        // Default implementation for the base class
        return 0;
    }

    void borrowBook(int memberId, const string& dueDate) {
        this->memberID = memberId;
        this->dueDate = dueDate;
    }

    void returnBook() {
        memberID = 0;
        dueDate = "";
    }
};

int Book::bookIDCounter = 0;

class ScienceFictionBook : public Book {
public:
    ScienceFictionBook(const string& name, const string& author, int pageCount)
        : Book(name, author, "Science Fiction", pageCount) {}

    // Override displayDetails method if needed...

    int calculateFine() const override {
        // Implement fine calculation for Science Fiction books
        return 0; // Placeholder
    }
};

// Add more derived classes for other book types...

class Librarian {
private:
    vector<Book*> books;
    vector<Member> members;

public:
    void addMember(const Member& member) {
        members.push_back(member);
        cout << "New member added:\n";
        member.displayDetails();
    }

    void addBook(Book* book) {
        books.push_back(book);
        cout << "New book added:\n";
        book->displayDetails();
    }

    void issueBook(int bookID, int memberID) {
        auto bookIt = find_if(books.begin(), books.end(),
            [bookID](const Book* book) { return book->getBookID() == bookID && book->getMemberID() == 0; });

        auto memberIt = find_if(members.begin(), members.end(),
            [memberID](const Member& member) { return member.getMemberID() == memberID; });

        if (bookIt != books.end() && memberIt != members.end()) {
            time_t now = time(0);
            struct tm dueDateStruct = *localtime(&now);
            dueDateStruct.tm_mday += 3;
            char dueDate[11];
            strftime(dueDate, sizeof(dueDate), "%Y-%m-%d", &dueDateStruct);

            (*bookIt)->borrowBook(memberID, dueDate);
            cout << "Book issued to member ID: " << memberID << " with due date: " << dueDate << endl;
        } else {
            cerr << "Book or member not found or book already borrowed." << endl;
        }
    }

    void returnBook(int bookID) {
        auto bookIt = find_if(books.begin(), books.end(),
            [bookID](const Book* book) { return book->getBookID() == bookID && book->getMemberID() != 0; });

        if (bookIt != books.end()) {
            (*bookIt)->returnBook();
            int fine = (*bookIt)->calculateFine();
            if (fine > 0) {
                cout << "Fine for overdue book: £" << fine << endl;
            }
            cout << "Book returned." << endl;
        } else {
            cerr << "Book not found or not borrowed." << endl;
        }
    }

    void displayBorrowedBooks(int memberID) const {
        cout << "Books borrowed by member ID: " << memberID << endl;
        for (const Book* book : books) {
            if (book->getMemberID() == memberID) {
                book->displayDetails();
                cout << "---------------------" << endl;
            }
        }
    }

    void displayAllMembers() const {
        cout << "All Members:" << endl;
        for (const Member& member : members) {
            member.displayDetails();
            cout << "---------------------" << endl;
        }
    }

    void displayAvailableBooks() const {
        cout << "Available Books:" << endl;
        for (const Book* book : books) {
            if (book->getMemberID() == 0) {
                book->displayDetails();
                cout << "---------------------" << endl;
            }
        }
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\nMenu:\n"
                << "1. Add a member\n"
                << "2. Add a book\n"
                << "3. Issue a book\n"
                << "4. Return a book\n"
                << "5. Display all books borrowed by a member\n"
                << "6. Display available books\n"
                << "7. Display all members\n"
                << "0. Exit\n"
                << "Enter your choice: ";

            cin >> choice;

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
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cerr << "Invalid choice! Please try again.\n";
            }
        } while (choice != 0);
    }

    Member createMember() {
        // Implement code to create a new member
        string name, address, email;
        cout << "Enter member name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter member address: ";
        getline(cin, address);
        cout << "Enter member email: ";
        getline(cin, email);
        return Member(name, address, email);
    }

    Book* createBook() {
        // Implement code to create a new book
        string name, author, type;
        int pageCount;
        cout << "Enter book name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter book author: ";
        getline(cin, author);
        cout << "Enter book type: ";
        getline(cin, type);
        cout << "Enter book page count: ";
        cin >> pageCount;
        return createBookByType(type, name, author, pageCount);
    }

    Book* createBookByType(const string& type, const string& name, const string& author, int pageCount) {
        // Create book based on type
        if (type == "Science Fiction") {
            return new ScienceFictionBook(name, author, pageCount);
        }
        // Add more conditions for other book types...

        cerr << "Invalid book type. Creating a default book." << endl;
        return new Book(name, author, "Default", pageCount);
    }

    void issueBook() {
        int bookID, memberID;
        cout << "Enter Book ID to issue: ";
        cin >> bookID;
        cout << "Enter Member ID to issue to: ";
        cin >> memberID;
        issueBook(bookID, memberID);
    }

    void returnBook() {
        int bookID;
        cout << "Enter Book ID to return: ";
        cin >> bookID;
        returnBook(bookID);
    }

    void displayBorrowedBooks() {
        int memberID;
        cout << "Enter Member ID: ";
        cin >> memberID;
        displayBorrowedBooks(memberID);
    }
};

int main() {
    Librarian librarian;
    librarian.displayMenu();

    return 0;
}
