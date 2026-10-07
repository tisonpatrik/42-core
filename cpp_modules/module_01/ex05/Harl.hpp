#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl
{
private:
    typedef void (Harl::*ComplaintHandler)(void);

    struct Complaint
    {
        const char *level;
        ComplaintHandler handler;
    };

    static const Complaint complaints[];

    void debug(void);
    void info(void);
    void warning(void);
    void error(void);

public:
    void complain(std::string level);
};

#endif
