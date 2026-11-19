# Mechanical sympathy – a talk for 42

A one-hour talk (~50 min + Q&A) for both old core (C) and new core (Python):
code the hardware likes, a no-bullshit approach and, as a bonus, memory safety (arenas).
The main example is our `cub3d` (flat `tiles[]`, ROM/RAM, one arena, scratch).

## Slides

```bash
make              # opens index.html in the browser
```

Runs straight from the file, no server and no build step.

| Key | Action |
| --- | --- |
| `→` / `←` | next / previous slide (mouse and space bar do nothing) |
| `F` | fullscreen |

PDF export: print from Chrome (1600×900 page, animations are switched off).

## Structure

```
Makefile                make = open the slides, make demos = benchmarks
index.html              skeleton: styles, scripts and section order
slides/
  1-motivation.js       part 1: motivation (slides 1–5)
  2-arenas.js           part 2: arenas (slides 6–18)
  3-data.js             part 3: organizing data (slides 19–26) + Beyond the core (27–30) + Tools (31) + Trade-off (32–33)
css/
  tokens.css            colors, fonts, sizes, motion (dark theme only)
  base.css              deck frame, typography, layout (grid, stack), utilities, chrome
  components.css        card, pill, code, bars, timeline, rewind, cost, …
js/
  core/talk.js          global Talk namespace: component registry, data, number formatting, typography
  core/deck.js          navigation, scaling, animations on slide enter
  components/*.js       components (bars, timeline, cost, code, raycast, pixeltitle, cores, …)
data/
  casey.js              Casey’s speed-ups – one source for slides 2, 3 and 4
  hardware.js           PassMark single-thread scores of chips 2000–2025
  aws.js                EC2 c7i.xlarge prices
  latency.js            latency ladder (Zen 2 + Dean/Norvig)
demos/                  benchmarks in C and Python
```

A component is attached with `data-component="name"` and takes its data from
`data-source="key"` (`Talk.data.key`). Elements with `data-grow` (width in %) and
`data-draw` (SVG line) animate every time their slide is entered.

The scripts are classic scripts (not ES modules) so the deck runs from `file://`, which is
why slides live in JS files rather than separate HTML files (those would need a server).
Order in `index.html`: core → data → components → slides → `deck.js` (renders and starts the deck).
A new slide = a new `<section class="slide">` in the matching file under `slides/`.

## Components (catalog)

Every piece of text on a slide belongs to one of these components. No loose paragraphs.

| Component | When | Slots / variants |
| --- | --- | --- |
| page skeleton | every content slide | `<header class="slide__head">` (`.kicker`, `h2`, optional `.lede`) · `<div class="slide__body">` (content, vertically centered) · `<footer class="slide__foot">` (`.source`) |
| statement slide | title, quotes, push/swap | `.slide--statement` (own centered composition), CUB3D and Beyond the core `.slide--full` |
| `.card` | any box with text | `__brand` `__label` `__num` `__value` `__title` (`--mono`) `__quote` (`--sm`) `__body` `__link`; `--compact`; color `.tone-*`; layout `.cards.cards--2/--3` |
| `.snippet` | code with a caption | `__head` (`__tag` `__file` `__note`), `.code`, `__stats` or `__mem` (memory strip: `is-read`, `__more`) |
| `.code` | code on its own | `data-component="code" data-lang="c|py"`, `--sm` `--xs` |
| `.bars` | bar chart | data from markup or `data-source`; `data-max` = shared scale for charts side by side |
| `.rw` | read/write matrix, ROM/RAM × hot/cold | `__col` `__row` `__cell` `__tag--r/--w` `__text`; `--2` = two columns |
| `.tally` + `.sites` | counts (big numbers + table) | `__label` `__num`; `__row` `__mod` `__n` |
| `.tree` + `.rule` | project tree + one rule next to it | `__dir` `__note` `__brace`; `__main` `__code` `__sub` |
| `.abar` + `.flow` | arena states + “now / better” | `__head` `__step` `__track` `__seg` `__offset`; `__label` `__steps` |
| `.beyond` + `.cores` | the “Beyond the core” title over a live die | `slide--full slide--clean`, `__title`; canvas `data-component="cores"` |
| `.lanes` | no SIMD vs SIMD | `__row` (+ tone) `__label` `__cells--apart` / `__cells--reg` `__stat` |
| `.hier` | memory hierarchy (core → L1 → … → RAM) | `__item` (`--core`, `--size`) `__size` `__like`; `__axis` |
| `.scale` | latency in human time | `data-component="scale" data-source="latency"` |
| `.lines` + `.cacheline` | cache lines, AoS vs SoA | `__row` `__label` `__stat`; `data-pattern="aos|soa"` or `data-fields` + `data-read` |
| `.quote`, `.cmd`, `.arcade`, `.manifesto`, `.rules`, `.memmap`, `.facts` | one-off big elements (quotes, push/swap, CUB3D, title, …) | see `css/components.css` |
| `.source` | source line at the bottom of a slide | links via `data-component="sources"` or `a.link` |

Colors only through tone classes: `.tone-c` (blue), `.tone-py` (yellow), `.tone-hot` (red), `.tone-ok` (green), `.tone-cold`.

## Demos

```bash
make demos        # everything
make particles    # AoS vs SoA in C and Python (+ memory)
make hotcold      # one fat struct vs a hot/cold split in C
make beyond       # SIMD (none, SSE, AVX2) and 1–6 threads, data in cache vs in RAM
make division     # division vs multiplying by the reciprocal
make lifetimes    # malloc/free vs an arena in C, out= in NumPy
make shapes       # shapes: fn pointer/switch/table in C + Python objects/NumPy
```

The Python demos need `numpy`.

Benchmark numbers were measured on a Ryzen 5 PRO 4650U, GCC 16 `-O2`, Python 3.14, NumPy 2.5.
Re-run them on the machine you present on before the talk.

## Fonts

The CUB3D title uses AmazDooM by Amazingmax ([dafont.com/amazdoom.font](https://www.dafont.com/amazdoom.font)),
licensed “free for personal use”. The font is embedded in `css/fonts.css` as a data URI.

## Logos

`assets/logos/nasa.svg` (NASA insignia, Wikimedia Commons) and `assets/logos/tigerbeetle.png`
(the TigerBeetle organization avatar on GitHub) are used only to identify the quoted source on the
“Allocate at startup, not at runtime” slide.
