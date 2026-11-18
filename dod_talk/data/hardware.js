/* PassMark single-thread rating of specific chips, cpubenchmark.net, 11/2026.
   year = launch year. Reference (100 %) = Apple M5. */

Talk.data.hardware = {
	ref: { name: 'Apple M5', year: 2025, score: 5777 },
	series: [
		{
			name: 'Intel desktop, top model roku',
			tone: 'c',
			crossings: true,  // Casey's thresholds are located on this line
			points: [
				[2000, 228, 'Pentium 4 1,5 GHz'],
				[2001, 349, 'Pentium 4 2 GHz'],
				[2003, 528, 'Pentium 4 3 GHz'],
				[2006, 943, 'Core 2 Duo E6600'],
				[2008, 1236, 'Core 2 Duo E8400'],
				[2011, 1740, 'Core i7-2600K'],
				[2013, 2160, 'Core i7-4770K'],
				[2015, 2494, 'Core i7-6700K'],
				[2017, 2712, 'Core i7-8700K'],
				[2018, 2907, 'Core i9-9900K'],
				[2020, 3106, 'Core i9-10900K'],
				[2021, 4128, 'Core i9-12900K'],
				[2022, 4594, 'Core i9-13900K'],
				[2023, 4689, 'Core i9-14900K'],
				[2024, 5087, 'Core Ultra 9 285K'],
			],
		},
		{
			name: 'Apple iPhone (A-čipy)',
			tone: 'py',
			points: [
				[2018, 2007, 'A12 · iPhone XS'],
				[2019, 2363, 'A13 · iPhone 11'],
				[2020, 3379, 'A14 · iPhone 12'],
				[2021, 3562, 'A15 · iPhone 13'],
				[2022, 3962, 'A16 · iPhone 14 Pro'],
				[2023, 4501, 'A17 Pro · iPhone 15 Pro'],
				[2024, 4074, 'A18 Pro · iPhone 16 Pro'],
				[2025, 5140, 'A19 Pro · iPhone 17 Pro'],
			],
		},
	],
	/* when a threshold falls between two Pentium 4 clocks, name it plainly */
	chipOverride: { onepass: 'Pentium 4' },
	/* extra line under a threshold label, keyed by Casey step */
	notes: { table: 'můj první „seriózní“ PC' },
	/* single highlighted points, e.g. the machine the talk runs on */
	markers: [
		{ year: 2020, score: 2341, label: 'tenhle notebook', chip: 'Ryzen 5 PRO 4650U', dx: 18, dy: 28, anchor: 'start' },
	],
	sources: [
		['cpubenchmark.net/single-thread', 'https://www.cpubenchmark.net/single-thread'],
		['Pentium 4 3 GHz', 'https://www.cpubenchmark.net/cpu.php?cpu=Intel+Pentium+4+3.00GHz&id=1074'],
		['2 GHz', 'https://www.cpubenchmark.net/cpu.php?cpu=Intel+Pentium+4+2.00GHz&id=1064'],
		['1,5 GHz', 'https://www.cpubenchmark.net/cpu.php?cpu=Intel+Pentium+4+1.50GHz&id=1053'],
	],
};
