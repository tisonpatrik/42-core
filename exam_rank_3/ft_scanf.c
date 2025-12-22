#include <__stdarg_va_list.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;

    while (isspace(c = fgetc(f)))
    {
    }

    if (c != EOF)
    {
        ungetc(c, f);
    }

    return (0);
}

int match_char(FILE *f, char expected)
{
    int c;

    while (isspace(c = fgetc(f)))
    {
    }

    if (c == EOF)
        return (0);

    if (c == expected)
    {
        return (1);
    }
    else
    {
        ungetc(c, f);
        return (0);
    }
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);

    int ret = ft_vfscanf(stdin, format, ap);

    va_end(ap);

    return ret;
}


int main(void) {
    int age;
    char name[20]; // Buffer for string

    printf("Enter name and age (e.g., Karel 25): ");

    // We expect 2 items: a string (max 19 chars) and an integer
    // Note: 'name' is an array, so no '&' needed. 'age' needs '&'.
    int result = ft_scanf("%19s %d", name, &age);

    // Check the return value
    if (result == 2) {
        printf("Success! Name: %s, Age: %d\n", name, age);
    }
    else if (result == 1) {
        printf("Partial success: Name read, but age missing or invalid.\n");
    }
    else if (result == EOF) {
        printf("Error: End of input or read error.\n");
    }
    else {
        printf("No match found (input didn't start with a string?).\n");
    }

    return 0;
}
