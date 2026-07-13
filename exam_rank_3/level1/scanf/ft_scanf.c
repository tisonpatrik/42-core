#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    while((c = fgetc(f)) != EOF && isspace(c))
        ;
    if(c != EOF)
    {
        ungetc(c, f);
        return 0;
    }
    else {
        return -1;
    }
}

int match_char(FILE *f, char expected)
{
    int c = fgetc(f);
    if ( c == expected )
    {
        return 1;
    }
    if (c != EOF)
        ungetc(c, f);

    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if (c == EOF)
        return 0;

    char *ptr = va_arg(ap, char*);
    *ptr = (char)c;

    return (1);
}


int scan_string(FILE *f, va_list ap)
{
    int c = fgetc(f);

    if (c == EOF || isspace(c))
    {
        if (c != EOF)
        {
            ungetc(c, f);
        }
        return 0;
    }

    int i = 0;
    char *ptr = va_arg(ap, char*);
    while(c != EOF && !isspace(c))
    {
        ptr[i] = (char)c;
        c = fgetc(f);
        i++;
    }
    ptr[i] = '\0';
    if (c != EOF)
        ungetc(c, f);

    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int c = fgetc(f);

    if (c == EOF)
        return 0;

    int sign = 1;
    if (c == '-' || c == '+')
    {
        if (c == '-')
            sign = -1;
        c = fgetc(f);
    }

    if (!isdigit(c))
    {
        if (c != EOF)
            ungetc(c, f);
        return 0;
    }

    int result = 0;

    while( c != EOF && isdigit(c))
    {
        result = result*10+(c - '0');
        c = fgetc(f);
    }

    if (c != EOF)
        ungetc(c, f);

    result = result * sign;

    int *ptr = va_arg(ap, int*);
    *ptr = (int)result;

    return (1);
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

void setup_stdin(const char *text)
{
    FILE *f = fopen("test_input.txt", "w");
    if (f)
    {
        fprintf(f, "%s", text);
        fclose(f);
    }
    freopen("test_input.txt", "r", stdin);
}

int main(void)
{
    printf("=== RUNNING ADVANCED FT_SCANF TESTS ===\n\n");

    /*
     * TEST 1: Exposes the bug in scan_char (incorrect ungetc)
     * Input: "A B"
     * Format: "%c %c"
     * Expected behavior: c1 = 'A', c2 = 'B', ret = 2
     * Buggy behavior:    c1 = 'A', c2 = 'A' (because 'A' was pushed back)
     */
    setup_stdin("A B");
    char c1 = 0, c2 = 0;
    int ret1 = ft_scanf("%c %c", &c1, &c2);
    printf("[TEST 1: scan_char ungetc check]\n");
    printf("Expected -> ret: 2 | c1: A | c2: B\n");
    printf("Actual   -> ret: %d | c1: %c | c2: %c\n", ret1, c1, c2);
    printf("%s\n\n", (c1 == 'A' && c2 == 'B') ? "PASSED" : "FAILED");


    /*
     * TEST 2: Exposes the bug in scan_int (missing ungetc on terminator)
     * Input: "42hello" (no space between number and string)
     * Format: "%d%s"
     * Expected behavior: d2 = 42, s2 = "hello", ret = 2
     * Buggy behavior:    d2 = 42, s2 = "ello"  (the 'h' character is lost forever)
     */
    setup_stdin("42hello");
    int d2 = 0;
    char s2[100] = {0};
    int ret2 = ft_scanf("%d%s", &d2, s2);
    printf("[TEST 2: scan_int missing ungetc check]\n");
    printf("Expected -> ret: 2 | d: 42 | s: hello\n");
    printf("Actual   -> ret: %d | d: %d | s: %s\n", ret2, d2, s2);
    printf("%s\n\n", (ret2 == 2 && s2[0] == 'h') ? "PASSED" : "FAILED");


    /*
     * TEST 3: Exposes the bug in scan_int (broken validation condition)
     * Input: "-A" (invalid integer input)
     * Format: "%d"
     * Expected behavior: ret = 0, d3 = 999 (remains unchanged)
     * Buggy behavior:    ret = 1, d3 = 0     (incorrectly claims success)
     */
    setup_stdin("-A");
    int d3 = 999;
    int ret3 = ft_scanf("%d", &d3);
    printf("[TEST 3: scan_int broken validation check]\n");
    printf("Expected -> ret: 0 | d: 999\n");
    printf("Actual   -> ret: %d | d: %d\n", ret3, d3);
    printf("%s\n", (ret3 == 0 && d3 == 999) ? "PASSED" : "FAILED");

    return 0;
}
