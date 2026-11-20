/* ==========================================================================
   Talk: the one global namespace.
   - Talk.data       shared numbers (filled by data/*.js)
   - Talk.slides     add slide markup (called by slides/*.js, in load order)
   - Talk.component  register a component: { mount(el), enter(el) }
   - Talk.fmt        number formatting (en-US)
   - Talk.typeset    keeps numbers and their units on one line
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

	const LOCALE = 'en-US';
	const fmt = {
		int: n => Math.round(n).toLocaleString(LOCALE),
		dec: (n, d = 1) => n.toLocaleString(LOCALE, { minimumFractionDigits: d, maximumFractionDigits: d }),
		/* slowdown factor as people say it: 1.8 · 10 · 15 · 24 */
		factor: f => (f < 2 ? fmt.dec(f, 1) : String(Math.round(f))),
	};

	const esc = s => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');

	/* Typography: no number torn from its unit, no "≈" alone at a line end.
	   Runs once after components mount. Skips code, SVG and canvas text. */
	const NBSP = '\u00a0';
	const UNITS = 'B|KB|MB|GB|GB/s|ms|ns|µs|s|min|×|years|days|hours|threads|thread|instructions|instruction';
	const RULES = [
		[new RegExp(`(\\d) (?=(${UNITS})(?!\\w))`, 'g'), `$1${NBSP}`],
		[/([≈~]) /g, `$1${NBSP}`],
	];

	function typeset(root = document) {
		const walker = document.createTreeWalker(root, NodeFilter.SHOW_TEXT, {
			acceptNode: n => n.parentElement.closest('pre, code, svg, script, style, .tree')
				? NodeFilter.FILTER_REJECT : NodeFilter.FILTER_ACCEPT,
		});
		const nodes = [];
		while (walker.nextNode()) nodes.push(walker.currentNode);
		for (const node of nodes) {
			let v = node.textContent;
			for (const [re, to] of RULES) v = v.replace(re, to);
			if (v !== node.textContent) node.textContent = v;
		}
	}

	return { data, slides, render, component, mountAll, enter, source, fmt, esc, typeset };
})();
