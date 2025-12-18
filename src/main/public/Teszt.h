/**
*   \file Teszt.cpp
*   Ez a fajl a program alapveto funkcioinak teszteleset vegzi.
*   A modul ellenorzi, hogy a rendszer fobb kepessegei helyesen mukodnek, es segit a hibak kiszureseben a fejlesztes soran.
*/

#ifndef TESZT_H
#define TESZT_H

/// Ellenorzi, hogy a megadott fajl letezik-e.
/// @param f - A vizsgalt fajl neve (eleresi utvonal is lehet).
/// @return - true, ha a fajl letezik, kulonben false.
bool tesztDBLetrehozas(SzervizNyilvantartoRendszer& aDB);

/// A megadott int erteket unsigned int-re konvertalja.
unsigned int fromIntToUnsigned(int x);

/// A megadott size_t erteket unsigned int-re konvertalja.
unsigned int fromSizetToUnsigned(size_t x);

/// A tesztelesi funkciok futtatasara szolgalo fuggveny.
void tesztek();

#endif // !TESZT_H