/* <pre class="code" data-component="code" data-lang="c|py">
   Tiny regex highlighter: comments, strings, preprocessor, numbers, keywords, types. */

(() => {
	const KEYWORDS = {
		c: 'typedef struct enum union return if else while for do static const sizeof void int char double float bool long short unsigned signed break continue case switch default true false NULL',
		py: 'def class return for in if else elif while import from as with not and or is None True False lambda yield del pass global self',
	};
	const PATTERN = {
		//  1 comment                         2 string                                 3 preprocessor        4 number                5 word
		c: /(\/\/.*$|\/\*[\s\S]*?\*\/)|("(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])')|(^[ \t]*#[ \t]*\w+)|(\b\d+(?:\.\d+)?f?\b)|([A-Za-z_]\w*)/gm,
		py: /(#.*$)|("(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*')|(^(?!))|(\b\d[\d_]*(?:\.\d+)?\b)|([A-Za-z_]\w*)/gm,
	};
	const keywords = Object.fromEntries(Object.entries(KEYWORDS).map(([k, v]) => [k, new Set(v.split(' '))]));
	const isType = w => /^(t_\w+|\w+_t|[A-Z][a-z]\w*)$/.test(w);

	function classify(lang, [, comment, string, pre, number, word]) {
		if (comment) return 'cm';
		if (string) return 'st';
		if (pre) return 'kw';
		if (number) return 'nu';
		if (keywords[lang].has(word)) return 'kw';
		return isType(word) ? 'ty' : '';
	}

	Talk.component('code', {
		mount(el) {
			const lang = el.dataset.lang;
			if (!PATTERN[lang]) return;
			const src = el.textContent;
			let out = '';
			let last = 0;
			for (const m of src.matchAll(PATTERN[lang])) {
				out += Talk.esc(src.slice(last, m.index));
				const cls = classify(lang, m);
				out += cls ? `<span class="${cls}">${Talk.esc(m[0])}</span>` : Talk.esc(m[0]);
				last = m.index + m[0].length;
			}
			el.innerHTML = out + Talk.esc(src.slice(last));
		},
	});
})();
