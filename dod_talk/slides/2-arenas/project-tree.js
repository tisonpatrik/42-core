/* Project tree: memory apart from logic */

Talk.slides(`
<section class="slide" data-title="Project tree: memory apart from logic">
	<header class="slide__head">
		<div class="kicker">How to split it</div>
		<h2>Memory apart from logic</h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-wide-left">
<div class="tree"><span class="tree__dir">push_swap/</span>
├── <span class="tree__dir">src/</span>
│   ├── <span class="tree__dir tree__dir--mem">memory/</span>         <span class="tree__note tree__note--mem">the only place with malloc / free</span>
│   │   ├── arena.c      <span class="tree__note">create · push · reset · destroy</span>
│   │   └── budget.c     <span class="tree__note">how much memory the whole run needs</span>
│   ├── main.c           <span class="tree__note">1× create … 1× destroy</span>
│   ├── <span class="tree__dir">validator/</span>      <span class="tree__brace">│</span>
│   ├── <span class="tree__dir">stack/</span>          <span class="tree__brace">│</span> <span class="tree__note">business logic</span>
│   ├── <span class="tree__dir">ops/</span>            <span class="tree__brace">│</span> <span class="tree__note">gets a t_arena *,</span>
│   ├── <span class="tree__dir">selector/</span>       <span class="tree__brace">│</span> <span class="tree__note">never calls</span>
│   ├── <span class="tree__dir">separator/</span>      <span class="tree__brace">│</span> <span class="tree__note">malloc or free</span>
│   └── <span class="tree__dir">solver/</span>         <span class="tree__brace">│</span>
└── Makefile</div>
		<div class="rule">
			<p class="rule__main"><span class="rule__code">malloc</span> and <span class="rule__code">free</span><br>only in <span class="rule__code">memory/</span></p>
			<p class="rule__sub">The rest borrows memory,<br>it never owns it.</p>
		</div>
	</div>
	</div>
</section>
`);
