/* Think first, then code */

Talk.slides(`
<section class="slide" data-title="Think first, then code">
	<header class="slide__head">
		<div class="kicker">architecture · before you write the first line</div>
		<h2>Think first, then code</h2>
	</header>
	<div class="slide__body">
	<div class="cards cards--3">
		<div class="card tone-hot"><span class="card__num">1</span><b class="card__title">Understand the domain</b><p class="card__body">What is really in the problem? Which things, how many, and how big?</p></div>
		<div class="card tone-hot"><span class="card__num">2</span><b class="card__title">Follow the data</b><p class="card__body">Where does the data come from, who reads it, who changes it, and how often?</p></div>
		<div class="card tone-hot"><span class="card__num">3</span><b class="card__title">Split by access</b><p class="card__body">What is only read belongs together. So does what changes. What dies together shares memory.</p></div>
	</div>
	</div>
</section>
`);
