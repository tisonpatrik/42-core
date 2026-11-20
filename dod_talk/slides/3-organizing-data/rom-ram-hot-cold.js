/* ROM/RAM × hot/cold */

Talk.slides(`
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
`);
