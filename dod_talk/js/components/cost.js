/* Yearly cloud bill for the same work, per Casey step.
   <div data-component="cost" data-source="aws">
   More slowdown = more servers = linearly bigger bill (EC2 bills per vCPU-hour). */

(() => {
	const usd = n => `$${Talk.fmt.int(n)}`;

	Talk.component('cost-lede', {
		mount(el) {
			const aws = Talk.source(el);
			const yearly = aws.hourly * aws.hoursPerYear;
			el.textContent = `A service whose clean code version needs ${aws.baseServers} `
				+ `${aws.instance} servers (${aws.vcpu} vCPU, ${aws.cpu}, $${Talk.fmt.dec(aws.hourly, 4)}/h, ${usd(yearly)} per year). `
				+ 'Same work, the code is just written differently.';
		},
	});

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
						<span class="cost__servers">${shownServers}</span>
						<span class="cost__price">${usd(cost)}</span>
						<span class="cost__saved">${step.factor > 1 ? usd(worst - cost) : ''}</span>
					</div>`;
			}).join('');

			const target = Talk.data.casey.step(aws.compareTo);
			const extra = worst - worst / target.factor;

			el.innerHTML = `
				<div class="cost">
					<div class="cost__row cost__row--head">
						<span>version</span><span class="cost__track"></span><span class="cost__servers">servers</span>
						<span class="cost__price">per year</span><span>you save</span>
					</div>
					${rows}
				</div>
				<div class="cards cards--3">
					<div class="card card--compact tone-hot"><b class="card__value">${usd(extra)}</b><p class="card__body">extra per year for clean code vs. the “${target.short}” version</p></div>
					<div class="card card--compact tone-hot"><b class="card__value">${Talk.fmt.factor(target.factor)}×</b><p class="card__body">more servers = a ${Talk.fmt.factor(target.factor)}× bigger bill, price scales linearly with vCPU</p></div>
					<div class="card card--compact tone-hot"><b class="card__value">${usd(extra * aws.horizonYears)}</b><p class="card__body">over ${aws.horizonYears} years of running one such service</p></div>
				</div>`;
		},
	});
})();
