/* Two cache lines (2 × 64 B, 16 cells of 4 B each), labelled by field.
   <div class="cacheline" data-component="cacheline" data-pattern="aos|soa">
   <div class="cacheline" data-component="cacheline"
        data-fields="x y z vx vy vz name:8 color" data-read="x y z vx vy vz">
   data-fields: one struct, repeated back to back; "name:8" = field 8 cells wide.
   data-read:   fields the loop reads (highlighted), the rest is loaded for nothing.
   soa: one line of x[], one line of vx[]: every byte is used. */

(() => {
	const CELLS = 32;
	const PRESETS = {
		aos: { fields: 'x y z vx vy vz', read: 'x vx' },
	};

	function structCells(fieldSpec, readSpec) {
		const fields = fieldSpec.split(/\s+/).map(f => {
			const [label, span] = f.split(':');
			return { label, span: Number(span) || 1 };
		});
		const read = new Set(readSpec.split(/\s+/));
		const cells = [];
		let used = 0;
		while (used < CELLS) {
			for (const f of fields) {
				if (used >= CELLS) break;
				const span = Math.min(f.span, CELLS - used, 16 - (used % 16));
				cells.push({ label: f.label, span, hot: read.has(f.label) });
				used += span;
			}
		}
		return cells;
	}

	function soaCells() {
		const cells = [];
		for (let i = 0; i < 16; i++) cells.push({ label: 'x', span: 1, hot: true });
		for (let i = 0; i < 16; i++) cells.push({ label: 'vx', span: 1, hot: true });
		return cells;
	}

	Talk.component('cacheline', {
		mount(el) {
			const preset = PRESETS[el.dataset.pattern];
			const cells = el.dataset.pattern === 'soa'
				? soaCells()
				: structCells(el.dataset.fields || preset.fields, el.dataset.read || preset.read);
			el.innerHTML = cells.map(c =>
				`<i class="${c.hot ? 'is-hot' : ''}"${c.span > 1 ? ` style="grid-column: span ${c.span}"` : ''}>${c.label}</i>`).join('');
		},
	});
})();
