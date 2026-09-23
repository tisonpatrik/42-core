#include "Contact.hpp"

#include <iostream>
#include <iomanip>

std::string Contact::readField(const std::string &prompt)
{
    std::string value;

    while (value.empty())
    {
        std::cout << prompt;

        if (!std::getline(std::cin, value))
            return "";

        if (value.empty())
            std::cout << "Field cannot be empty." << std::endl;
    }

    return value;
}

bool Contact::input()
{
    firstName = readField("First name: ");
    if (firstName.empty())
        return false;

    lastName = readField("Last name: ");
    if (lastName.empty())
        return false;

    nickname = readField("Nickname: ");
    if (nickname.empty())
        return false;

    phoneNumber = readField("Phone number: ");
    if (phoneNumber.empty())
        return false;

    darkestSecret = readField("Darkest secret: ");
    if (darkestSecret.empty())
        return false;

    return true;
}

std::string Contact::formatField(const std::string &value) const
{
    if (value.length() > 10)
        return value.substr(0, 9) + ".";

    return value;
}

void Contact::displayRow(int index) const
{
    std::cout
        << std::setw(10) << index << "|"
        << std::setw(10) << formatField(firstName) << "|"
        << std::setw(10) << formatField(lastName) << "|"
        << std::setw(10) << formatField(nickname)
        << std::endl;
}

void Contact::displayDetails() const
{
    std::cout << "First name: " << firstName << std::endl;
    std::cout << "Last name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone number: " << phoneNumber << std::endl;
    std::cout << "Darkest secret: " << darkestSecret << std::endl;
}
