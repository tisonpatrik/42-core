#include "Harl.hpp"

#include <cstddef>
#include <iostream>

void Harl::debug(void)
{
    std::cout << "I love having extra bacon for my "
              << "7XL-double-cheese-triple-pickle-special-ketchup burger. "
              << "I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "I cannot believe adding extra bacon costs more money. "
              << "You didn't put enough bacon in my burger! "
              << "If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << "I think I deserve to have some extra bacon for free. "
              << "I've been coming for years, whereas you started working here "
              << "just last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "This is unacceptable! I want to speak to the manager now."
              << std::endl;
}

void Harl::complain(std::string level)
{
    const std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    typedef void (Harl::*Complaint)(void);
    const Complaint complaints[] = {
        &Harl::debug, &Harl::info, &Harl::warning, &Harl::error
    };

    for (std::size_t i = 0; i < sizeof(levels) / sizeof(levels[0]); ++i)
    {
        if (level == levels[i])
        {
            (this->*complaints[i])();
            return;
        }
    }
}
