/* ==========================================================================
   Deck: navigation, scaling, entry animations.
   Loaded last; renders the slides and boots once everything is registered.

   Keys: → next · ← prev · Home / End · F fullscreen.
   Mouse clicks do not navigate.
   ========================================================================== */

(() => {
	const root = document.documentElement;
	Talk.render(document.querySelector('.deck'));
	const slides = [...document.querySelectorAll('.slide')];
	const progress = document.querySelector('.progress__bar');
	const counter = document.querySelector('.counter');
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

	function toggleFullscreen() {
		if (document.fullscreenElement) document.exitFullscreen();
		else if (root.requestFullscreen) root.requestFullscreen();
	}

	const NEXT = ['ArrowRight'];
	const PREV = ['ArrowLeft'];

	addEventListener('keydown', e => {
		if (e.metaKey || e.ctrlKey || e.altKey) return;
		const k = e.key;
		if (NEXT.includes(k)) { e.preventDefault(); go(current + 1); }
		else if (PREV.includes(k)) { e.preventDefault(); go(current - 1); }
		else if (k === 'Home') go(0);
		else if (k === 'End') go(slides.length - 1);
		else if (k === 'f' || k === 'F') toggleFullscreen();
	});

	addEventListener('resize', fit);

	/* ---------- boot ---------- */

	Talk.mountAll();
	fit();
	go((parseInt(location.hash.slice(1), 10) || 1) - 1);
})();
