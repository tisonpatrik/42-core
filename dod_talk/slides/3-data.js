/* Jak organizovat data: latence, cache line, cub3D mapa, Python list, SIMD, pravidla */

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
		<div class="kicker">AoS vs SoA · Python · 1M částic</div>
		<h2>Stejná práce, jinak uložená data</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag">AoS</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">pole objektů</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">class Particle:
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
				<figcaption class="snippet__head"><span class="snippet__tag">SoA</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">pole na každý atribut</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">import numpy as np

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

<section class="slide" data-title="Cache line: AoS vs SoA">
	<header class="slide__head">
		<div class="kicker">cache line · AoS vs SoA</div>
		<h2>CPU nečte bajty, čte řádky po 64 B</h2>
	</header>
	<div class="slide__body">
		<div class="lines">
			<div class="lines__row tone-hot">
				<div class="lines__label"><b>AoS</b><span>pole structů, 72 B na částici</span></div>
				<div class="cacheline" data-component="cacheline" data-pattern="aos"></div>
				<div class="lines__stat"><b>38 %</b><span>načtených bajtů smyčka použije</span></div>
			</div>
			<div class="lines__row tone-ok">
				<div class="lines__label"><b>SoA</b><span>struct polí: x[], vx[], …</span></div>
				<div class="cacheline" data-component="cacheline" data-pattern="soa"></div>
				<div class="lines__stat"><b>100 %</b><span>načtených bajtů smyčka použije</span></div>
			</div>
		</div>
		<div class="legend">
			<span><b class="legend__swatch tone-hot"></b>čte hot loop: x y z vx vy vz</span>
			<span><b class="legend__swatch tone-cold"></b>načte se zbytečně</span>
			<span>1 políčko = 4 B · 1 řádek = 64 B</span>
		</div>
	</div>
</section>

<section class="slide" data-title="Python: list je pole ukazatelů">
	<header class="slide__head">
		<div class="kicker">Python · list vs NumPy</div>
		<h2>Python list je pole ukazatelů</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--2">
			<div class="card tone-hot">
				<span class="card__label">list · [1.0, 2.0, 3.0]</span>
				<div class="mem">
					<div class="mem__ptrs"><i>ptr</i><i>ptr</i><i>ptr</i></div>
					<div class="mem__scatter mem__scatter--obj">
						<i style="--x: 22%"><small>refcnt · type ·</small> 1.0</i>
						<i style="--x: 2%"><small>refcnt · type ·</small> 2.0</i>
						<i style="--x: 40%"><small>refcnt · type ·</small> 3.0</i>
					</div>
				</div>
				<p class="card__body">Každé číslo je objekt na haldě: 8 B ukazatel + 24 B objekt = 32 B.</p>
			</div>
			<div class="card tone-ok">
				<span class="card__label">NumPy · float32</span>
				<div class="mem">
					<div class="mem__block mem__block--row"><i>1.0</i><i>2.0</i><i>3.0</i><i>…</i></div>
				</div>
				<p class="card__body">Čísla za sebou jako pole v C: 4 B na číslo, žádné ukazatele.</p>
			</div>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-ok"><b class="card__value">8×</b><p class="card__body">méně paměti</p></div>
			<div class="card card--compact tone-ok"><b class="card__value">≈ 50×</b><p class="card__body">rychlejší update pozic</p></div>
			<div class="card card--compact tone-c"><b class="card__value">1M</b><p class="card__body">částic, x += vx · dt</p><span class="card__link">particles.py · Python 3.14 · NumPy 2.5</span></div>
		</div>
	</div>
</section>

<section class="slide" data-title="cub3D: mapa jako jeden blok">
	<header class="slide__head">
		<div class="kicker">cub3D · mapa</div>
		<h2>Jeden blok, ne pole ukazatelů</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--2">
			<div class="card tone-hot">
				<span class="card__label">parser · char **grid</span>
				<div class="mem">
					<div class="mem__ptrs"><i>ptr</i><i>ptr</i><i>ptr</i><i>ptr</i></div>
					<div class="mem__scatter">
						<i style="--x: 30%">1 1 1 1 1 1</i>
						<i style="--x: 4%">1 0 0 N 0 1</i>
						<i style="--x: 48%">1 0 1 0 0 1</i>
						<i style="--x: 18%">1 1 1 1 1 1</i>
					</div>
				</div>
				<p class="card__body">Každý řádek vlastní malloc, kdekoliv na haldě. Na buňku dva skoky v paměti.</p>
			</div>
			<div class="card tone-ok">
				<span class="card__label">engine · uint8_t *tiles</span>
				<div class="mem">
					<div class="mem__block"><i>1 1 1 1 1 1</i><i>1 0 0 N 0 1</i><i>1 0 1 0 0 1</i><i>1 1 1 1 1 1</i></div>
				</div>
				<p class="card__body">Celá mapa v jednom bloku, řádek za řádkem. Buňka je jeden bajt a jeden přístup.</p>
			</div>
		</div>
	</div>
</section>

<section class="slide" data-title="Ochutnávka: SIMD">
	<header class="slide__head">
		<div class="kicker">bonus · SIMD</div>
		<h2>Jedna instrukce, osm čísel</h2>
	</header>
	<div class="slide__body">
		<div class="lanes">
			<div class="lanes__row">
				<span class="lanes__label">x[] v paměti</span>
				<div class="lanes__cells"><i>x0</i><i>x1</i><i>x2</i><i>x3</i><i>x4</i><i>x5</i><i>x6</i><i>x7</i></div>
			</div>
			<div class="lanes__arrow">↓ jedno načtení</div>
			<div class="lanes__row lanes__row--reg">
				<span class="lanes__label">AVX registr · 256 bitů</span>
				<div class="lanes__cells"><i>x0</i><i>x1</i><i>x2</i><i>x3</i><i>x4</i><i>x5</i><i>x6</i><i>x7</i></div>
			</div>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-ok"><b class="card__value">8×</b><p class="card__body">float32 v jednom AVX registru</p></div>
			<div class="card card--compact tone-c"><b class="card__value">SoA</b><p class="card__body">data už leží za sebou, kompilátor je umí načíst najednou</p></div>
			<div class="card card--compact tone-hot"><b class="card__value">23,7×</b><p class="card__body">Casey s ručním AVX proti „clean“ verzi</p></div>
		</div>
	</div>
</section>

<section class="slide" data-title="Jak organizovat data: co si odnést">
	<header class="slide__head">
		<div class="kicker">jak organizovat data</div>
		<h2>Co si odnést</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--3">
			<div class="card tone-c"><span class="card__num">1</span><b class="card__title">Co se čte spolu, leží spolu</b><p class="card__body">Hot loop chce svoje data za sebou. Zbytek ať leží jinde.</p></div>
			<div class="card tone-c"><span class="card__num">2</span><b class="card__title">Kde je jeden, je jich hodně</b><p class="card__body">Nepiš kód pro jeden objekt. Piš ho pro pole.</p></div>
			<div class="card tone-c"><span class="card__num">3</span><b class="card__title">Jeden blok, ne ukazatele</b><p class="card__body">Pole a indexy místo pole ukazatelů na rozházené kousky.</p></div>
		</div>
	</div>
	<footer class="slide__foot">
		<p class="source"><a class="link" href="https://www.dataorienteddesign.com/dodbook/" target="_blank" rel="noopener">Richard Fabian: Data-Oriented Design</a> · „Where there is one, there are many.“</p>
	</footer>
</section>
`);
