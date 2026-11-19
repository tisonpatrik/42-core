/* Organizing data: cache, latency, AoS/SoA in C and Python, cache line, hot/cold, ROM/RAM × hot/cold, Beyond the core, SIMD, threads, what's next, tools, trade-off, Knuth */

Talk.slides(`
<section data-section="Organizing data" class="slide" data-title="What is a cache">
	<header class="slide__head">
		<div class="kicker">hardware · cache</div>
		<h2>What are L1, L2 and L3 caches?</h2>
		<p class="lede">Small, fast memory right inside the CPU. Whatever the CPU used recently, it keeps as close as it can.</p>
	</header>
	<div class="slide__body">
		<div class="hier">
			<div class="hier__item hier__item--core"><b>CPU core</b><span>computes</span></div>
			<div class="hier__item tone-ok" style="--size: 1"><b>L1</b><span class="hier__size">32 KB</span><span class="hier__like">desk</span></div>
			<div class="hier__item tone-c" style="--size: 2"><b>L2</b><span class="hier__size">512 KB</span><span class="hier__like">shelf</span></div>
			<div class="hier__item tone-py" style="--size: 3"><b>L3</b><span class="hier__size">8 MB</span><span class="hier__like">cupboard</span></div>
			<div class="hier__item tone-hot" style="--size: 4"><b>RAM</b><span class="hier__size">32 GB</span><span class="hier__like">library across town</span></div>
		</div>
		<div class="hier__axis"><span>closer, smaller, faster</span><span>farther, bigger, slower</span></div>
	</div>
	<footer class="slide__foot">
		<p class="source">Sizes from the laptop I’m presenting on: AMD Ryzen 5 PRO 4650U (L1 and L2 per core, L3 shared)</p>
	</footer>
</section>

<section class="slide" data-title="Latency: the CPU waits for data">
	<header class="slide__head">
		<div class="kicker">hardware · latency</div>
		<h2>The CPU spends most of its time waiting for data</h2>
		<p class="lede">If a read from L1 cache took one second…</p>
	</header>
	<div class="slide__body">
		<div class="scale" data-component="scale" data-source="latency"></div>
	</div>
	<footer class="slide__foot">
		<p class="source" data-component="sources" data-source="latency">L1–RAM: Zen 2 cycles at 4 GHz · SSD and network: orders of magnitude ·</p>
	</footer>
</section>

<section class="slide" data-title="AoS vs SoA in plain C">
	<header class="slide__head">
		<div class="kicker"><span class="keep-case">AoS vs SoA</span> · plain C · no library</div>
		<h2>AoS and SoA, flat in C</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">AoS</span><span class="snippet__note">array of structs</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">#define N 1000000         /* number of particles */
#define DT (1.0f / 60)    /* one frame */
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
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">SoA</span><span class="snippet__note">struct of arrays</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">#define N 1000000         /* number of particles */
#define DT (1.0f / 60)    /* one frame */
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

<section class="slide" data-title="AoS vs SoA in code (Python)">
	<header class="slide__head">
		<div class="kicker"><span class="keep-case">AoS vs SoA</span> · Python · 1M particles</div>
		<h2>Same work, different data layout</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">AoS</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">list of objects</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">N = 1_000_000      # number of particles
DT = 1 / 60        # one frame at 60 FPS

class Particle:
    def __init__(self):
        self.x = self.y = self.z = 0.0
        self.vx = self.vy = self.vz = 1.0

ps = [Particle() for _ in range(N)]

for p in ps:
    p.x += p.vx * DT
    p.y += p.vy * DT
    p.z += p.vz * DT</pre>
				<div class="snippet__stats"><span><b>188 ms</b>per step</span><span><b>200 MB</b>memory</span></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">SoA</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">one array per field</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">import numpy as np

N = 1_000_000      # number of particles
DT = 1 / 60        # one frame at 60 FPS

x  = np.zeros(N, np.float32)   # y, z the same
vx = np.ones(N, np.float32)    # vy, vz the same

x += vx * DT
y += vy * DT
z += vz * DT</pre>
				<div class="snippet__stats"><span><b>3.7 ms</b>per step</span><span><b>24 MB</b>memory</span></div>
			</figure>
		</div>
	</div>
</section>

<section class="slide" data-title="Cache line: AoS vs SoA">
	<header class="slide__head">
		<div class="kicker">cache line · <span class="keep-case">AoS vs SoA</span> · t_particle from the C example</div>
		<h2>The CPU doesn’t read bytes, it reads 64 B lines</h2>
	</header>
	<div class="slide__body">
		<div class="lines">
			<div class="lines__row tone-hot">
				<div class="lines__label"><b>AoS</b><span>t_particle ps[N]</span></div>
				<div class="cacheline" data-component="cacheline" data-pattern="aos"></div>
				<div class="lines__stat"><b>33%</b><span>of loaded bytes used</span></div>
			</div>
			<div class="lines__row tone-ok">
				<div class="lines__label"><b>SoA</b><span>t_particles ps</span></div>
				<div class="cacheline" data-component="cacheline" data-pattern="soa"></div>
				<div class="lines__stat"><b>100%</b><span>of loaded bytes used</span></div>
			</div>
		</div>
		<div class="legend">
			<span><b class="legend__swatch tone-hot"></b>read by the loop: x and vx</span>
			<span><b class="legend__swatch tone-cold"></b>loaded for nothing</span>
			<span>1 cell = 4 B · 1 line = 64 B</span>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-hot"><b class="card__value">377,000</b><p class="card__body">cache lines per step with AoS</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">128,000</b><p class="card__body">cache lines per step with SoA, 3× fewer</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">4.3×</b><p class="card__body">faster step, 2.1 ms → 0.49 ms</p><span class="card__link">demos/c/particles.c · perf stat</span></div>
		</div>
	</div>
</section>

<section class="slide" data-title="Hot/cold split: how to split a struct">
	<header class="slide__head">
		<div class="kicker">hot/cold split · what if the struct needs more?</div>
		<h2>Split the struct by how often you read it</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag">1 struct</span><span class="snippet__file">demos/c/hotcold.c</span></figcaption>
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
				<div class="snippet__stats"><span><b>72 B</b>per particle</span><span><b>24 B</b>of it read by the loop</span></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag">hot + cold</span><span class="snippet__file">demos/c/hotcold.c</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_hot     /* every frame */
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
}	t_hot;
typedef struct s_cold    /* only now and then */
{
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_cold;
t_hot	g_hot[N];
t_cold	g_cold[N];       /* same i = same particle */</pre>
				<div class="snippet__stats"><span><b>24 B</b>hot, read by the loop</span><span><b>48 B</b>cold, lives elsewhere</span></div>
			</figure>
		</div>
	</div>
</section>

<section class="slide" data-title="Hot/cold split: measurement">
	<header class="slide__head">
		<div class="kicker">hot/cold split · what it does to the cache</div>
		<h2>What the loop doesn’t read should live elsewhere</h2>
	</header>
	<div class="slide__body">
		<div class="lines">
			<div class="lines__row tone-hot">
				<div class="lines__label"><b>1 struct</b><span>t_particle, 72 B</span></div>
				<div class="cacheline" data-component="cacheline" data-fields="x y z vx vy vz name:8 color mass flags id" data-read="x y z vx vy vz"></div>
				<div class="lines__stat"><b>33%</b><span>of loaded bytes used</span></div>
			</div>
			<div class="lines__row tone-ok">
				<div class="lines__label"><b>hot + cold</b><span>t_hot[N], t_cold[N]</span></div>
				<div class="cacheline" data-component="cacheline" data-fields="x y z vx vy vz" data-read="x y z vx vy vz"></div>
				<div class="lines__stat"><b>100%</b><span>of loaded bytes used</span></div>
			</div>
		</div>
		<div class="legend">
			<span><b class="legend__swatch tone-hot"></b>hot: read every frame</span>
			<span><b class="legend__swatch tone-cold"></b>cold: name, color, mass, flags, id</span>
			<span>1 cell = 4 B · 1 line = 64 B</span>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-ok"><b class="card__value">3× fewer</b><p class="card__body">cache lines per step, 1.14M → 0.39M</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">2–3×</b><p class="card__body">faster step, ≈ 8.5 ms → 3–5 ms</p><span class="card__link">demos/c/hotcold.c · perf stat</span></div>
			<div class="card card--compact tone-c"><b class="card__title">A cousin of ROM/RAM</b><p class="card__body">ROM/RAM: who changes the data. Hot/cold: how often it’s read.</p></div>
		</div>
	</div>
</section>

<section class="slide" data-title="ROM/RAM × hot/cold">
	<header class="slide__head">
		<div class="kicker">ROM/RAM × hot/cold · two independent questions</div>
		<h2>Does it change? How often do we read it?</h2>
	</header>
	<div class="slide__body">
		<div class="rw rw--2">
			<span></span>
			<span class="rw__col tone-hot"><b>hot</b><small>read every frame</small></span>
			<span class="rw__col"><b>cold</b><small>read only now and then</small></span>

			<span class="rw__row tone-c"><b>ROM</b><small>never changes after startup</small></span>
			<span class="rw__cell"><span class="rw__text">textures, map size</span></span>
			<span class="rw__cell"><span class="rw__text">settings, file paths</span></span>

			<span class="rw__row tone-py"><b>RAM</b><small>changes at runtime</small></span>
			<span class="rw__cell"><span class="rw__text">player, tiles, fire</span></span>
			<span class="rw__cell"><span class="rw__text">score, menu state</span></span>
		</div>
		<div class="cards cards--2">
			<div class="card card--compact tone-c"><span class="card__label">ROM/RAM · correctness</span><p class="card__body">What never changes can’t be broken by accident. Restarting the game = a fresh RAM.</p></div>
			<div class="card card--compact tone-hot"><span class="card__label">hot/cold · performance</span><p class="card__body">The loop pulls into cache only what it actually reads.</p></div>
		</div>
	</div>
</section>

<section data-section="Beyond the core" class="slide slide--full slide--clean" data-title="Beyond the core">
	<canvas class="cores" data-component="cores" aria-hidden="true"></canvas>
	<div class="beyond">
		<h1 class="beyond__title">Beyond the <span>core</span></h1>
	</div>
</section>

<section class="slide" data-title="SIMD: one instruction, many numbers">
	<header class="slide__head">
		<div class="kicker">SIMD · Single Instruction, Multiple Data</div>
		<h2>One instruction, eight numbers</h2>
		<p class="lede">The CPU can apply the same operation to a whole row of numbers with a single instruction.</p>
	</header>
	<div class="slide__body">
		<div class="lanes">
			<div class="lanes__row tone-hot">
				<div class="lanes__label"><b>no SIMD</b><span>one number per instruction</span></div>
				<div class="lanes__cells lanes__cells--apart"><i>x0</i><i>x1</i><i>x2</i><i>x3</i><i>x4</i><i>x5</i><i>x6</i><i>x7</i></div>
				<div class="lanes__stat"><b>8</b><span>instructions</span></div>
			</div>
			<div class="lanes__row tone-ok">
				<div class="lanes__label"><b>SIMD</b><span>8 numbers in one register</span></div>
				<div class="lanes__cells lanes__cells--reg"><i>x0</i><i>x1</i><i>x2</i><i>x3</i><i>x4</i><i>x5</i><i>x6</i><i>x7</i></div>
				<div class="lanes__stat"><b>1</b><span>instruction</span></div>
			</div>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-ok"><b class="card__value">≈ 4.7×</b><p class="card__body">faster loop, data in cache</p><span class="card__link">demos/c/beyond.c</span></div>
			<div class="card card--compact tone-hot"><b class="card__value">1.1×</b><p class="card__body">the same loop over 128 MB in RAM: the math is fast, the memory is not</p></div>
			<div class="card card--compact tone-c"><b class="card__title">The compiler does it</b><p class="card__body">When the data sits side by side in an array (SoA). Not through pointers and objects.</p></div>
		</div>
	</div>
</section>

<section class="slide" data-title="Threads: more cores, same RAM">
	<header class="slide__head">
		<div class="kicker">threads · pthreads, as in philosophers</div>
		<h2>More cores, same RAM</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--2">
			<div class="card tone-hot">
				<span class="card__label">data in RAM · 128 MB</span>
				<div class="bars" data-component="bars" data-unit="×" data-max="3.5">
					<div data-label="1 thread" data-value="1.0" data-tone="hot"></div>
					<div data-label="2 threads" data-value="1.1" data-tone="hot"></div>
					<div data-label="4 threads" data-value="1.2" data-tone="hot"></div>
					<div data-label="6 threads" data-value="1.2" data-tone="hot"></div>
				</div>
				<p class="card__body">RAM delivers ≈ 30 GB/s. More cores won’t make it faster.</p>
			</div>
			<div class="card tone-ok">
				<span class="card__label">each thread with its own 64 KB in L2</span>
				<div class="bars" data-component="bars" data-unit="×" data-max="3.5">
					<div data-label="1 thread" data-value="1.0" data-tone="ok"></div>
					<div data-label="2 threads" data-value="1.6" data-tone="ok"></div>
					<div data-label="4 threads" data-value="2.4" data-tone="ok"></div>
					<div data-label="6 threads" data-value="3.1" data-tone="ok"></div>
				</div>
				<p class="card__body">Data in cache: threads help. Not 6×, the laptop lowers its clock when all cores are busy.</p>
				<span class="card__link">demos/c/beyond.c · best of 7 runs</span>
			</div>
		</div>
	</div>
</section>

<section class="slide" data-title="What's next: more techniques">
	<header class="slide__head">
		<div class="kicker">what’s next · just a taste</div>
		<h2>Where to go from here</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--2">
			<div class="card tone-c"><b class="card__title">Branch prediction</b><p class="card__body">The CPU guesses the outcome of an <code>if</code> ahead of time. Random branches cost time, sorted data or branchless code doesn’t.</p></div>
			<div class="card tone-c"><b class="card__title">Lookup tables</b><p class="card__body">Compute up front, at runtime just read from an array. Casey’s table version from the start: 10.3×.</p></div>
			<div class="card tone-c"><b class="card__title">Multiply instead of divide</b><p class="card__body">Division is ≈ 3× more expensive here. Compute <code>1 / k</code> once, then multiply. For floats the compiler won’t do it for you.</p><span class="card__link">demos/c/division.c</span></div>
			<div class="card tone-c"><b class="card__title">GPU</b><p class="card__body">Thousands of small cores, SIMD at scale. Without arrays and SoA it has nothing to work on.</p></div>
		</div>
	</div>
</section>

<section data-section="Tools" class="slide" data-title="Tools: don't guess, measure">
	<header class="slide__head">
		<div class="kicker">tools · what they do and what to use them for</div>
		<h2>Don’t guess, measure</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--3">
			<div class="card card--compact tone-c">
				<span class="card__label">C · Linux</span>
				<b class="card__title">perf</b>
				<p class="card__body">Reads counters right inside the CPU: instructions, cache misses, mispredicted branches. Tells you why code is slow, not just that it is.</p>
				<span class="card__link">here: cache lines in AoS/SoA, hot/cold</span>
			</div>
			<div class="card card--compact tone-c">
				<span class="card__label">C</span>
				<b class="card__title">objdump</b>
				<p class="card__body">Shows the machine code the compiler actually produced. Compiler Explorer does the same online.</p>
				<span class="card__link">here: did the compiler use SIMD?</span>
			</div>
			<div class="card card--compact tone-c">
				<span class="card__label">C and Python</span>
				<b class="card__title">monotonic clock</b>
				<p class="card__body"><code>clock_gettime</code> in C, <code>time.perf_counter</code> in Python. Measure several times, keep the best run.</p>
				<span class="card__link">here: every timing</span>
			</div>
		</div>
		<div class="cards cards--2">
			<div class="card card--compact tone-py">
				<span class="card__label">Python</span>
				<b class="card__title">py-spy</b>
				<p class="card__body">Sampling profiler: shows which functions your program spends its time in. Attaches even to a running program, no code changes. Draws flame graphs.</p>
				<a class="card__link link" href="https://github.com/benfred/py-spy" target="_blank" rel="noopener">github.com/benfred/py-spy</a>
			</div>
			<div class="card card--compact tone-py">
				<span class="card__label">Python</span>
				<b class="card__title">tracemalloc</b>
				<p class="card__body">In the standard library. Tracks every Python allocation: how much memory and from which line.</p>
				<span class="card__link">here: 200 MB vs 24 MB</span>
			</div>
		</div>
	</div>
</section>

<section data-section="Trade-off" class="slide" data-title="Trade-off: it isn't free">
	<header class="slide__head">
		<div class="kicker">trade-off · what it costs</div>
		<h2>It isn’t free</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--3">
			<div class="card tone-hot"><span class="card__num">1</span><b class="card__title">You have to understand the domain</b><p class="card__body">What really has to happen, with which data, and how often. No convention tells you that, only the problem does. And that takes time.</p></div>
			<div class="card tone-hot"><span class="card__num">2</span><b class="card__title">You won’t get it right the first time</b><p class="card__body">The right data split only shows once you have code in hand. My push_swap arenas have a “now” and a “better” too. Plan to rewrite.</p></div>
			<div class="card tone-hot"><span class="card__num">3</span><b class="card__title">The code is tailored to the data</b><p class="card__body">The data changes, the code changes. It’s less generic, but you can see what it really does.</p></div>
		</div>
	</div>
</section>

<section class="slide slide--statement" data-title="Quote: Knuth, premature optimization (in full)">
	<figure class="quote">
		<blockquote class="quote__text">
			<p class="muted">We should forget about small efficiencies, say about 97% of the time: premature optimization is the root of all evil.</p>
			<p class="quote__turn">Yet we should not pass up our opportunities in that critical <span class="quote__end">3%.<span class="quote__close" aria-hidden="true">”</span></span></p>
		</blockquote>
		<figcaption class="quote__cite">
			Donald Knuth · Structured Programming with go to Statements · 1974 ·
			<a class="link" href="https://doi.org/10.1145/356635.356640" target="_blank" rel="noopener">doi.org/10.1145/356635.356640</a>
		</figcaption>
	</figure>
</section>
`);
