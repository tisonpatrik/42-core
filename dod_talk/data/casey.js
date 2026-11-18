/* Casey Muratori, "Clean" Code, Horrible Performance (2023).
   Speed-ups vs. the clean (polymorphic) version, "corner area" variant,
   read off the video at 19:35. Used by slides 3, 4 and 5. */

Talk.data.casey = {
	video: 'https://www.youtube.com/watch?v=tD5NrevFtbU',
	at: '19:35',
	steps: [
		{ key: 'clean',   label: 'clean code',   short: 'clean',     factor: 1.0,  tone: 'cold' },
		{ key: 'switch',  label: '① switch',     short: 'switch',    factor: 1.8,  tone: 'c' },
		{ key: 'table',   label: '② tabulka',    short: 'tabulka',   factor: 10.3, tone: 'c' },
		{ key: 'onepass', label: '③④ 1 průchod', short: '1 průchod', factor: 14.6, tone: 'c' },
		{ key: 'avx',     label: '+ AVX',        short: 'AVX',       factor: 23.7, tone: 'hot' },
	],
};

Talk.data.casey.step = key => Talk.data.casey.steps.find(s => s.key === key);
