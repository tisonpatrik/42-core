/* Hardware timeline: where does each of Casey's slowdowns put you in time?
   <div data-component="timeline" data-source="hardware">  log-scale SVG chart
   <div data-component="rewind"   data-source="hardware">  table year / chip / years back
   Both read Talk.data.hardware + Talk.data.casey. */

(() => {
	const W = 940, H = 520;
	const X0 = 92, X1 = 900, Y_TOP = 28, Y_BASE = 470;
	const YEAR_FROM = 2000, YEAR_TO = 2026;
	const LOG_MIN = Math.log10(0.03); // bottom of the chart = 3 %

	const x = year => X0 + ((year - YEAR_FROM) / (YEAR_TO - YEAR_FROM)) * (X1 - X0);
	const y = ratio => Y_TOP + (-Math.log10(ratio) / -LOG_MIN) * (Y_BASE - Y_TOP);

	/* Casey steps that slow you down, each located on the crossing series */
	function thresholds(hw) {
		const line = hw.series.find(s => s.crossings).points;
		return Talk.data.casey.steps
			.filter(s => s.factor > 1)
			.map(step => {
				const target = hw.ref.score / step.factor;
				for (let i = 0; i + 1 < line.length; i++) {
					const [y0, v0, n0] = line[i];
					const [y1, v1, n1] = line[i + 1];
					if (v0 <= target && target <= v1) {
						const t = Math.log(target / v0) / Math.log(v1 / v0);
						const year = Math.round(y0 + t * (y1 - y0));
						return {
							step,
							ratio: 1 / step.factor,
							exactYear: y0 + t * (y1 - y0),
							year,
							chip: hw.chipOverride[step.key] || (t < 0.5 ? n0 : n1),
							tone: step.factor < 2 ? 'fg' : 'hot',
						};
					}
				}
				return null;
			})
			.filter(Boolean);
	}

	const label = th => `÷${Talk.fmt.factor(th.step.factor)} ${th.step.short}`;

	function svg(hw) {
		const out = [];
		for (const r of [1, 0.5, 0.2, 0.1, 0.05]) {
			out.push(`<line x1="${X0}" x2="${X1}" y1="${y(r)}" y2="${y(r)}" class="grid-line"/>`);
			out.push(`<text x="${X0 - 14}" y="${y(r) + 6}" class="axis" text-anchor="end">${r * 100} %</text>`);
		}
		for (let yr = YEAR_FROM; yr <= 2025; yr += 5)
			out.push(`<text x="${x(yr)}" y="${Y_BASE + 34}" class="axis" text-anchor="middle">${yr}</text>`);
		out.push(`<line x1="${X0}" x2="${X1}" y1="${Y_BASE}" y2="${Y_BASE}" class="base-line"/>`);

		const ths = thresholds(hw);
		for (const th of ths) {
			const ty = y(th.ratio);
			const left = th.tone === 'fg'; // the shallow line sits above the curve on the left
			out.push(`<g class="tone-${th.tone}">`);
			out.push(`<line x1="${X0}" x2="${X1}" y1="${ty}" y2="${ty}" class="threshold"/>`);
			out.push(`<text x="${left ? X0 + 8 : X1 - 6}" y="${ty - 10}" class="threshold-label" text-anchor="${left ? 'start' : 'end'}">${label(th)}</text>`);
			out.push('</g>');
		}

		for (const s of hw.series) {
			const pts = s.points.map(([yr, v, name]) => [x(yr), y(v / hw.ref.score), `${name} (${yr}): ${v}`]);
			out.push(`<g class="tone-${s.tone}">`);
			out.push(`<polyline class="series" data-draw points="${pts.map(([px, py]) => `${px.toFixed(1)},${py.toFixed(1)}`).join(' ')}"/>`);
			for (const [px, py, title] of pts)
				out.push(`<circle class="dot" cx="${px.toFixed(1)}" cy="${py.toFixed(1)}" r="5"><title>${Talk.esc(title)}</title></circle>`);
			out.push('</g>');
		}

		const rx = x(hw.ref.year), ry = y(1);
		out.push(`<circle class="ref" cx="${rx}" cy="${ry}" r="9"><title>${hw.ref.name} (${hw.ref.year}): ${hw.ref.score}</title></circle>`);
		out.push(`<text class="note" x="${rx - 16}" y="${ry + 6}" text-anchor="end">${hw.ref.name} = 100 %</text>`);

		for (const th of ths) {
			const cx = x(th.exactYear), cy = y(th.ratio);
			out.push(`<circle class="ring" cx="${cx}" cy="${cy}" r="10"/>`);
			out.push(`<text class="note" x="${cx + 16}" y="${cy + 28}">${th.year} · ${Talk.esc(th.chip)}</text>`);
		}

		return `<svg class="timeline" viewBox="0 0 ${W} ${H}" role="img" aria-label="Výkon jednoho jádra ${YEAR_FROM}–2025 relativně k ${hw.ref.name}, logaritmická osa">${out.join('')}</svg>`;
	}

	Talk.component('timeline', {
		mount(el) {
			const hw = Talk.source(el);
			const legend = hw.series
				.map(s => `<span><b class="legend__swatch tone-${s.tone}"></b>${Talk.esc(s.name)}</span>`)
				.join('');
			el.innerHTML = `${svg(hw)}<div class="legend">${legend}<span>osa Y je logaritmická</span></div>`;
		},
	});

	Talk.component('rewind', {
		mount(el) {
			const hw = Talk.source(el);
			const rows = thresholds(hw).map(th => `
				<div class="rewind__row tone-${th.tone}">
					<span class="rewind__factor">÷${Talk.fmt.factor(th.step.factor)}</span>
					<span class="rewind__year">${th.year}</span>
					<span class="rewind__chip">${Talk.esc(th.chip)}</span>
					<span class="rewind__back">−${hw.ref.year - th.year} let</span>
				</div>`).join('');
			el.innerHTML = `
				<div class="rewind__row rewind__row--head"><span>pomaleji</span><span>rok</span><span>čip</span><span></span></div>
				${rows}`;
		},
	});
})();
