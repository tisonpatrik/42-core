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
        ungetc(c,f);
        return 0;
    }
    else {
        return -1;
    }
}

int match_char(FILE *f, char expected)
{
    int c = fgetc(f);
    if ( c == EOF)
        return 0;

    if ( c == expected)
        return 1;

    if (c != EOF)
    {
        ungetc(c,f);
    }
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);

    if ( c == EOF)
        return 0;

    char* ptr = va_arg(ap, char*);
    *ptr = (char)c;

    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int c = fgetc(f);

    if (c == EOF || isspace(c))
    {
        if (c != EOF)
            ungetc(c,f);
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

    if(c != EOF)
    {
        ungetc(c,f);
    }

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

    while ( c != EOF && isdigit(c))
    {
        result = result * 10 + (c - '0');
        c = fgetc(f);
    }
    result = result * sign;
    if ( c != EOF)
    {
        ungetc(c, f);
    }
    int *ptr = va_arg(ap, int* );
    *ptr = (int)result;
    return 1;
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


#include <string.h>

/* Helper function to simulate stdin using a local file */
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
    printf("=== RUNNING STRICT FT_SCANF TESTS ===\n\n");

    /*
     * TEST 1: Strict check for scan_char (incorrect ungetc)
     * Input: "A B"
     * Format: "%c %c"
     */
    setup_stdin("A B");
    char c1 = 0, c2 = 0;
    int ret1 = ft_scanf("%c %c", &c1, &c2);

    int passed1 = (ret1 == 2 && c1 == 'A' && c2 == 'B');
    printf("[TEST 1: scan_char ungetc check]\n");
    printf("Expected -> ret: 2 | c1: A | c2: B\n");
    printf("Actual   -> ret: %d | c1: %c | c2: %c\n", ret1, c1, c2);
    printf("Result   -> %s\n\n", passed1 ? "PASSED" : "FAILED");


    /*
     * TEST 2: Strict check for scan_int math and ungetc
     * Input: "42hello"
     * Format: "%d%s"
     */
    setup_stdin("42hello");
    int d2 = 0;
    char s2[100] = {0};
    int ret2 = ft_scanf("%d%s", &d2, s2);

    // CRITICAL FIX: Now strictly checks both the exact number AND the full string
    int passed2 = (ret2 == 2 && d2 == 42 && strcmp(s2, "hello") == 0);
    printf("[TEST 2: scan_int math and ungetc check]\n");
    printf("Expected -> ret: 2 | d: 42 | s: hello\n");
    printf("Actual   -> ret: %d | d: %d | s: %s\n", ret2, d2, s2);
    printf("Result   -> %s\n\n", passed2 ? "PASSED" : "FAILED");


    /*
     * TEST 3: Strict check for scan_int validation
     * Input: "-A"
     * Format: "%d"
     */
    setup_stdin("-A");
    int d3 = 999;
    int ret3 = ft_scanf("%d", &d3);

    int passed3 = (ret3 == 0 && d3 == 999);
    printf("[TEST 3: scan_int validation check]\n");
    printf("Expected -> ret: 0 | d: 999\n");
    printf("Actual   -> ret: %d | d: %d\n", ret3, d3);
    printf("Result   -> %s\n\n", passed3 ? "PASSED" : "FAILED");


    /*
     * BONUS TEST 4: Edge case with multiple spaces and mixed signs
     * Input: "   +100   stop   K"
     * Format: " %d %s %c"
     */
    setup_stdin("   +100   stop   K");
    int d4 = 0;
    char s4[100] = {0};
    char c4 = 0;
    int ret4 = ft_scanf(" %d %s %c", &d4, s4, &c4);

    int passed4 = (ret4 == 3 && d4 == 100 && strcmp(s4, "stop") == 0 && c4 == 'K');
    printf("[BONUS TEST 4: Mixed formatting and spacing]\n");
    printf("Expected -> ret: 3 | d: 100 | s: stop | c: K\n");
    printf("Actual   -> ret: %d | d: %d | s: %s | c: %c\n", ret4, d4, s4, c4);
    printf("Result   -> %s\n", passed4 ? "PASSED" : "FAILED");

    return 0;
}
