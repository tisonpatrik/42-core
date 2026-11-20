/* How many times I write malloc and free */

Talk.slides(`
<section class="slide" data-title="How many times I write malloc and free">
	<header class="slide__head">
		<div class="kicker">push_swap · static count in src/</div>
		<h2>How many times do I write <code>malloc</code> and <code>free</code>?</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-2">
		<div class="stack stack--sm">
			<div class="tally tone-hot">
				<span class="tally__label">no arenas</span>
				<span class="tally__num">26<small>× malloc</small></span>
				<span class="tally__num">70<small>× free</small></span>
			</div>
			<div class="tally tone-py">
				<span class="tally__label">with arenas</span>
				<span class="tally__num">15<small>× malloc</small></span>
				<span class="tally__num">20<small>× free</small></span>
			</div>
			<div class="tally tone-ok">
				<span class="tally__label">ideal</span>
				<span class="tally__num">1<small>× malloc</small></span>
				<span class="tally__num">1<small>× free</small></span>
			</div>
		</div>
		<div class="sites">
			<div class="sites__row sites__row--head"><span></span><span class="sites__group">no arenas</span><span class="sites__group">with arenas</span><span class="sites__group">ideal</span></div>
			<div class="sites__row sites__row--sub"><span>module</span><span>m</span><span>f</span><span>m</span><span>f</span><span>m</span><span>f</span></div>
			<div class="sites__row"><span class="sites__mod">validator/</span><span class="sites__n">5</span><span class="sites__n">7</span><span class="sites__n">5</span><span class="sites__n">7</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">stack/</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">ops/</span><span class="sites__n">2</span><span class="sites__n">3</span><span class="sites__n">2</span><span class="sites__n">3</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">optimizer/</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row sites__row--hl"><span class="sites__mod">selector/</span><span class="sites__n">8</span><span class="sites__n">30</span><span class="sites__n">3</span><span class="sites__n">6</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row sites__row--hl"><span class="sites__mod">separator/</span><span class="sites__n">7</span><span class="sites__n">28</span><span class="sites__n">1</span><span class="sites__n">2</span><span class="sites__n">0</span><span class="sites__n">0</span></div><div class="sites__row"><span class="sites__mod">main.c</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">0</span><span class="sites__n">1</span><span class="sites__n">1</span></div>
			<div class="sites__row sites__row--total"><span class="sites__mod">total</span><span class="sites__n">26</span><span class="sites__n">70</span><span class="sites__n">15</span><span class="sites__n">20</span><span class="sites__n">1</span><span class="sites__n">1</span></div>
		</div>
	</div>
	</div>
</section>
`);
