/* AoS vs SoA in code (Python) */

Talk.slides(`
<section class="slide" data-title="AoS vs SoA in code (Python)">
	<header class="slide__head">
		<div class="kicker"><span class="keep-case">AoS vs SoA</span> · Python · 1M particles</div>
		<h2>Same work, different data layout</h2>
	</header>
	<div class="slide__body">
		<div class="grid cols-2">
			<figure class="snippet tone-hot">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">AoS</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">list of objects</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">N = 1_000_000      # number of particles
DT = 1 / 60        # one frame at 60 FPS

class Particle:
    def __init__(self):
        self.x = self.y = self.z = 0.0
        self.vx = self.vy = self.vz = 1.0

ps = [Particle() for _ in range(N)]

for p in ps:
    p.x += p.vx * DT
    p.y += p.vy * DT
    p.z += p.vz * DT</pre>
				<div class="snippet__stats"><span><b>188 ms</b>per step</span><span><b>200 MB</b>memory</span></div>
			</figure>
			<figure class="snippet tone-ok">
				<figcaption class="snippet__head"><span class="snippet__tag keep-case">SoA</span><span class="snippet__file">demos/python/particles.py</span><span class="snippet__note">one array per field</span></figcaption>
<pre class="code code--sm" data-component="code" data-lang="py">import numpy as np

N = 1_000_000      # number of particles
DT = 1 / 60        # one frame at 60 FPS

x  = np.zeros(N, np.float32)   # y, z the same
vx = np.ones(N, np.float32)    # vy, vz the same

x += vx * DT
y += vy * DT
z += vz * DT</pre>
				<div class="snippet__stats"><span><b>3.7 ms</b>per step</span><span><b>24 MB</b>memory</span></div>
			</figure>
		</div>
	</div>
</section>
`);
