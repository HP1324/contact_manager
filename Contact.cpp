#include "Contact.h"

//Globals
const char DELIM = ';';
const char* const CONTACT_FILE = "contact_data.txt";
std::vector<Contact> contacts = loadContacts();

int Contact::maxID = static_cast<int>(contacts.size());

//Constructors
Contact::Contact() {}
Contact::Contact(const int& id, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber, const std::string emailAddress)
    :id(id), firstName(firstName), lastName(lastName), phoneNumber(phoneNumber), emailAddress(emailAddress) {}
//Destructor
Contact::~Contact() {}
//Contact class methods
void Contact::print() const
{
    std::cout << "   | Name   : " << firstName << ' ' << lastName << "\n"
        << id << "  | Phone  : " << phoneNumber << "\n"
        << "   | Email  : " << emailAddress << "\n\n";
}
std::string Contact::serialize() {
    std::ostringstream serialized;

    serialized << std::to_string(id)
        << DELIM << firstName
        << DELIM << lastName
        << DELIM << phoneNumber
        << DELIM << emailAddress << "\n";
    return serialized.str();
}
Contact Contact::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, DELIM)) {
        tokens.push_back(token);
    }
    return Contact(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4]);
}
void Contact::addToFile(std::ofstream& contactFile) {
    std::string serialized_contact = serialize();
    if (contactFile.is_open()) {
        contactFile << serialized_contact;
    }
    else {
        std::cerr << "file is not open!";
    }
}
//setters
void Contact::setID(int id) { this->id = id; }
void Contact::setFirstName(std::string firstName) { this->firstName = firstName; }
void Contact::setLastName(std::string lastName) { this->lastName = lastName; }
void Contact::setPhone(std::string phoneNumber) { this->phoneNumber = phoneNumber; }
void Contact::setEmail(std::string emailAddress) { this->emailAddress = emailAddress; }
//gettters
int Contact::getID() const { return id; }
std::string Contact::getFirstName()const { return firstName; }
std::string Contact::getLastName() const { return lastName; }
std::string Contact::getPhone()const { return phoneNumber; }
std::string Contact::getEmail()const { return emailAddress; }

//Helper functions
inline void ignoreLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int getInputID() {
    int inputID;
    if (!contacts.empty()) {
        std::cout << "Enter contact ID or 0 if you dont want any change: ";
        while (true)
        {
            std::cin >> inputID;
            if (inputID > 0 && inputID <= static_cast<int>(contacts.size()))
            {
                ignoreLine();
                return inputID;
            }
            else if (inputID == 0) {
                return inputID;
            }
            else {
                std::cout << "Please enter correct ID : ";
            }
        }
    }
    else {
        return -1;
    }
}


//Input functions
std::string takeFirstName() {
    std::string firstName;
    std::regex namePattern("^[A-Za-z\\s-]+$");
    std::cout << "First Name: ";
    while (true) {
        std::getline(std::cin, firstName);
        if (std::regex_match(firstName, namePattern))
            return firstName;
        else std::cout << "Please enter correct name: ";
    }
}
std::string takeLastName() {
    std::string lastName;
    std::regex namePattern("^[A-Za-z\\s-]+$");
    std::cout << "Last Name: ";
    while (true) {
        std::getline(std::cin, lastName);
        if (std::regex_match(lastName, namePattern))
            return lastName;
        else std::cout << "Please enter correct name: ";
    }

}
std::string takePhone() {
    std::string phone;
    std::regex phonePattern("^(?:\\+91|91)?[-\\s]?[7-9]\\d{4}[-\\s]?\\d{5}$");
    std::cout << "Phone: ";
    while (true) {
        std::getline(std::cin, phone);
        if (std::regex_match(phone, phonePattern))
            return phone;
        else std::cout << "Please enter correct phone number: ";
    }
}
std::string takeEmail() {
    std::string email;
    std::regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    std::cout << "Email: ";
    while (true) {
        std::getline(std::cin, email);
        if (std::regex_match(email, emailPattern))
            return email;
        else std::cout << "Please enter correct email: ";
    }
}


//load and save
std::vector<Contact> loadContacts()
{
    std::ifstream readContacts(CONTACT_FILE, std::ios::in);

    std::vector<Contact> contacts;
    if (!readContacts) {
        std::cout << "Can't open the file for reading\n";
        return contacts;
    }
    std::string line;
    while (getline(readContacts, line))
    {
        try {
            Contact contact = Contact::deserialize(line);
            contacts.push_back(contact);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error deserializing line: " << e.what() << '\n';
        }
    }

    readContacts.close();
    return contacts;

}
void saveContacts()
{
    std::ofstream contactFile{ CONTACT_FILE, std::ios::out };
    if (!contactFile)
        std::cout << "File couldn't be opened for writing\n";
    else
    {
        for (Contact c : contacts)
        {
            c.addToFile(contactFile);
        }
    }
    contactFile.close();
}

void printContactsTable() {

    tabulate::Table tab_contacts;
    tab_contacts.add_row({ "ID", "First Name","Last Name", "Phone Number", "Email Address" });
    tab_contacts.format().font_align(tabulate::FontAlign::center);
    for (auto c : contacts) {
        tab_contacts.add_row({ std::to_string(c.getID()), c.getFirstName(),c.getLastName(),c.getPhone(),c.getEmail() });
    }
    std::cout << tab_contacts;
    std::cout << "\n\n";
}