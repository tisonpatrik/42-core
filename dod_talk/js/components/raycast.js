/* Live raycaster background (what cub3D does, in ~150 lines of JS).
   <canvas class="raycast" data-component="raycast"></canvas>
   Low-res render scaled up with pixelated sampling. Runs only while its slide is active. */

(() => {
	const W = 320, H = 180;
	const TEX = 64;
	const MAP = [
		'1111111111111111',
		'1000000000000001',
		'1011101111011101',
		'1010000000000101',
		'1010111001110101',
		'1000100000010001',
		'1000100000010001',
		'1010111001110101',
		'1010000000000101',
		'1011101111011101',
		'1000000000000001',
		'1111111111111111',
	];
	/* camera loops around the outer corridor */
	const PATH = [[1.5, 1.5], [14.5, 1.5], [14.5, 10.5], [1.5, 10.5]];
	const SPEED = 1.6;      // cells per second
	const TURN = 3.2;       // heading smoothing
	const FOV_PLANE = 0.66;

	const solid = (x, y) => MAP[y] === undefined || MAP[y][x] !== '0';
	const rgb = (r, g, b) => (255 << 24) | (b << 16) | (g << 8) | r; // little-endian ABGR

	/* procedural bricks: red-brown blocks, dark mortar, a bit of noise */
	function brickTexture(base) {
		const t = new Uint32Array(TEX * TEX);
		let seed = 7;
		const rand = () => ((seed = (seed * 1103515245 + 12345) >>> 0) / 4294967296);
		for (let y = 0; y < TEX; y++) {
			const row = Math.floor(y / 16);
			const offset = row % 2 ? 16 : 0;
			for (let x = 0; x < TEX; x++) {
				const mortar = y % 16 < 2 || (x + offset) % 32 < 2;
				const n = rand() * 0.35 + 0.65;
				const [r, g, b] = mortar ? [28, 14, 10] : base.map(c => Math.min(255, c * n));
				t[y * TEX + x] = rgb(r | 0, g | 0, b | 0);
			}
		}
		return t;
	}

	function makeState(canvas) {
		canvas.width = W;
		canvas.height = H;
		const ctx = canvas.getContext('2d');
		const image = ctx.createImageData(W, H);
		return {
			ctx,
			image,
			pixels: new Uint32Array(image.data.buffer),
			textures: [brickTexture([150, 52, 30]), brickTexture([110, 40, 26])],
			pos: { x: PATH[0][0], y: PATH[0][1] },
			angle: 0,
			target: 1,
			last: 0,
			running: false,
		};
	}

	function step(st, dt) {
		const [tx, ty] = PATH[st.target];
		const dx = tx - st.pos.x, dy = ty - st.pos.y;
		const dist = Math.hypot(dx, dy);
		if (dist < 0.05) {
			st.target = (st.target + 1) % PATH.length;
			return;
		}
		const want = Math.atan2(dy, dx);
		let diff = want - st.angle;
		diff = Math.atan2(Math.sin(diff), Math.cos(diff));
		st.angle += diff * Math.min(1, TURN * dt);
		const move = Math.min(dist, SPEED * dt) * Math.max(0, Math.cos(diff));
		st.pos.x += (dx / dist) * move;
		st.pos.y += (dy / dist) * move;
	}

	function render(st, time) {
		const { pixels } = st;
		const dirX = Math.cos(st.angle), dirY = Math.sin(st.angle);
		const planeX = -dirY * FOV_PLANE, planeY = dirX * FOV_PLANE;
		const bob = Math.sin(time * 0.008) * 2;
		const horizon = (H / 2 + bob) | 0;

		/* ceiling and floor: dark gradients, floor with a hot glow near the horizon */
		for (let y = 0; y < H; y++) {
			let c;
			if (y < horizon) {
				const k = y / horizon;
				c = rgb(10 + 18 * k | 0, 8 + 10 * k | 0, 12 + 10 * k | 0);
			} else {
				const k = (y - horizon) / (H - horizon);
				c = rgb(60 - 30 * k | 0, 18 - 8 * k | 0, 8);
			}
			pixels.fill(c, y * W, (y + 1) * W);
		}

		for (let x = 0; x < W; x++) {
			const cam = (2 * x) / W - 1;
			const rx = dirX + planeX * cam, ry = dirY + planeY * cam;
			let mx = st.pos.x | 0, my = st.pos.y | 0;
			const ddx = Math.abs(1 / rx), ddy = Math.abs(1 / ry);
			const sx = rx < 0 ? -1 : 1, sy = ry < 0 ? -1 : 1;
			let sdx = (rx < 0 ? st.pos.x - mx : mx + 1 - st.pos.x) * ddx;
			let sdy = (ry < 0 ? st.pos.y - my : my + 1 - st.pos.y) * ddy;
			let side = 0;
			for (let i = 0; i < 64; i++) {
				if (sdx < sdy) { sdx += ddx; mx += sx; side = 0; }
				else { sdy += ddy; my += sy; side = 1; }
				if (solid(mx, my)) break;
			}
			const dist = side === 0 ? sdx - ddx : sdy - ddy;
			const lineH = (H / Math.max(dist, 0.0001)) | 0;
			const top = Math.max(0, horizon - (lineH >> 1));
			const bottom = Math.min(H - 1, horizon + (lineH >> 1));
			let wallX = side === 0 ? st.pos.y + dist * ry : st.pos.x + dist * rx;
			wallX -= Math.floor(wallX);
			const texX = (wallX * TEX) | 0;
			const tex = st.textures[side];
			const shade = Math.max(0.12, 1 - dist / 9) * (side ? 0.7 : 1);
			const stepY = TEX / lineH;
			let texPos = (top - horizon + lineH / 2) * stepY;
			for (let y = top; y <= bottom; y++) {
				const c = tex[((texPos | 0) & (TEX - 1)) * TEX + texX];
				texPos += stepY;
				const r = (c & 255) * shade, g = ((c >> 8) & 255) * shade, b = ((c >> 16) & 255) * shade;
				pixels[y * W + x] = rgb(r | 0, g | 0, b | 0);
			}
		}
		st.ctx.putImageData(st.image, 0, 0);
	}

	function loop(el, st) {
		const frame = time => {
			const active = el.closest('.slide').classList.contains('is-active');
			if (!active) { st.running = false; return; }
			const dt = st.last ? Math.min(0.05, (time - st.last) / 1000) : 0;
			st.last = time;
			step(st, dt);
			render(st, time);
			requestAnimationFrame(frame);
		};
		requestAnimationFrame(frame);
	}

	const states = new WeakMap();

	Talk.component('raycast', {
		mount(el) {
			const st = makeState(el);
			states.set(el, st);
			render(st, 0);
		},
		enter(el) {
			const st = states.get(el);
			if (!st || st.running) return;
			st.running = true;
			st.last = 0;
			loop(el, st);
		},
	});
})();
