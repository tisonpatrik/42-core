/* 4 · Závěr: kdy ne, tahák, zdroje, otázky */

Talk.slides(`
<section class="slide">
	<div class="kicker">4 · Kdy ne</div>
	<h2>DOD není náboženství</h2>
	<div class="grid grid--fill cols-2">
		<div class="card">
			<h3>Nevyplatí se, když…</h3>
			<ul>
				<li>máš 5 orbů, ne 5 milionů (náš <code>bool active</code> je OK)</li>
				<li>program čeká na síť nebo disk (I/O-bound)</li>
				<li>prototypuješ a ještě nevíš, jak data vypadají</li>
				<li>čitelnost pro tým je důležitější než milisekundy</li>
			</ul>
		</div>
		<div class="card">
			<h3>Vždycky měř</h3>
			<ul>
				<li><span class="pill tone-c">C</span><code>perf stat -e cache-misses</code>, <code>hyperfine</code></li>
				<li><span class="pill tone-c">C</span><code>valgrind --tool=cachegrind</code></li>
				<li><span class="pill tone-py">Py</span><code>timeit</code>, <code>tracemalloc</code>, <code>py-spy</code></li>
			</ul>
			<p class="small muted mt">Casey Muratori vs. Robert C. Martin (2023): veřejná debata na GitHubu o tom, kde je hranice.</p>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">Tahák do příštího projektu</div>
	<h2>Pět otázek, než napíšeš první struct</h2>
	<ol class="checklist lead lead--light">
		<li><b>Kolik</b> toho bude? 1, 1000, 1 000 000?</li>
		<li>Co čte <b>hot loop</b>? Dej to k sobě, zbytek jinam.</li>
		<li><b>Kdy to vznikne a kdy umře?</b> Co umírá spolu → jedna aréna.</li>
		<li>Dá se velikost <b>spočítat dopředu</b>? → measure + 1 alokace.</li>
		<li><b>Změřil</b> jsi to?</li>
	</ol>
</section>

<section class="slide">
	<div class="kicker">Zdroje</div>
	<div class="grid cols-2">
		<ul class="reading small">
			<li><b>Richard Fabian</b>: <em>Data-Oriented Design</em> (2018), zdarma na dataorienteddesign.com/dodbook</li>
			<li><b>Mike Acton</b>: <em>Data-Oriented Design and C++</em>, CppCon 2014</li>
			<li><b>Casey Muratori</b>: <em>Clean Code, Horrible Performance</em> (2023), kurz <em>Performance-Aware Programming</em> na computerenhance.com, <em>The Big OOPs</em> (BSC 2025), Handmade Hero</li>
			<li><b>Ryan Fleury</b>: <em>Untangling Lifetimes: The Arena Allocator</em></li>
		</ul>
		<ul class="reading small">
			<li><b>Andrew Kelley</b>: <em>A Practical Guide to Applying Data-Oriented Design</em>, Handmade Seattle 2021</li>
			<li><b>gingerBill</b>: série <em>Memory Allocation Strategies</em></li>
			<li><b>Noel Llopis</b>: <em>Data-Oriented Design (Or Why You Might Be Shooting Yourself in the Foot With OOP)</em>, 2009</li>
			<li><b>Ulrich Drepper</b>: <em>What Every Programmer Should Know About Memory</em>, 2007</li>
			<li>CPython: <code>Objects/obmalloc.c</code></li>
		</ul>
	</div>
</section>

<section class="slide slide--center">
	<div class="kicker">Díky</div>
	<h1>Otázky?</h1>
	<p class="lead lead--light muted">Dema: <code>dod_talk/demos</code> → <code>make run</code><br>Kód: <code>cub3d/src/app/setup_memory.c</code>, <code>lib/libft/src/allocator</code></p>
</section>
`);
