/* AoS vs SoA, exactly the code from the slide: N particles, x += vx * DT.
** cc -O2 particles.c -o particles && ./particles        (both, timed)
** perf stat -e L1-dcache-load-misses ./particles aos    (one layout only) */
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
}	t_particle;

typedef struct s_particles
{
	float	x[N];
	float	y[N];
	float	z[N];
	float	vx[N];
	float	vy[N];
	float	vz[N];
}	t_particles;

static t_particle	g_aos[N];
static t_particles	g_soa;

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

static double	run_aos(void)
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
			g_aos[i].x += g_aos[i].vx * DT;
			i++;
		}
	}
	return ((now() - t0) / STEPS);
}

static double	run_soa(void)
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
			g_soa.x[i] += g_soa.vx[i] * DT;
			i++;
		}
	}
	return ((now() - t0) / STEPS);
}

int	main(int argc, char **argv)
{
	double	t_aos;
	double	t_soa;
	int		i;

	i = 0;
	while (i < N)
	{
		g_aos[i].vx = (float)(i % 7);
		g_soa.vx[i] = (float)(i % 7);
		i++;
	}
	if (argc > 1 && !strcmp(argv[1], "aos"))
		return (printf("AoS: %.2f ms / step\n", run_aos() * 1e3), 0);
	if (argc > 1 && !strcmp(argv[1], "soa"))
		return (printf("SoA: %.2f ms / step\n", run_soa() * 1e3), 0);
	t_aos = run_aos();
	t_soa = run_soa();
	printf("sizeof(t_particle) = %zu B, the loop reads x and vx = 8 B\n",
		sizeof(t_particle));
	printf("AoS: %6.2f ms / step\n", t_aos * 1e3);
	printf("SoA: %6.2f ms / step  (%.1fx)\n", t_soa * 1e3, t_aos / t_soa);
	printf("check: %f %f\n", g_aos[N - 2].x, g_soa.x[N - 2]);
	return (0);
}
