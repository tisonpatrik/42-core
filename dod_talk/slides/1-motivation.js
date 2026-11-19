/* Motivation: title, Casey, hardware over time, AWS, quote */

Talk.slides(`
<section data-section="Motivation" class="slide slide--statement">
	<div class="kicker">42 · talk · 60 min</div>
	<h1>Mechanical<br>sympathy</h1>
	<p class="lead muted">Code the hardware likes.</p>
	<div class="manifesto">
		<div class="manifesto__item">
			<span class="manifesto__num">01</span>
			<p><b>Write for the real machine.</b><br><span class="muted">CPU, cache and memory, not a class diagram.</span></p>
		</div>
		<div class="manifesto__item">
			<span class="manifesto__num">02</span>
			<p><b>No bullshit.</b><br><span class="muted">No layers that do nothing. Just data and what happens to it.</span></p>
		</div>
		<div class="manifesto__item manifesto__item--bonus">
			<span class="manifesto__num">+</span>
			<p><b>Bonus: memory safety.</b><br><span class="muted">Fewer leaks and dangling pointers. By design, not by discipline.</span></p>
		</div>
	</div>
	<p><span class="pill tone-c">C</span><span class="pill tone-py">Python</span></p>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">Casey Muratori · “Clean” Code, Horrible Performance · 2023</div>
		<h2>Five “clean code” rules. What do they cost?</h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<ol class="rules">
			<li><b>Prefer polymorphism to “if/else” and “switch”</b></li>
			<li><b>Code should not know about the internals of objects it’s working with</b></li>
			<li><b>Functions should be small</b></li>
			<li><b>Functions should do one thing</b></li>
			<li class="rules__keep"><b>“DRY”: Don’t Repeat Yourself</b><span>“seems fine”, Casey keeps this one</span></li>
		</ol>
		<div class="card">
			<b class="card__title">Speed-up when you break them</b>
			<div class="bars" data-component="bars" data-source="casey" data-unit="×"></div>
		</div>
	</div>
	</div>
	<footer class="slide__foot">
	<p class="source"><a class="link" href="https://www.youtube.com/watch?v=tD5NrevFtbU" target="_blank" rel="noopener">youtube.com/watch?v=tD5NrevFtbU</a> · results at 19:35</p>
	</footer>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">Hardware over time · single-core performance · 100% = Apple M5 (2025)</div>
		<h2>How far back in time does it put you?</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-chart">
		<div data-component="timeline" data-source="hardware"></div>
		<div class="rewind" data-component="rewind" data-source="hardware"></div>
	</div>
	</div>
	<footer class="slide__foot">
	<p class="source" data-component="sources" data-source="hardware">PassMark single-thread, 11/2026, year = launch year ·</p>
	</footer>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">AWS EC2 · on-demand · Linux · us-east-1 · 11/2026</div>
		<h2>What does clean code cost you per year?</h2>
		<p class="lede" data-component="cost-lede" data-source="aws"></p>
	</header>
	<div class="slide__body">
	<div class="stack" data-component="cost" data-source="aws"></div>
	</div>
	<footer class="slide__foot">
	<p class="source" data-component="sources" data-source="aws">Prices (updated 18 Nov 2026):</p>
	</footer>
</section>

<section class="slide slide--statement" data-title="Quote: Our job is to write programs…">
	<figure class="quote">
		<blockquote class="quote__text">
			<p>Our job is to write programs that actually run well on the hardware that we’re given.</p>
			<p class="quote__gap">[…]</p>
			<p>We can still try to come up with rules of thumb that help you keep your code well organized, easy to maintain and easy to read. Those aren’t bad <span class="quote__end">goals.<span class="quote__close" aria-hidden="true">”</span></span></p>
		</blockquote>
		<figcaption class="quote__cite">
			Casey Muratori · “Clean” Code, Horrible Performance ·
			<a class="link" href="https://www.youtube.com/watch?v=tD5NrevFtbU&amp;t=1320s" target="_blank" rel="noopener">22:00</a>
		</figcaption>
	</figure>
</section>
`);
