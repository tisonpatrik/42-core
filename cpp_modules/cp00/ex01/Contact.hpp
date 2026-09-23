#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

    std::string readField(const std::string &prompt);
    std::string formatField(const std::string &value) const;

public:
    bool input();
    void displayRow(int index) const;
    void displayDetails() const;
};

#endif
