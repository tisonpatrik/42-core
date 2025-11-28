#ifndef FT_STRTOI_H
#define FT_STRTOI_H

#include <limits.h>

typedef struct s_parse_result
{
	unsigned int	accumulated_value;
	int				overflow_detected;
	int				digits_found;
}					t_parse_result;

int					ft_strtoi10(const char *nptr, char **endptr);
unsigned int		calculate_cutoff(int is_negative);
unsigned int		calculate_cutlim(unsigned int *cutoff_value);
void				set_endptr(char **end_pointer,
						const char *original_string_start,
						const char *current_position, int digits_found);
int					would_overflow(unsigned int current_accumulated,
						unsigned int overflow_threshold,
						unsigned int last_digit_limit,
						unsigned int current_digit);
int					handle_overflow(int is_negative);

#endif
