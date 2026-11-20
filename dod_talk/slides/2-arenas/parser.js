/* cub3D parser: lines via malloc vs. str8 + arena */

Talk.slides(`
<section class="slide" data-title="cub3D parser: lines via malloc vs. str8 + arena">
	<header class="slide__head">
		<div class="kicker">cub3D · loading the .cub file</div>
		<h2>Lines without <code>malloc</code></h2>
	</header>
	<div class="slide__body">
	<div class="grid cols-2">
		<figure class="snippet tone-hot">
			<figcaption class="snippet__head"><span class="snippet__tag">now</span><span class="snippet__file">src/parser/init_file.c</span><span class="snippet__note">shortened</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">/* pass 1: count the lines */
line = ft_get_line(fd);
while (line)
{
	count++;
	free(line);
	line = ft_get_line(fd);
}

/* pass 2: read every line again */
file.lines = ft_calloc(count + 1, sizeof(char *));
while (i &lt; count)
	file.lines[i++] = ft_get_line(fd);

/* free_structs.c: clean up */
while (i &lt; file-&gt;line_count)
	free(file-&gt;lines[i++]);
free(file-&gt;lines);</pre>
			<div class="snippet__stats"><span><b>2×</b>file read</span><span><b>2N×</b>malloc</span><span><b>2N×</b>free</span></div>
		</figure>
		<figure class="snippet tone-ok">
			<figcaption class="snippet__head"><span class="snippet__tag">with an arena</span><span class="snippet__note">same work via libft</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">t_str8	file;
t_str8	line;

/* whole file: 1× push */
if (!ft_read_file(arena, path, &amp;file))
	return (false);

/* lines: just views into the buffer */
while (ft_str8_next_token(&amp;file, '\\n', &amp;line))
	parse_line(ft_str8_trim(line));

/* after parsing */
ft_arena_destroy(arena);</pre>
			<div class="snippet__stats"><span><b>1×</b>read</span><span><b>1×</b>push</span><span><b>0</b>malloc per line</span><span><b>1×</b>destroy</span></div>
		</figure>
	</div>
	</div>
</section>
`);
