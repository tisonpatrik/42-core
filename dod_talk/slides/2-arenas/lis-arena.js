/* push_swap: LIS without vs. with an arena */

Talk.slides(`
<section class="slide" data-title="push_swap: LIS without vs. with an arena">
	<header class="slide__head">
		<div class="kicker">push_swap · separator · LIS computation</div>
		<h2>Five arrays, one lifetime</h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<figure class="snippet tone-hot">
			<figcaption class="snippet__head"><span class="snippet__tag">without an arena</span><span class="snippet__note">what it would look like</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">c = malloc(sizeof(t_lis_computation));
if (!c)
	return (NULL);
c-&gt;nodes = malloc(sizeof(t_node *) * n);
if (!c-&gt;nodes)
	return (free(c), NULL);
c-&gt;values = malloc(sizeof(int) * n);
if (!c-&gt;values)
	return (free(c-&gt;nodes), free(c), NULL);
c-&gt;lis_lengths = malloc(sizeof(int) * n);
if (!c-&gt;lis_lengths)
	return (free(c-&gt;values), free(c-&gt;nodes),
		free(c), NULL);
/* + previous_indices, lis_nodes
   + free_computation() with 6× free */</pre>
			<div class="snippet__stats"><span><b>6×</b>malloc</span><span><b>6×</b>free</span><span><b>5</b>error paths</span></div>
		</figure>
		<figure class="snippet tone-ok">
			<figcaption class="snippet__head"><span class="snippet__tag">with an arena</span><span class="snippet__file">src/separator/separator_arena.c</span><span class="snippet__note">shortened</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">size = sizeof(t_lis_computation);
size += sizeof(t_node *) * n * 2;
size += sizeof(int) * n * 3;
arena-&gt;arena = ft_arena_create(size);

c = ft_arena_alloc(arena-&gt;arena, sizeof(*c));
c-&gt;nodes = ft_arena_alloc(arena-&gt;arena,
		sizeof(t_node *) * n);
c-&gt;values = ft_arena_alloc(arena-&gt;arena,
		sizeof(int) * n);
/* lis_lengths, previous_indices, lis_nodes
   the same: just an offset bump */

/* separator.c, after the computation */
free_separator_arena(arena);</pre>
			<div class="snippet__stats"><span><b>1</b>block</span><span><b>1×</b>free</span><span><b>1</b>error return</span></div>
		</figure>
	</div>
	</div>
	<footer class="slide__foot">
	<p class="source">
		<a class="link" href="https://www.dgtlgrove.com/p/untangling-lifetimes-the-arena-allocator" target="_blank" rel="noopener">Ryan Fleury: Untangling Lifetimes</a> ·
		<a class="link" href="https://www.youtube.com/watch?v=rJrd2QMVbGM" target="_blank" rel="noopener">Boot.dev: C Programming and Memory Management</a>
	</p>
	</footer>
</section>
`);
