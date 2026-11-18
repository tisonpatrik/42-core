/* Retro pixel title: text drawn into a tiny canvas and scaled up without smoothing.
   <canvas class="pixeltitle" data-component="pixeltitle" data-left="CUB" data-right="3D"></canvas>
   Left part uses DoomLeft, right part DoomRight (the logo leans outwards on both sides).
   Hard colour bands like a 256-colour palette, blocky extrusion, no anti-aliased edges. */

(() => {
	const W = 360, H = 170, SIZE = 132;
	/* colours sampled from the 1993 logo: steel-blue top, rust-to-gold bottom, orange edge */
	const BANDS = [
		'#3e5468', '#476a85', '#557a90', '#6a8fa3', '#7ba0b2',
		'#8f5a34', '#b46d2a', '#cf8f35', '#e8b04a', '#f4d58a', '#dc8830',
	];
	const EXTRUDE = ['#e2a65d', '#d5873d', '#b8602a', '#7a3418'];
	const OUTLINE = '#8fb0c6';

	function draw(el) {
		const ctx = el.getContext('2d');
		const left = el.dataset.left || '';
		const right = el.dataset.right || '';
		ctx.clearRect(0, 0, W, H);

		ctx.font = `${SIZE}px DoomLeft`;
		const ml = ctx.measureText(left);
		ctx.font = `${SIZE}px DoomRight`;
		const mr = ctx.measureText(right);
		const ascent = Math.max(ml.actualBoundingBoxAscent, mr.actualBoundingBoxAscent);
		const descent = Math.max(ml.actualBoundingBoxDescent, mr.actualBoundingBoxDescent);
		const x0 = Math.round((W - ml.width - mr.width) / 2) - 4;
		const base = Math.round((H + ascent - descent) / 2) - 4;

		const text = (paint, dx, dy) => {
			ctx.font = `${SIZE}px DoomLeft`;
			paint(left, x0 + dx, base + dy);
			ctx.font = `${SIZE}px DoomRight`;
			paint(right, x0 + ml.width + dx, base + dy);
		};
		const fill = (style, dx, dy) => { ctx.fillStyle = style; text((t, x, y) => ctx.fillText(t, x, y), dx, dy); };

		/* blocky extrusion: one solid step per pixel, darker as it goes back */
		for (let i = EXTRUDE.length * 2; i >= 1; i--)
			fill(EXTRUDE[Math.min(EXTRUDE.length - 1, (i - 1) >> 1)], i, i);

		/* body: hard bands, no smooth gradient */
		const g = ctx.createLinearGradient(0, base - ascent, 0, base + descent);
		BANDS.forEach((c, i) => {
			g.addColorStop(i / BANDS.length, c);
			g.addColorStop((i + 1) / BANDS.length - 0.0001, c);
		});
		fill(g, 0, 0);

		ctx.lineWidth = 2;
		ctx.strokeStyle = OUTLINE;
		text((t, x, y) => ctx.strokeText(t, x, y), 0, 0);

		/* kill anti-aliasing: every pixel is either fully on or off */
		const img = ctx.getImageData(0, 0, W, H);
		const d = img.data;
		for (let i = 3; i < d.length; i += 4) d[i] = d[i] > 110 ? 255 : 0;
		ctx.putImageData(img, 0, 0);
	}

	Talk.component('pixeltitle', {
		mount(el) {
			el.width = W;
			el.height = H;
			Promise.all([
				document.fonts.load(`${SIZE}px DoomLeft`),
				document.fonts.load(`${SIZE}px DoomRight`),
			]).then(() => draw(el));
		},
	});
})();
