/* Trade-off: it isn't free */

Talk.slides(`
<section class="slide" data-title="Trade-off: it isn't free">
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
`);
