/* "Beyond the core" background: a die full of cores.
   <canvas class="cores" data-component="cores"></canvas>
   The title sits in one big core in the middle of the die (the one we optimized
   so far). It is lit from the start, then the small cores light up
   in random order (parallelism) and 8 lanes pulse inside every lit core (SIMD).
   Afterwards cores randomly idle for a moment and come back, so the die stays alive.
   Restarts on slide enter, loops while the slide is active.
   Performance: glow (shadowBlur) is expensive, so core frames are pre-rendered once
   into sprites; a frame is just drawImage + a few fillRects per core. */

(() => {
	const W = 1600, H = 900;
	const CELL = 80, GAP = 14, COLS = 17, ROWS = 9;
	const LANES = 8;
	const BIG_COLS = 13, BIG_ROWS = 3; // the big middle core, in cells
	const SOLO = 0.5;      // seconds with only the big core lit
	const FILL = 1.6;      // seconds until every core is lit, in random order
	const SLOT = 1.2;      // seconds per idle/busy decision after the fill
	const IDLE = 0.18;     // chance a core idles during one slot
	const FADE = 0.15;     // seconds to light up or go dark

	const css = name => getComputedStyle(document.documentElement).getPropertyValue(name).trim();

	const GLOW = 24; // sprite margin for the glow

	function sprite(w, h, paint) {
		const c = document.createElement('canvas');
		c.width = w + 2 * GLOW;
		c.height = h + 2 * GLOW;
		paint(c.getContext('2d'), GLOW, GLOW);
		return c;
	}

	function frame(ctx, x, y, w, h, r, fill, stroke, width, blur) {
		ctx.beginPath();
		ctx.roundRect(x, y, w, h, r);
		if (fill) { ctx.fillStyle = fill; ctx.fill(); }
		ctx.lineWidth = width;
		ctx.strokeStyle = stroke;
		if (blur) { ctx.shadowColor = stroke; ctx.shadowBlur = blur; ctx.stroke(); ctx.shadowBlur = 0; }
		ctx.stroke();
	}

	function makeSprites(colors, big) {
		return {
			dark: sprite(CELL, CELL, (g, x, y) => frame(g, x, y, CELL, CELL, 10, colors.panel, colors.line, 2, 0)),
			lit: sprite(CELL, CELL, (g, x, y) => frame(g, x, y, CELL, CELL, 10, colors.panel, colors.c, 2, 18)),
			big: sprite(big.w, big.h, (g, x, y) => frame(g, x, y, big.w, big.h, 18, colors.bg, colors.hot, 3, 0)),
			bigGlow: sprite(big.w, big.h, (g, x, y) => frame(g, x, y, big.w, big.h, 18, null, colors.hot, 3, 30)),
		};
	}

	function makeState(canvas) {
		canvas.width = W;
		canvas.height = H;
		const ox = (W - (COLS * (CELL + GAP) - GAP)) / 2;
		const oy = (H - (ROWS * (CELL + GAP) - GAP)) / 2;
		const c0 = (COLS - BIG_COLS) / 2, r0 = (ROWS - BIG_ROWS) / 2;
		const inBig = (c, r) => c >= c0 && c < c0 + BIG_COLS && r >= r0 && r < r0 + BIG_ROWS;
		const cores = [];
		for (let r = 0; r < ROWS; r++)
			for (let c = 0; c < COLS; c++)
				if (!inBig(c, r))
					cores.push({
						x: ox + c * (CELL + GAP),
						y: oy + r * (CELL + GAP),
						seed: (c * 7919 + r * 104729) % 997,
						on: 0,
						k: 0,
					});
		const big = {
			x: ox + c0 * (CELL + GAP),
			y: oy + r0 * (CELL + GAP),
			w: BIG_COLS * (CELL + GAP) - GAP,
			h: BIG_ROWS * (CELL + GAP) - GAP,
		};
		const colors = { bg: css('--bg'), panel: css('--panel'), line: css('--line'), hot: css('--hot'), c: css('--c'), ok: css('--ok') };
		return {
			ctx: canvas.getContext('2d', { alpha: false }),
			cores,
			big,
			colors,
			sprites: makeSprites(colors, big),
			start: 0,
			salt: 0,
			running: false,
		};
	}

	/* deterministic noise in [0, 1) for (core, slot) */
	function noise(seed, slot) {
		const x = Math.sin(seed * 12.9898 + slot * 78.233) * 43758.5453;
		return x - Math.floor(x);
	}

	function shuffle(st) {
		for (const core of st.cores)
			core.on = SOLO + Math.random() * FILL;
		st.salt = Math.random() * 1000;
	}

	/* 0 = dark, 1 = fully lit */
	function level(st, core, t) {
		if (t < core.on) return 0;
		let k = Math.min(1, (t - core.on) / FADE);
		const settled = SOLO + FILL;
		if (t > settled) {
			const slot = Math.floor((t - settled) / SLOT);
			const into = (t - settled) - slot * SLOT;
			if (noise(core.seed + st.salt, slot) < IDLE) {
				const off = Math.min(into, SLOT - into) / FADE;
				k = Math.max(0, 1 - Math.min(1, off));
			}
		}
		return k;
	}

	function draw(st, time) {
		const { ctx, cores, big, colors, sprites } = st;
		const pad = 12, lw = (CELL - 2 * pad) / LANES, lanesH = CELL - 2 * pad;
		ctx.fillStyle = colors.bg;
		ctx.fillRect(0, 0, W, H);

		/* pass 1: core frames (pre-rendered sprites) */
		for (const core of cores) {
			const k = level(st, core, time);
			core.k = k;
			const sx = core.x - GLOW, sy = core.y - GLOW;
			if (k < 1) ctx.drawImage(sprites.dark, sx, sy);
			if (k > 0) {
				ctx.globalAlpha = k;
				ctx.drawImage(sprites.lit, sx, sy);
				ctx.globalAlpha = 1;
			}
		}

		/* pass 2: SIMD lanes, plain fillRect grouped by style (dark, lit, fading) */
		const lanes = (core, k) => {
			for (let i = 0; i < LANES; i++) {
				const wave = 0.5 + 0.5 * Math.sin(time * 6 + i * 0.9 + core.seed);
				const h = Math.max(3, lanesH * (0.15 + 0.85 * wave) * k);
				ctx.fillRect(core.x + pad + i * lw + 1, core.y + CELL - pad - h, lw - 2, h);
			}
		};
		ctx.globalAlpha = 0.25;
		ctx.fillStyle = colors.line;
		for (const core of cores) if (core.k === 0) lanes(core, 0);
		ctx.globalAlpha = 1;
		ctx.fillStyle = colors.ok;
		for (const core of cores) if (core.k === 1) lanes(core, 1);
		for (const core of cores) {
			if (core.k === 0 || core.k === 1) continue;
			ctx.globalAlpha = 0.25 + 0.75 * core.k;
			lanes(core, core.k);
		}
		ctx.globalAlpha = 1;

		/* the big core: always lit, holds the title; the glow breathes */
		ctx.globalAlpha = 0.7 + 0.3 * Math.sin(time * 2);
		ctx.drawImage(sprites.bigGlow, big.x - GLOW, big.y - GLOW);
		ctx.globalAlpha = 1;
		ctx.drawImage(sprites.big, big.x - GLOW, big.y - GLOW);
	}

	function loop(el, st) {
		const frame = now => {
			if (!el.closest('.slide').classList.contains('is-active')) { st.running = false; return; }
			if (!st.start) st.start = now;
			draw(st, (now - st.start) / 1000);
			requestAnimationFrame(frame);
		};
		requestAnimationFrame(frame);
	}

	const states = new WeakMap();
	const still = () => window.matchMedia('(prefers-reduced-motion: reduce)').matches;

	Talk.component('cores', {
		mount(el) {
			const st = makeState(el);
			states.set(el, st);
			shuffle(st);
			draw(st, SOLO + FILL); // static frame: everything lit (print, thumbnails)
		},
		enter(el) {
			const st = states.get(el);
			if (!st) return;
			if (still()) { draw(st, SOLO + FILL); return; }
			shuffle(st);
			st.start = 0;
			if (st.running) return;
			st.running = true;
			loop(el, st);
		},
	});
})();
