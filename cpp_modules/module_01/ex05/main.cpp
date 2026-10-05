#include "Harl.hpp"

#include <cstddef>
#include <iostream>
#include <sstream>

struct ComplaintTest
{
    const char *level;
    const char *expected;
};

static bool testComplaint(Harl &harl, const ComplaintTest &test)
{
    std::ostringstream output;
    std::streambuf *original = std::cout.rdbuf(output.rdbuf());
    harl.complain(test.level);
    std::cout.rdbuf(original);

    if (output.str() != test.expected)
    {
        std::cerr << "[FAIL] Unexpected complaint for level \""
                  << test.level << "\"." << std::endl;
        return false;
    }

    std::cout << "[PASS] level=\"" << test.level << "\"" << std::endl
              << output.str() << std::endl;
    return true;
}

int main()
{
    Harl harl;
    const ComplaintTest tests[] = {
        {"DEBUG", "I love having extra bacon for my "
         "7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!\n"},
        {"INFO", "I cannot believe adding extra bacon costs more money. "
         "You didn't put enough bacon in my burger! "
         "If you did, I wouldn't be asking for more!\n"},
        {"WARNING", "I think I deserve to have some extra bacon for free. "
         "I've been coming for years, whereas you started working here "
         "just last month.\n"},
        {"ERROR", "This is unacceptable! I want to speak to the manager now.\n"},
        {"", ""},
        {"UNKNOWN", ""},
        {"debug", ""},
        {" INFO ", ""}
    };

    bool passed = true;
    for (int round = 0; round < 2; ++round)
    {
        for (std::size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i)
            passed = testComplaint(harl, tests[i]) && passed;
    }

    if (!passed)
        return 1;
    std::cout << "All Harl tests passed." << std::endl;
    return 0;
}
