#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
class ClapTrap
{
    private:
        std::string name;
        static const int hitPoints = 10;
        static const int energyPoints = 10;
        static const int attack_damage = 0;

    public:
        ClapTrap(void);
        ClapTrap(std::string name);
        ClapTrap(const ClapTrap &other);
        ClapTrap &operator=(const ClapTrap &other);
        ~ClapTrap(void);

        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif
