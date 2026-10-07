#include "replaceText.hpp"

#include <stdexcept>

std::string replaceText(const std::string &content, const std::string &search,
                        const std::string &replacement)
{
    if (search.empty())
        throw std::invalid_argument("the search string must not be empty.");

    std::string result;
    std::string::size_type position = 0;
    std::string::size_type match = content.find(search, position);
    while (match != std::string::npos)
    {
        result.append(content, position, match - position);
        result.append(replacement);
        position = match + search.size();
        match = content.find(search, position);
    }
    result.append(content, position, std::string::npos);
    return result;
}
