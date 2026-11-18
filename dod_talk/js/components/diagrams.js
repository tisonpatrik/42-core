/* Small generated diagrams: cache line cells, lifetime ticks, source links. */

/* <div class="cacheline" data-component="cacheline" data-pattern="aos|soa">
   32 cells of 4 B = two 64 B cache lines. AoS: 72 B struct, first 24 B hot. */
Talk.component('cacheline', {
	mount(el) {
		const CELLS = 32;
		const STRUCT = 18; // 72 B / 4 B
		const HOT = 6;     // x y z vx vy vz
		const aos = el.dataset.pattern === 'aos';
		let html = '';
		for (let i = 0; i < CELLS; i++) {
			const hot = !aos || i % STRUCT < HOT;
			const split = aos && i > 0 && i % STRUCT === 0;
			html += `<i class="${hot ? 'is-hot' : ''}${split ? ' is-split' : ''}"></i>`;
		}
		el.innerHTML = html;
	},
});

/* <div class="lifetimes__lane" data-component="ticks" data-ticks="28" data-tone="ok"> */
Talk.component('ticks', {
	mount(el) {
		const n = Number(el.dataset.ticks);
		const tone = el.dataset.tone || 'ok';
		const step = 88 / n;
		let html = '';
		for (let i = 0; i < n; i++)
			html += `<div class="lifetimes__seg tone-${tone}" style="--from:${10 + i * step}%;--len:${step * 0.6}%"></div>`;
		el.innerHTML = html;
	},
});

/* <p class="source" data-component="sources" data-source="aws">Ceny:</p>
   Appends the data's [label, url] pairs as links. */
Talk.component('sources', {
	mount(el) {
		const links = Talk.source(el).sources
			.map(([label, url]) => `<a class="link" href="${url}" target="_blank" rel="noopener">${Talk.esc(label)}</a>`)
			.join(' · ');
		el.insertAdjacentHTML('beforeend', ` ${links}`);
	},
});
