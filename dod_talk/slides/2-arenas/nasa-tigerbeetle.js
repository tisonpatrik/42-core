/* NASA and TigerBeetle: allocate at startup */

Talk.slides(`
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
`);
