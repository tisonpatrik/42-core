/* Inside an arena */

Talk.slides(`
<section class="slide" data-title="Inside an arena">
	<header class="slide__head">
		<div class="kicker">libft · src/allocator · called ft_arena_alloc in push_swap</div>
		<h2>Inside an arena</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-2">
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_arena
{
	uint8_t		*base;
	size_t		offset;
	size_t		capacity;
}	t_arena;

void	*ft_arena_push(t_arena *arena, size_t size)
{
	void	*ptr;
	size_t	aligned_size;

	aligned_size = ft_arena_align_size(size);
	if (aligned_size &gt; arena-&gt;capacity - arena-&gt;offset)
		return (NULL);
	ptr = arena-&gt;base + arena-&gt;offset;
	arena-&gt;offset += aligned_size;
	ft_memset(ptr, 0, aligned_size);
	return (ptr);
}

/* ft_arena_reset: arena-&gt;offset = 0; */</pre>
		<div class="abars">
			<div class="abar">
				<div class="abar__head"><span class="abar__step">1</span><code>ft_arena_create(size)</code><span class="muted">an arena for picking a move</span></div>
				<div class="abar__track"><span class="abar__offset" style="--at: 0%"></span></div>
			</div>
			<div class="abar">
				<div class="abar__head"><span class="abar__step">2</span><code>select_best_move</code><span class="muted">3× push</span></div>
				<div class="abar__track"><span class="abar__seg tone-c" style="--w: 24">candidates</span><span class="abar__seg tone-py" style="--w: 18">filtered</span><span class="abar__seg tone-hot" style="--w: 12">top_k</span><span class="abar__offset" style="--at: 84.4%"></span></div>
			</div>
			<div class="abar">
				<div class="abar__head"><span class="abar__step">3</span><code>ft_arena_reset</code><span class="muted">move played, start over</span></div>
				<div class="abar__track"><span class="abar__seg tone-cold" style="--w: 24">candidates</span><span class="abar__seg tone-cold" style="--w: 18">filtered</span><span class="abar__seg tone-cold" style="--w: 12">top_k</span><span class="abar__offset" style="--at: 0%"></span></div>
			</div>
			<div class="flow">
				<span class="flow__label hot">now</span>
				<span class="flow__steps">create <i>→</i> move <i>→</i> destroy <em>× every move</em></span>
				<span class="flow__label ok">better</span>
				<span class="flow__steps">create <i>→</i> move <i>→</i> reset <i>→ … →</i> destroy</span>
			</div>
		</div>
	</div>
	</div>
</section>
`);
