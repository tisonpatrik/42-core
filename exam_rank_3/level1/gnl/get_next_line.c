#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


char *ft_strchr(char *s, int c)
{
	if(!s)
		return NULL;
	
	int i = 0;
	while(s[i])
	{
		if(s[i]== c)
		{
			return &s[i];
		}
		i++;
	}
	if(s[i] == c)
		return &s[i];

	return NULL;
	
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	char* d = ((char *)dest);
	const char* s	= ((const char *)src);
	size_t i =0;
	while(i < n)
	{
		d[i]= s[i];	
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t i =0;
	while (s[i]) 
	{
		i++;
	}
	return i;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1;
	if(*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;

	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	
	if(*s1)
		ft_memcpy(tmp, *s1, size1);

	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';

	free(*s1);
	*s1 = tmp;
	return 1; 
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if(!dest || !src)
		return NULL;

	if(dest < src)
	{
		return ft_memcpy(dest, src, n);
	}
	

	char* d = ((char *)dest);
	const char* s	= ((const char *)src);
	if(dest > src)
	{
		size_t i =n;
		while(i < 0)
		{
			d[i-1]= s[i-1];	
			i--;
		}
	}
	return dest;
}

char* get_next_line(int fd)
{
	if(fd < 0 || BUFFER_SIZE ==0)
		return NULL;

	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char* tmp;
	int read_ret;

	while(1)
	{
		tmp = ft_strchr(b, '\n');
		if(tmp)
		{
			if (!str_append_mem(&ret, b, tmp - b + 1))
			{
				free(ret);
				return NULL;
			}
			ft_memmove(b, tmp +1, ft_strlen(tmp + 1) + 1);
			return ret;
		}
		if (!str_append_str(&ret, b))
		{
			free(ret);
			return (NULL);
		}
		read_ret = read(fd, b, BUFFER_SIZE);

		if (read_ret < 0)
		{
			b[0] = '\0';
			free(ret);
			return (NULL);
		}

		if (read_ret == 0)
		{
			b[0] = '\0';
			if(*ret && ret != NULL)
				return ret;
			free(ret);
			return (NULL);
		}
		
		b[read_ret] = '\0';
	}
}

/*
int main(void)
{
	char dest[100];
	char* src = "Hello world";
	ft_memcpy(dest, src, 4);
	printf("%s", dest);
	return 0;
}
*/


int main(void)
{
	char* line;
	int fd = open("text.txt", O_RDONLY);
	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
	}
	free(line);
	close(fd);
}
