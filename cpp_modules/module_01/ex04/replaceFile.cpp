#include "replaceFile.hpp"

#include <fstream>
#include <iostream>

static bool reportError(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
    return false;
}

bool replaceFile(const std::string &filename, const std::string &s1,
                 const std::string &s2)
{
    if (filename.empty())
        return reportError("the filename must not be empty.");
    if (s1.empty())
        return reportError("the search string must not be empty.");

    std::ifstream input(filename.c_str(), std::ios::binary);
    if (!input.is_open())
        return reportError("cannot open input file '" + filename + "'.");

    std::string content;
    char buffer[4096];
    while (input)
    {
        input.read(buffer, sizeof(buffer));
        content.append(buffer,
                       static_cast<std::string::size_type>(input.gcount()));
    }
    if (input.bad() || !input.eof())
        return reportError("cannot read input file '" + filename + "'.");

    const std::string outputName = filename + ".replace";
    std::ofstream output(outputName.c_str(), std::ios::binary | std::ios::trunc);
    if (!output.is_open())
        return reportError("cannot open output file '" + outputName + "'.");

    std::string::size_type position = 0;
    std::string::size_type match = content.find(s1, position);
    while (match != std::string::npos)
    {
        output << content.substr(position, match - position) << s2;
        position = match + s1.size();
        match = content.find(s1, position);
    }
    output << content.substr(position);

    // Closing flushes buffered data, so delayed write errors are checked too.
    output.close();
    if (!output)
        return reportError("cannot write output file '" + outputName + "'.");

    return true;
}
