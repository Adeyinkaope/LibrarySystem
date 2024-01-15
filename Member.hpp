// Member.h

// Header guards to prevent multiple inclusions of the same header file
#ifndef Member_hpp
#define Member_hpp

#include <iostream>
#include <string>

class Member {
private:
    static int memberIDCounter;  // A static counter for generating unique member IDs
    int memberID;   // Unique identifier for each member
    std::string name;   // Member's name
    std::string address;  // Member's address
    std::string email;   // Member's email

public:
// Constructor to initialize a Member object with the provided details
    Member(const std::string& n, const std::string& a, const std::string& e);
     // method to retrieve member attributes
    int getMemberID() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getEmail() const;

    void displayDetails() const;
};

#endif // MEMBER_H
