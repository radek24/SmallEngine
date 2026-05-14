# Small ECS Engine
Rozhodl jsem se vytvořit relativně jednoduchý herní engine, využívající architekturu ECS (entity component system). Protože
mi tenhto způsob handlování gameobjektů přišel zajímavý a chtěl jsem se o něm více naučit.

## Struktura
Celý projekt je rozdělený na tři části.
- **SmallEngine**
- **Sandbox** - Showcase funkcionality enginu, tato část se kompiluje do spustitelného .exe a jde na něm vidět funcionalita enginu a možnosti vlastního rozšíření
- **Tests** -  Testy, testují základní funkcionalitu enginu, netestují SDL, pouze vlastní funcionalitu

## Small Engine
Samotný engine, je možné ho použít jako engine, kompiluje se jako dll které jde liknout k vlastnímu hernímu projektu. Stará se o otevření okna,
vykreslování, input, managment levelů, entit, komponent a systémů a další věci.


#### Části enginu

- **Rendering** - Třídy zodpovědné za vykreslování, wrapery SDL a managers (font, textures) které fungují přes handles aby se nenačítaly duplicitní textury více krát. Většinou jsou scoped do levelu aby nezůstavaly textury z už načtených levelů
- **Math** - Vektory, barvy a základní kolize
- **Input** - EventHandler, stará se o jednoduhé odchycení eventů a jejich dispatch pro celou aplikaci
- **Levels** - Jednotlivé herní scény, mají v sobě všechny objekty potřebné pro hru. Jde mezi nimi přepínat díky `QueeLevelTransition`.
- **Log** - Log systém (spdlog)
- **Registry** - Ta zajímavá část. Kontejner pro entity. Stará se o views, runuje systémy atd
- **Entity** - Jen a pouze wrapper pro int nastavený tak aby nešel vytvořit ručně a muselo se to dělat přes registry. (má ID a generaci)
- **Systems** - Systémy operující na komponentech (mám jich celkem dost, render, UIRender, Debug, Mover, Lifetime, Particle atd)
- **Komponenty** - POD strukty
- **Prefab** - Objekt který má více nastavených komponentů na sobě, dělá se z něho entita
- **SignalManager** - Objekt který řídí obsrver -> subscriber logiku, která jde použít třeba při gameplay eventech. Subscribe("PlayerDie")

## Sandbox
Likuje dll SmallEnginu, ukazuje že můžeme jakkoliv rožšířit systémy, komponenty a využít existující třídy díky SE_DLL makru.
Je tam několik demo levelů, které ukazují handlování entit atd.
**V debugu jdou použít F1-4 na debug okna**

## Tests
Testy na některé funkcionality enginu

## Dependencies
Všechny dependencies jsem se snažil brát jako github moduly, příjde mi to tak více čisté a tím že všecho kompiluju já from source tak nad tím mám větší kontrolu.
- SDL3
- SDL_TTF
- SDL_IMAGE
- SDL_MIXER
- nlohmann::json
- spdlog
- Doctest
- FastNoiseLite


## Build systém
Cmake

## Co bych rád někdy dodělal / Jak to vylepšit
- Lepší serializace
- Vlastní asset manager schopný ukládat / načítat assety z disku
- Vylepšit Rendering aby mohl podporovat i jiné API (Vulkan, DX12 atd.)
- Pořádný physics systém