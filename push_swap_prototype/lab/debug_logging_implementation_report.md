# Debug Logging Implementation Report

## Problém
Původní logger nelogoval všechny stavy proměnných po každém řádku. Bylo potřeba ručně volat `debug_log()` po každé operaci.

## Řešení
Implementoval jsem nový systém automatického logování, který:

1. **Automaticky loguje stav po každém řádku** pomocí `DEBUG_LINE()`
2. **Sleduje změny proměnných** pomocí `DEBUG_VAR()`
3. **Loguje před a po operacích** pomocí `DEBUG_BEFORE_OP()` a `DEBUG_AFTER_OP()`
4. **Zachytává kompletní stav** všech relevantních proměnných

## Nová makra

### `DEBUG_LINE(data, line_num)`
- Loguje kompletní stav všech proměnných na daném řádku
- Automaticky volá `debug_log_all_variables()`

### `DEBUG_VAR(data, var_name, var_value)`
- Loguje změnu konkrétní proměnné
- Obsahuje číslo řádku a název funkce
- Automaticky loguje i stav stacků

### `DEBUG_BEFORE_OP(data, op_name)` a `DEBUG_AFTER_OP(data, op_name)`
- Loguje stav před a po operaci
- Užitečné pro sledování změn

### `DEBUG_FUNC_ENTRY(data)` a `DEBUG_FUNC_EXIT(data)`
- Loguje vstup a výstup z funkcí
- Zachytává kompletní stav

## Příklad použití

```c
void example_function(t_ps *data) {
    DEBUG_FUNC_ENTRY(data);
    DEBUG_LINE(data, __LINE__);
    
    int counter = 0;
    DEBUG_VAR(data, "counter", "0");
    DEBUG_LINE(data, __LINE__);
    
    DEBUG_BEFORE_OP(data, "push_a");
    push_a(data);
    DEBUG_AFTER_OP(data, "push_a");
    DEBUG_LINE(data, __LINE__);
    
    counter++;
    DEBUG_VAR(data, "counter", "incremented");
    DEBUG_LINE(data, __LINE__);
    
    DEBUG_FUNC_EXIT(data);
}
```

## Co se loguje automaticky

### Stack stav:
- Velikost, top, bottom indexy
- Prvních 5 elementů každého stacku
- Kompletní obsah stacků (v DEBUG_DEBUG úrovni)

### Proměnné:
- Všechny změny proměnných s číslem řádku
- Kontext změny

### Operace:
- Stav před a po každé operaci
- Název operace a funkce

## Úrovně logování

- `DEBUG_ERROR` (0): Chyby
- `DEBUG_WARN` (1): Varování  
- `DEBUG_INFO` (2): Informace
- `DEBUG_DEBUG` (3): Debug informace
- `DEBUG_TRACE` (4): Detailní sledování (všechny řádky)

## Implementace v chunk_sort.c

Ukázal jsem kompletní implementaci v `chunk_sort.c`, kde:

1. **Každá funkce** má `DEBUG_FUNC_ENTRY` a `DEBUG_FUNC_EXIT`
2. **Každý řádek** má `DEBUG_LINE` pro sledování stavu
3. **Každá změna proměnné** má `DEBUG_VAR`
4. **Každá operace** má `DEBUG_BEFORE_OP` a `DEBUG_AFTER_OP`

## Výhody nového systému

1. **Automatické logování** - není potřeba ručně psát log volání
2. **Kompletní sledování** - vidíte stav po každém řádku
3. **Kontext informace** - víte, kde a kdy se co změnilo
4. **Snadné použití** - stačí přidat makra do kódu
5. **Výkon** - logování se vypne, když není potřeba

## Jak spustit

1. Logger se automaticky inicializuje v `main.c`
2. Logy se ukládají do `logs/` adresáře
3. Každý běh má vlastní soubor s timestampem
4. Log úroveň se nastavuje v `g_debug_config.log_level`

## Doporučení pro použití

1. **Začněte s `DEBUG_DEBUG` úrovní** pro základní sledování
2. **Použijte `DEBUG_TRACE`** pro detailní sledování každého řádku
3. **Přidejte `DEBUG_LINE`** po každém důležitém řádku
4. **Použijte `DEBUG_VAR`** pro sledování změn proměnných
5. **Obalte operace** do `DEBUG_BEFORE_OP` a `DEBUG_AFTER_OP`

Tímto způsobem budete mít kompletní přehled o tom, co se děje v každém kroku vašeho algoritmu!
