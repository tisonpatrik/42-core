/* Inside t_str8 */

Talk.slides(`
<section class="slide" data-title="Inside t_str8">
	<header class="slide__head">
		<div class="kicker">libft · src/str8</div>
		<h2>Inside <code>t_str8</code></h2>
	</header>
	<div class="slide__body">
	<div class="grid grid--center cols-wide-left">
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_str8
{
	uint8_t	*str;
	size_t	len;
}	t_str8;

/* a view into existing memory: 0 allocations */
t_str8	ft_str8_create(uint8_t *str, size_t len)
{
	return ((t_str8){str, len});
}

/* new string: 1× push into the arena (checks omitted) */
t_str8	ft_str8_join(t_arena *arena, t_str8 a, t_str8 b)
{
	t_str8	res;

	res.len = a.len + b.len;
	res.str = ft_arena_push(arena, res.len + 1);
	ft_memcpy(res.str, a.str, a.len);
	ft_memcpy(res.str + a.len, b.str, b.len);
	return (res);
}</pre>
		<div class="facts facts--big">
			<span><b>substr · trim · next_token</b> just a view, 0 allocations</span>
			<span><b>join · dup · split</b> 1× push into the arena</span>
			<span><b>free</b> doesn’t exist, an arena reset cleans up</span>
		</div>
	</div>
	</div>
</section>
`);
