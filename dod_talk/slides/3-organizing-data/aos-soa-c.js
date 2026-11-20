/* AoS vs SoA in plain C */

Talk.slides(`
<section class="slide" data-title="AoS vs SoA in plain C">
	<header class="slide__head">
		<div class="kicker"><span class="keep-case">AoS vs SoA</span> · plain C · no library</div>
		<h2>AoS and SoA, flat in C</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">AoS</span><span class="snippet__note">array of structs</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">#define N 1000000         /* number of particles */
#define DT (1.0f / 60)    /* one frame */
typedef struct s_particle
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
}	t_particle;

t_particle	ps[N];
i = 0;
while (i &lt; N)
{
	ps[i].x += ps[i].vx * DT;
	i++;
}</pre>
				<div class="snippet__mem"><i class="is-read">x</i><i>y</i><i>z</i><i class="is-read">vx</i><i>vy</i><i>vz</i><i class="is-read">x</i><i>y</i><i>z</i><i class="is-read">vx</i><i>vy</i><i>vz</i><i class="snippet__more">…</i></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">SoA</span><span class="snippet__note">struct of arrays</span></figcaption>
<pre class="code code--xs" data-component="code" data-lang="c">#define N 1000000         /* number of particles */
#define DT (1.0f / 60)    /* one frame */
typedef struct s_particles
{
	float	x[N];
	float	y[N];
	float	z[N];
	float	vx[N];
	float	vy[N];
	float	vz[N];
}	t_particles;

t_particles	ps;
i = 0;
while (i &lt; N)
{
	ps.x[i] += ps.vx[i] * DT;
	i++;
}</pre>
				<div class="snippet__mem"><i class="is-read">x</i><i class="is-read">x</i><i class="is-read">x</i><i class="is-read">x</i><i class="is-read">x</i><i class="snippet__more">… y[N] z[N] …</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="is-read">vx</i><i class="snippet__more">…</i></div>
			</figure>
		</div>
	</div>
</section>
`);
