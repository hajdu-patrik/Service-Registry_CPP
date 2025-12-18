/**
*   \file Applikacio.h
*   Az Applikaciot leiro osztaly deklaracioja.
*/

#ifndef APPLIKACIO_H
#define APPLIKACIO_H

struct Applikacio {
	/// Futtatja a programot, beleertve a menut es a felhasznaloi interakciot
	/// @return - true, ha a program sikeresen befejezodott, kulonben false.
    bool applikacio();
};

#endif // APPLIKACIO_H