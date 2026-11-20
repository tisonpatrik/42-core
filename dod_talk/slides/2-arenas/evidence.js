/* Is it really faster? Evidence */

Talk.slides(`
<section class="slide" data-title="Is it really faster? Evidence">
	<header class="slide__head">
		<div class="kicker">evidence · research and practice</div>
		<h2>Is it really faster?</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--3">
		<figure class="card card--compact tone-ok">
			<b class="card__value">17×</b>
			<p class="card__body">Our measurement: 20,000 lines × 500 tokens, <span class="nowrap">560 ms → 33 ms</span>.</p>
			<figcaption class="card__link">demos/c/arena.c · microbenchmark</figcaption>
		</figure>
		<figure class="card card--compact tone-c">
			<b class="card__value">up to 44%</b>
			<p class="card__body">Of 8 programs with a custom allocator, only the ones using regions (arenas) beat a general-purpose malloc.</p>
			<a class="card__link link" href="https://www.microsoft.com/en-us/research/?p=355667" target="_blank" rel="noopener">Berger, Zorn, McKinley · OOPSLA 2002</a>
		</figure>
		<figure class="card card--compact tone-py">
			<b class="card__value">up to 15%</b>
			<p class="card__body">Less CPU and memory in large Google applications after adding arenas to Go.</p>
			<a class="card__link link" href="https://github.com/golang/go/issues/51317" target="_blank" rel="noopener">Go proposal #51317 · 2022</a>
		</figure>
	</div>
	<div class="cards cards--2">
		<figure class="card card--compact tone-c">
			<span class="card__label">Protobuf · Google</span>
			<blockquote class="card__quote card__quote--sm">“Memory allocation and deallocation constitutes a significant fraction of CPU time spent in Protobuf code.”</blockquote>
			<p class="card__body">Arena: allocating is a pointer bump, freeing is almost free, data sits side by side in cache.</p>
			<a class="card__link link" href="https://protobuf.dev/reference/cpp/arenas" target="_blank" rel="noopener">protobuf.dev/reference/cpp/arenas</a>
		</figure>
		<figure class="card card--compact tone-hot">
			<span class="card__label">To be fair · van Kempen, Berger · ISMM 2026</span>
			<b class="card__title">Per-type custom allocators don’t beat a modern malloc. Bulk freeing and locality do.</b>
			<p class="card__body">Exactly what an arena does: everything at once, everything side by side.</p>
			<a class="card__link link" href="https://arxiv.org/abs/2605.17119" target="_blank" rel="noopener">arxiv.org/abs/2605.17119</a>
		</figure>
	</div>
	</div>
</section>
`);
