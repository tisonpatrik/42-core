/* Yearly cloud bill for the same work, per Casey step.
   <div data-component="cost" data-source="aws">
   More slowdown = more servers = linearly bigger bill (EC2 bills per vCPU-hour). */

(() => {
	const usd = n => `${Talk.fmt.int(n)} $`;

	Talk.component('cost', {
		mount(el) {
			const aws = Talk.source(el);
			const steps = Talk.data.casey.steps;
			const yearly = aws.hourly * aws.hoursPerYear;
			const worst = aws.baseServers * yearly;

			const rows = steps.map(step => {
				const servers = aws.baseServers / step.factor;
				const cost = servers * yearly;
				const tone = step.factor >= 10 ? 'c' : 'hot';
				const shownServers = servers >= 10 ? Talk.fmt.int(servers) : Talk.fmt.dec(servers, 1);
				return `
					<div class="cost__row">
						<span class="cost__name">${step.label}</span>
						<span class="cost__track"><i class="cost__fill tone-${tone}" data-grow="${((cost / worst) * 100).toFixed(2)}"></i></span>
						<span class="cost__servers">${shownServers} ×</span>
						<span class="cost__price">${usd(cost)}</span>
						<span class="cost__saved">${step.factor > 1 ? usd(worst - cost) : ''}</span>
					</div>`;
			}).join('');

			const target = Talk.data.casey.step(aws.compareTo);
			const extra = worst - worst / target.factor;

			el.innerHTML = `
				<p class="small muted">Služba, které při clean code verzi stačí ${aws.baseServers} serverů
					${aws.instance} (${aws.vcpu} vCPU, ${aws.cpu}, ${Talk.fmt.dec(aws.hourly, 4)} $/h, ${usd(yearly)} za rok).
					Stejná práce, jen jinak napsaný kód.</p>
				<div class="cost">
					<div class="cost__row cost__row--head">
						<span>verze</span><span class="cost__track"></span><span class="cost__servers">serverů</span>
						<span class="cost__price">za rok</span><span>ušetříš</span>
					</div>
					${rows}
				</div>
				<div class="cost__summary">
					<div class="card"><p><b class="card__value">${usd(extra)}</b><span>ročně navíc za clean code proti verzi ${target.short}</span></p></div>
					<div class="card"><p><b class="card__value">${Talk.fmt.factor(target.factor)}×</b><span>víc serverů = ${Talk.fmt.factor(target.factor)}× větší účet, cena roste lineárně s vCPU</span></p></div>
					<div class="card"><p><b class="card__value">${usd(extra * aws.horizonYears)}</b><span>za ${aws.horizonYears} let provozu jedné takové služby</span></p></div>
				</div>`;
		},
	});
})();
