/**
 * @brief Check if character is a whitespace character
 *
 * This function checks if the given character is a whitespace character.
 * It mimics the behavior of the standard isspace function.
 * Returns non-zero for space, tab, newline, carriage return, vertical tab, and form feed.
 *
 * @param c The character to test
 * @return Non-zero if character is whitespace, zero otherwise
 */
int ft_isspace(int c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}