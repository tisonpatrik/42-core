#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon
{
private:
    std::string type;

public:
    explicit Weapon(const std::string &type);

    const std::string &getType(void) const;
    void setType(const std::string &type);
};

#endif
