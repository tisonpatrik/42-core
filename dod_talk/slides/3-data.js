/* Jak organizovat data: cache, latence, AoS/SoA v Pythonu a C, cache line, hot/cold, ROM/RAM × hot/cold */

Talk.slides(`
<section data-section="Jak organizovat data" class="slide" data-title="Co je cache">
	<header class="slide__head">
		<div class="kicker">hardware · cache</div>
		<h2>Co je L1 a L2 cache?</h2>
		<p class="lede">Malá a rychlá paměť přímo v procesoru. Co CPU použilo nedávno, drží co nejblíž.</p>
	</header>
	<div class="slide__body">
		<div class="hier">
			<div class="hier__item hier__item--core"><b>CPU jádro</b><span>počítá</span></div>
			<div class="hier__item tone-ok" style="--size: 1"><b>L1</b><span class="hier__size">32 KB</span><span class="hier__like">stůl</span></div>
			<div class="hier__item tone-c" style="--size: 2"><b>L2</b><span class="hier__size">512 KB</span><span class="hier__like">polička</span></div>
			<div class="hier__item tone-py" style="--size: 3"><b>L3</b><span class="hier__size">8 MB</span><span class="hier__like">skříň</span></div>
			<div class="hier__item tone-hot" style="--size: 4"><b>RAM</b><span class="hier__size">32 GB</span><span class="hier__like">knihovna přes město</span></div>
		</div>
		<div class="hier__axis"><span>blíž, menší, rychlejší</span><span>dál, větší, pomalejší</span></div>
	</div>
	<footer class="slide__foot">
		<p class="source">Velikosti z notebooku, na kterém prezentuju: AMD Ryzen 5 PRO 4650U (L1 a L2 na jádro, L3 sdílená)</p>
	</footer>
</section>

<section class="slide" data-title="Latence: CPU čeká na data">
	<header class="slide__head">
		<div class="kicker">hardware · latence</div>
		<h2>CPU většinu času čeká na data</h2>
		<p class="lede">Kdyby čtení z L1 cache trvalo jednu sekundu…</p>
	</header>
	<div class="slide__body">
		<div class="scale" data-component="scale" data-source="latency"></div>
	</div>
	<footer class="slide__foot">
		<p class="source" data-component="sources" data-source="latency">L1–RAM: cykly Zen 2 při 4 GHz · SSD a síť řádově ·</p>
	</footer>
</section>

<section class="slide" data-title="AoS vs SoA v kódu (Python)">
	<header class="slide__head">
		<div class="kicker"><span class="keep-case">AoS vs SoA</span> · Python · 1M částic</div>
		<h2>Stejná práce, jinak uložená data</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">AoS</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">pole objektů</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">N = 1_000_000      # počet částic
DT = 1 / 60        # jeden snímek při 60 FPS

class Particle:
    def __init__(self):
        self.x = self.y = self.z = 0.0
        self.vx = self.vy = self.vz = 1.0

ps = [Particle() for _ in range(N)]

for p in ps:
    p.x += p.vx * DT
    p.y += p.vy * DT
    p.z += p.vz * DT</pre>
				<div class="snippet__stats"><span><b>188 ms</b>na krok</span><span><b>191 MiB</b>paměti</span></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">SoA</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">pole na každý atribut</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">import numpy as np

N = 1_000_000      # počet částic
DT = 1 / 60        # jeden snímek při 60 FPS

x  = np.zeros(N, np.float32)   # y, z stejně
vx = np.ones(N, np.float32)    # vy, vz stejně

x += vx * DT
y += vy * DT
z += vz * DT</pre>
				<div class="snippet__stats"><span><b>3,7 ms</b>na krok</span><span><b>23 MiB</b>paměti</span></div>
			</figure>
		</div>
	</div>
</section>

<section class="slide" data-title="AoS vs SoA v čistém C">
	<header class="slide__head">
		<div class="kicker"><span class="keep-case">AoS vs SoA</span> · čisté C · bez knihovny</div>
		<h2>Totéž naplocho v C</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">AoS</span><span class="snippet__note">pole structů</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">#define N 1000000         /* počet částic */
#define DT (1.0f / 60)    /* jeden snímek */

typedef struct s_particle
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
}	t_particle;

t_particle	ps[N];
i = 0;
while (i &lt; N)
{
	ps[i].x += ps[i].vx * DT;
	i++;
}</pre>
				<div class="snippet__mem"><i class="is-read">x</i><i>y</i><i>z</i><i class="is-read">vx</i><i>vy</i><i>vz</i><i class="is-read">x</i><i>y</i><i>z</i><i class="is-read">vx</i><i>vy</i><i>vz</i><i class="snippet__more">…</i></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">SoA</span><span class="snippet__note">struct polí</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">#define N 1000000         /* počet částic */
#define DT (1.0f / 60)    /* jeden snímek */

typedef struct s_particles
{
	float	x[N];
	float	y[N];
	float	z[N];
	float	vx[N];
	float	vy[N];
	float	vz[N];
}	t_particles;

t_particles	ps;
i = 0;
while (i &lt; N)
{
	ps.x[i] += ps.vx[i] * DT;
	i++;
}</pre>
				<div class="snippet__mem"><i class="is-read">x</i><i class="is-read">x</i><i class="is-read">x</i><i class="is-read">x</i><i class="is-read">x</i><i class="snippet__more">… y[N] z[N] …</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="snippet__more">…</i></div>
			</figure>
		</div>
	</div>
</section>

<section class="slide" data-title="Cache line: AoS vs SoA">
	<header class="slide__head">
		<div class="kicker">cache line · <span class="keep-case">AoS vs SoA</span> · kód z minulého slidu</div>
		<h2>CPU nečte bajty, čte řádky po 64 B</h2>
	</header>
	<div class="slide__body">
		<div class="lines">
			<div class="lines__row tone-hot">
				<div class="lines__label"><b>AoS</b><span>t_particle ps[N]</span></div>
				<div class="cacheline" data-component="cacheline" data-pattern="aos"></div>
				<div class="lines__stat"><b>33 %</b><span>načtených bajtů smyčka použije</span></div>
			</div>
			<div class="lines__row tone-ok">
				<div class="lines__label"><b>SoA</b><span>t_particles ps</span></div>
				<div class="cacheline" data-component="cacheline" data-pattern="soa"></div>
				<div class="lines__stat"><b>100 %</b><span>načtených bajtů smyčka použije</span></div>
			</div>
		</div>
		<div class="legend">
			<span><b class="legend__swatch tone-hot"></b>čte smyčka: x a vx</span>
			<span><b class="legend__swatch tone-cold"></b>načte se zbytečně</span>
			<span>1 políčko = 4 B · 1 řádek = 64 B</span>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-hot"><b class="card__value">377 000</b><p class="card__body">cache line na krok s AoS</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">128 000</b><p class="card__body">cache line na krok se SoA, 3× méně</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">4,3×</b><p class="card__body">rychlejší krok, 2,1 ms → 0,49 ms</p><span class="card__link">demos/c/particles.c · perf stat</span></div>
		</div>
	</div>
</section>

<section class="slide" data-title="Hot/cold split: jak rozdělit struct">
	<header class="slide__head">
		<div class="kicker">hot/cold split · co když struct potřebuje víc?</div>
		<h2>Rozděl struct podle toho, kdo ho čte</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag">jeden struct</span><span class="snippet__file">demos/c/hotcold.c</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_particle
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_particle;
t_particle	g_ps[N];</pre>
				<div class="snippet__stats"><span><b>72 B</b>na částici</span><span><b>24 B</b>z nich čte smyčka</span></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag">hot + cold</span><span class="snippet__file">demos/c/hotcold.c</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_hot     /* každý snímek */
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
}	t_hot;

typedef struct s_cold    /* jen občas */
{
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_cold;
t_hot	g_hot[N];
t_cold	g_cold[N];       /* stejné i = stejná částice */</pre>
				<div class="snippet__stats"><span><b>24 B</b>hot, čte smyčka</span><span><b>48 B</b>cold, leží jinde</span></div>
			</figure>
		</div>
	</div>
</section>

<section class="slide" data-title="Hot/cold split: měření">
	<header class="slide__head">
		<div class="kicker">hot/cold split · co to udělá s cache</div>
		<h2>Co smyčka nečte, ať leží jinde</h2>
	</header>
	<div class="slide__body">
		<div class="lines">
			<div class="lines__row tone-hot">
				<div class="lines__label"><b>1 struct</b><span>t_particle, 72 B</span></div>
				<div class="cacheline" data-component="cacheline" data-fields="x y z vx vy vz name:8 color mass flags id" data-read="x y z vx vy vz"></div>
				<div class="lines__stat"><b>33 %</b><span>načtených bajtů smyčka použije</span></div>
			</div>
			<div class="lines__row tone-ok">
				<div class="lines__label"><b>hot + cold</b><span>t_hot[N], t_cold[N]</span></div>
				<div class="cacheline" data-component="cacheline" data-fields="x y z vx vy vz" data-read="x y z vx vy vz"></div>
				<div class="lines__stat"><b>100 %</b><span>načtených bajtů smyčka použije</span></div>
			</div>
		</div>
		<div class="legend">
			<span><b class="legend__swatch tone-hot"></b>hot: čte každý snímek</span>
			<span><b class="legend__swatch tone-cold"></b>cold: name, color, mass, flags, id</span>
			<span>1 políčko = 4 B · 1 řádek = 64 B</span>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-ok"><b class="card__value">3× méně</b><p class="card__body">cache line na krok, 1 137 000 → 386 000</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">2–3×</b><p class="card__body">rychlejší krok, ≈ 8,5 ms → 3–5 ms (9 běhů)</p><span class="card__link">demos/c/hotcold.c · perf stat</span></div>
			<div class="card card--compact tone-c"><b class="card__title">Stejný nápad jako ROM/RAM</b><p class="card__body">V cub3D dělíme data podle toho, kdo je mění. Tady podle toho, jak často je čteme.</p></div>
		</div>
	</div>
</section>

<section class="slide" data-title="ROM/RAM × hot/cold">
	<header class="slide__head">
		<div class="kicker">ROM/RAM × hot/cold · dvě nezávislé otázky</div>
		<h2>Mění se to? Jak často to čteme?</h2>
	</header>
	<div class="slide__body">
		<div class="rw rw--2">
			<span></span>
			<span class="rw__col tone-hot"><b>hot</b><small>čte se každý snímek</small></span>
			<span class="rw__col"><b>cold</b><small>čte se jen občas</small></span>

			<span class="rw__row tone-c"><b>ROM</b><small>po startu se nemění</small></span>
			<span class="rw__cell"><span class="rw__text">textury, rozměry mapy</span></span>
			<span class="rw__cell"><span class="rw__text">nastavení, cesty k souborům</span></span>

			<span class="rw__row tone-py"><b>RAM</b><small>mění se za běhu</small></span>
			<span class="rw__cell"><span class="rw__text">hráč, dlaždice, oheň</span></span>
			<span class="rw__cell"><span class="rw__text">skóre, stav menu</span></span>
		</div>
		<div class="cards cards--2">
			<div class="card card--compact tone-c"><span class="card__label">ROM/RAM · správnost</span><p class="card__body">Co se nemění, nikdo omylem nerozbije. Restart hry = nová RAM.</p></div>
			<div class="card card--compact tone-hot"><span class="card__label">hot/cold · výkon</span><p class="card__body">Smyčka tahá do cache jen to, co opravdu čte.</p></div>
		</div>
	</div>
</section>
`);
