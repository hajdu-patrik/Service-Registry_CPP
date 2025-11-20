/**
*	\file MainSegedFuggvenyek.h
*   Ez a fajl a program alapveto funkcioinak teszteleset vegzi.
*	A modul ellenorzi, hogy a rendszer fobb kepessegei helyesen mukodnek, es segit a hibak kiszureseben a fejlesztes soran.
*/

#ifndef MAINSEGEDFUGGVENYEK_H  
#define MAINSEGEDFUGGVENYEK_H  

#include <string>

#include "SzervizNyilvantartoRendszer.h"
#include "MuveletAllapot.h"

struct MainSegedFuggvenyei {
    /*-------------------------------------------
            Menu rendszerhez
    -------------------------------------------*/
    /// "Autoszerviz" felirat ASCII art kiirasa a konzolra, tabulatorral behuzva
    void kiirASCII1();

    /// "Arrivederci" felirat ASCII art kiirasa a konzolra, tabulatorral behuzva
    void kiirASCII2();

    /// A program altal biztositott funkciok hasznalatahoz szukseges menu opciok kiirasa
    void menuOpciok();



    /*-------------------------------------------
                  UI elmenyhez
    -------------------------------------------*/
    /// Megvarja, amig a felhasznalo lenyomja az Enter billentyut.
    /// altalaban hibauzenetek vagy informaciok megjelenitese utan hasznalatos, hogy a felhasznalonak legyen ideje elolvasni azokat.
    /// @param o - A kiirando uzenet.
    void varakozasEnterre(const std::string& o);

    /// Torli a konzol kepernyot
    void torolKonzol();

    /// Meghivja a torolKonzol-t majd kiirja a "Szerviz Nyilvantarto Rendszer" feliratot ASCII art formatumban
    void toroloMajdCim();

    /// Varakozik az Enter billentyu lenyomasara, majd torli a konzolt
    void varakozasTorol();



    /*-------------------------------------------
                   Seged
    -------------------------------------------*/
    /// Ellenorzi, hogy a megadott rendszam formatuma helyes-e.
    /// @param rendszam - A vizsgalt rendszam.
    /// @return - true, ha a formatum helytelen, false, ha helyes.
    bool helyesRendszamFormatum(const std::string& rendszam);

    /// Ellenorzi, hogy a megadott fajl letezik-e.
    /// @param f - A vizsgalt fajl neve (eleresi utvonal is lehet).
    /// @return - true, ha a fajl letezik, kulonben false.
    bool letezikAFajl(const std::string& f);

    /// Bekeri a felhasznalotol egy datum (ev, honap, nap) ertekeit.
    /// Addig ismetli a bekerest, amig helyes formatumu (ervenyes tartomanyban levo) datumot nem kap.
    /// @return - A bekert datum `Datum` tipusban.
    Datum bekerDatum();

    /// Beker egy sort a felhasznalotol, miutan kiir egy megadott uzenetet.
    /// @param t - A felhasznalonak megjelenitendo uzenet.
    /// @return - A felhasznalo altal beirt sor.
    std::string sorBeker(const std::string& t);

    /// Lefuttat egy adott muveletet, majd a visszateresi ertektol fuggoen kiirja a megfelelo uzenetet.
    /// @param muvelet - A vegrehajtando fuggveny.
    /// @param aDB - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @param sikerUzenet - Az uzenet, ha a muvelet sikeres.
    void muveletFuttato(MuveletAllapot(MainSegedFuggvenyei::* muvelet)(SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, const std::string& sikerUzenet);

    /// Lefuttatja a fajlkezeleshez szukseges muveletet, majd a visszateresi ertektol fuggoen kiirja a megfelelo uzenetet.
    /// @param muvelet - A vegrehajtando fuggveny, amely fajlmuveletet vegez.
    /// @param aDB - A szerviz nyilvantarto rendszer.
    /// @param tipus - Igaz (true) ha mentes, hamis (false) ha beolvasas.
    /// @param sikerUzenet - Az uzenet, ha a muvelet sikeres.
    // Valtoztasd a fuggveny deklaraciokat
    void fajlMuveletFuttato(MuveletAllapot(MainSegedFuggvenyei::* muvelet)(bool, SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, bool tipus, const std::string& sikerUzenet);



    /*-------------------------------------------
               1. menuponthoz
    -------------------------------------------*/
    /// Listazza az ugyfeleket vagy az autokat a megadott adatbazisbol.
    /// @param aDB - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot kiListazo(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               2. menuponthoz
    -------------------------------------------*/
    /// uj ugyfel vagy auto rogzitese.
    /// @param aDB - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot ugyfelAutoAdd(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               3. menuponthoz
    -------------------------------------------*/
    /// Meglevo ugyfel vagy auto frissitese.
    /// @param aDB - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot ugyfelAutoFrissit(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               4. menuponthoz
    -------------------------------------------*/
    /// A rendszerben levo ugyfel vagy auto torlesere szolgal.
    /// @param aDB - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot ugyfelAutoTorlo(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               5. menuponthoz
    -------------------------------------------*/
    /// Keres egy ugyfelet a megadott nev alapjan.
    /// @param aDB - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot ugyfelKereses(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               6. menuponthoz
    -------------------------------------------*/
    /// Keres egy autot a megadott rendszam alapjan.
    /// @param rendszer - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot autoKereses(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               7. menuponthoz
    -------------------------------------------*/
    /// uj szerviz muvelet rogzitese egy autohoz.
    /// @param rendszer - A szerviz nyilvantarto rendszer, amely tartalmazza az ugyfeleket es autokat.
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot ujSzervizMuvelet(SzervizNyilvantartoRendszer& aDB);



    /*-------------------------------------------
               8.-9. menuponthoz
    -------------------------------------------*/
    /// Fajlnev bekerese, formatumanak es letezesenek ellenorzese.
    /// Elfogadja az "exit" szot is, ami visszalepest jelent a fomenube.
    /// @param mentesE - A fuggveny celjat jelzo kapcsolo (mentes vagy betoltes)
    /// @param aDB - A szerviz adatbazis objektum referenciaja
    /// @return - MuveletAllapot ertek a muvelet eredmenye szerint.
    MuveletAllapot fajlHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // MAINSEGEDFUGGVENYEK_H
};