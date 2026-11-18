/* Motivace: titul, osnova, Casey, hardware v čase, AWS, citát */

Talk.slides(`
<section data-section="Motivace" class="slide slide--statement">
	<div class="kicker">42 · přednáška · 60 min</div>
	<h1>Mechanical<br>sympathy</h1>
	<p class="lead muted">Kód, který má hardware rád.</p>
	<div class="manifesto">
		<div class="manifesto__item">
			<span class="manifesto__num">01</span>
			<p><b>Piš pro skutečný stroj.</b><br><span class="muted">CPU, cache a paměť, ne diagram tříd.</span></p>
		</div>
		<div class="manifesto__item">
			<span class="manifesto__num">02</span>
			<p><b>No bullshit.</b><br><span class="muted">Žádné vrstvy, které nic nedělají. Jen data a co se s nimi děje.</span></p>
		</div>
		<div class="manifesto__item manifesto__item--bonus">
			<span class="manifesto__num">+</span>
			<p><b>Bonus: memory safety.</b><br><span class="muted">Méně leaků a dangling pointerů. Z návrhu, ne z disciplíny.</span></p>
		</div>
	</div>
	<p><span class="pill tone-c">C</span><span class="pill tone-py">Python</span></p>
</section>

<section class="slide" data-title="Pracovní seznam slidů">
	<header class="slide__head">
		<div class="kicker">Pracovní osnova · smazat před přednáškou</div>
		<h2>Slidy</h2>
	</header>
	<div class="slide__body">
	<ol class="outline" data-component="outline"></ol>
	</div>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">Casey Muratori · „Clean“ Code, Horrible Performance · 2023</div>
		<h2>Pět pravidel „clean code“. Co stojí?</h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<ol class="rules">
			<li><b>Prefer polymorphism to „if/else“ and „switch“</b><span>polymorfismus místo if/switch</span></li>
			<li><b>Code should not know about the internals of objects it's working with</b><span>neznej vnitřek objektů</span></li>
			<li><b>Functions should be small</b><span>malé funkce</span></li>
			<li><b>Functions should do one thing</b><span>funkce dělá jednu věc</span></li>
			<li class="rules__keep"><b>„DRY“: Don't Repeat Yourself</b><span>„seems fine“, Casey ho nechává</span></li>
		</ol>
		<div class="card">
			<b class="card__title">Zrychlení, když je porušíš</b>
			<div class="bars" data-component="bars" data-source="casey" data-unit="×"></div>
		</div>
	</div>
	</div>
	<footer class="slide__foot">
	<p class="source"><a class="link" href="https://www.youtube.com/watch?v=tD5NrevFtbU" target="_blank" rel="noopener">youtube.com/watch?v=tD5NrevFtbU</a> · výsledky v 19:35</p>
	</footer>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">Hardware v čase · výkon jednoho jádra · 100 % = Apple M5 (2025)</div>
		<h2>Kam tě to vrátí v čase?</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-chart">
		<div data-component="timeline" data-source="hardware"></div>
		<div class="rewind" data-component="rewind" data-source="hardware"></div>
	</div>
	</div>
	<footer class="slide__foot">
	<p class="source" data-component="sources" data-source="hardware">Zdroj: PassMark single-thread rating konkrétních čipů, stav 11/2026, rok = uvedení na trh ·</p>
	</footer>
</section>

<section class="slide">
	<header class="slide__head">
		<div class="kicker">AWS EC2 · on-demand · Linux · us-east-1 · 11/2026</div>
		<h2>Kolik tě clean code stojí za rok?</h2>
		<p class="lede" data-component="cost-lede" data-source="aws"></p>
	</header>
	<div class="slide__body">
	<div class="stack" data-component="cost" data-source="aws"></div>
	</div>
	<footer class="slide__foot">
	<p class="source" data-component="sources" data-source="aws">Ceny (aktualizováno 18. 11. 2026):</p>
	</footer>
</section>

<section class="slide slide--statement" data-title="Citát: Our job is to write programs…">
	<figure class="quote">
		<blockquote class="quote__text">
			<p>Our job is to write programs that actually run well on the hardware that we’re given.</p>
			<p class="quote__gap">[…]</p>
			<p>We can still try to come up with rules of thumb that help you keep your code well organized, easy to maintain and easy to read. Those aren’t bad <span class="quote__end">goals.<span class="quote__close" aria-hidden="true">”</span></span></p>
		</blockquote>
		<figcaption class="quote__cite">
			Casey Muratori · „Clean“ Code, Horrible Performance ·
			<a class="link" href="https://www.youtube.com/watch?v=tD5NrevFtbU&amp;t=1320s" target="_blank" rel="noopener">22:00</a>
		</figcaption>
	</figure>
</section>
`);
