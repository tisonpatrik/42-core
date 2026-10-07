#include "replaceFile.hpp"

#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>"
                  << std::endl;
        return 1;
    }

    try
    {
        replaceFile(argv[1], argv[2], argv[3]);
    }
    catch (const std::exception &error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
