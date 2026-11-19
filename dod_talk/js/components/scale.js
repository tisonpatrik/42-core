/* Latency in human time. <div class="scale" data-component="scale" data-source="latency">
   Bar length is logarithmic; bars grow on slide enter ([data-grow]). */

(() => {
	function realTime(ns) {
		if (ns < 1000) return `${ns < 10 && ns % 1 ? Talk.fmt.dec(ns, 1) : Talk.fmt.int(ns)} ns`;
		if (ns < 1e6) return `${Talk.fmt.int(ns / 1e3)} µs`;
		return `${Talk.fmt.int(ns / 1e6)} ms`;
	}

	function humanTime(s) {
		const units = [[31557600, 'years'], [86400, 'days'], [3600, 'hours'], [60, 'min'], [1, 's']];
		for (const [size, short] of units) {
			if (s >= size) {
				const v = s / size;
				return `${v < 10 && size > 1 ? Talk.fmt.dec(v, 1) : Talk.fmt.int(v)} ${short}`;
			}
		}
		return `${Talk.fmt.dec(s, 1)} s`;
	}

	Talk.component('scale', {
		mount(el) {
			const d = Talk.source(el);
			const min = Math.log10(d.rows[0].ns);
			const max = Math.log10(d.rows[d.rows.length - 1].ns);
			el.innerHTML = d.rows.map(r => {
				const pct = 3 + ((Math.log10(r.ns) - min) / (max - min)) * 97;
				return `<div class="scale__row${r.hot ? ' tone-hot' : ' tone-c'}">
					<span class="scale__name">${Talk.esc(r.name)}</span>
					<span class="scale__real">${realTime(r.ns)}</span>
					<span class="scale__track"><i class="scale__fill" data-grow="${pct.toFixed(1)}"></i></span>
					<span class="scale__human">${humanTime(r.ns * 1e-9 * d.humanScale)}</span>
				</div>`;
			}).join('');
		},
	});
})();
