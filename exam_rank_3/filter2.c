#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool is_match(char* pattern, char* buf, int len)
{
	int i = 0;
	while(i < len)
	{
		if (pattern[i]!=buf[i])
			return false;
		i++;
	}
	return true;
}

void print_stars(int len)
{
	int i = 0;
	while(i < len)
	{
		printf("*");
		i++;
	}
}

void shift_window(char* buf, int len)
{
	int i = 0;
	while(i < len)
	{
		buf[i]= buf[i+1];
		i++;
	}
}

void print_buffer(char* buf, int len)
{
	int i = 0;
	while(i < len)
	{
		printf("%c", buf[i]);
		i++;
	}
}

int main(int ac, char* av[])
{
	if(ac != 2 || av[1][0]=='\0')
		return 1;
	char* pattern = av[1];
	int p_len = strlen(pattern);
	char* buf = malloc(p_len);

	if (!buf)
	{
	    perror("Error");
		return 1;
	}

	int buf_len = 0;
	ssize_t bytes_read;
	char c;

	while((bytes_read = read(0, &c, 1)) > 0)
	{
		buf[buf_len++] = c;
		if (buf_len < p_len)
			continue;
		if(is_match(pattern, buf, p_len))
		{
			print_stars(p_len);
			buf_len = 0;
		}
		else
		{
			printf("%c", buf[0]);
			shift_window(buf, p_len);
			buf_len--;
		}

	}

	if(bytes_read == -1)
	{
		perror("Error");
		free(buf);
		return 1;

	}
	print_buffer(buf, buf_len);
	free(buf);
	return 0;
}
