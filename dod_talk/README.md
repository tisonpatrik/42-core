# Mechanical sympathy – přednáška pro 42

Hodinová přednáška (~50 min + Q&A) pro old core (C) i new core (Python):
kód, který má hardware rád, no-bullshit přístup a jako bonus memory safety (arény).
Hlavní příklad je náš `cub3d` (flat `tiles[]`, ROM/RAM, jedna aréna, scratch).

## Prezentace

```bash
make              # otevře index.html v prohlížeči
```

Funguje přímo ze souboru, bez serveru a bez buildu.

| Klávesa | Akce |
| --- | --- |
| `→` / `←` | další / předchozí slide (myš ani mezerník nepřepínají) |
| `F` | fullscreen |

Export do PDF: tisk z Chromu (stránka 1600×900, animace se vypnou).

## Struktura

```
Makefile                make = otevři prezentaci, make demos = benchmarky
index.html              kostra: styly, skripty a pořadí sekcí
slides/
  1-motivace.js         část 1: motivace (slidy 1–6)
  2-areny.js            část 2: arény (slidy 7–19)
  3-data.js             část 3: jak organizovat data (slidy 20–27)
css/
  tokens.css            barvy, písma, velikosti, motion (jen tmavé téma)
  base.css              rám decku, typografie, layout (grid, stack), utility, chrome
  components.css        card, pill, code, bars, timeline, rewind, cost, agenda, …
js/
  core/talk.js          globální namespace Talk: registr komponent, data, formátování
  core/deck.js          navigace, škálování, animace při vstupu na slide
  components/*.js       komponenty (bars, timeline, cost, code, outline, raycast, pixeltitle, …)
data/
  casey.js              Caseyho zrychlení – jeden zdroj pro slidy 3, 4 a 5
  hardware.js           PassMark single-thread čipů 2000–2025
  aws.js                ceny EC2 c7i.xlarge
demos/                  benchmarky v C a Pythonu
```

Komponenta se připojí atributem `data-component="jméno"` a data si vezme z
`data-source="klíč"` (`Talk.data.klíč`). Prvky s `data-grow` (šířka v %) a
`data-draw` (SVG čára) se animují při každém vstupu na slide.

Skripty jsou klasické (ne ES moduly), aby deck běžel z `file://`, a proto jsou
slidy v JS souborech, ne v samostatných HTML (ty by šly načíst jen přes server).
Pořadí v `index.html`: core → data → components → slides → `deck.js` (ten deck vykreslí a spustí).
Nový slide = nová `<section class="slide">` v příslušném souboru ve `slides/`.

## Komponenty (katalog)

Každý text na slidu patří do některé z těchto komponent. Žádné volné odstavce.

| Komponenta | Kdy | Sloty / varianty |
| --- | --- | --- |
| kostra stránky | každý obsahový slide | `<header class="slide__head">` (`.kicker`, `h2`, volitelně `.lede`) · `<div class="slide__body">` (obsah, svisle na střed) · `<footer class="slide__foot">` (`.source`) |
| výrazový slide | titul, citát, push/swap | `.slide--statement` (vlastní kompozice na střed), CUB3D `.slide--full` |
| `.card` | jakýkoli box s textem | `__brand` `__label` `__num` `__value` `__title` (`--mono`) `__quote` (`--sm`) `__body` `__link`; `--compact`; barva `.tone-*`; rozložení `.cards.cards--2/--3` |
| `.snippet` | kód s popisem | `__head` (`__tag` `__file` `__note`), `.code`, `__stats` |
| `.code` | samotný kód | `data-component="code" data-lang="c|py"`, `--sm` `--xs` |
| `.bars` | sloupcový graf | data z markupu nebo `data-source` |
| `.rw` | matice čtení / zápisu | `__col` `__row` `__cell` `__tag--r/--w` |
| `.tally` + `.sites` | počty (velká čísla + tabulka) | `__label` `__num`; `__row` `__mod` `__n` |
| `.tree` + `.rule` | strom projektu + jedno pravidlo vedle | `__dir` `__note` `__brace`; `__main` `__code` `__sub` |
| `.abar` + `.flow` | stavy arény + „teď / lépe“ | `__head` `__step` `__track` `__seg` `__offset`; `__label` `__steps` |
| `.hier` | hierarchie paměti (jádro → L1 → … → RAM) | `__item` (`--core`, `--size`) `__size` `__like`; `__axis` |
| `.scale` | latence v lidském čase | `data-component="scale" data-source="latency"` |
| `.lines` + `.cacheline` | cache line AoS vs SoA | `__row` `__label` `__stat`; `data-pattern="aos|soa"` |
| `.mem` | ukazatele na rozházené bloky vs jeden blok | `__ptrs` `__scatter` (`--x`) `__block` (`--row`) |
| `.lanes` | SIMD registr | `__row` (`--reg`) `__label` `__cells` `__arrow` |
| `.quote`, `.cmd`, `.arcade`, `.manifesto`, `.rules`, `.memmap`, `.facts`, `.outline` | jednorázové velké prvky (citát, push/swap, CUB3D, titul, …) | viz `css/components.css` |
| `.source` | zdroj dole na slidu | odkazy přes `data-component="sources"` nebo `a.link` |

Barvy jen přes tónové třídy: `.tone-c` (modrá), `.tone-py` (žlutá), `.tone-hot` (červená), `.tone-ok` (zelená), `.tone-cold`.

## Dema

```bash
make demos        # vše
make particles    # AoS vs SoA v C a Pythonu (+ paměť)
make lifetimes    # malloc/free vs aréna v C, out= v NumPy
make shapes       # tvary: fn pointer/switch/tabulka v C + Python objekty/numpy
```

Python dema potřebují `numpy`.

Čísla benchmarků jsou naměřená na Ryzen 5 PRO 4650U, GCC 16 `-O2`, Python 3.14, NumPy 2.5.
Před přednáškou je přeměř na stroji, na kterém budeš prezentovat.

## Fonty

Nadpis CUB3D používá AmazDooM od Amazingmax ([dafont.com/amazdoom.font](https://www.dafont.com/amazdoom.font)),
licence „free for personal use“. Font je vložený v `css/fonts.css` jako data URI.

## Loga

`assets/logos/nasa.svg` (NASA insignia, Wikimedia Commons) a `assets/logos/tigerbeetle.png`
(avatar organizace TigerBeetle na GitHubu) slouží jen k označení citovaného zdroje na slidu
„Alokuj na startu, ne za běhu“.
