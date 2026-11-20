/* Threads: more cores, same RAM */

Talk.slides(`
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
`);
