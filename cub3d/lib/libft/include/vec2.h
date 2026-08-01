#ifndef VEC2_H
# define VEC2_H

# include <stdbool.h>

typedef struct s_v2d
{
	double	x;
	double	y;
}	t_v2d;

typedef struct s_v2i
{
	int	x;
	int	y;
}	t_v2i;

/* Double vector operations */
t_v2d	ft_v2d_add(t_v2d a, t_v2d b);
t_v2d	ft_v2d_sub(t_v2d a, t_v2d b);
t_v2d	ft_v2d_scale(t_v2d v, double scalar);
t_v2d	ft_v2d_rotate(t_v2d v, double angle);
double	ft_v2d_length(t_v2d v);
double	ft_v2d_length_squared(t_v2d v);
double	ft_v2d_distance_squared(t_v2d a, t_v2d b);
double	ft_v2d_cross(t_v2d a, t_v2d b);
t_v2d	ft_v2d_perpendicular(t_v2d v);
bool	ft_v2d_is_finite(t_v2d v);
t_v2d	ft_v2d_normalize(t_v2d v);
bool	ft_v2d_basis_coordinates(t_v2d vector, t_v2d x_axis,
			t_v2d y_axis, t_v2d *coordinates);

/* Integer vector operations */
t_v2i	ft_v2i_add(t_v2i a, t_v2i b);
t_v2i	ft_v2i_sub(t_v2i a, t_v2i b);
double	ft_v2i_distance_squared(t_v2i a, t_v2i b);
bool	ft_v2i_equal(t_v2i a, t_v2i b);
t_v2d	ft_v2i_to_v2d(t_v2i v);

#endif
