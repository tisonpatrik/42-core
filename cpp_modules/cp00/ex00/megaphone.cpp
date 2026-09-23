#include <iostream>
#include <cctype>

void printUppercase(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        std::cout << static_cast<char>(
            std::toupper(static_cast<unsigned char>(str[i]))
        );
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return 0;
    }

    for (int i = 1; i < argc; ++i)
        printUppercase(argv[i]);

    std::cout << std::endl;
    return 0;
}
