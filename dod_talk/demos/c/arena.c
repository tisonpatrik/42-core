/* minishell-like workload: every "command line" creates many small tokens,
** then everything dies at once. malloc/free vs arena.
** cc -O2 arena.c -o arena && ./arena */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINES 20000
#define TOKENS 500

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_arena
{
	uint8_t	*base;
	size_t	offset;
	size_t	capacity;
}	t_arena;

static void	*arena_push(t_arena *a, size_t size)
{
	size_t	off;

	off = (a->offset + 15) & ~(size_t)15;
	if (off + size > a->capacity)
		return (NULL);
	a->offset = off + size;
	return (a->base + off);
}

static double	now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec * 1e-9);
}

static long	with_malloc(void)
{
	long	sum = 0;

	for (int l = 0; l < LINES; l++)
	{
		t_token	*head = NULL;
		for (int i = 0; i < TOKENS; i++)
		{
			t_token	*t = malloc(sizeof(t_token));
			t->str = malloc(16);
			memcpy(t->str, "echo_hello_42", 14);
			t->type = i & 3;
			t->next = head;
			head = t;
		}
		for (t_token *t = head; t; t = t->next)
			sum += t->type;
		while (head)
		{
			t_token	*next = head->next;
			free(head->str);
			free(head);
			head = next;
		}
	}
	return (sum);
}

static long	with_arena(t_arena *a)
{
	long	sum = 0;

	for (int l = 0; l < LINES; l++)
	{
		t_token	*head = NULL;
		for (int i = 0; i < TOKENS; i++)
		{
			t_token	*t = arena_push(a, sizeof(t_token));
			t->str = arena_push(a, 16);
			memcpy(t->str, "echo_hello_42", 14);
			t->type = i & 3;
			t->next = head;
			head = t;
		}
		for (t_token *t = head; t; t = t->next)
			sum += t->type;
		a->offset = 0;
	}
	return (sum);
}

int	main(void)
{
	t_arena	a = {malloc(1 << 20), 0, 1 << 20};
	double	t0, t_m, t_a;
	long	r1, r2;

	t0 = now(); r1 = with_malloc(); t_m = now() - t0;
	t0 = now(); r2 = with_arena(&a); t_a = now() - t0;
	printf("%d lines x %d tokens\n", LINES, TOKENS);
	printf("malloc/free: %7.1f ms  (%d malloc + %d free)\n", t_m * 1e3,
		LINES * TOKENS * 2, LINES * TOKENS * 2);
	printf("arena:       %7.1f ms  (1 malloc + 1 free)  (%.1fx)\n",
		t_a * 1e3, t_m / t_a);
	printf("check: %ld %ld\n", r1, r2);
	free(a.base);
	return (0);
}
