#include "ft_printf.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include "io.h"
#include "str.h"

static int	print_unsigned(uintmax_t value, unsigned int base, bool uppercase)
{
	const char	*digits;
	char		buffer[32];
	int			length;
	int			count;

	digits = "0123456789abcdef";
	if (uppercase)
		digits = "0123456789ABCDEF";
	length = 0;
	if (value == 0)
		buffer[length++] = '0';
	while (value > 0)
	{
		buffer[length++] = digits[value % base];
		value /= base;
	}
	count = length;
	while (length > 0)
		ft_putchar_fd(buffer[--length], STDOUT_FILENO);
	return (count);
}

static int	print_signed(int value)
{
	long long	number;

	number = value;
	if (number < 0)
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		return (1 + print_unsigned((uintmax_t)(-number), 10, false));
	}
	return (print_unsigned((uintmax_t)number, 10, false));
}

static int	print_pointer(void *pointer)
{
	if (!pointer)
	{
		ft_putstr_fd("(nil)", STDOUT_FILENO);
		return (5);
	}
	ft_putstr_fd("0x", STDOUT_FILENO);
	return (2 + print_unsigned((uintptr_t)pointer, 16, false));
}

static int	dispatch_conversion(char type, va_list args)
{
	char	*string;

	if (type == 'c')
		return (ft_putchar_fd((char)va_arg(args, int), STDOUT_FILENO), 1);
	if (type == 's')
	{
		string = va_arg(args, char *);
		if (!string)
			string = "(null)";
		return (ft_putstr_fd(string, STDOUT_FILENO), (int)ft_strlen(string));
	}
	if (type == 'p')
		return (print_pointer(va_arg(args, void *)));
	if (type == 'd' || type == 'i')
		return (print_signed(va_arg(args, int)));
	if (type == 'u')
		return (print_unsigned(va_arg(args, unsigned int), 10, false));
	if (type == 'x' || type == 'X')
		return (print_unsigned(va_arg(args, unsigned int), 16, type == 'X'));
	if (type == '%')
		return (ft_putchar_fd('%', STDOUT_FILENO), 1);
	ft_putchar_fd('%', STDOUT_FILENO);
	ft_putchar_fd(type, STDOUT_FILENO);
	return (2);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total;

	if (!format)
		return (-1);
	total = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && format[1])
		{
			total += dispatch_conversion(format[1], args);
			format += 2;
		}
		else
		{
			ft_putchar_fd(*format++, STDOUT_FILENO);
			total++;
		}
	}
	va_end(args);
	return (total);
}
