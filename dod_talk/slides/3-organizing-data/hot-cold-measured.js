/* Hot/cold split: measurement */

Talk.slides(`
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
`);
