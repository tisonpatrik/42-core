/* What is a cache */

Talk.slides(`
<section class="slide" data-title="What is a cache">
	<header class="slide__head">
		<div class="kicker">hardware · cache</div>
		<h2>What are L1, L2 and L3 caches?</h2>
		<p class="lede">Small, fast memory right inside the CPU. Whatever the CPU used recently, it keeps as close as it can.</p>
	</header>
	<div class="slide__body">
		<div class="hier">
			<div class="hier__item hier__item--core"><b>CPU core</b><span>computes</span></div>
			<div class="hier__item tone-ok" style="--size: 1"><b>L1</b><span class="hier__size">32 KB</span><span class="hier__like">desk</span></div>
			<div class="hier__item tone-c" style="--size: 2"><b>L2</b><span class="hier__size">512 KB</span><span class="hier__like">shelf</span></div>
			<div class="hier__item tone-py" style="--size: 3"><b>L3</b><span class="hier__size">8 MB</span><span class="hier__like">cupboard</span></div>
			<div class="hier__item tone-hot" style="--size: 4"><b>RAM</b><span class="hier__size">32 GB</span><span class="hier__like">library across town</span></div>
		</div>
		<div class="hier__axis"><span>closer, smaller, faster</span><span>farther, bigger, slower</span></div>
	</div>
	<footer class="slide__foot">
		<p class="source">Sizes from the laptop I’m presenting on: AMD Ryzen 5 PRO 4650U (L1 and L2 per core, L3 shared)</p>
	</footer>
</section>
`);
