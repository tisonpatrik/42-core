/* Horizontal bar chart.
   Rows from markup:  <div class="bars" data-component="bars" data-unit=" ms">
                        <div data-label="AoS" data-value="27" data-tone="c" data-delta="4,6×"></div>
   or from data:      <div class="bars" data-component="bars" data-source="casey" data-unit="×">
   Bars grow when the slide is entered (see deck.js, [data-grow]). */

(() => {
	const MAX_WIDTH = 70; // % of track, leaves room for the value label

	function rowsFromMarkup(el) {
		return [...el.children].map(r => ({
			label: r.dataset.label,
			value: Number(r.dataset.value),
			shown: r.dataset.value.replace('.', ','),
			tone: r.dataset.tone || 'c',
			delta: r.dataset.delta || '',
		}));
	}

	function rowsFromCasey(data) {
		return data.steps.map(s => ({
			label: s.label,
			value: s.factor,
			shown: Talk.fmt.dec(s.factor, 1),
			tone: s.tone,
			delta: '',
		}));
	}

	Talk.component('bars', {
		mount(el) {
			const data = Talk.source(el);
			const rows = data ? rowsFromCasey(data) : rowsFromMarkup(el);
			const unit = el.dataset.unit || '';
			const max = Math.max(...rows.map(r => r.value));
			el.innerHTML = rows.map(r => {
				const pct = Math.max(0.6, (r.value / max) * MAX_WIDTH);
				const shown = r.value < 0.05 ? '≈ 0' : r.shown;
				const delta = r.delta ? `<em class="bars__delta">${r.delta}</em>` : '';
				return `<div class="bars__label">${r.label}</div>
					<div class="bars__track">
						<div class="bars__fill tone-${r.tone}" data-grow="${pct.toFixed(2)}"></div>
						<div class="bars__value" style="left:${pct.toFixed(2)}%">${shown}${unit}${delta}</div>
					</div>`;
			}).join('');
		},
	});
})();
