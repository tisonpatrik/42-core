#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    while((c= fgetc(f))!= EOF)
    {
        if(!isspace(c))
        {
            ungetc(c, f);
            return 0;
        }
    }
    return (-1);
}

int match_char(FILE *f, char c)
{
    int input = fgetc(f);

    if(input == EOF)
        return -1;

    if (input == c)
        return 1;

    ungetc(input, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    char c = fgetc(f);
    if (c == EOF)
        return -1;
    *ptr = (char)c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int *ptr = va_arg(ap, int *);
    long result = 0;
    int sign = 1;
    int c = fgetc(f);
    int count = 0;

    if(c == '-')
    {
        sign = -1;
        c =fgetc(f);
    }
    else if (c == '+')
        c = fgetc(f);

    while (isdigit(c)) {
        count++;
        result = result *10 +(c - '0');
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);
    if (count==0)
        return 0;

    *ptr = (int)(result*sign);

    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    int c = fgetc(f);
    int count =0;
    while(c != EOF && !isspace(c))
    {
        *ptr = (char)c;
        ptr++;
        count++;
        c = fgetc(f);
    }
    if (c != EOF)
    {
        ungetc(c, f);
    }
    *ptr = '\0';
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

#include <assert.h>
#include <string.h>

// Helper to mock stdin with a string
void prepare_input(const char *input_str) {
    FILE *f = fopen("test_input.txt", "w");
    if (!f) {
        perror("Failed to create test file");
        return;
    }
    fprintf(f, "%s", input_str);
    fclose(f);

    // Redirect stdin to read from this file
    freopen("test_input.txt", "r", stdin);
}

void test_simple_string_and_int() {
    printf("Test: Simple String and Int... ");

    // 1. Arrange
    char name[50] = {0}; // Initialize to empty
    int age = 0;
    prepare_input("Karel 25");

    // 2. Act
    int ret = ft_scanf("%s %d", name, &age);

    // 3. Assert
    assert(ret == 2);
    assert(strcmp(name, "Karel") == 0);
    assert(age == 25);

    printf("OK\n");
}

void test_negative_integer() {
    printf("Test: Negative Integer... ");

    // 1. Arrange
    int num = 0;
    prepare_input("-42");

    // 2. Act
    int ret = ft_scanf("%d", &num);

    // 3. Assert
    assert(ret == 1);
    assert(num == -42);

    printf("OK\n");
}

void test_whitespace_skipping() {
    printf("Test: Whitespace Skipping (Int)... ");

    // 1. Arrange
    int num = 0;
    prepare_input("     \t  100"); // Tabs and spaces

    // 2. Act
    int ret = ft_scanf("%d", &num);

    // 3. Assert
    assert(ret == 1);
    assert(num == 100);

    printf("OK\n");
}

void test_multiple_strings() {
    printf("Test: Multiple Strings... ");

    // 1. Arrange
    char s1[20] = {0}, s2[20] = {0};
    prepare_input("Hello World");

    // 2. Act
    int ret = ft_scanf("%s %s", s1, s2);

    // 3. Assert
    assert(ret == 2);
    assert(strcmp(s1, "Hello") == 0);
    assert(strcmp(s2, "World") == 0);

    printf("OK\n");
}

void test_char_reading() {
    printf("Test: Char Reading... ");

    // 1. Arrange
    char c1 = 0, c2 = 0;
    prepare_input("AB");

    // 2. Act
    int ret = ft_scanf("%c%c", &c1, &c2);

    // 3. Assert
    assert(ret == 2);
    assert(c1 == 'A');
    assert(c2 == 'B');

    printf("OK\n");
}

void test_literal_matching() {
    printf("Test: Literal Matching in Format... ");

    // 1. Arrange
    int val = 0;
    // Format expects "Value: ", input provides exactly that
    prepare_input("Value: 99");

    // 2. Act
    // Note: We need to handle the literal "Value:" in format string logic
    // Your current implementation logic needs to support this via match_char
    int ret = ft_scanf("Value: %d", &val);

    // 3. Assert
    assert(ret == 1);
    assert(val == 99);

    printf("OK\n");
}

void test_failure_no_match() {
    printf("Test: Failure (Type Mismatch)... ");

    // 1. Arrange
    int val = 999; // Sentinel value
    prepare_input("Hello"); // String where int is expected

    // 2. Act
    int ret = ft_scanf("%d", &val);

    // 3. Assert
    assert(ret == 0); // Should return 0 conversions
    assert(val == 999); // Value should remain untouched

    printf("OK\n");
}

void test_eof() {
    printf("Test: Empty Input (EOF)... ");

    // 1. Arrange
    int val = 0;
    prepare_input(""); // Empty file

    // 2. Act
    int ret = ft_scanf("%d", &val);

    // 3. Assert
    assert(ret == -1); // Or EOF constant

    printf("OK\n");
}

int main(void) {
    printf("=== RUNNING TESTS ===\n");

    test_simple_string_and_int();
    test_negative_integer();
    test_whitespace_skipping();
    test_multiple_strings();
    test_char_reading();
    test_literal_matching();
    test_failure_no_match();
    test_eof();

    printf("\n=== ALL TESTS PASSED ===\n");
    return 0;
}
