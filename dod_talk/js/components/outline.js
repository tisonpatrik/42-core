/* Working outline: lists every slide in the deck with its number and title.
   <ol class="outline" data-component="outline">
   Title = data-title on the section, else its h1/h2/statement, else the kicker.
   A slide with data-section starts a new part; slides marked data-draft are dimmed. */

Talk.component('outline', {
	mount(el) {
		/* <br> counts as a space, so "Mechanical<br>sympathy" stays two words */
		const text = node => {
			if (!node) return '';
			const copy = node.cloneNode(true);
			copy.querySelectorAll('br').forEach(br => br.replaceWith(' '));
			return copy.textContent.replace(/\s+/g, ' ').trim();
		};
		const title = slide =>
			slide.dataset.title ||
			text(slide.querySelector('h1, h2, .statement')) ||
			text(slide.querySelector('.kicker'));

		el.innerHTML = [...document.querySelectorAll('.slide')].map((slide, i) => {
			const draft = slide.hasAttribute('data-draft');
			const section = slide.dataset.section
				? `<li class="outline__section">${Talk.esc(slide.dataset.section)}</li>`
				: '';
			return `${section}<li class="outline__item${draft ? ' outline__item--draft' : ''}">
				<span class="outline__num">${i + 1}</span>
				<span class="outline__title">${Talk.esc(title(slide))}</span>
			</li>`;
		}).join('');
	},
});
