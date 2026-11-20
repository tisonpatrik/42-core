/* SIMD: one instruction, many numbers */

Talk.slides(`
<section class="slide" data-title="SIMD: one instruction, many numbers">
	<header class="slide__head">
		<div class="kicker">SIMD · Single Instruction, Multiple Data</div>
		<h2>One instruction, eight numbers</h2>
		<p class="lede">The CPU can apply the same operation to a whole row of numbers with a single instruction.</p>
	</header>
	<div class="slide__body">
		<div class="lanes">
			<div class="lanes__row tone-hot">
				<div class="lanes__label"><b>no SIMD</b><span>one per instruction</span></div>
				<div class="lanes__cells lanes__cells--apart"><i>x0</i><i>x1</i><i>x2</i><i>x3</i><i>x4</i><i>x5</i><i>x6</i><i>x7</i></div>
				<div class="lanes__stat"><b>8</b><span>instructions</span></div>
			</div>
			<div class="lanes__row tone-ok">
				<div class="lanes__label"><b>SIMD</b><span>8 in one register</span></div>
				<div class="lanes__cells lanes__cells--reg"><i>x0</i><i>x1</i><i>x2</i><i>x3</i><i>x4</i><i>x5</i><i>x6</i><i>x7</i></div>
				<div class="lanes__stat"><b>1</b><span>instruction</span></div>
			</div>
		</div>
		<div class="cards cards--3">
			<div class="card card--compact tone-ok"><b class="card__value">≈ 4.7×</b><p class="card__body">faster loop, data in cache</p><span class="card__link">demos/c/beyond.c</span></div>
			<div class="card card--compact tone-hot"><b class="card__value">1.1×</b><p class="card__body">the same loop over 128 MB in RAM: the math is fast, the memory is not</p></div>
			<div class="card card--compact tone-c"><b class="card__title">The compiler does it</b><p class="card__body">When the data sits side by side in an array (SoA). Not through pointers and objects.</p></div>
		</div>
	</div>
</section>
`);
