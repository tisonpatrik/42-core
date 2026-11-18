/* ==========================================================================
   Deck: navigation, scaling, theme, entry animations.
   Loaded last; renders the slides and boots once everything is registered.

   Keys: → / space / enter next · ← / backspace prev · Home / End
         T theme · F fullscreen. Click right 2/3 = next, left 1/3 = prev.
   ========================================================================== */

(() => {
	const root = document.documentElement;
	Talk.render(document.querySelector('.deck'));
	const slides = [...document.querySelectorAll('.slide')];
	const progress = document.querySelector('.progress__bar');
	const counter = document.querySelector('.counter');
	const THEME_KEY = 'dod-theme';
	let current = 0;

	/* ---------- entry animations ---------- */

	/* Restart a CSS transition: jump to `from` without animating, then go to `to`. */
	function replay(el, apply, from, to) {
		const saved = el.style.transition;
		el.style.transition = 'none';
		apply(el, from);
		el.getBoundingClientRect(); // flush
		el.style.transition = saved;
		requestAnimationFrame(() => apply(el, to));
	}

	const setWidth = (el, v) => { el.style.width = v; };
	const setOffset = (el, v) => { el.style.strokeDashoffset = v; };

	function animate(slide) {
		slide.querySelectorAll('[data-grow]').forEach(el =>
			replay(el, setWidth, '0', `${el.dataset.grow}%`));
		slide.querySelectorAll('[data-draw]').forEach(el => {
			const len = el.getTotalLength();
			el.style.strokeDasharray = len;
			replay(el, setOffset, len, 0);
		});
	}

	/* print / PDF: show every animated element in its final state */
	addEventListener('beforeprint', () => {
		document.querySelectorAll('[data-grow]').forEach(el => setWidth(el, `${el.dataset.grow}%`));
		document.querySelectorAll('[data-draw]').forEach(el => setOffset(el, 0));
	});

	/* ---------- navigation ---------- */

	function fit() {
		const scale = Math.min(innerWidth / 1600, innerHeight / 900);
		root.style.setProperty('--scale', scale);
	}

	function go(n) {
		current = Math.max(0, Math.min(slides.length - 1, n));
		slides.forEach((s, i) => s.classList.toggle('is-active', i === current));
		const slide = slides[current];

		progress.style.width = `${((current + 1) / slides.length) * 100}%`;
		counter.textContent = `${current + 1} / ${slides.length}`;
		history.replaceState(null, '', `#${current + 1}`);

		Talk.enter(slide);
		animate(slide);
	}

	function toggleTheme() {
		root.dataset.theme = root.dataset.theme === 'light' ? 'dark' : 'light';
		try { localStorage.setItem(THEME_KEY, root.dataset.theme); } catch (_) { /* storage blocked */ }
	}

	function toggleFullscreen() {
		if (document.fullscreenElement) document.exitFullscreen();
		else if (root.requestFullscreen) root.requestFullscreen();
	}

	const NEXT = ['ArrowRight', 'PageDown', ' ', 'Enter'];
	const PREV = ['ArrowLeft', 'PageUp', 'Backspace'];

	addEventListener('keydown', e => {
		if (e.metaKey || e.ctrlKey || e.altKey) return;
		const k = e.key;
		if (NEXT.includes(k)) { e.preventDefault(); go(current + 1); }
		else if (PREV.includes(k)) { e.preventDefault(); go(current - 1); }
		else if (k === 'Home') go(0);
		else if (k === 'End') go(slides.length - 1);
		else if (k === 't' || k === 'T') toggleTheme();
		else if (k === 'f' || k === 'F') toggleFullscreen();
	});

	addEventListener('click', e => {
		if (e.target.closest('a')) return;
		go(current + (e.clientX > innerWidth / 3 ? 1 : -1));
	});

	addEventListener('resize', fit);

	/* ---------- boot ---------- */

	try {
		const saved = localStorage.getItem(THEME_KEY);
		if (saved) root.dataset.theme = saved;
	} catch (_) { /* storage blocked */ }

	Talk.mountAll();
	fit();
	go((parseInt(location.hash.slice(1), 10) || 1) - 1);
})();
