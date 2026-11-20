/* What's next: more techniques */

Talk.slides(`
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
`);
