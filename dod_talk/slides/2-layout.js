/* 2 · Layout: AoS → SoA, cub3D mapa a paralelní pole, triky, Python */

Talk.slides(`
<section class="slide">
	<div class="kicker">2 · Layout</div>
	<h2>Array of Structs → Struct of Arrays</h2>
	<div class="grid grid--fill cols-2">
<pre class="code code--sm" data-component="code" data-lang="c">typedef struct s_particle   /* AoS, 72 B */
{
	float	x, y, z;
	float	vx, vy, vz;
	char	name[32];
	int		color;
	float	mass;
	/* ... */
}	t_particle;

typedef struct s_particles  /* SoA */
{
	float	*x, *y, *z;
	float	*vx, *vy, *vz;
}	t_particles;

p.x[i] += p.vx[i] * dt;</pre>
<pre class="code code--sm" data-component="code" data-lang="py">class Particle:                  # AoS
    def __init__(self, i):
        self.x = self.y = self.z = 0.0
        self.vx = float(i % 7)
        # ...

for p in particles:
    p.x += p.vx * DT


# SoA
x  = np.zeros(N, np.float32)
vx = np.arange(N) % 7

x += vx * DT                     # celé pole</pre>
	</div>
</section>

<section class="slide">
	<div class="kicker">2 · Layout · výsledky</div>
	<h2>Jeden update pozic, jeden krok</h2>
	<div class="grid grid--fill cols-2">
		<div class="card">
			<h3><span class="pill tone-c">C</span>4M částic, ms / krok</h3>
			<div class="bars" data-component="bars" data-unit=" ms">
				<div data-label="AoS" data-value="27" data-tone="c"></div>
				<div data-label="SoA" data-value="5.8" data-tone="c" data-delta="4,6×"></div>
			</div>
		</div>
		<div class="card">
			<h3><span class="pill tone-py">Python</span>1M částic, ms / krok</h3>
			<div class="bars" data-component="bars" data-unit=" ms">
				<div data-label="objekty" data-value="171" data-tone="py"></div>
				<div data-label="__slots__" data-value="166" data-tone="py"></div>
				<div data-label="numpy" data-value="3.7" data-tone="py" data-delta="~45×"></div>
			</div>
			<h3 class="mt">paměť, MiB</h3>
			<div class="bars" data-component="bars" data-unit=" MiB">
				<div data-label="objekty" data-value="191" data-tone="hot"></div>
				<div data-label="__slots__" data-value="153" data-tone="hot"></div>
				<div data-label="numpy" data-value="23" data-tone="hot" data-delta="8×"></div>
			</div>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">2 · Layout · náš cub3D</div>
	<h2>Mapa: parser vs. engine</h2>
	<div class="grid grid--fill cols-2">
		<div>
			<p class="small muted mb-sm"><code>include/parser.h</code>: jak to píše každý</p>
<pre class="code code--sm" data-component="code" data-lang="c">typedef struct s_map
{
	char	**grid;   /* rows × malloc */
	int		rows;
	int		max_cols;
	/* ... */
}	t_map;

grid[y][x]  /* pointer → pointer → char */</pre>
			<p class="small mt">N řádků = N alokací, N lifetimes, N× <code>free</code>.</p>
		</div>
		<div>
			<p class="small muted mb-sm"><code>src/world/world.c</code>: engine po parsování</p>
<pre class="code code--sm" data-component="code" data-lang="c">uint8_t	*tiles;   /* jeden blok w × h */

bool	world_index(const t_game *game,
			t_v2i map, size_t *index)
{
	if (!index || !world_contains(game, map))
		return (false);
	*index = (size_t)map.y
		* (size_t)game-&gt;rom-&gt;map_size.x
		+ (size_t)map.x;
	return (true);
}</pre>
			<p class="small mt"><code>tiles[i]</code>: 1 B na buňku, souvislé, kopíruje se jedním <code>memcpy</code>.</p>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">2 · Layout · náš cub3D</div>
	<h2>Paralelní pole: index místo pointeru</h2>
	<div class="grid grid--fill cols-2">
<pre class="code code--sm" data-component="code" data-lang="c">typedef struct s_fire_cell     /* 16 B */
{
	t_fire_state	state;
	double			height;
}	t_fire_cell;

/* tiles[i] a fire.cells[i] = stejná buňka */
while (i &lt; tile_count)
{
	cell = &amp;game-&gt;ram-&gt;fire.cells[i];
	if (game-&gt;ram-&gt;tiles[i] == TILE_FIRE)
	{
		cell-&gt;state = FIRE_IDLE;
		cell-&gt;height = 1.0;
		game-&gt;ram-&gt;fire.count++;
	}
	i++;
}</pre>
		<div class="stack">
			<div class="card"><h3>Žádné <code>t_fire *</code> v tile</h3><p>Raycast čte jen <code>tiles[]</code> (1 B). Výška ohně (16 B) se načte, jen když paprsek opravdu trefí oheň. To je hot/cold split.</p></div>
			<div class="card"><h3>ROM vs. RAM</h3><p><code>t_rom</code>: textury, barvy, <code>map_size</code>, po setupu jen čtení.<br><code>t_ram</code>: tiles, hráč, oheň, orby, mění se každý frame.</p></div>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">2 · Layout · tahák</div>
	<h2>Čtyři triky, které fungují všude</h2>
	<div class="grid grid--tight cols-2">
		<div class="card"><h3>Hot / cold split</h3><p>Co čte hot loop, dej k sobě. Jména, debug info, statistiky dej jinam.</p></div>
		<div class="card"><h3>Existence-based processing</h3><p>Místo <code>if (orb.active)</code> v každém framu drž pole jen aktivních. Žádná data = žádná větev.</p></div>
		<div class="card"><h3>Indexy místo pointerů</h3><p><code>uint32_t</code> je 4 B, pointer 8 B. Index přežije <code>realloc</code> a jde serializovat.</p></div>
		<div class="card"><h3>Funkce nad polem</h3><p><code>update_all(particles, n)</code> místo <code>p-&gt;update()</code>. Kompilátor může vektorizovat a v Pythonu to jde do NumPy.</p></div>
	</div>
</section>

<section class="slide">
	<div class="kicker">2 · Layout · Python ve skutečném světě</div>
	<h2>Rychlý Python = Python, který řídí C nad poli</h2>
	<div class="grid grid--tight cols-2">
		<div class="card"><h3><span class="pill tone-py">NumPy</span></h3><p>SoA v C. Každý vektorový výraz je jeden průchod souvislou pamětí.</p></div>
		<div class="card"><h3><span class="pill tone-py">Polars · Apache Arrow</span></h3><p>Sloupcový formát (columnar) = SoA pro tabulky. Proto je Polars rychlejší než klasický pandas.</p></div>
		<div class="card"><h3><span class="pill tone-py">pandas 2</span></h3><p>Volitelný Arrow backend: i pandas se posouvá ke sloupcům.</p></div>
		<div class="card"><h3><span class="pill tone-py">ECS (esper)</span></h3><p>Entity–Component–System: herní DOD. Entita je jen ID, komponenty jsou pole.</p></div>
	</div>
</section>
`);
