#ifndef REPLACETEXT_HPP
#define REPLACETEXT_HPP

#include <string>

// Replaces non-overlapping matches in the original text. Search must not be empty.
std::string replaceText(const std::string &content, const std::string &search,
                        const std::string &replacement);

#endif
