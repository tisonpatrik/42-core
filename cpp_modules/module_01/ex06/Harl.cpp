#include "Harl.hpp"

#include <cstddef>
#include <iostream>

void Harl::debug(void)
{
    std::cout << "[ DEBUG ]\n"
              << "I love having extra bacon for my "
              << "7XL-double-cheese-triple-pickle-special-ketchup burger.\n"
              << "I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "[ INFO ]\n"
              << "I cannot believe adding extra bacon costs more money.\n"
              << "You didn't put enough bacon in my burger!\n"
              << "If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << "[ WARNING ]\n"
              << "I think I deserve to have some extra bacon for free.\n"
              << "I've been coming for years, whereas you started working here "
              << "just last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "[ ERROR ]\n"
              << "This is unacceptable! I want to speak to the manager now."
              << std::endl;
}

void Harl::complain(std::string level)
{
    const std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    const std::size_t count = sizeof(levels) / sizeof(levels[0]);
    std::size_t index = 0;
    while (index < count && level != levels[index])
        ++index;

    switch (index)
    {
        case 0:
            debug();
            // fall through
        case 1:
            info();
            // fall through
        case 2:
            warning();
            // fall through
        case 3:
            error();
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]"
                      << std::endl;
            break;
    }
}
