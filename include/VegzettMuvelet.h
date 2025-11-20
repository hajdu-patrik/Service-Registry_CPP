/**
*   \file VegzettMuvelet.h
*   Az VegzettMuvelet(et) leiro absztrakt osztaly deklaracioja es tagfuggvenyeinek inline megvalositasa.
*
*   Az osztalyban szereplo osszes std::string tipusu adattag feltetelezi, hogy nem kell ekezetes betuket kezelnie.
*/

#ifndef VEGZETTMUVELET_H  
#define VEGZETTMUVELET_H 

#include <string>

#include "Datum.h"

class VegzettMuvelet {
    std::string muvelet;    ///< A muvelet megnevezese  
    Datum idopont;          ///< A muvelet idopontja  
    int ar;                 ///< A muvelet ara  
    int akt_kmOra;          ///< Az aktualis kilometerora allas
public:
    /*-------------------------------------------
                  Konstruktorok
    -------------------------------------------*/
    /// Alapertelmezett konstruktor
    /// Letrehoz egy ures muveletet nullakkal inicializalt datummal es 0 arral.
    VegzettMuvelet() : muvelet(""), idopont(), ar(0), akt_kmOra(0) {}

    /// Parameteres konstruktor
    /// @param m - Muvelet neve
    /// @param d - Muvelet idopontja
    /// @param a - Muvelet ara
    VegzettMuvelet(const std::string& m, const Datum& d, int a, int k) : muvelet(m), idopont(d), ar(a), akt_kmOra(k) {}

    /// Masolo konstruktor
    /// @param vm - Masolando VegzettMuvelet objektum
    VegzettMuvelet(const VegzettMuvelet& vm) : muvelet(vm.muvelet), idopont(vm.idopont), ar(vm.ar), akt_kmOra(vm.akt_kmOra) {}



    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator
    /// @param vm - Masolando VegzettMuvelet objektum
    /// @return - Az aktualis objektum referencia
    VegzettMuvelet& operator=(const VegzettMuvelet& vm) {
        if (this != &vm) {
            muvelet = vm.muvelet;
            idopont = vm.idopont;
            ar = vm.ar;
            akt_kmOra = vm.akt_kmOra;
        }
        return *this;
    }



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Getter a muvelet nevehez
    /// @return - A muvelet neve (const referencia)
    const std::string& getMuvelet() const { return muvelet; }

    /// Getter az idoponthoz
    /// @return - A muvelet datuma (const referencia)
    const Datum& getDatum() const { return idopont; }

    /// Getter az arhoz
    /// @return - A muvelet ara
    int getAr() const { return ar; }

    /// Getter az aktualis kilometerora allasahoz
    /// @return - Az aktualis kilometerora allas
    int getAktKmOra() const { return akt_kmOra; }



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Setter az idoponthoz
    /// @param d - uj datum
    void setDatum(const Datum& d) { idopont = d; }

    /// Setter az arhoz
    /// @param a - uj ar
    void setAr(int a) { ar = a; }

    /// Setter a muvelet nevehez
    /// @param m - uj muvelet nev
    void setMuvelet(const std::string& m) { muvelet = m; }

    /// Setter az aktualis kilometerora allasahoz
    /// @param k - uj kilometerora allas
    void setAktKmOra(int k) { akt_kmOra = k; }



    /*-------------------------------------------
                Virtualis fuggvenyek
    -------------------------------------------*/
    /// Kiiro fuggveny (virtualis, tisztan absztrakt)
    /// @param os - A kimeneti stream, ahova a muvelet kiirasra kerul
    virtual void kiir(std::ostream& os) const = 0;

    /// Masolo fuggveny (virtualis, tisztan absztrakt)
    /// @return - Egy uj VegzettMuvelet pointer, amely a masolt objektumot reprezentalja
    virtual VegzettMuvelet* clone() const = 0;

    /// Virtualis destruktor
    virtual ~VegzettMuvelet() = default;
};

#endif // VEGZETTMUVELET_H