#include "fs.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#define READ_CHUNK_SIZE 4096

static bool	file_size(int fd, size_t *size)
{
	struct stat	info;

	if (fstat(fd, &info) < 0 || !S_ISREG(info.st_mode) || info.st_size < 0
		|| (uintmax_t)info.st_size > SIZE_MAX)
		return (false);
	*size = (size_t)info.st_size;
	return (true);
}

static bool	read_all(int fd, uint8_t *bytes, size_t size)
{
	ssize_t	read_size;
	size_t	offset;
	size_t	request;

	offset = 0;
	while (offset < size)
	{
		request = size - offset;
		if (request > READ_CHUNK_SIZE)
			request = READ_CHUNK_SIZE;
		read_size = read(fd, bytes + offset, request);
		if (read_size < 0 && errno == EINTR)
			continue ;
		if (read_size <= 0)
			return (false);
		offset += (size_t)read_size;
	}
	return (true);
}

static bool	read_rollback(t_arena_temp scratch, int fd)
{
	close(fd);
	ft_scratch_end(scratch);
	return (false);
}

bool	ft_read_file(t_arena *arena, const char *path, t_str8 *file)
{
	t_arena_temp	scratch;
	size_t			size;
	int				fd;

	if (!arena || !path || !file)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	scratch = ft_scratch_begin(arena);
	if (!file_size(fd, &size))
		return (read_rollback(scratch, fd));
	if (size == 0)
		file->str = arena->base + arena->offset;
	else
		file->str = ft_arena_push_array(arena, size, sizeof(uint8_t));
	file->len = size;
	if (!file->str || !read_all(fd, file->str, file->len))
		return (read_rollback(scratch, fd));
	close(fd);
	return (true);
}
