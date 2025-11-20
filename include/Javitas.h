/**
*   \file Javitas.h
*   A Javitas(t) leiro osztaly deklaracioja es tagfuggvenyeinek inline megvalositasa.
*   Ez az osztaly a VegzettMuvelet osztalybol szarmazik, es a javitasi muveletek adatait tarolja.
*/

#ifndef JAVITAS_H
#define JAVITAS_H

#ifdef MEMTRACE
#include "Memtrace.h"
#endif

#include <iostream>

#include "VegzettMuvelet.h"

class Javitas : public VegzettMuvelet {
public:
    /*-------------------------------------------
            Konstruktorok es destruktor
    -------------------------------------------*/
    /// Alapertelmezett konstruktor
    Javitas() : VegzettMuvelet() {}

    /// Parameteres konstruktor
    /// @param m - muvelet megnevezese
    /// @param d - datum
    /// @param a - ar
    /// @param k - aktualis km ora allas
    Javitas(const std::string& m, const Datum& d, int a, int k) : VegzettMuvelet(m, d, a, k) {}

    /// Masolo konstruktor
    /// @param j - masolando Javitas objektum
    Javitas(const Javitas& j) : VegzettMuvelet(j.getMuvelet(), j.getDatum(), j.getAr(), j.getAktKmOra()) {}

    /// Destruktor
    ~Javitas() {}

    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator
    /// @param j - masolando Javitas objektum
	/// @return - Az aktualis objektum referenciaja
    Javitas& operator=(const Javitas& j) {
        if (this != &j) {
            setMuvelet(j.getMuvelet());
            setDatum(j.getDatum());
            setAr(j.getAr());
            setAktKmOra(j.getAktKmOra());
        }
        return *this;
    }

    /*-------------------------------------------
    Tiszta absztrakt fuggvenyek feluldefinialasa
    -------------------------------------------*/
    /// Masolo fuggveny (virtualis, tisztan absztrakt)
    /// @return - uj peldany
    VegzettMuvelet* clone() const override {
        return new Javitas(*this);
    }

    /// Kiiro fuggveny feluldefinialasa
    /// @param os - kimeneti stream
    void kiir(std::ostream& os) const override {
        os << "\tJavitas: " << getMuvelet()
            << ", Datum: " << getDatum()
            << ", Ar: " << getAr() << " Ft"
            << ", Akt. km: " << getAktKmOra()
            << std::endl;
    }
};

#endif // JAVITAS_H