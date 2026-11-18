/* "Clean Code, Horrible Performance" (Casey Muratori) in C:
** "polymorphism" with function pointers vs switch vs lookup table.
** cc -O2 shapes.c -o shapes && ./shapes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (1 << 20)
#define REPS 20

typedef enum e_kind { SQUARE, RECTANGLE, TRIANGLE, CIRCLE, KIND_COUNT }	t_kind;

/* "object": every shape is its own heap allocation with a vtable pointer */
typedef struct s_shape
{
	float	(*area)(const struct s_shape *self);
	float	w;
	float	h;
}	t_shape;

/* data: one flat array, kind is just a number */
typedef struct s_shape_data
{
	t_kind	kind;
	float	w;
	float	h;
}	t_shape_data;

static float	square_area(const t_shape *s) { return (s->w * s->w); }
static float	rect_area(const t_shape *s) { return (s->w * s->h); }
static float	tri_area(const t_shape *s) { return (0.5f * s->w * s->h); }
static float	circle_area(const t_shape *s) { return (3.14159265f * s->w * s->w); }

static float	area_switch(const t_shape_data *s)
{
	switch (s->kind)
	{
		case SQUARE: return (s->w * s->w);
		case RECTANGLE: return (s->w * s->h);
		case TRIANGLE: return (0.5f * s->w * s->h);
		case CIRCLE: return (3.14159265f * s->w * s->w);
		default: return (0);
	}
}

static const float	g_coef[KIND_COUNT] = {1.0f, 1.0f, 0.5f, 3.14159265f};

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

int	main(void)
{
	static float	(*const fn[KIND_COUNT])(const t_shape *)
		= {square_area, rect_area, tri_area, circle_area};
	t_shape			**objs = malloc(N * sizeof(t_shape *));
	t_shape_data	*data = malloc(N * sizeof(t_shape_data));
	volatile float	sink = 0;
	double			t0, t_fn, t_sw, t_tab;

	srand(42);
	for (int i = 0; i < N; i++)
	{
		t_kind	k = rand() % KIND_COUNT;
		float	a = 1.0f + rand() % 10;
		float	b = (k == SQUARE || k == CIRCLE) ? a : 1.0f + rand() % 10;

		data[i] = (t_shape_data){k, a, b};
		objs[i] = malloc(sizeof(t_shape));
		*objs[i] = (t_shape){fn[k], a, b};
	}
	t0 = now();
	for (int r = 0; r < REPS; r++)
	{
		float	sum = 0;
		for (int i = 0; i < N; i++)
			sum += objs[i]->area(objs[i]);
		sink = sink + sum;
	}
	t_fn = (now() - t0) / REPS;
	t0 = now();
	for (int r = 0; r < REPS; r++)
	{
		float	sum = 0;
		for (int i = 0; i < N; i++)
			sum += area_switch(&data[i]);
		sink = sink + sum;
	}
	t_sw = (now() - t0) / REPS;
	t0 = now();
	for (int r = 0; r < REPS; r++)
	{
		float	sum = 0;
		for (int i = 0; i < N; i++)
			sum += g_coef[data[i].kind] * data[i].w * data[i].h;
		sink = sink + sum;
	}
	t_tab = (now() - t0) / REPS;
	printf("fn pointer: %6.2f ms\n", t_fn * 1e3);
	printf("switch:     %6.2f ms  (%.1fx)\n", t_sw * 1e3, t_fn / t_sw);
	printf("table:      %6.2f ms  (%.1fx)\n", t_tab * 1e3, t_fn / t_tab);
	for (int i = 0; i < N; i++)
		free(objs[i]);
	free(objs);
	free(data);
	return (0);
}
