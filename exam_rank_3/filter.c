#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 4048

int read_input(char* buf)
{
	ssize_t bytes_read;
	char c;
	int buf_len = 0;

	while((bytes_read = read(0, &c, 1)) > 0)
	{
		if(buf_len == MAX)
			break;
		buf[buf_len] = c;
		buf_len++;
	}
	if (bytes_read == -1)
		return -1;
	
	buf[buf_len] = '\0';
	return buf_len;
}

bool is_match(char* buf, char* pattern, int p_len)
{
	int i = 0;
	while(i < p_len)
	{
		if(buf[i]== '\0' || buf[i] != pattern[i])
		{
			return false;
		}
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

void process_buffer(char* buf, int buf_len, char* pattern, int p_len)
{
	int i = 0;
	while(buf[i])
	{
		if(is_match(&buf[i], pattern, p_len))
		{
			print_stars(p_len);
			i += p_len;
		}
		else 
		{
			printf("%c", buf[i]);
			i++;
		}
	}
}

int main(int ac, char* av[])
{
	if(ac != 2 || !av[1] || av[1][0] == '\0')
	{
		return 1;
	}

	char* pattern = av[1];
	int p_len = strlen(pattern);
	
	char* buf = malloc(MAX + 1);
	if(!buf)
	{
		perror("Error");
		free(buf);
		return 1;
	}
	int buf_len = read_input(buf);

	if (buf_len == -1)
	{
		perror("Error");
		free(buf);
		return 1;
	}
	process_buffer(buf, buf_len, pattern, p_len);

	return 0;
}
