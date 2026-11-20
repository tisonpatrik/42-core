/* cub3D: who reads and who writes what (ROM and RAM) */

Talk.slides(`
<section class="slide" data-title="cub3D: who reads and who writes what (ROM and RAM)">
	<header class="slide__head">
		<div class="kicker">cub3D · data flow</div>
		<h2>Who reads the data and who changes it</h2>
	</header>
	<div class="slide__body">
	<div class="rw">
		<span></span>
		<span class="rw__col"><b>start</b><small>setup.c, once</small></span>
		<span class="rw__col"><b>update</b><small>every frame</small></span>
		<span class="rw__col"><b>render</b><small>every frame</small></span>

		<span class="rw__row tone-c"><b>t_rom</b><small>textures, colors, map size</small></span>
		<span class="rw__cell"><i class="rw__tag rw__tag--w">write</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i></span>

		<span class="rw__row tone-py"><b>t_ram</b><small>tiles, player, fire, orbs</small></span>
		<span class="rw__cell"><i class="rw__tag rw__tag--w">write</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i><i class="rw__tag rw__tag--w">write</i></span><span class="rw__cell"><i class="rw__tag rw__tag--r">read</i><small>+ per-frame helper buffers</small></span>
	</div>
	<div class="cards cards--3 mt">
		<div class="card card--compact tone-c"><b class="card__title">t_rom never changes after startup</b><p class="card__body">Update and render only read it, so nothing can break it at runtime.</p></div>
		<div class="card card--compact tone-py"><b class="card__title">t_ram is the whole game state</b><p class="card__body">Everything that changes lives in one place.</p></div>
		<div class="card card--compact tone-hot"><b class="card__title">It’s not hardware</b><p class="card__body">ROM and RAM are just two structs, split by who changes the data.</p></div>
	</div>
	</div>
</section>
`);
