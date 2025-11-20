/**
*   \file Karbantartas.h
*   A Karbantartas(t) leiro osztaly deklaracioja es tagfuggvenyeinek inline megvalositasa.
*   Ez az osztaly a VegzettMuvelet osztalybol szarmazik, es a karbantartasi muveletek adatait tarolja.
*/

#ifndef KARBANTARTAS_H
#define KARBANTARTAS_H

#ifdef MEMTRACE
#include "Memtrace.h"
#endif

#include <iostream>

#include "VegzettMuvelet.h"

class Karbantartas : public VegzettMuvelet {
public:
    /*-------------------------------------------
            Konstruktorok es destruktor
    -------------------------------------------*/
    /// Alapertelmezett konstruktor
    Karbantartas() : VegzettMuvelet() {}

    /// Parameteres konstruktor
    /// @param m - muvelet megnevezese
    /// @param d - datum
    /// @param a - ar
    /// @param k - aktualis km ora allas
    Karbantartas(const std::string& m, const Datum& d, int a, int k) : VegzettMuvelet(m, d, a, k) {}

    /// Masolo konstruktor
    /// @param k - masolando Karbantartas objektum
    Karbantartas(const Karbantartas& k) : VegzettMuvelet(k.getMuvelet(), k.getDatum(), k.getAr(), k.getAktKmOra()) {}

    /// Destruktor
    ~Karbantartas() {}

    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator
    /// @param k - masolando Karbantartas objektum
	/// @return - Az aktualis objektum referenciaja
    Karbantartas& operator=(const Karbantartas& k) {
        if (this != &k) {
            setMuvelet(k.getMuvelet());
            setDatum(k.getDatum());
            setAr(k.getAr());
            setAktKmOra(k.getAktKmOra());
        }
        return *this;
    }

    /*-------------------------------------------
     Tiszta absztrakt fuggvenyek feluldefinialasa
    -------------------------------------------*/
    /// Masolo fuggveny (virtualis, tisztan absztrakt)
    /// @return - uj peldany
    VegzettMuvelet* clone() const override {
        return new Karbantartas(*this);
    }

    /// Kiiro fuggveny feluldefinialasa
    /// @param os - kimeneti stream
    void kiir(std::ostream& os) const override {
        os << "\tKarbantartas: " << getMuvelet()
            << ", Datum: " << getDatum()
            << ", Ar: " << getAr() << " Ft"
            << ", Akt. km: " << getAktKmOra()
            << std::endl;
    }
};

#endif // KARBANTARTAS_H