#include "ClapTrap.hpp"

#include <climits>
#include <iostream>

static void printTitle(const std::string &title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main(void)
{
    printTitle("Basic actions");
    {
        ClapTrap clap("Clappy");

        clap.attack("a target dummy");
        clap.takeDamage(3);
        clap.beRepaired(2);
    }

    printTitle("Out of energy: the 11th action must fail");
    {
        ClapTrap clap("Tired");

        for (int i = 0; i < 10; i++)
            clap.attack("a target dummy");
        clap.attack("a target dummy");
        clap.beRepaired(1);
        std::cout << "-- taking damage costs no energy, so it still works:"
                  << std::endl;
        clap.takeDamage(1);
    }

    printTitle("Out of hit points: nothing else may work");
    {
        ClapTrap clap("Fragile");

        clap.takeDamage(25);
        clap.attack("a target dummy");
        clap.beRepaired(5);
        clap.takeDamage(1);
    }

    printTitle("Huge values must not wrap around");
    {
        ClapTrap weak("Weak");
        ClapTrap strong("Strong");

        weak.takeDamage(UINT_MAX);
        strong.beRepaired(UINT_MAX);
    }

    printTitle("Orthodox Canonical Form");
    {
        ClapTrap unnamed;
        ClapTrap original("Original");

        original.takeDamage(4);

        ClapTrap copy(original);
        copy.beRepaired(1);

        unnamed = original;
        unnamed.attack("a target dummy");
        original.attack("a target dummy");
    }
    return 0;
}
