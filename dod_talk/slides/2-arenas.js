/* Arenas: push_swap, inside an arena, tree, counts, CUB3D, str8, parser, think first, NASA/TigerBeetle, measure, ROM/RAM, evidence */

Talk.slides(`
<section data-section="Arenas" class="slide slide--statement" data-title="git push --force · sudo swapoff -a">
	<h1 class="cmd" aria-label="git push --force, sudo swapoff -a">
		<span class="cmd__prompt">$</span><span class="cmd__tool">git</span><span class="cmd__key">push</span><span class="cmd__rest"> --force</span>
		<span class="cmd__prompt">$</span><span class="cmd__tool">sudo</span><span class="cmd__key">swap</span><span class="cmd__rest">off -a</span>
	</h1>
</section>

<section class="slide" data-title="push_swap: LIS without vs. with an arena">
	<header class="slide__head">
		<div class="kicker">push_swap · separator · LIS computation</div>
		<h2>Five arrays, one lifetime</h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<figure class="snippet tone-hot">
			<figcaption class="snippet__head"><span class="snippet__tag">without an arena</span><span class="snippet__note">what it would look like</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">c = malloc(sizeof(t_lis_computation));
if (!c)
	return (NULL);
c-&gt;nodes = malloc(sizeof(t_node *) * n);
if (!c-&gt;nodes)
	return (free(c), NULL);
c-&gt;values = malloc(sizeof(int) * n);
if (!c-&gt;values)
	return (free(c-&gt;nodes), free(c), NULL);
c-&gt;lis_lengths = malloc(sizeof(int) * n);
if (!c-&gt;lis_lengths)
	return (free(c-&gt;values), free(c-&gt;nodes),
		free(c), NULL);
/* + previous_indices, lis_nodes
   + free_computation() with 6× free */</pre>
			<div class="snippet__stats"><span><b>6×</b>malloc</span><span><b>6×</b>free</span><span><b>5</b>error paths</span></div>
		</figure>
		<figure class="snippet tone-ok">
			<figcaption class="snippet__head"><span class="snippet__tag">with an arena</span><span class="snippet__file">src/separator/separator_arena.c</span><span class="snippet__note">shortened</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">size = sizeof(t_lis_computation);
size += sizeof(t_node *) * n * 2;
size += sizeof(int) * n * 3;
arena-&gt;arena = ft_arena_create(size);

c = ft_arena_alloc(arena-&gt;arena, sizeof(*c));
c-&gt;nodes = ft_arena_alloc(arena-&gt;arena,
		sizeof(t_node *) * n);
c-&gt;values = ft_arena_alloc(arena-&gt;arena,
		sizeof(int) * n);
/* lis_lengths, previous_indices, lis_nodes
   the same: just an offset bump */

/* separator.c, after the computation */
free_separator_arena(arena);</pre>
			<div class="snippet__stats"><span><b>1</b>block</span><span><b>1×</b>free</span><span><b>1</b>error return</span></div>
		</figure>
	</div>
	</div>
	<footer class="slide__foot">
	<p class="source">
		<a class="link" href="https://www.dgtlgrove.com/p/untangling-lifetimes-the-arena-allocator" target="_blank" rel="noopener">Ryan Fleury: Untangling Lifetimes</a> ·
		<a class="link" href="https://www.youtube.com/watch?v=rJrd2QMVbGM" target="_blank" rel="noopener">Boot.dev: C Programming and Memory Management</a>
	</p>
	</footer>
</section>

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

<section class="slide" data-title="Project tree: memory apart from logic">
	<header class="slide__head">
		<div class="kicker">How to split it</div>
		<h2>Memory apart from logic</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-wide-left">
<div class="tree"><span class="tree__dir">push_swap/</span>
├── <span class="tree__dir">src/</span>
│   ├── <span class="tree__dir tree__dir--mem">memory/</span>         <span class="tree__note tree__note--mem">the only place with malloc / free</span>
│   │   ├── arena.c      <span class="tree__note">create · push · reset · destroy</span>
│   │   └── budget.c     <span class="tree__note">how much memory the whole run needs</span>
│   ├── main.c           <span class="tree__note">1× create … 1× destroy</span>
│   ├── <span class="tree__dir">validator/</span>      <span class="tree__brace">│</span>
│   ├── <span class="tree__dir">stack/</span>          <span class="tree__brace">│</span> <span class="tree__note">business logic</span>
│   ├── <span class="tree__dir">ops/</span>            <span class="tree__brace">│</span> <span class="tree__note">gets a t_arena *,</span>
│   ├── <span class="tree__dir">selector/</span>       <span class="tree__brace">│</span> <span class="tree__note">never calls</span>
│   ├── <span class="tree__dir">separator/</span>      <span class="tree__brace">│</span> <span class="tree__note">malloc or free</span>
│   └── <span class="tree__dir">solver/</span>         <span class="tree__brace">│</span>
└── Makefile</div>
		<div class="rule">
			<p class="rule__main"><span class="rule__code">malloc</span> and <span class="rule__code">free</span><br>only in <span class="rule__code">memory/</span></p>
			<p class="rule__sub">The rest borrows memory,<br>it never owns it.</p>
		</div>
	</div>
	</div>
</section>

<section class="slide" data-title="How many times I write malloc and free">
	<header class="slide__head">
		<div class="kicker">push_swap · static count in src/</div>
		<h2>How many times do I write <code>malloc</code> and <code>free</code>?</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-2">
		<div class="stack stack--sm">
			<div class="tally tone-hot">
				<span class="tally__label">no arenas</span>
				<span class="tally__num">26<small>× malloc</small></span>
				<span class="tally__num">70<small>× free</small></span>
			</div>
			<div class="tally tone-py">
				<span class="tally__label">with arenas</span>
				<span class="tally__num">15<small>× malloc</small></span>
				<span class="tally__num">20<small>× free</small></span>
			</div>
			<div class="tally tone-ok">
				<span class="tally__label">ideal</span>
				<span class="tally__num">1<small>× malloc</small></span>
				<span class="tally__num">1<small>× free</small></span>
			</div>
		</div>
		<div class="sites">
			<div class="sites__row sites__row--head"><span></span><span class="sites__group">no arenas</span><span class="sites__group">with arenas</span><span class="sites__group">ideal</span></div>
			<div class="sites__row sites__row--sub"><span>module</span><span>m</span><span>f</span><span>m</span><span>f</span><span>m</span><span>f</span></div>
			<div class="sites__row"><span class="sites__mod">validator/</span><span class="sites__n">5</span><span class="sites__n">7</span><span class="sites__n">5</span><span class="sites__n">7</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">stack/</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">ops/</span><span class="sites__n">2</span><span class="sites__n">3</span><span class="sites__n">2</span><span class="sites__n">3</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">optimizer/</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row sites__row--hl"><span class="sites__mod">selector/</span><span class="sites__n">8</span><span class="sites__n">30</span><span class="sites__n">3</span><span class="sites__n">6</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row sites__row--hl"><span class="sites__mod">separator/</span><span class="sites__n">7</span><span class="sites__n">28</span><span class="sites__n">1</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">main.c</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">1</span><span class="sites__n">1</span></div>
			<div class="sites__row sites__row--total"><span class="sites__mod">total</span><span class="sites__n">26</span><span class="sites__n">70</span><span class="sites__n">15</span><span class="sites__n">20</span><span class="sites__n">1</span><span class="sites__n">1</span></div>
		</div>
	</div>
	</div>
</section>

<section class="slide slide--full" data-title="CUB3D">
	<canvas class="raycast" data-component="raycast" aria-hidden="true"></canvas>
	<div class="arcade">
		<h1 class="visually-hidden">CUB3D</h1>
		<canvas class="pixeltitle" data-component="pixeltitle" data-left="CUB" data-right="3D" aria-hidden="true"></canvas>
	</div>
</section>

<section class="slide" data-title="Inside t_str8">
	<header class="slide__head">
		<div class="kicker">libft · src/str8</div>
		<h2>Inside <code>t_str8</code></h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-wide-left">
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_str8
{
	uint8_t	*str;
	size_t	len;
}	t_str8;

/* a view into existing memory: 0 allocations */
t_str8	ft_str8_create(uint8_t *str, size_t len)
{
	return ((t_str8){str, len});
}

/* new string: 1× push into the arena (checks omitted) */
t_str8	ft_str8_join(t_arena *arena, t_str8 a, t_str8 b)
{
	t_str8	res;

	res.len = a.len + b.len;
	res.str = ft_arena_push(arena, res.len + 1);
	ft_memcpy(res.str, a.str, a.len);
	ft_memcpy(res.str + a.len, b.str, b.len);
	return (res);
}</pre>
		<div class="facts facts--big">
			<span><b>substr · trim · next_token</b> just a view, 0 allocations</span>
			<span><b>join · dup · split</b> 1× push into the arena</span>
			<span><b>free</b> doesn’t exist, an arena reset cleans up</span>
		</div>
	</div>
	</div>
</section>

<section class="slide" data-title="cub3D parser: lines via malloc vs. str8 + arena">
	<header class="slide__head">
		<div class="kicker">cub3D · loading the .cub file</div>
		<h2>Lines without <code>malloc</code></h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<figure class="snippet tone-hot">
			<figcaption class="snippet__head"><span class="snippet__tag">now</span><span class="snippet__file">src/parser/init_file.c</span><span class="snippet__note">shortened</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">/* pass 1: count the lines */
line = ft_get_line(fd);
while (line)
{
	count++;
	free(line);
	line = ft_get_line(fd);
}

/* pass 2: read every line again */
file.lines = ft_calloc(count + 1, sizeof(char *));
while (i &lt; count)
	file.lines[i++] = ft_get_line(fd);

/* free_structs.c: clean up */
while (i &lt; file-&gt;line_count)
	free(file-&gt;lines[i++]);
free(file-&gt;lines);</pre>
			<div class="snippet__stats"><span><b>2×</b>file read</span><span><b>2N×</b>malloc</span><span><b>2N×</b>free</span></div>
		</figure>
		<figure class="snippet tone-ok">
			<figcaption class="snippet__head"><span class="snippet__tag">with an arena</span><span class="snippet__note">same work via libft</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">t_str8	file;
t_str8	line;

/* whole file: 1× push */
if (!ft_read_file(arena, path, &amp;file))
	return (false);

/* lines: just views into the buffer */
while (ft_str8_next_token(&amp;file, '\\n', &amp;line))
	parse_line(ft_str8_trim(line));

/* after parsing */
ft_arena_destroy(arena);</pre>
			<div class="snippet__stats"><span><b>1×</b>read</span><span><b>1×</b>push</span><span><b>0</b>malloc per line</span><span><b>1×</b>destroy</span></div>
		</figure>
	</div>
	</div>
</section>

<section class="slide" data-title="Think first, then code">
	<header class="slide__head">
		<div class="kicker">architecture · before you write the first line</div>
		<h2>Think first, then code</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--3">
		<div class="card tone-hot"><span class="card__num">1</span><b class="card__title">Understand the domain</b><p class="card__body">What is really in the problem? Which things, how many, and how big?</p></div>
		<div class="card tone-hot"><span class="card__num">2</span><b class="card__title">Follow the data</b><p class="card__body">Where does the data come from, who reads it, who changes it, and how often?</p></div>
		<div class="card tone-hot"><span class="card__num">3</span><b class="card__title">Split by access</b><p class="card__body">What is only read belongs together. So does what changes. What dies together shares memory.</p></div>
	</div>
	</div>
</section>

<section class="slide" data-title="NASA and TigerBeetle: allocate at startup">
	<header class="slide__head">
		<div class="kicker">we are not the first</div>
		<h2>Allocate at startup, not at runtime</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--2 mt">
		<figure class="card tone-c">
			<figcaption class="card__brand"><img class="card__logo" src="assets/logos/nasa.svg" alt="NASA"><span class="card__label">NASA / JPL · The Power of 10<br>Gerard Holzmann, 2006</span></figcaption>
			<blockquote class="card__quote">“Do not use dynamic memory allocation after initialization.”</blockquote>
			<p class="card__body">Rule no. 3 for software that must not crash.</p>
			<a class="card__link link" href="https://spinroot.com/gerard/pdf/P10.pdf" target="_blank" rel="noopener">spinroot.com/gerard/pdf/P10.pdf</a>
		</figure>
		<figure class="card tone-ok">
			<figcaption class="card__brand"><img class="card__logo card__logo--square" src="assets/logos/tigerbeetle.png" alt="TigerBeetle"><span class="card__label">TigerBeetle<br>TIGER_STYLE</span></figcaption>
			<blockquote class="card__quote">“All memory must be statically allocated at startup. No memory may be dynamically allocated (or freed and reallocated) after initialization.”</blockquote>
			<p class="card__body">A coding style that shaped how I write code.</p>
			<a class="card__link link" href="https://github.com/tigerbeetle/tigerbeetle/blob/main/docs/TIGER_STYLE.md" target="_blank" rel="noopener">github.com/tigerbeetle · TIGER_STYLE.md</a>
		</figure>
	</div>
	</div>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">cub3D · memory for the whole game</div>
		<h2>Measure first, then allocate once</h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
<pre class="code code--sm" data-component="code" data-lang="c">/* src/app/setup_memory.c */
*total = 0;
ft_arena_measure(total, 1, sizeof(t_rom));
ft_arena_measure(total, 1, sizeof(t_ram));
ft_arena_measure(total, tiles, sizeof(uint8_t));
ft_arena_measure(total, tiles, sizeof(t_fire_cell));
ft_arena_measure(total, hits, sizeof(t_ray_hit));
/* bonus: sprite_depth + scratch for the orbs */

/* src/app/setup.c */
game-&gt;arena = ft_arena_create(memory_size);

/* src/app/lifecycle.c */
ft_arena_destroy(game-&gt;arena);   /* done */</pre>
		<div class="stack stack--sm">
			<div class="card card--compact tone-ok"><span class="card__label">start</span><b class="card__title card__title--mono">1× <b>ft_arena_create</b></b><p class="card__body">Size computed up front from the map dimensions.</p></div>
			<div class="card card--compact tone-ok"><span class="card__label">playing</span><b class="card__title card__title--mono">0× <b>malloc</b> · 0× <b>free</b></b><p class="card__body">The game loop only uses what is already in the arena.</p></div>
			<div class="card card--compact tone-ok"><span class="card__label">end</span><b class="card__title card__title--mono">1× <b>ft_arena_destroy</b></b><p class="card__body">1 + 1 in total, the ideal from the counting slide.</p></div>
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
	</div>
</section>

<section class="slide" data-title="cub3D: who reads and who writes what (ROM and RAM)">
	<header class="slide__head">
		<div class="kicker">cub3D · data flow</div>
		<h2>Who reads the data and who changes it</h2>
	</header>
	<div class="slide__body">
	<div class="rw">
		<span></span>
		<span class="rw__col"><b>start</b><small>setup.c, once</small></span>
		<span class="rw__col"><b>update</b><small>every frame</small></span>
		<span class="rw__col"><b>render</b><small>every frame</small></span>

		<span class="rw__row tone-c"><b>t_rom</b><small>textures, colors, map size</small></span>
		<span class="rw__cell"><i class="rw__tag rw__tag--w">write</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i></span>

		<span class="rw__row tone-py"><b>t_ram</b><small>tiles, player, fire, orbs</small></span>
		<span class="rw__cell"><i class="rw__tag rw__tag--w">write</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i><i class="rw__tag rw__tag--w">write</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i><small>+ per-frame helper buffers</small></span>
	</div>
	<div class="cards cards--3 mt">
		<div class="card card--compact tone-c"><b class="card__title">t_rom never changes after startup</b><p class="card__body">Update and render only read it, so nothing can break it at runtime.</p></div>
		<div class="card card--compact tone-py"><b class="card__title">t_ram is the whole game state</b><p class="card__body">Everything that changes lives in one place.</p></div>
		<div class="card card--compact tone-hot"><b class="card__title">It’s not hardware</b><p class="card__body">ROM and RAM are just two structs, split by who changes the data.</p></div>
	</div>
	</div>
</section>

<section class="slide" data-title="Is it really faster? Evidence">
	<header class="slide__head">
		<div class="kicker">evidence · research and practice</div>
		<h2>Is it really faster?</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--3">
		<figure class="card card--compact tone-ok">
			<b class="card__value">17×</b>
			<p class="card__body">Our measurement: 20,000 lines × 500 tokens, <span class="nowrap">560 ms → 33 ms</span>.</p>
			<figcaption class="card__link">demos/c/arena.c · microbenchmark</figcaption>
		</figure>
		<figure class="card card--compact tone-c">
			<b class="card__value">up to 44%</b>
			<p class="card__body">Of 8 programs with a custom allocator, only the ones using regions (arenas) beat a general-purpose malloc.</p>
			<a class="card__link link" href="https://www.microsoft.com/en-us/research/?p=355667" target="_blank" rel="noopener">Berger, Zorn, McKinley · OOPSLA 2002</a>
		</figure>
		<figure class="card card--compact tone-py">
			<b class="card__value">up to 15%</b>
			<p class="card__body">Less CPU and memory in large Google applications after adding arenas to Go.</p>
			<a class="card__link link" href="https://github.com/golang/go/issues/51317" target="_blank" rel="noopener">Go proposal #51317 · 2022</a>
		</figure>
	</div>
	<div class="cards cards--2">
		<figure class="card card--compact tone-c">
			<span class="card__label">Protobuf · Google</span>
			<blockquote class="card__quote card__quote--sm">“Memory allocation and deallocation constitutes a significant fraction of CPU time spent in Protobuf code.”</blockquote>
			<p class="card__body">Arena: allocating is a pointer bump, freeing is almost free, data sits side by side in cache.</p>
			<a class="card__link link" href="https://protobuf.dev/reference/cpp/arenas" target="_blank" rel="noopener">protobuf.dev/reference/cpp/arenas</a>
		</figure>
		<figure class="card card--compact tone-hot">
			<span class="card__label">To be fair · van Kempen, Berger · ISMM 2026</span>
			<b class="card__title">Per-type custom allocators don’t beat a modern malloc. Bulk freeing and locality do.</b>
			<p class="card__body">Exactly what an arena does: everything at once, everything side by side.</p>
			<a class="card__link link" href="https://arxiv.org/abs/2605.17119" target="_blank" rel="noopener">arxiv.org/abs/2605.17119</a>
		</figure>
	</div>
	</div>
</section>
`);
