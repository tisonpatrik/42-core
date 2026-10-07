#include "replaceFile.hpp"
#include "replaceText.hpp"

#include <fstream>
#include <stdexcept>

static void validateArguments(const std::string &filename,
                              const std::string &search)
{
    if (filename.empty())
        throw std::invalid_argument("the filename must not be empty.");
    if (search.empty())
        throw std::invalid_argument("the search string must not be empty.");
}

static std::string readFile(const std::string &filename)
{
    std::ifstream input(filename.c_str(), std::ios::binary);
    if (!input.is_open())
        throw std::runtime_error("cannot open input file '" + filename + "'.");

    std::string content;
    char buffer[4096];
    while (input)
    {
        input.read(buffer, sizeof(buffer));
        content.append(buffer,
                       static_cast<std::string::size_type>(input.gcount()));
    }
    if (input.bad() || !input.eof())
        throw std::runtime_error("cannot read input file '" + filename + "'.");
    return content;
}

static void writeFile(const std::string &filename, const std::string &content)
{
    std::ofstream output(filename.c_str(), std::ios::binary | std::ios::trunc);
    if (!output.is_open())
        throw std::runtime_error("cannot open output file '" + filename + "'.");

    output << content;
    // Closing flushes buffered data, so delayed write errors are checked too.
    output.close();
    if (!output)
        throw std::runtime_error("cannot write output file '" + filename + "'.");
}

void replaceFile(const std::string &filename, const std::string &search,
                 const std::string &replacement)
{
    validateArguments(filename, search);
    const std::string content = readFile(filename);
    const std::string result = replaceText(content, search, replacement);
    writeFile(filename + ".replace", result);
}
