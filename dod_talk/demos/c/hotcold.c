/* Hot/cold split: the update loop reads position + velocity (24 B),
** the rest of the particle (name, color, mass, flags, id) is cold.
** cc -O2 hotcold.c -o hotcold && ./hotcold          (both, timed)
** perf stat -e L1-dcache-load-misses ./hotcold fat  (one layout only) */
#include <stdio.h>
#include <string.h>
#include <time.h>

#define N 1000000
#define DT (1.0f / 60)
#define STEPS 200

typedef struct s_particle
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_particle;

typedef struct s_hot
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
}	t_hot;

typedef struct s_cold
{
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_cold;

static t_particle	g_ps[N];
static t_hot		g_hot[N];
static t_cold		g_cold[N];

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

static double	run_one(void)
{
	double	t0;
	int		s;
	int		i;

	t0 = now();
	s = 0;
	while (s++ < STEPS)
	{
		i = 0;
		while (i < N)
		{
			g_ps[i].x += g_ps[i].vx * DT;
			g_ps[i].y += g_ps[i].vy * DT;
			g_ps[i].z += g_ps[i].vz * DT;
			i++;
		}
	}
	return ((now() - t0) / STEPS);
}

static double	run_split(void)
{
	double	t0;
	int		s;
	int		i;

	t0 = now();
	s = 0;
	while (s++ < STEPS)
	{
		i = 0;
		while (i < N)
		{
			g_hot[i].x += g_hot[i].vx * DT;
			g_hot[i].y += g_hot[i].vy * DT;
			g_hot[i].z += g_hot[i].vz * DT;
			i++;
		}
	}
	return ((now() - t0) / STEPS);
}

int	main(int argc, char **argv)
{
	double	t_fat;
	double	t_split;
	int		i;

	i = 0;
	while (i < N)
	{
		g_ps[i].vx = (float)(i % 7);
		g_hot[i].vx = (float)(i % 7);
		g_ps[i].id = i;
		g_cold[i].id = i;
		i++;
	}
	if (argc > 1 && !strcmp(argv[1], "fat"))
		return (printf("fat:   %.2f ms / step\n", run_one() * 1e3), 0);
	if (argc > 1 && !strcmp(argv[1], "split"))
		return (printf("split: %.2f ms / step\n", run_split() * 1e3), 0);
	t_fat = run_one();
	t_split = run_split();
	printf("sizeof(t_particle) = %zu B, sizeof(t_hot) = %zu B\n",
		sizeof(t_particle), sizeof(t_hot));
	printf("one struct: %6.2f ms / step\n", t_fat * 1e3);
	printf("hot/cold:   %6.2f ms / step  (%.1fx)\n", t_split * 1e3, t_fat / t_split);
	printf("check: %f %f %d\n", g_ps[N - 2].x, g_hot[N - 2].x, g_cold[N - 2].id);
	return (0);
}
