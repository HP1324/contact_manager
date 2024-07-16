
#include "ContactManager.h"
void ContactManager::run() {
    showMenu();
    int input;
    int inputID;

    do
    {
        std::cin >> input;
        ignoreLine();
        switch (input)
        {
        case 1:
        {
            addContact();
            showMenu();
            break;
        }
        case 2:
            viewContacts();
            showMenu();
            break;
        case 3:
        {
            std::string searchKey;

            std::cout << "Enter one of the following to search \n (First Name, Last Name, Phone Number, Email Address): ";
            std::getline(std::cin, searchKey);
            std::unique_ptr<Contact> found = searchContact(searchKey);
            if (found) {
                std::cout << "Contact found!!\n";
                found->print();
            }
            else
            {
                std::cout << "Contact not found!\n";
            }
            showMenu();
            break;
        }
        case 4:
        {
            viewContacts();
            inputID = getInputID();
            if (inputID != -1 && inputID != 0)deleteContact(inputID);
            showMenu();
            break;
        }
        case 5:
            viewContacts();
            inputID = getInputID();
            if (inputID != -1 && inputID != 0) editContact(inputID);
            showMenu();
            break;
        case 6:
            std::cout << "Exiting...";
            break;
        default:
            std::cout << "Invalid Input! try again!! : ";
            break;
        }

    } while (input != 6);

    saveContacts();

}
ContactManager* ContactManager::s_manager = nullptr;
ContactManager* ContactManager::GetInstance() {
    if (s_manager == nullptr) { s_manager = new ContactManager; }
    return s_manager;
}
void ContactManager::showMenu()
{
    tabulate::Table root_table;
    tabulate::Table menu_table;

    root_table.add_row({ "Contact Book Menu" }).format().font_align(tabulate::FontAlign::center);

    menu_table.add_row({ "Index" , "Options" });
    menu_table.add_row({ "1","Add Contacts" });
    menu_table.add_row({ "2","View Contacts" });
    menu_table.add_row({ "3","Search Contacts" });
    menu_table.add_row({ "4","Delete Contact" });
    menu_table.add_row({ "5","Edit Contact" });
    menu_table.add_row({ "6","Exit" });


    root_table.format().
        corner_color(tabulate::Color::cyan).
        border_color(tabulate::Color::cyan).
        font_color(tabulate::Color::yellow);

    menu_table.column(0).format().
        font_align(tabulate::FontAlign::center);

    root_table.add_row({ menu_table });

    std::cout << root_table << '\n';
    std::cout << "Please choose an option(1-6): ";
}
//Contact management functions
void ContactManager::addContact()
{
    Contact contact = getContact();
    std::cout << "Contact added successfully\n";
    ++Contact::maxID;
    contact.setID(Contact::maxID);
    contacts.push_back(contact);

}
Contact ContactManager::getContact() {
    Contact contact;
    contact.setFirstName(takeFirstName());
    contact.setLastName(takeLastName());
    contact.setPhone(takePhone());
    contact.setEmail(takeEmail());
    return contact;
}
void ContactManager::viewContacts()
{
    if (contacts.empty())
        std::cout << "Contact list empty! add some contacts first\n";
    else
    {
        printContactsTable();
    }
}
std::unique_ptr<Contact> ContactManager::searchContact(const std::string& searchKey) {
    for (const auto& c : contacts)
    {
        if (searchKey == c.getFirstName()
            || searchKey == c.getLastName()
            || searchKey == c.getPhone()
            || searchKey == c.getEmail())
        {
            return std::make_unique<Contact>(c);
        }
    }
    return nullptr;
}
void ContactManager::editContact(int editID)
{
    int index = editID - 1;
    std::cout << "Editing contact " << editID << '\n';
    contacts[index].print();
    Contact editedContact = getContact();
    editedContact.setID(contacts.at(index).getID());
    contacts[index] = editedContact;
}
void ContactManager::deleteContact(int deleteID)
{

    int index = deleteID - 1;
    std::cout << "Deleting cotact " << deleteID << "...\n";
    auto it = contacts.erase(contacts.begin() + (index));
    std::cout << "Contact " << deleteID << " deleted succesfully!\n";
    std::cout << "\nContact in the list: " << contacts.size() << "\n\n";
    //decrement ids of elements that followed the deleted element by one
    //it points to the element followed by the deleted element, now in
    //place of the deleted element
    while (it != contacts.end()) {
        //--it->getID(); //not valid
        it->setID(it->getID() - 1);
        ++it;
    }
    //set it to vector size after deleting a contact to maintain id continuously
    //because not doing it will increment id just further and jump ids(e.g.3 after 1)
    Contact::maxID = static_cast<int> (contacts.size());

}


int ContactManager::getInputID() {
    int inputID;
    if (!contacts.empty())
    {
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
    else
    {
        return -1;
    }
}


