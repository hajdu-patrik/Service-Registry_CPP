/**
*   \file Auto.h
*   Az auto adatait leiro osztaly.
*
*   Az osztaly celja, hogy reprezentalja egy auto adatait, beleertve a
*   rendszam, marka, tipus, kilometerora allasa, uzembe helyezes datuma,
*   valamint a hozza tartozo szervizmuveletek listajat.
*   Az osztaly lehetoseget biztosit az adatok kezelesere, modositasara,
*   valamint a szerviztortenet nyilvantartasara.
*
*   Az osztalyban szereplo osszes std::string tipusu adattag feltetelezi, hogy nem kell ekezetes betuket kezelnie.
*/

#ifndef AUTO_H
#define AUTO_H

#include <string>

#include "Datum.h"
#include "Ugyfel.h"
#include "Vector.hpp"
#include "VegzettMuvelet.h"

class Auto {
    std::string rendszam;                               ///< Az auto rendszama  
    std::string marka;                                  ///< Az auto markaja  
    std::string tipus;                                  ///< Az auto tipusa  
    int kmOra;                                          ///< Kilometerora allasa  
    Datum uzembeHelyezes;                               ///< uzembe helyezes datuma  
    Vector<VegzettMuvelet*> vegzettSzervizMuveletek;    ///< Elvegzett szervizmuveletek  
    Ugyfel* tulajdonos;                                 ///< Az auto tulajdonosa  
public:
    /*-------------------------------------------
            Konstruktorok es destruktor
    -------------------------------------------*/
    /// Alapertelmezett konstruktor.  
    Auto();

    /// Parameteres konstruktor.  
    /// @param r - Az auto rendszama  
    /// @param m - Az auto markaja  
    /// @param t - Az auto tipusa  
    /// @param k - A kilometerora allasa  
    Auto(const std::string& r, const std::string& m, const std::string& t, int k);

    /// Parameteres konstruktor.  
    /// @param r - Az auto rendszama  
    /// @param m - Az auto markaja  
    /// @param t - Az auto tipusa  
    /// @param k - A kilometerora allasa  
    /// @param d - Az uzembe helyezes datuma  
    /// @param v - Az autohoz tartozo szervizmuveletek listaja  
    /// @param u - Az auto tulajdonosa  
    Auto(const std::string& r, const std::string& m, const std::string& t, int k, const Datum& d, const Vector<VegzettMuvelet*>& v, Ugyfel* u);

    /// Masolo konstruktor.  
    /// @param a - Masolando Auto objektum  
    Auto(const Auto& a);

    /// Destruktor  
    virtual ~Auto();



    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator.
    /// @param a - masolando Auto objektum
    /// @return - Az aktualis objektum referenciaja
    Auto& operator=(const Auto& a);

    /// Egyenloseg operator tulterhelese az Auto osztalyhoz.
    /// @param a - Az osszehasonlitando Auto objektum.
    /// @return - true, ha az objektumok megegyeznek, kulonben false.
    bool operator==(const Auto& a) const;



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Visszaadja az auto rendszamat.
    /// @return - Rendszam.
    const std::string& getRendszam() const;

    /// Visszaadja az auto markajat.
    /// @return - Marka.
    const std::string& getMarka() const;

    /// Visszaadja az auto tipusat.
    /// @return - Tipus.
    const std::string& getTipus() const;

    /// Visszaadja a kilometerora aktualis erteket.
    /// @return - Km ora erteke.
    int getKmOra() const;

    /// Visszaadja az uzembe helyezes datumat.
    /// @return - Datum .
    const Datum& getUzembeHelyezes() const;

    /// Visszaadja az autohoz tartozo szervizmuveletek listajat.
    /// @return - Szervizmuveletek vektora.
    Vector<VegzettMuvelet*>& getSzervizMuveletek();

    /// Visszaadja az autohoz tartozo szervizmuveletek listajat (const valtozat).
    /// @return - Szervizmuveletek vektora.
    const Vector<VegzettMuvelet*>& getSzervizMuveletek() const;

    // Visszaadja az auto tulajdonosat.
    /// @return - Az auto tulajdonosa.
    Ugyfel* getTulajdonos();

    // Visszaadja az auto tulajdonosat (const valtozat).
    /// @return - Az auto tulajdonosa.
    const Ugyfel* getTulajdonos() const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Beallitja az auto rendszamat.
    /// @param r - Az uj rendszam.
    void setRendszam(const std::string& r);

    /// Beallitja a kilometerora erteket.
    /// @param k - Az uj km ora ertek.
    void setKmOra(int k);

    /// Beallitja a tulajdonost.
    /// @param u - Az uj tulajdonos.
    void setTulajdonos(Ugyfel* u);



    /*-------------------------------------------
                Fontos tagmuveletek
    -------------------------------------------*/
    /// Masolo fuggveny (virtualis, tisztan absztrakt)
    /// @return - uj peldany
    virtual Auto* clone() const;

    /// Hozzaad egy szervizmuveletet az auto szervizlistajahoz.
    /// @param m - A hozzaadando szervizmuvelet pointere
    void addVegzettSzerviz(VegzettMuvelet* m);

    /// Torli a megadott indexu szervizmuveletet a listabol.
    /// @param idx - A torlendo muvelet pozicioja
    void torolVegzettSzerviz(size_t idx);

    /// Kiirja az auto adatait es szervizmuveleteit az adott ostream-re.
    /// @param os - A kimeneti adatfolyam
    /// @return - Az ostream referenciaja (lancolashoz)
    void kiir(std::ostream& os) const;
};
/*-------------------------------------------
            Globalis operatorok
-------------------------------------------*/
/// Kimeneti operator Datum objektumhoz
/// @param os - kimeneti stream
/// @param a - kiirando Auto objektum
/// @return - modositott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Auto& a);

#endif // AUTO_H