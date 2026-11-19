/* Division vs multiplication by the reciprocal, same loop over 8K floats (in cache).
** The compiler will not do this for floats by itself: x / k and x * (1 / k)
** can differ in the last bit, so it needs your permission (or -ffast-math).
** cc -O2 division.c -o division && ./division */
#include <stdio.h>
#include <time.h>

#define N 8192
#define STEPS 20000
#define REPS 7

static float	g_x[N];

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

__attribute__((noinline))
static void	by_div(float k)
{
	int	i;

	i = 0;
	while (i < N)
	{
		g_x[i] = g_x[i] / k + 1.0f;
		i++;
	}
}

__attribute__((noinline))
static void	by_mul(float k)
{
	float	inv;
	int		i;

	inv = 1.0f / k;
	i = 0;
	while (i < N)
	{
		g_x[i] = g_x[i] * inv + 1.0f;
		i++;
	}
}

static double	best(void (*step)(float))
{
	double	b;
	double	t;
	int		r;
	int		s;

	b = 1e9;
	r = 0;
	while (r++ < REPS)
	{
		t = now();
		s = 0;
		while (s++ < STEPS)
			step(1.0001f);
		t = now() - t;
		if (t < b)
			b = t;
	}
	return (b);
}

int	main(void)
{
	double	d;
	double	m;
	int		i;

	i = -1;
	while (++i < N)
		g_x[i] = (float)i;
	d = best(by_div);
	m = best(by_mul);
	printf("x / k:        %5.1f ms\n", d * 1e3);
	printf("x * (1 / k):  %5.1f ms  (%.1fx)\n", m * 1e3, d / m);
	return (0);
}
