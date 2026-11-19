/* Latency ladder. L1–RAM: AMD Zen 2 (same architecture as the talk laptop),
   7-cpu.com cycles converted at 4 GHz (Ryzen 5 PRO 4650U boost):
   L1 4 cyc, L2 12 cyc, L3 38 cyc, RAM 38 cyc + 66 ns.
   SSD and network: "Latency numbers every programmer should know" (Dean, Norvig). */

Talk.data.latency = {
	humanScale: 1e9, // L1 (1 ns) becomes 1 second
	rows: [
		{ name: 'L1 cache', ns: 1 },
		{ name: 'L2 cache', ns: 3 },
		{ name: 'L3 cache', ns: 9.5 },
		{ name: 'RAM', ns: 75.5, hot: true },
		{ name: 'SSD, random 4 KB read', ns: 150000 },
		{ name: 'network California ↔ Netherlands', ns: 150000000 },
	],
	sources: [
		['7-cpu.com · Zen 2', 'https://www.7-cpu.com/cpu/Zen2.html'],
		['Latency numbers (Dean, Norvig)', 'https://gist.github.com/jboner/2841832'],
	],
};
