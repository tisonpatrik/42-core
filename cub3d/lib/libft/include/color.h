#ifndef COLOR_H
# define COLOR_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define FT_RGBA_CHANNEL_COUNT 4
# define FT_COLOR_CHANNEL_MAX 255

/* Named color value and mutable view over RGBA byte storage. */
typedef struct s_rgba
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}	t_rgba;

typedef struct s_rgba_ref
{
	uint8_t	*bytes;
}	t_rgba_ref;

typedef struct s_rgba_view
{
	uint8_t	*bytes;
	size_t	width;
	size_t	height;
	size_t	stride;
}	t_rgba_view;

t_rgba		ft_rgba_create(uint8_t red, uint8_t green, uint8_t blue,
				uint8_t alpha);
t_rgba_ref	ft_rgba_ref(uint8_t *bytes);
t_rgba_view	ft_rgba_view(uint8_t *bytes, size_t width, size_t height,
				size_t stride);
bool		ft_rgba_view_contains(const t_rgba_view *view, int x, int y);
/* Unchecked hot-path access; validate coordinates at the caller boundary. */
t_rgba_ref	ft_rgba_view_pixel(const t_rgba_view *view, int x, int y);
t_rgba		ft_rgba_read(t_rgba_ref source);
void		ft_rgba_write(t_rgba_ref destination, t_rgba color);
void		ft_rgba_copy(t_rgba_ref destination, t_rgba_ref source);
void		ft_rgba_fill(t_rgba_ref destination, size_t count, t_rgba color);
t_rgba		ft_rgba_source_over(t_rgba source, t_rgba destination);

#endif
