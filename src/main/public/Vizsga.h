/**
*   \file Vizsga.h
*   A Vizsga(t) leiro osztaly deklaracioja es tagfuggvenyeinek inline megvalositasa.
*   Ez az osztaly a VegzettMuvelet osztalybol szarmazik, es a vizsgak adatait tarolja.
*
*   Kiegesziti az ososztalyt egy sikeres logikai ertekkel, ami a vizsga sikeresseget jelzi.
*/

#ifndef VIZSGA_H
#define VIZSGA_H

#ifdef MEMTRACE
#include "Memtrace.h"
#endif

#include <iostream>

#include "VegzettMuvelet.h"

class Vizsga : public VegzettMuvelet {
    bool sikeres; ///< A vizsga sikeressege
public:
    /*-------------------------------------------
            Konstruktorok es destruktor
    -------------------------------------------*/
    /// Alapertelmezett konstruktor
    Vizsga() : VegzettMuvelet(), sikeres(false) {}

    /// Parameteres konstruktor
    /// @param m - muvelet megnevezese
    /// @param d - datum
    /// @param a - ar
    /// @param k - aktualis km ora allas
    /// @param s - sikeresseg
    Vizsga(const std::string& m, const Datum& d, int a, int k, bool s) : VegzettMuvelet(m, d, a, k), sikeres(s) {}

    /// Masolo konstruktor
    /// @param v - masolando Vizsga objektum
    Vizsga(const Vizsga& v) : VegzettMuvelet(v.getMuvelet(), v.getDatum(), v.getAr(), v.getAktKmOra()), sikeres(v.sikeres) {}

    /// Destruktor
    ~Vizsga() {}

    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator
    /// @param v - masolando Vizsga objektum
	/// @return - az aktualis objektum referenciaja
    Vizsga& operator=(const Vizsga& v) {
        if (this != &v) {
            setMuvelet(v.getMuvelet());
            setDatum(v.getDatum());
            setAr(v.getAr());
            setAktKmOra(v.getAktKmOra());
            sikeres = v.sikeres;
        }
        return *this;
    }

    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Sikeresseg lekerdezese
    /// @return - igaz, ha sikeres volt
    bool getSikeres() const { return sikeres; }

    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Sikeresseg beallitasa
    /// @param s - uj sikeressegi ertek
    void setSikeres(bool s) { sikeres = s; }

    /*-------------------------------------------
     Tiszta absztrakt fuggvenyek feluldefinialasa
    -------------------------------------------*/
    /// Masolo fuggveny (virtualis, tisztan absztrakt)
    /// @return - uj peldany
    VegzettMuvelet* clone() const override {
        return new Vizsga(*this);
    }

    /// Kiiro fuggveny feluldefinialasa
    /// @param os - kimeneti stream
    void kiir(std::ostream& os) const override {
        os << "\tVizsga: " << getMuvelet()
            << ", Datum: " << getDatum()
            << ", Ar: " << getAr()
            << " Ft, Sikeres: " << (sikeres ? "igen" : "nem")
            << ", Akt. km: " << getAktKmOra()
            << std::endl;
    }
};

#endif // VIZSGA_H