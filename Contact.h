#ifndef CONTACT_H
#define CONTACT_H

#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <vector>

#include <tabulate/table.hpp>

class Contact;

void saveContacts();
std::vector<Contact> loadContacts();
void printContactsTable();
extern const char DELIM;
extern const char* const CONTACT_FILE;


extern std::vector<Contact> contacts;


std::string takeFirstName();
std::string takeLastName();
std::string takePhone();
std::string takeEmail();


inline void ignoreLine();
class Contact
{
private:
    int id = 0;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string emailAddress;

public:
    static int maxID;

    Contact();
    Contact(const int& id, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber, const std::string emailAddress);
    ~Contact();


    void setID(int id);
    void setFirstName(std::string firstName);
    void setLastName(std::string lastName);
    void setPhone(std::string phoneNumber);
    void setEmail(std::string emailAddress);

    int getID()const;
    std::string getFirstName()const;
    std::string getLastName()const;
    std::string getPhone()const;
    std::string getEmail()const;

    void addToFile(std::ofstream& contactFile);
    void print() const;
    std::string serialize();
    static Contact deserialize(const std::string& line);



};

#endif

