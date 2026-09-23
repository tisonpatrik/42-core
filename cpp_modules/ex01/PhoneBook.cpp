#include "PhoneBook.hpp"

#include <iostream>
#include <sstream>

PhoneBook::PhoneBook()
    : contactCount(0), nextIndex(0)
{
}

void PhoneBook::addContact()
{
    if (!contacts[nextIndex].input())
        return;

    nextIndex = (nextIndex + 1) % 8;

    if (contactCount < 8)
        contactCount++;
}

void PhoneBook::searchContacts() const
{
    if (contactCount == 0)
    {
        std::cout << "PhoneBook is empty." << std::endl;
        return;
    }

    for (int i = 0; i < contactCount; i++)
        contacts[i].displayRow(i);

    std::cout << "Index: ";

    std::string input;
    int index;

    std::getline(std::cin, input);
    std::stringstream stream(input);

    if (!(stream >> index) || index < 0 || index >= contactCount)
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    contacts[index].displayDetails();
}
