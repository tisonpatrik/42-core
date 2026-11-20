/* Cache line: AoS vs SoA */

Talk.slides(`
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
`);
