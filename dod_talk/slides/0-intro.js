/* 0 · Úvod: titul, osnova, Casey, hardware v čase, AWS, teze */

Talk.slides(`
<section class="slide slide--center">
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

<section class="slide">
	<div class="kicker">Osnova</div>
	<h2>Kam dnes půjdeme</h2>
	<div class="agenda">
		<div class="agenda__row">
			<div class="agenda__num">00</div>
			<div><div class="agenda__title">Úvod</div><div class="agenda__sub">Proč tě to má zajímat: leaky, pomalé cykly, jedna teze</div></div>
			<div class="agenda__time">5 min</div>
		</div>
		<div class="agenda__row">
			<div class="agenda__num">01</div>
			<div><div class="agenda__title">Hardware</div><div class="agenda__sub">Proč CPU většinu času čeká na paměť</div></div>
			<div class="agenda__time">8 min</div>
		</div>
		<div class="agenda__row agenda__row--pillar">
			<div class="agenda__num">02</div>
			<div><div class="agenda__title">Layout</div><div class="agenda__sub">Jak data leží v paměti: AoS → SoA, náš cub3D, NumPy</div></div>
			<div class="agenda__time">15 min</div>
		</div>
		<div class="agenda__row agenda__row--pillar">
			<div class="agenda__num">03</div>
			<div><div class="agenda__title">Lifetime</div><div class="agenda__sub">Jak dlouho data žijí: arény, scratch, CPython pymalloc</div></div>
			<div class="agenda__time">15 min</div>
		</div>
		<div class="agenda__row">
			<div class="agenda__num">04</div>
			<div><div class="agenda__title">Závěr</div><div class="agenda__sub">Kdy DOD nedělat + pět otázek do příštího projektu</div></div>
			<div class="agenda__time">7 min</div>
		</div>
		<div class="agenda__row agenda__row--qa">
			<div class="agenda__num">??</div>
			<div><div class="agenda__title">Otázky</div></div>
			<div class="agenda__time">10 min</div>
		</div>
	</div>
</section>

<section class="slide">
	<div class="kicker">Casey Muratori · „Clean“ Code, Horrible Performance · 2023</div>
	<h2>Pět pravidel „clean code“. Co stojí?</h2>
	<div class="grid grid--fill cols-2">
		<ol class="rules">
			<li><b>Prefer polymorphism to „if/else“ and „switch“</b><span>polymorfismus místo if/switch</span></li>
			<li><b>Code should not know about the internals of objects it's working with</b><span>neznej vnitřek objektů</span></li>
			<li><b>Functions should be small</b><span>malé funkce</span></li>
			<li><b>Functions should do one thing</b><span>funkce dělá jednu věc</span></li>
			<li class="rules__keep"><b>„DRY“: Don't Repeat Yourself</b><span>„seems fine“, Casey ho nechává</span></li>
		</ol>
		<div class="card">
			<h3>Zrychlení, když je porušíš</h3>
			<div class="bars" data-component="bars" data-source="casey" data-unit="×"></div>
		</div>
	</div>
	<p class="source"><a class="link" href="https://www.youtube.com/watch?v=tD5NrevFtbU" target="_blank" rel="noopener">youtube.com/watch?v=tD5NrevFtbU</a> · výsledky v 19:35</p>
</section>

<section class="slide">
	<div class="kicker">Hardware v čase · výkon jednoho jádra · 100 % = Apple M5 (2025)</div>
	<h2>Kam tě to vrátí v čase?</h2>
	<div class="grid grid--fill grid--center cols-chart">
		<div data-component="timeline" data-source="hardware"></div>
		<div class="rewind" data-component="rewind" data-source="hardware"></div>
	</div>
	<p class="source" data-component="sources" data-source="hardware">Zdroj: PassMark single-thread rating konkrétních čipů, stav 11/2026, rok = uvedení na trh ·</p>
</section>

<section class="slide">
	<div class="kicker">AWS EC2 · on-demand · Linux · us-east-1 · 11/2026</div>
	<h2>Kolik tě clean code stojí za rok?</h2>
	<div class="stack" data-component="cost" data-source="aws"></div>
	<p class="source" data-component="sources" data-source="aws">Ceny (aktualizováno 18. 11. 2026):</p>
</section>

<section class="slide slide--center">
	<div class="kicker">Teze</div>
	<p class="statement">Program je transformace dat.<br><span class="muted">Znej svoje data.</span></p>
	<div class="grid cols-2 mt">
		<div class="card">
			<h3>① Layout</h3>
			<p>Jaký mají tvar? Kolik jich je?<br>Jak k nim přistupuju v hot loopu?</p>
		</div>
		<div class="card">
			<h3>② Lifetime</h3>
			<p>Kdy vznikají? Kdy umírají?<br>Co umírá <em>spolu</em>? → <b class="hot">arény</b></p>
		</div>
	</div>
</section>
`);
