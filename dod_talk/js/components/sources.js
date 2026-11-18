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
