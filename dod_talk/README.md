# Mechanical sympathy – přednáška pro 42

Hodinová přednáška (~50 min + Q&A) pro old core (C) i new core (Python):
kód, který má hardware rád, no-bullshit přístup a jako bonus memory safety (arény).
Hlavní příklad je náš `cub3d` (flat `tiles[]`, ROM/RAM, jedna aréna, scratch).

## Prezentace

Otevři `index.html` v prohlížeči. Funguje přímo ze souboru, bez serveru.

| Klávesa | Akce |
| --- | --- |
| `→` `Space` / `←` | další / předchozí slide |
| `T` | světlé / tmavé téma (na projektor spíš světlé) |
| `F` | fullscreen |

Export do PDF: tisk z Chromu (stránka 1600×900, animace se vypnou).

## Struktura

```
index.html              kostra: styly, skripty a pořadí sekcí
slides/
  0-intro.js … 4-end.js  obsah slidů po sekcích (HTML v Talk.slides`…`)
css/
  tokens.css            barvy, písma, velikosti, motion – světlé i tmavé téma
  base.css              rám decku, typografie, layout (grid, stack), utility, chrome
  components.css        card, pill, code, bars, timeline, rewind, cost, agenda, …
js/
  core/talk.js          globální namespace Talk: registr komponent, data, formátování
  core/deck.js          navigace, škálování, téma, animace při vstupu na slide
  components/*.js       komponenty vykreslované z dat (bars, timeline, cost, code, …)
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

## Dema

```bash
cd demos
make run          # vše
make particles    # AoS vs SoA v C a Pythonu (+ paměť)
make lifetimes    # malloc/free vs aréna v C, out= v NumPy
make shapes       # tvary: fn pointer/switch/tabulka v C + Python objekty/numpy
```

Python dema potřebují `numpy`.

Čísla benchmarků jsou naměřená na Ryzen 5 PRO 4650U, GCC 16 `-O2`, Python 3.14, NumPy 2.5.
Před přednáškou je přeměř na stroji, na kterém budeš prezentovat.
