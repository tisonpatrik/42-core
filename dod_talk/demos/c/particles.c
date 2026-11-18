/* AoS vs SoA: update positions of N particles.
** cc -O2 particles.c -o particles && ./particles */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4000000
#define STEPS 20

typedef struct s_particle
{
	float	x, y, z;
	float	vx, vy, vz;
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_particle;

typedef struct s_particles
{
	float	*x, *y, *z;
	float	*vx, *vy, *vz;
}	t_particles;

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

int	main(void)
{
	t_particle	*aos = calloc(N, sizeof(t_particle));
	t_particles	soa;
	float		dt = 0.016f;
	double		t0, t_aos, t_soa;

	soa.x = calloc(N, 4); soa.y = calloc(N, 4); soa.z = calloc(N, 4);
	soa.vx = calloc(N, 4); soa.vy = calloc(N, 4); soa.vz = calloc(N, 4);
	for (int i = 0; i < N; i++)
	{
		aos[i].vx = soa.vx[i] = (float)(i % 7);
		aos[i].vy = soa.vy[i] = (float)(i % 5);
		aos[i].vz = soa.vz[i] = (float)(i % 3);
	}
	t0 = now();
	for (int s = 0; s < STEPS; s++)
		for (int i = 0; i < N; i++)
		{
			aos[i].x += aos[i].vx * dt;
			aos[i].y += aos[i].vy * dt;
			aos[i].z += aos[i].vz * dt;
		}
	t_aos = now() - t0;
	t0 = now();
	for (int s = 0; s < STEPS; s++)
		for (int i = 0; i < N; i++)
		{
			soa.x[i] += soa.vx[i] * dt;
			soa.y[i] += soa.vy[i] * dt;
			soa.z[i] += soa.vz[i] * dt;
		}
	t_soa = now() - t0;
	printf("sizeof(t_particle) = %zu B, hot data = 24 B\n", sizeof(t_particle));
	printf("AoS: %7.1f ms / step\n", t_aos / STEPS * 1e3);
	printf("SoA: %7.1f ms / step  (%.1fx)\n", t_soa / STEPS * 1e3, t_aos / t_soa);
	printf("check: %f %f\n", aos[N - 1].x, soa.x[N - 1]);
	return (0);
}
