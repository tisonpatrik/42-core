#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <string>

class PhoneBook
{
private:
    Contact contacts[8];
    int contactCount;
    int nextIndex;

    std::string readField(const std::string &prompt) const;

public:
    PhoneBook();

    void addContact();
    void searchContacts() const;
};

#endif
