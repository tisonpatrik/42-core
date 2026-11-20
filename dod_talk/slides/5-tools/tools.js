/* Tools: don't guess, measure */

Talk.slides(`
<section class="slide" data-title="Tools: don't guess, measure">
	<header class="slide__head">
		<div class="kicker">tools · what they do and what to use them for</div>
		<h2>Don’t guess, measure</h2>
	</header>
	<div class="slide__body">
		<div class="cards cards--3">
			<div class="card card--compact tone-c">
				<span class="card__label">C · Linux</span>
				<b class="card__title">perf</b>
				<p class="card__body">Reads counters right inside the CPU: instructions, cache misses, mispredicted branches. Tells you why code is slow, not just that it is.</p>
				<span class="card__link">here: cache lines in AoS/SoA, hot/cold</span>
			</div>
			<div class="card card--compact tone-c">
				<span class="card__label">C</span>
				<b class="card__title">objdump</b>
				<p class="card__body">Shows the machine code the compiler actually produced. Compiler Explorer does the same online.</p>
				<span class="card__link">here: did the compiler use SIMD?</span>
			</div>
			<div class="card card--compact tone-c">
				<span class="card__label">C and Python</span>
				<b class="card__title">monotonic clock</b>
				<p class="card__body"><code>clock_gettime</code> in C, <code>time.perf_counter</code> in Python. Measure several times, keep the best run.</p>
				<span class="card__link">here: every timing</span>
			</div>
		</div>
		<div class="cards cards--2">
			<div class="card card--compact tone-py">
				<span class="card__label">Python</span>
				<b class="card__title">py-spy</b>
				<p class="card__body">Sampling profiler: shows which functions your program spends its time in. Attaches even to a running program, no code changes. Draws flame graphs.</p>
				<a class="card__link link" href="https://github.com/benfred/py-spy" target="_blank" rel="noopener">github.com/benfred/py-spy</a>
			</div>
			<div class="card card--compact tone-py">
				<span class="card__label">Python</span>
				<b class="card__title">tracemalloc</b>
				<p class="card__body">In the standard library. Tracks every Python allocation: how much memory and from which line.</p>
				<span class="card__link">here: 200 MB vs 24 MB</span>
			</div>
		</div>
	</div>
</section>
`);
