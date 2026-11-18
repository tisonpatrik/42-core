/* ==========================================================================
   Talk: the one global namespace.
   - Talk.data       shared numbers (filled by data/*.js)
   - Talk.slides     add slide markup (called by slides/*.js, in load order)
   - Talk.component  register a component: { mount(el), enter(el) }
   - Talk.fmt        Czech number formatting
   Plain scripts (no ES modules) so the deck works straight from file://.
   ========================================================================== */

window.Talk = (() => {
	const data = {};
	const registry = {};
	const markup = [];

	function slides(html) {
		markup.push(html);
	}

	function render(deck) {
		deck.innerHTML = markup.join('\n');
	}

	function component(name, def) {
		registry[name] = def;
	}

	/* Every element with data-component="a b" is mounted by each named component. */
	function each(root, fn) {
		root.querySelectorAll('[data-component]').forEach(el => {
			el.dataset.component.split(/\s+/).forEach(name => {
				const def = registry[name];
				if (!def) {
					console.warn(`Talk: unknown component "${name}"`, el);
					return;
				}
				fn(def, el);
			});
		});
	}

	function mountAll(root = document) {
		each(root, (def, el) => def.mount && def.mount(el));
	}

	function enter(slide) {
		each(slide, (def, el) => def.enter && def.enter(el));
	}

	function source(el) {
		const key = el.dataset.source;
		if (!key) return null;
		if (!data[key]) throw new Error(`Talk: missing data "${key}"`);
		return data[key];
	}

	const cs = 'cs-CZ';
	const fmt = {
		int: n => Math.round(n).toLocaleString(cs),
		dec: (n, d = 1) => n.toLocaleString(cs, { minimumFractionDigits: d, maximumFractionDigits: d }),
		/* slowdown factor as people say it: 1,8 · 10 · 15 · 24 */
		factor: f => (f < 2 ? fmt.dec(f, 1) : String(Math.round(f))),
	};

	const esc = s => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');

	return { data, slides, render, component, mountAll, enter, source, fmt, esc };
})();
