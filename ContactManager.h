#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H
#include "Contact.h"
#include <memory>

class ContactManager {
public:
	static ContactManager* GetInstance();
	void run();
private:
	void showMenu();
	void addContact();
	Contact getContact();
	void viewContacts();
	std::unique_ptr<Contact> searchContact(const std::string& searchKey);
	void editContact(int editID);
	void deleteContact(int deleteID);


	int getInputID();
	ContactManager() {}
	ContactManager(const ContactManager&) = delete;
	ContactManager& operator=(const ContactManager&) = delete;


	static ContactManager* s_manager;
};

#endif