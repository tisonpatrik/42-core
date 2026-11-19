/* Beyond one core: the same SoA loop as on the slides (x += vx * DT),
** 1) without SIMD, 2) SSE: 4 floats at once (what -O2 does by itself),
** 3) AVX2: 8 floats at once (only with -mavx2 / -march=native, here per function),
** 4) SSE on 1..6 threads (pthreads). Every number = best of REPS runs.
** SIMD is measured twice: on 16M floats (128 MB, waits for RAM) and on 8K floats
** (64 KB, fits in L2), with the same total amount of work. Threads run on the
** 128 MB arrays (no thread's share fits in cache) and then once more with every
** thread working on its own 64 KB slice in L2 (same total work).
** cc -O2 -pthread beyond.c -o beyond && ./beyond */
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define N 16000000
#define DT (1.0f / 60)
#define STEPS 20
#define MAX_T 6
#define REPS 7
#define SMALL 8192

static float	g_x[N];
static float	g_vx[N];

typedef struct s_job
{
	int	from;
	int	to;
	int	steps;
}	t_job;

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

__attribute__((optimize("no-tree-vectorize")))
static void	step_scalar(int from, int to)
{
	int	i;

	i = from;
	while (i < to)
	{
		g_x[i] += g_vx[i] * DT;
		i++;
	}
}

static void	step_simd(int from, int to)
{
	int	i;

	i = from;
	while (i < to)
	{
		g_x[i] += g_vx[i] * DT;
		i++;
	}
}

__attribute__((target("avx2")))
static void	step_avx2(int from, int to)
{
	int	i;

	i = from;
	while (i < to)
	{
		g_x[i] += g_vx[i] * DT;
		i++;
	}
}

static double	timed(void (*step)(int, int), int n)
{
	double	best;
	double	t0;
	int		r;
	int		s;

	best = 1e9;
	r = 0;
	while (r++ < REPS)
	{
		t0 = now();
		s = 0;
		while (s++ < STEPS * (N / n))
			step(0, n);
		t0 = (now() - t0) / STEPS;
		if (t0 < best)
			best = t0;
	}
	return (best);
}

static void	*worker(void *arg)
{
	t_job	*job;
	int		s;

	job = arg;
	s = 0;
	while (s++ < job->steps)
		step_simd(job->from, job->to);
	return (NULL);
}

/* in_cache: thread i updates its own SMALL slice, total work = STEPS * N updates */
static double	run_threads_once(int threads, int in_cache)
{
	pthread_t	tid[MAX_T];
	t_job		jobs[MAX_T];
	double		t0;
	int			i;

	t0 = now();
	i = -1;
	while (++i < threads)
	{
		jobs[i] = (t_job){N / threads * i, N / threads * (i + 1), STEPS};
		if (i == threads - 1)
			jobs[i].to = N;
		if (in_cache)
			jobs[i] = (t_job){SMALL * i, SMALL * (i + 1),
				10 * STEPS * (N / SMALL) / threads};
		pthread_create(&tid[i], NULL, worker, &jobs[i]);
	}
	while (i-- > 0)
		pthread_join(tid[i], NULL);
	return ((now() - t0) / STEPS / (in_cache ? 10 : 1));
}

static double	run_threads(int threads, int in_cache)
{
	double	best;
	double	t;
	int		r;

	best = 1e9;
	r = 0;
	while (r++ < REPS)
	{
		t = run_threads_once(threads, in_cache);
		if (t < best)
			best = t;
	}
	return (best);
}

static void	simd_table(const char *title, int n)
{
	double	scalar;
	double	sse;
	double	avx2;

	scalar = timed(step_scalar, n);
	sse = timed(step_simd, n);
	avx2 = timed(step_avx2, n);
	printf("--- %s\n", title);
	printf("no SIMD:          %5.2f ms\n", scalar * 1e3);
	printf("SSE  (4 floats):  %5.2f ms  (%.1fx)\n", sse * 1e3, scalar / sse);
	printf("AVX2 (8 floats):  %5.2f ms  (%.1fx)\n", avx2 * 1e3, scalar / avx2);
}

static void	thread_table(const char *title, int in_cache)
{
	double	one;
	double	t;
	int		i;

	printf("--- %s\n", title);
	one = run_threads(1, in_cache);
	i = 0;
	while (++i <= MAX_T)
	{
		t = run_threads(i, in_cache);
		printf("%d threads:        %5.2f ms  (%.1fx)\n", i, t * 1e3, one / t);
	}
}

int	main(void)
{
	int	i;

	i = -1;
	while (++i < N)
		g_vx[i] = (float)(i % 7);
	simd_table("SIMD, data in L2 (8K floats, 64 KB)", SMALL);
	simd_table("SIMD, data in RAM (16M floats, 128 MB)", N);
	thread_table("threads, data in RAM (16M floats, 128 MB)", 0);
	thread_table("threads, each with its own 64 KB in L2", 1);
	return (0);
}
