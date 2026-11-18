/* 1 · Hardware: latence, cache line, Python objekty, Acton */

Talk.slides(`
<section class="slide">
	<div class="kicker">1 · Hardware</div>
	<h2>Kdyby L1 cache trvala 1 sekundu…</h2>
	<div class="latency">
		<div class="latency__head">kde</div><div class="latency__head">reálně</div><div class="latency__head">lidsky</div>
		<div>L1 cache</div><div class="latency__real">~1 ns</div><div class="latency__human">1 s</div>
		<div>L2 cache</div><div class="latency__real">~4 ns</div><div class="latency__human">4 s</div>
		<div>L3 cache</div><div class="latency__real">~15 ns</div><div class="latency__human">15 s</div>
		<div class="hot">RAM</div><div class="latency__real">~100 ns</div><div class="latency__human hot">1,5 minuty</div>
		<div>SSD</div><div class="latency__real">~100 µs</div><div class="latency__human">1 den</div>
		<div>ping přes Atlantik</div><div class="latency__real">~80 ms</div><div class="latency__human">2,5 roku</div>
	</div>
	<p class="small muted push-bottom">Řádové hodnoty. Moderní CPU umí za čas jednoho čtení z RAM udělat stovky instrukcí.</p>
</section>

<section class="slide">
	<div class="kicker">1 · Hardware</div>
	<h2>CPU nečte bajty. Čte řádky po 64 B.</h2>
	<div class="stack stack--lg">
		<div>
			<p class="small mb-sm"><span class="pill tone-hot">AoS</span><code>t_particle</code> = 72 B, update potřebuje jen <code>x y z vx vy vz</code> = 24 B</p>
			<div class="cacheline" data-component="cacheline" data-pattern="aos"></div>
			<p class="small muted mt-sm">2 cache lines = 128 B načteno · <span class="hot">48 B užitečných (38 %)</span></p>
		</div>
		<div>
			<p class="small mb-sm"><span class="pill tone-c">SoA</span><code>float *x</code>, <code>float *vx</code>, … každé pole zvlášť</p>
			<div class="cacheline" data-component="cacheline" data-pattern="soa"></div>
			<p class="small muted mt-sm">2 cache lines = 128 B načteno · <span class="ok">128 B užitečných (100 %)</span> + prefetcher + SIMD</p>
		</div>
		<div class="legend">
			<span><b class="legend__swatch tone-hot"></b>hot data (čtu v loopu)</span>
			<span><b class="legend__swatch tone-cold"></b>cold data (name, color, mass, id…)</span>
			<span>1 čtvereček = 4 B</span>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">1 · Hardware · Python edition</div>
	<h2>Co je doopravdy <code>[1.0, 2.0, 3.0]</code>?</h2>
	<div class="grid grid--fill cols-2">
		<div>
			<p class="small mb-sm"><span class="pill tone-py">list</span>pole <em>pointerů</em> na objekty na haldě</p>
			<div class="objects">
				<div class="objbox"><div>ptr →</div><div>ptr →</div><div>ptr →</div></div>
				<div class="stack stack--sm">
					<div class="objbox"><div><span class="objbox__type">ob_refcnt</span> 8 B</div><div><span class="objbox__type">ob_type</span> 8 B</div><div class="hot">1.0 · 8 B</div></div>
					<div class="objbox"><div><span class="objbox__type">ob_refcnt</span> 8 B</div><div><span class="objbox__type">ob_type</span> 8 B</div><div class="hot">2.0 · 8 B</div></div>
				</div>
			</div>
			<p class="small muted mt-sm">= 8 B pointer + 24 B objekt <b class="hot">= 32 B na číslo</b>, rozházené po paměti</p>
		</div>
		<div>
			<p class="small mb-sm"><span class="pill tone-py">numpy</span>jeden souvislý blok, jako C pole</p>
			<div class="objbox objbox--row"><div class="hot">1.0</div><div class="hot">2.0</div><div class="hot">3.0</div><div>…</div></div>
			<p class="small muted mt-sm"><code>float32</code> <b class="ok">= 4 B na číslo</b>, za sebou</p>
<pre class="code mt" data-component="code" data-lang="py">&gt;&gt;&gt; sys.getsizeof(1.0)
24
&gt;&gt;&gt; sys.getsizeof(1)
28</pre>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">1 · Mike Acton, 2014</div>
	<h2>Tři velké lži</h2>
	<div class="grid grid--tight cols-3">
		<div class="card"><h3 class="hot">„Software je platforma.“</h3><p>Platforma je hardware. Kód běží na skutečném CPU s cache, ne na abstraktním stroji.</p></div>
		<div class="card"><h3 class="hot">„Kód má modelovat svět.“</h3><p><code>Dog : Animal</code> je model světa. CPU ale nezajímá, co je pes, zajímají ho bajty a přístupy k nim.</p></div>
		<div class="card"><h3 class="hot">„Kód je důležitější než data.“</h3><p>Kód existuje jen proto, aby transformoval data. Nerozumíš datům = nerozumíš problému.</p></div>
	</div>
	<p class="lead push-bottom">„Where there is one, there are many.“ <span class="muted small">— Richard Fabian</span></p>
</section>
`);
