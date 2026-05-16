# Small ECS Engine
Rozhodl jsem se vytvořit 2D herní engine, využívající architekturu ECS (entity component system). Protože
mi tenhto způsob handlování gameobjektů přišel zajímavý a chtěl jsem se o něm více naučit. Hlavní prioritou tohle projektu pro mě bylo vytvořit čistý, pěkný kod se kterým půjde dobře pracovat.

## Instrukce k buildu
*Problémek: Jsem zvyklý se hrabat v sourcu knihoven se kterými dělám, takže jsem si natáhnul všechny dependencies jako git submoduly, kvůli toho doporučuju shallow clon, ale i tak to má kolem 800mb. Já dělám s Unrealem tak je mi to celkem jedno, ale jestli to bude muset klonovat cvičící tak se mu omlouvám :(*

Tady je [Github](https://github.com/radek24/SmallEngine) ze kterého jde projekt naklonovat a zkompilovat.

`git clone --depth 1 --recurse-submodules --shallow-submodules https://github.com/radek24/SmallEngine.git`

Projekt podporuje 2 konfigurace: DEBUG a RELEASE

### Podporované platformy
Windows a Mac

## Build konfigurace
- **Debug** - Má SE_DEBUG makro, debug informace, timery atd 
- **Release** - Má SE_RELEASE makro, optimalizace, žádné timery, logování.

## Struktura
Celý projekt je rozdělený na tři části.
- **SmallEngine** - Kompiluje se do dll, umožnuje uživateli enginu používat exposnuté funkce
- **Sandbox** - Showcase funkcionality enginu, tato část se kompiluje do spustitelného .exe a jde na něm vidět funcionalita enginu a možnosti vlastního rozšíření
- **Tests** -  Testy, testují základní funkcionalitu enginu, netestují SDL, pouze vlastní funcionalitu

## Small Engine
Samotný engine, kompiluje se jako dll které jde liknout k vlastnímu hernímu projektu. Stará se o otevření okna,
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
- **SettingManager** - Objekt řídící nastavení hry, umí se automaticky celý vykreslit a nastavuje se podle configu.

## Sandbox
Likuje dll SmallEnginu, ukazuje že můžeme jakkoliv rožšířit systémy, komponenty a využít existující třídy díky SE_DLL makru.
Je tam několik demo levelů, které ukazují handlování entit atd.
**V debugu jdou použít F1-4 na debug funkce**

V sandboxu je main menu, showcase nastavení a pár demo levelů. Nějaké stress testy, ukázky interakcí, ale hlavní showcase je klon hry asteroids, využívající ECS architekturu.


## Návrh enginu
Engine se snaží být co nejvíc uživatelsky přívětivý, všechny metody a objekty jsou alespoň trochu popsané. Práce s enginem by měla být co nejjednoduší, uživatel si vytvoří vlastní potomek App a poté už implementuje vlastní herní logiku, engine mu v tomhle co nejvíce pomáhá už existujícími systémy a předpřipravenou funkcionalitou (Rendering,UI rendering, Transformace, levely).

Základní kostru enginu jsem se snažil udělat objektově, máme třídu App, Window, Renderer, Level, atd. Poté máme ECS část, která je data-oriented - Entity je jen uint32 ID, Komponenty jsou čisté POD struktury a veškerá logika je v Systémech. Tohle oddělení mi přišlo elegantní, komponenty neví nic o sobě
navzájem a systémy si vezmou co potřebují přes View.

```cpp
// Uživatel si vytvoří vlastní Level a implementuje lifecycle metody
class MyLevel : public Level {
void OnEnter() override { /* spawn entit, načtení textur */ }
void OnUpdate(float DeltaTime) override { /* herní logika */ }
void OnRender(Renderer& R, float DeltaTime) override { /* vlastní rendering */ }
void OnExit() override { /* cleanup */ }
};
```

Entity se vytváří přes Registry, která je součástí každého levelu. Komponenty se přidávají přímo na entitu, systémy pak iterují přes entity které mají relevantní komponenty pomocí View:
```cpp
auto Player = CurrentRegistry.CreateEntity();
CurrentRegistry.AddComponent<TransformComponent>(Player);
CurrentRegistry.AddComponent<SpriteComponent>(Player);

// V systému:
auto View = Registry.MakeView<TransformComponent, SpriteComponent>();
View.Each([&](Entity E, TransformComponent& TC, SpriteComponent& SC) {
// ...
});
```
Systémy mají definovanou SystemPhase která říká kdy se spouštějí, takže je zaručené deterministické pořadí. Uživatel si může napsat vlastní systémy a přidat je do registry, nebo použít ty co jsou v enginu.

Pro komunikaci mezi systémy nebo gameplaykódem bez přímé závislosti slouží SignalManager. Funguje na observer principu - kód se subscribeuje na topic a pak kdokoliv může dispatchnout zprávu:
```
App::Get().SignalManager->Subscribe("PlayerDied", [](SignalPayload& P) {
// handle
});

App::Get().SignalManager->Dispatch("PlayerDied", MyPayload{});
```


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

## Zajímavé problémy
- Tím jak řeším ID entity (v id entity je zakodované číslo entity a generace kvůli invalidaci existujících IDs), nejsou tyto IDs sekvenčí, to mi ale vůbec nedošlo když jsem je použil jako index v poli které alokuju. Kvůli tohohle jsem při smazání a opětném přidání entit alokoval pole o velikosti x milionů. 
- Component Pool prošel asi 3x implementacemi než jsem se rozhodl že použiju pooled sparse set. První to bylo jen pole které indexovalo pomocí indexů entit, to by ale alokovalo obrovské pole pro component pooly s pouze jedním komponentem. (entita player má id 100000 a jediný vlastní playerComopnent. gl). Pak jsem implementoval sparse set bez poolingu což mělo podobný problém jako předchozí řešení, akrát byl komponenty cache packed
- Další super problém bylo přepínání levelů, pokud jakýkoliv gameplay kod změní level, okamžitě se ukončilo aktuální provádění kodu a přepnul se level. To hooodně leakovalo. Vyřešil jsem to tím že mám LevelQueue do které se dá level pokud chce být změně a to se udělá až na konci framu.
- Cpp spouští destruktory v opačném pořadí deklarace, na tohle jsem narazil když se mi signal manager zničil dříve než level.
- Stable sort v renderingu, můj render systém podporuje z-index, ale i když jsem implementoval tohle tak jsem zjistil že entity se stejným z-indexem problikávají, takže jsem je musel třídit i podle entity ID
## Co bych rád někdy dodělal / Jak to vylepšit
- Lepší serializace
- Vlastní asset manager schopný ukládat / načítat assety z disku
- Vylepšit Rendering aby mohl podporovat i jiné API (Vulkan, DX12 atd.)
- Pořádný physics systém
- Dependency injection pro managery