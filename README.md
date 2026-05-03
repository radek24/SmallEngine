# Small ECS Engine
Rozhodl jsem se vytvořit relativně jednoduchý herní engine, využívající architekturu ECS (entity component system). Protože
mi tenhto způsob handlování gameobjektů přišel zajímavý a chtěl jsem se o něm více naučit.

## Struktura
Celý projekt je rozdělený na tři části.
- **SmallEngine**
- **Sandbox** - Showcase funkcionality enginu, tato část se kompiluje do spustitelného .exe a jde na něm vidět funcionalita enginu a možnosti vlastního rozšíření
- **Tests** -  Testy, testují základní funkcionalitu enginu, netestují SDL, pouze vlastní funcionalitu

### Small Engine
Samotný engine, je možné ho použít jako engine, kompiluje se jako dll které jde liknout k vlastnímu hernímu projektu. Stará se o otevření okna,
vykreslování, input, managment levelů, entit, komponent a systémů.

Implementuje vlastní math knihovnu pro jednodušší práíci s vektory, rotacemi a kolizemi.