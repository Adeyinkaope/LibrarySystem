// Member.cpp

// Include the corresponding header file for the Member class
#include "Member.hpp"

// Initialize the static member variable for generating unique member IDs
int Member::memberIDCounter = 0;

// Constructor to initialize a Member object with provided details
Member::Member(const std::string& n, const std::string& a, const std::string& e)
    : memberID(++memberIDCounter), name(n), address(a), email(e) {}

// Getter method to retrieve the member's unique ID
int Member::getMemberID() const {
    return memberID;
}

// Getter method to retrieve the member's name
std::string Member::getName() const {
    return name;
}

// Getter method to retrieve the member's address
std::string Member::getAddress() const {
    return address;
}

// Getter method to retrieve the member's email
std::string Member::getEmail() const {
    return email;
}

// Method to display details of the member
void Member::displayDetails() const {
    std::cout << "Member ID: " << memberID << "\nName: " << name << "\nAddress: " << address << "\nEmail: " << email << std::endl;
}
