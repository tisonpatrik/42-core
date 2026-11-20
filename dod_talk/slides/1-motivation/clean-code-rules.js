/* Five “clean code” rules. What do they cost? */

Talk.slides(`
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
`);
