/* Latency: the CPU waits for data */

Talk.slides(`
<section class="slide" data-title="Latency: the CPU waits for data">
	<header class="slide__head">
		<div class="kicker">hardware · latency</div>
		<h2>The CPU spends most of its time waiting for data</h2>
		<p class="lede">If a read from L1 cache took one second…</p>
	</header>
	<div class="slide__body">
		<div class="scale" data-component="scale" data-source="latency"></div>
	</div>
	<footer class="slide__foot">
		<p class="source" data-component="sources" data-source="latency">L1–RAM: Zen 2 cycles at 4 GHz · SSD and network: orders of magnitude ·</p>
	</footer>
</section>
`);
