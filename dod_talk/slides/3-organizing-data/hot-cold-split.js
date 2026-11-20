/* Hot/cold split: how to split a struct */

Talk.slides(`
<section class="slide" data-title="Hot/cold split: how to split a struct">
	<header class="slide__head">
		<div class="kicker">hot/cold split · what if the struct needs more?</div>
		<h2>Split the struct by how often you read it</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag">1 struct</span><span class="snippet__file">demos/c/hotcold.c</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_particle
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_particle;
t_particle	g_ps[N];</pre>
				<div class="snippet__stats"><span><b>72 B</b>per particle</span><span><b>24 B</b>of it read by the loop</span></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag">hot + cold</span><span class="snippet__file">demos/c/hotcold.c</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">typedef struct s_hot     /* every frame */
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
}	t_hot;
typedef struct s_cold    /* only now and then */
{
	char	name[32];
	int		color;
	float	mass;
	int		flags;
	int		id;
}	t_cold;
t_hot	g_hot[N];
t_cold	g_cold[N];       /* same i = same particle */</pre>
				<div class="snippet__stats"><span><b>24 B</b>hot, read by the loop</span><span><b>48 B</b>cold, lives elsewhere</span></div>
			</figure>
		</div>
	</div>
</section>
`);
