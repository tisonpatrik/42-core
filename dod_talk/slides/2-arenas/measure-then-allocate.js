/* Measure first, then allocate once */

Talk.slides(`
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
`);
