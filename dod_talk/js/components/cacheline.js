/* Two cache lines (2 × 64 B, 16 cells of 4 B each), labelled by field.
   <div class="cacheline" data-component="cacheline" data-pattern="aos|soa">
   aos: struct of 72 B, the update loop reads only x y z vx vy vz.
   soa: one line of x[], one line of vx[]: every byte is used. */

(() => {
	const AOS_STRUCT = [
		['x', 1, 1], ['y', 1, 1], ['z', 1, 1], ['vx', 1, 1], ['vy', 1, 1], ['vz', 1, 1],
		['name', 8, 0], ['color', 1, 0], ['mass', 1, 0], ['flags', 1, 0], ['id', 1, 0],
	];

	function aosCells() {
		const cells = [];
		let used = 0;
		for (let p = 0; used < 32; p++) {
			for (const [label, span, hot] of AOS_STRUCT) {
				if (used >= 32) break;
				const s = Math.min(span, 32 - used, 16 - (used % 16));
				cells.push({ label: p ? `${label}₁` : label, span: s, hot });
				used += s;
			}
		}
		return cells;
	}

	function soaCells() {
		const cells = [];
		for (let i = 0; i < 16; i++) cells.push({ label: `x${i}`, span: 1, hot: 1 });
		for (let i = 0; i < 16; i++) cells.push({ label: `vx${i}`, span: 1, hot: 1 });
		return cells;
	}

	Talk.component('cacheline', {
		mount(el) {
			const cells = el.dataset.pattern === 'soa' ? soaCells() : aosCells();
			el.innerHTML = cells.map(c =>
				`<i class="${c.hot ? 'is-hot' : ''}" style="grid-column: span ${c.span}">${c.label}</i>`).join('');
		},
	});
})();
