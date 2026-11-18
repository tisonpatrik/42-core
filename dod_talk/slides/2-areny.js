/* Arény: push_swap, aréna zevnitř, strom, počty, CUB3D, str8, parser, přemýšlej, NASA/TigerBeetle, změř, ROM/RAM, důkazy */

Talk.slides(`
<section data-section="Arény" class="slide slide--statement" data-title="git push --force · sudo swapoff -a">
	<h1 class="cmd" aria-label="git push --force, sudo swapoff -a">
		<span class="cmd__prompt">$</span><span class="cmd__tool">git</span><span class="cmd__key">push</span><span class="cmd__rest"> --force</span>
		<span class="cmd__prompt">$</span><span class="cmd__tool">sudo</span><span class="cmd__key">swap</span><span class="cmd__rest">off -a</span>
	</h1>
</section>

<section class="slide" data-title="push_swap: LIS bez arény vs. s arénou">
	<header class="slide__head">
		<div class="kicker">push_swap · separator · výpočet LIS</div>
		<h2>Pět polí, jeden lifetime</h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<figure class="snippet tone-hot">
			<figcaption class="snippet__head"><span class="snippet__tag">bez arény</span><span class="snippet__note">takhle by to vypadalo</span></figcaption>
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
c-&gt;previous_indices = malloc(sizeof(int) * n);
if (!c-&gt;previous_indices)
	return (free(c-&gt;lis_lengths), free(c-&gt;values),
		free(c-&gt;nodes), free(c), NULL);
/* + lis_nodes + free_computation() s 6× free */</pre>
			<div class="snippet__stats"><span><b>6×</b>malloc</span><span><b>6×</b>free</span><span><b>5</b>chybových cest</span></div>
		</figure>
		<figure class="snippet tone-ok">
			<figcaption class="snippet__head"><span class="snippet__tag">s arénou</span><span class="snippet__file">src/separator/separator_arena.c</span><span class="snippet__note">zkráceno</span></figcaption>
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
   stejně: jen posun offsetu */

/* separator.c, po výpočtu */
free_separator_arena(arena);</pre>
			<div class="snippet__stats"><span><b>1</b>blok</span><span><b>1×</b>free</span><span><b>1</b>return při chybě</span></div>
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

<section class="slide" data-title="Aréna zevnitř">
	<header class="slide__head">
		<div class="kicker">libft · src/allocator · push_swap</div>
		<h2>Aréna zevnitř</h2>
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
				<div class="abar__head"><span class="abar__step">1</span><code>ft_arena_create(size)</code><span class="muted">aréna pro výběr tahu</span></div>
				<div class="abar__track"><span class="abar__offset" style="--at: 0%"></span></div>
			</div>
			<div class="abar">
				<div class="abar__head"><span class="abar__step">2</span><code>select_best_move</code><span class="muted">3× push</span></div>
				<div class="abar__track"><span class="abar__seg tone-c" style="--w: 24">candidates</span><span class="abar__seg tone-py" style="--w: 18">filtered</span><span class="abar__seg tone-hot" style="--w: 12">top_k</span><span class="abar__offset" style="--at: 84.4%"></span></div>
			</div>
			<div class="abar">
				<div class="abar__head"><span class="abar__step">3</span><code>ft_arena_reset</code><span class="muted">tah zahraný, další od nuly</span></div>
				<div class="abar__track"><span class="abar__seg tone-cold" style="--w: 24">candidates</span><span class="abar__seg tone-cold" style="--w: 18">filtered</span><span class="abar__seg tone-cold" style="--w: 12">top_k</span><span class="abar__offset" style="--at: 0%"></span></div>
			</div>
			<div class="flow">
				<span class="flow__label hot">teď</span>
				<span class="flow__steps">create <i>→</i> tah <i>→</i> destroy <em>× každý tah</em></span>
				<span class="flow__label ok">lépe</span>
				<span class="flow__steps">create <i>→</i> tah <i>→</i> reset <i>→</i> tah <i>→ … →</i> destroy</span>
			</div>
		</div>
	</div>
	</div>
</section>

<section class="slide" data-title="Projektový strom: paměť zvlášť, logika zvlášť">
	<header class="slide__head">
		<div class="kicker">Jak to rozdělit</div>
		<h2>Paměť zvlášť, logika zvlášť</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-wide-left">
<div class="tree"><span class="tree__dir">push_swap/</span>
├── <span class="tree__dir">src/</span>
│   ├── <span class="tree__dir tree__dir--mem">memory/</span>         <span class="tree__note tree__note--mem">jediné místo s malloc / free</span>
│   │   ├── arena.c      <span class="tree__note">create · push · reset · destroy</span>
│   │   └── budget.c     <span class="tree__note">kolik paměti potřebuje celý běh</span>
│   ├── main.c           <span class="tree__note">1× create … 1× destroy</span>
│   ├── <span class="tree__dir">validator/</span>      <span class="tree__brace">│</span>
│   ├── <span class="tree__dir">stack/</span>          <span class="tree__brace">│</span> <span class="tree__note">business logika</span>
│   ├── <span class="tree__dir">ops/</span>            <span class="tree__brace">│</span> <span class="tree__note">dostane t_arena *,</span>
│   ├── <span class="tree__dir">selector/</span>       <span class="tree__brace">│</span> <span class="tree__note">nikdy nevolá</span>
│   ├── <span class="tree__dir">separator/</span>      <span class="tree__brace">│</span> <span class="tree__note">malloc ani free</span>
│   └── <span class="tree__dir">solver/</span>         <span class="tree__brace">│</span>
└── Makefile</div>
		<div class="rule">
			<p class="rule__main"><span class="rule__code">malloc</span> a <span class="rule__code">free</span><br>jen v <span class="rule__code">memory/</span></p>
			<p class="rule__sub">Zbytek kódu paměť dostává,<br>nevlastní ji.</p>
		</div>
	</div>
	</div>
</section>

<section class="slide" data-title="Kolikrát v kódu píšu malloc a free">
	<header class="slide__head">
		<div class="kicker">push_swap · statický počet v src/</div>
		<h2>Kolikrát v kódu píšu <code>malloc</code> a <code>free</code>?</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-2">
		<div class="stack stack--sm">
			<div class="tally tone-hot">
				<span class="tally__label">bez arén</span>
				<span class="tally__num">26<small>× malloc</small></span>
				<span class="tally__num">70<small>× free</small></span>
			</div>
			<div class="tally tone-py">
				<span class="tally__label">s arénami</span>
				<span class="tally__num">15<small>× malloc</small></span>
				<span class="tally__num">20<small>× free</small></span>
			</div>
			<div class="tally tone-ok">
				<span class="tally__label">ideál</span>
				<span class="tally__num">1<small>× malloc</small></span>
				<span class="tally__num">1<small>× free</small></span>
			</div>
		</div>
		<div class="sites">
			<div class="sites__row sites__row--head"><span></span><span class="sites__group">bez arén</span><span class="sites__group">s arénami</span><span class="sites__group">ideál</span></div>
			<div class="sites__row sites__row--sub"><span>modul</span><span>m</span><span>f</span><span>m</span><span>f</span><span>m</span><span>f</span></div>
			<div class="sites__row"><span class="sites__mod">validator/</span><span class="sites__n">5</span><span class="sites__n">7</span><span class="sites__n">5</span><span class="sites__n">7</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">stack/</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">ops/</span><span class="sites__n">2</span><span class="sites__n">3</span><span class="sites__n">2</span><span class="sites__n">3</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">optimizer/</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row sites__row--hl"><span class="sites__mod">selector/</span><span class="sites__n">8</span><span class="sites__n">30</span><span class="sites__n">3</span><span class="sites__n">6</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row sites__row--hl"><span class="sites__mod">separator/</span><span class="sites__n">7</span><span class="sites__n">28</span><span class="sites__n">1</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">main.c</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">1</span><span class="sites__n">1</span></div>
			<div class="sites__row sites__row--total"><span class="sites__mod">celkem</span><span class="sites__n">26</span><span class="sites__n">70</span><span class="sites__n">15</span><span class="sites__n">20</span><span class="sites__n">1</span><span class="sites__n">1</span></div>
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

<section class="slide" data-title="t_str8 zevnitř">
	<header class="slide__head">
		<div class="kicker">libft · src/str8</div>
		<h2><code>t_str8</code> zevnitř</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-wide-left">
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_str8
{
	uint8_t	*str;
	size_t	len;
}	t_str8;

/* pohled do existující paměti: 0 alokací */
t_str8	ft_str8_create(uint8_t *str, size_t len)
{
	return ((t_str8){str, len});
}

/* nový řetězec: 1× push do arény (zkráceno o kontroly) */
t_str8	ft_str8_join(t_arena *arena, t_str8 a, t_str8 b)
{
	t_str8	res;

	res.len = a.len + b.len;
	res.str = ft_arena_push(arena, res.len + 1);
	if (!res.str)
		return ((t_str8){NULL, 0});
	ft_memcpy(res.str, a.str, a.len);
	ft_memcpy(res.str + a.len, b.str, b.len);
	return (res);
}</pre>
		<div class="facts facts--big">
			<span><b>substr · trim · next_token</b> jen pohled, 0 alokací</span>
			<span><b>join · dup · split</b> 1× push do arény</span>
			<span><b>free</b> neexistuje, uklidí reset arény</span>
		</div>
	</div>
	</div>
</section>

<section class="slide" data-title="cub3D parser: řádky přes malloc vs. str8 + aréna">
	<header class="slide__head">
		<div class="kicker">cub3D · načtení .cub souboru</div>
		<h2>Řádky bez <code>malloc</code></h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<figure class="snippet tone-hot">
			<figcaption class="snippet__head"><span class="snippet__tag">teď</span><span class="snippet__file">src/parser/init_file.c</span><span class="snippet__note">zkráceno</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">/* 1. průchod: spočítej řádky */
line = ft_get_line(fd);
while (line)
{
	count++;
	free(line);
	line = ft_get_line(fd);
}

/* 2. průchod: každý řádek znovu */
file.lines = ft_calloc(count + 1, sizeof(char *));
while (i &lt; count)
	file.lines[i++] = ft_get_line(fd);

/* free_structs.c: uklidit */
while (i &lt; file-&gt;line_count)
	free(file-&gt;lines[i++]);
free(file-&gt;lines);</pre>
			<div class="snippet__stats"><span><b>2×</b>čtení souboru</span><span><b>2N×</b>malloc</span><span><b>2N×</b>free</span></div>
		</figure>
		<figure class="snippet tone-ok">
			<figcaption class="snippet__head"><span class="snippet__tag">s arénou</span><span class="snippet__note">stejná práce přes libft</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">t_str8	file;
t_str8	line;

/* celý soubor: 1× push */
if (!ft_read_file(arena, path, &amp;file))
	return (false);

/* řádky: jen pohledy do bufferu */
while (ft_str8_next_token(&amp;file, '\\n', &amp;line))
	parse_line(ft_str8_trim(line));

/* po parsování */
ft_arena_destroy(arena);</pre>
			<div class="snippet__stats"><span><b>1×</b>čtení</span><span><b>1×</b>push</span><span><b>0</b>malloc na řádek</span><span><b>1×</b>destroy</span></div>
		</figure>
	</div>
	</div>
</section>

<section class="slide" data-title="Nejdřív přemýšlej, potom programuj">
	<header class="slide__head">
		<div class="kicker">architektura · než napíšeš první řádek</div>
		<h2>Nejdřív přemýšlej, potom programuj</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--3">
		<div class="card tone-hot"><span class="card__num">1</span><b class="card__title">Pochop doménu</b><p class="card__body">Co v problému doopravdy je? Jaké věci, kolik jich je a jak jsou velké?</p></div>
		<div class="card tone-hot"><span class="card__num">2</span><b class="card__title">Sleduj tok dat</b><p class="card__body">Odkud data přicházejí, kdo je čte, kdo je mění a jak často?</p></div>
		<div class="card tone-hot"><span class="card__num">3</span><b class="card__title">Rozděl podle přístupu</b><p class="card__body">Co se jen čte, patří k sobě. Co se mění, taky. Co umírá spolu, sdílí paměť.</p></div>
	</div>
	</div>
</section>

<section class="slide" data-title="NASA a TigerBeetle: alokuj na startu">
	<header class="slide__head">
		<div class="kicker">nejsme první</div>
		<h2>Alokuj na startu, ne za běhu</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--2 mt">
		<figure class="card tone-c">
			<figcaption class="card__brand"><img class="card__logo" src="assets/logos/nasa.svg" alt="NASA"><span class="card__label">NASA / JPL · The Power of 10<br>Gerard Holzmann, 2006</span></figcaption>
			<blockquote class="card__quote">„Do not use dynamic memory allocation after initialization.“</blockquote>
			<p class="card__body">Pravidlo č. 3 pro software, který nesmí spadnout.</p>
			<a class="card__link link" href="https://spinroot.com/gerard/pdf/P10.pdf" target="_blank" rel="noopener">spinroot.com/gerard/pdf/P10.pdf</a>
		</figure>
		<figure class="card tone-ok">
			<figcaption class="card__brand"><img class="card__logo card__logo--square" src="assets/logos/tigerbeetle.png" alt="TigerBeetle"><span class="card__label">TigerBeetle<br>TIGER_STYLE</span></figcaption>
			<blockquote class="card__quote">„All memory must be statically allocated at startup. No memory may be dynamically allocated (or freed and reallocated) after initialization.“</blockquote>
			<p class="card__body">Coding style, který mě hodně ovlivnil.</p>
			<a class="card__link link" href="https://github.com/tigerbeetle/tigerbeetle/blob/main/docs/TIGER_STYLE.md" target="_blank" rel="noopener">github.com/tigerbeetle · TIGER_STYLE.md</a>
		</figure>
	</div>
	</div>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">cub3D · paměť celé hry</div>
		<h2>Nejdřív změř, pak alokuj jednou</h2>
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
/* bonus: sprite_depth + scratch pro orby */

/* src/app/setup.c */
game-&gt;arena = ft_arena_create(memory_size);

/* src/app/lifecycle.c */
ft_arena_destroy(game-&gt;arena);   /* hotovo */</pre>
		<div class="stack stack--sm">
			<div class="card card--compact tone-ok"><span class="card__label">start</span><b class="card__title card__title--mono">1× <b>ft_arena_create</b></b><p class="card__body">Velikost spočítaná předem z rozměrů mapy.</p></div>
			<div class="card card--compact tone-ok"><span class="card__label">hraní</span><b class="card__title card__title--mono">0× <b>malloc</b> · 0× <b>free</b></b><p class="card__body">Herní smyčka jen používá, co už v aréně je.</p></div>
			<div class="card card--compact tone-ok"><span class="card__label">konec</span><b class="card__title card__title--mono">1× <b>ft_arena_destroy</b></b><p class="card__body">Celkem 1 + 1, ideál ze slidu o počtech.</p></div>
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

<section class="slide" data-title="cub3D: kdo co čte a kdo co zapisuje (ROM a RAM)">
	<header class="slide__head">
		<div class="kicker">cub3D · tok dat</div>
		<h2>Kdo data čte a kdo je mění</h2>
	</header>
	<div class="slide__body">
	<div class="rw">
		<span></span>
		<span class="rw__col"><b>start</b><small>setup.c, jednou</small></span>
		<span class="rw__col"><b>update</b><small>každý snímek</small></span>
		<span class="rw__col"><b>render</b><small>každý snímek</small></span>

		<span class="rw__row tone-c"><b>t_rom</b><small>textury, barvy, rozměry mapy</small></span>
		<span class="rw__cell"><i class="rw__tag rw__tag--w">zápis</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">čtení</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">čtení</i></span>

		<span class="rw__row tone-py"><b>t_ram</b><small>dlaždice, hráč, oheň, orby</small></span>
		<span class="rw__cell"><i class="rw__tag rw__tag--w">zápis</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">čtení</i><i class="rw__tag rw__tag--w">zápis</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">čtení</i><small>+ pomocné buffery snímku</small></span>
	</div>
	<div class="cards cards--3 mt">
		<div class="card card--compact tone-c"><b class="card__title">t_rom se po startu nemění</b><p class="card__body">Update i render ji jen čtou, takže ji nic za běhu nerozbije.</p></div>
		<div class="card card--compact tone-py"><b class="card__title">t_ram je celý stav hry</b><p class="card__body">Všechno, co se mění, je pohromadě na jednom místě.</p></div>
		<div class="card card--compact tone-hot"><b class="card__title">Není to hardware</b><p class="card__body">ROM a RAM jsou jen dva structy rozdělené podle toho, kdo data mění.</p></div>
	</div>
	</div>
</section>

<section class="slide" data-title="Je to opravdu rychlejší? Důkazy">
	<header class="slide__head">
		<div class="kicker">důkazy · výzkum a praxe</div>
		<h2>Je to opravdu rychlejší?</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--3">
		<figure class="card card--compact tone-ok">
			<b class="card__value">17×</b>
			<p class="card__body">Naše měření: 20 000 řádků × 500 tokenů, <span class="nowrap">560 ms → 33 ms</span>.</p>
			<figcaption class="card__link">demos/c/arena.c · mikrobenchmark</figcaption>
		</figure>
		<figure class="card card--compact tone-c">
			<b class="card__value">až 44 %</b>
			<p class="card__body">Z 8 programů s vlastním alokátorem porazily obecný malloc jen ty s regiony (arénami).</p>
			<a class="card__link link" href="https://www.microsoft.com/en-us/research/?p=355667" target="_blank" rel="noopener">Berger, Zorn, McKinley · OOPSLA 2002</a>
		</figure>
		<figure class="card card--compact tone-py">
			<b class="card__value">až 15 %</b>
			<p class="card__body">Méně CPU i paměti ve velkých aplikacích Google po zavedení arén v Go.</p>
			<a class="card__link link" href="https://github.com/golang/go/issues/51317" target="_blank" rel="noopener">Go proposal #51317 · 2022</a>
		</figure>
	</div>
	<div class="cards cards--2">
		<figure class="card card--compact tone-c">
			<span class="card__label">Protobuf · Google</span>
			<blockquote class="card__quote card__quote--sm">„Memory allocation and deallocation constitutes a significant fraction of CPU time spent in Protobuf code.“</blockquote>
			<p class="card__body">Aréna: alokace je posun ukazatele, uvolnění téměř zdarma, data leží za sebou v cache.</p>
			<a class="card__link link" href="https://protobuf.dev/reference/cpp/arenas" target="_blank" rel="noopener">protobuf.dev/reference/cpp/arenas</a>
		</figure>
		<figure class="card card--compact tone-hot">
			<span class="card__label">Poctivě · van Kempen, Berger · ISMM 2026</span>
			<b class="card__title">Vlastní alokátor na jednotlivé typy proti modernímu malloc nepomůže. Pomáhá hromadné uvolnění a lokalita.</b>
			<p class="card__body">Přesně to, co aréna dělá: všechno najednou, všechno za sebou.</p>
			<a class="card__link link" href="https://arxiv.org/abs/2605.17119" target="_blank" rel="noopener">arxiv.org/abs/2605.17119</a>
		</figure>
	</div>
	</div>
</section>
`);
