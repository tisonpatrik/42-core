/* 3 · Lifetimes: arény, measure + 1 alokace, scratch, parser, benchmark, pymalloc */

Talk.slides(`
<section class="slide slide--center">
	<div class="kicker">3 · Lifetimes</div>
	<p class="statement">Kolik má tvůj program lifetimes?</p>
	<p class="lead lead--light muted">Každý <code>malloc</code> = jeden lifetime, který musíš uhlídat.<br>Minishell s 500 tokeny na řádku = 1000 lifetimes na příkaz.</p>
	<p class="small muted">Ryan Fleury: „Untangling Lifetimes: The Arena Allocator“</p>
</section>

<section class="slide">
	<div class="kicker">3 · Lifetimes · cub3D</div>
	<h2>Data neumírají po jednom. Umírají ve skupinách.</h2>
	<div class="lifetimes">
		<div class="lifetimes__name">permanentní <small>t_rom: textury, barvy, map_size</small></div>
		<div class="lifetimes__lane"><div class="lifetimes__seg tone-c" style="--from: 2%; --len: 96%"></div></div>
		<div class="lifetimes__name">per hra <small>t_ram: tiles, fire.cells, player</small></div>
		<div class="lifetimes__lane"><div class="lifetimes__seg tone-py" style="--from: 4%; --len: 94%"></div></div>
		<div class="lifetimes__name">per paprsek <small>fire_hits: count = 0</small></div>
		<div class="lifetimes__lane" data-component="ticks" data-ticks="28" data-tone="ok"></div>
		<div class="lifetimes__name">scratch <small>orb_generate: visited, candidates</small></div>
		<div class="lifetimes__lane"><div class="lifetimes__seg tone-hot" style="--from: 6%; --len: 3%"></div></div>
	</div>
	<div class="card push-bottom"><p><span class="pill tone-c">minishell</span><b>env</b> = celá session · <b>tokeny + AST</b> = jeden příkaz, reset po každé řádce · <b>expanze</b> = scratch</p></div>
</section>

<section class="slide">
	<div class="kicker">3 · Aréna · naše libft</div>
	<h2>Alokace = posun ukazatele. Free = <code>offset = 0</code>.</h2>
	<div class="grid grid--fill cols-wide-left">
<pre class="code code--sm" data-component="code" data-lang="c">typedef struct s_arena
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
/* reset: arena-&gt;offset = 0; */</pre>
		<div class="stack">
			<div class="card"><h3>Projde normou</h3><p>Krátké funkce, žádné globály, jeden <code>malloc</code> při vytvoření.</p></div>
			<div class="card"><h3>Nulování zdarma</h3><p><code>ft_memset</code> v push = žádné neinicializované struktury.</p></div>
			<div class="card"><h3>Zarovnání</h3><p><code>_Alignof(max_align_t)</code>, takže je to bezpečné pro <code>double</code> i structy.</p></div>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">3 · Aréna · náš cub3D</div>
	<h2>Nejdřív změř, pak alokuj jednou</h2>
	<div class="grid grid--fill cols-2">
<pre class="code code--sm" data-component="code" data-lang="c">/* src/app/setup_memory.c */
*total = 0;
ft_arena_measure(total, 1, sizeof(t_rom));
ft_arena_measure(total, 1, sizeof(t_ram));
ft_arena_measure(total, tiles, sizeof(uint8_t));
ft_arena_measure(total, tiles, sizeof(t_fire_cell));
ft_arena_measure(total, hits, sizeof(t_ray_hit));
/* bonus: sprite_depth + scratch pro orby */

/* src/app/setup.c */
game-&gt;arena = ft_arena_create(memory_size);

/* src/app/lifecycle.c */
ft_arena_destroy(game-&gt;arena);   /* hotovo */</pre>
		<div class="stack">
			<div class="card"><p>Velikost mapy je známá po parsování → víme <b>přesně</b>, kolik paměti hra kdy bude potřebovat.</p></div>
			<div class="card"><p>Za běhu hry: <b class="ok">0× malloc, 0× free</b>.<br>Malloc nemůže selhat uprostřed framu.</p></div>
			<div class="card"><p>Valgrind: žádné leaky z enginu, a to ne díky disciplíně, ale protože to jinak nejde.</p></div>
		</div>
	</div>
	<div class="memmap">
		<div class="memmap__seg tone-c" style="--w: 1">rom</div>
		<div class="memmap__seg tone-c" style="--w: 1.4">ram</div>
		<div class="memmap__seg tone-py" style="--w: 2">tiles<small>w·h × 1 B</small></div>
		<div class="memmap__seg tone-py" style="--w: 4">fire.cells<small>w·h × 16 B</small></div>
		<div class="memmap__seg tone-py" style="--w: 2.2">fire_hits<small>(w+h) × 32 B</small></div>
		<div class="memmap__seg tone-ok" style="--w: 2.2">sprite_depth<small>W × 8 B</small></div>
		<div class="memmap__seg tone-hot" style="--w: 3.2">scratch<small>visited + candidates</small></div>
	</div>
</section>

<section class="slide">
	<div class="kicker">3 · Scratch aréna · náš cub3D</div>
	<h2>Dočasná paměť se vrací jedním řádkem</h2>
	<div class="grid grid--fill cols-wide-left">
<pre class="code code--sm" data-component="code" data-lang="c">bool	orb_generate(t_game *game, uint32_t seed)
{
	t_arena_temp	scratch;
	uint8_t			*visited;
	t_v2i			*candidates;
	/* ... */
	scratch = ft_scratch_begin(game-&gt;arena);
	visited = ft_arena_push_array(game-&gt;arena,
			tile_count, sizeof(uint8_t));
	candidates = ft_arena_push_array(game-&gt;arena,
			tile_count, sizeof(t_v2i));
	if (!visited || !candidates)
		return (ft_scratch_end(scratch), false);
	count = flood_reachable(game, visited, candidates);
	/* ... */
	ft_scratch_end(scratch);
	return (true);
}</pre>
		<div class="stack">
			<div class="card"><h3>begin = ulož offset</h3><p><code>ft_scratch_begin</code> si zapamatuje, kde aréna je.</p></div>
			<div class="card"><h3>end = vrať offset</h3><p>Všechno alokované mezi tím zmizí najednou, včetně chybové cesty.</p></div>
			<div class="card"><h3>Error handling zdarma</h3><p>Žádné „uvolni prvních 3 z 5 věcí, které se stihly alokovat“.</p></div>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">3 · Poctivě · náš cub3D</div>
	<h2>A teď parser. Ten jsme psali „normálně“.</h2>
	<div class="grid grid--fill cols-2">
<pre class="code code--sm" data-component="code" data-lang="c">void	free_file(t_file *file)
{
	int	i;

	if (!file)
		return ;
	i = 0;
	if (file-&gt;lines)
	{
		while (i &lt; file-&gt;line_count)
		{
			if (file-&gt;lines[i])
				free(file-&gt;lines[i]);
			i++;
		}
		free(file-&gt;lines);
	}
	if (file-&gt;map.grid)
		free_map(&amp;file-&gt;map);
}</pre>
		<div class="stack">
			<p class="lead">Memory leak, který jsme v projektu museli ladit, byl…</p>
			<p class="statement hot">v parseru.</p>
			<p class="small muted">README: <em>„AI tools were used… for diagnosing a memory leak in the map parser.“</em></p>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">3 · Aréna · benchmark</div>
	<h2>Minishell-like: 20 000 řádků × 500 tokenů</h2>
	<div class="grid grid--fill cols-2">
		<div class="card">
			<h3><span class="pill tone-c">C</span>celkem, ms</h3>
			<div class="bars" data-component="bars" data-unit=" ms">
				<div data-label="malloc/free" data-value="374" data-tone="hot"></div>
				<div data-label="aréna" data-value="23" data-tone="c" data-delta="16×"></div>
			</div>
			<p class="small muted mt">20M <code>malloc</code> + 20M <code>free</code> vs. 1 + 1</p>
		</div>
<pre class="code code--sm" data-component="code" data-lang="c">/* malloc verze: 2 alokace na token */
t = malloc(sizeof(t_token));
t-&gt;str = malloc(16);
/* ... a na konci řádku */
while (head) { /* free, free */ }

/* aréna: stejný kód, jiný alokátor */
t = arena_push(a, sizeof(t_token));
t-&gt;str = arena_push(a, 16);
/* ... a na konci řádku */
a-&gt;offset = 0;</pre>
	</div>
</section>

<section class="slide">
	<div class="kicker">3 · Python</div>
	<h2>Arény používáš celou dobu. Jen o tom nevíš.</h2>
	<div class="grid grid--fill cols-2">
		<div>
<pre class="code code--sm" data-component="code" data-lang="py">&gt;&gt;&gt; sys._debugmallocstats()
...
2 arenas * 1048576 bytes/arena
19 unused pools * 16384 bytes
...</pre>
			<p class="small mt-sm">CPython <code>pymalloc</code>: <b>aréna 1 MiB → pool 16 KiB → bloky ≤ 512 B</b>. Každý malý objekt (int, float, tuple…) žije v aréně.</p>
<pre class="code code--sm mt" data-component="code" data-lang="py">tmp = np.empty(N, np.float32)   # jednou
for frame in range(FRAMES):
    np.multiply(vel, DT, out=tmp)
    np.add(pos, tmp, out=pos)   # 0 nových polí</pre>
		</div>
		<div class="card">
			<h3><span class="pill tone-py">NumPy</span>200 framů, 2M prvků</h3>
			<div class="bars" data-component="bars" data-unit=" ms">
				<div data-label="nová pole" data-value="2.40" data-tone="py"></div>
				<div data-label="out= reuse" data-value="2.09" data-tone="py" data-delta="1,15×"></div>
			</div>
			<h3 class="mt">špička paměti navíc</h3>
			<div class="bars" data-component="bars" data-unit=" MiB">
				<div data-label="nová pole" data-value="22.9" data-tone="hot"></div>
				<div data-label="out= reuse" data-value="0.01" data-tone="hot"></div>
			</div>
			<p class="small muted mt">Poctivě: v Pythonu vyhraješ hlavně paměť a předvídatelnost, ne 16× čas.</p>
		</div>
	</div>
</section>
`);
