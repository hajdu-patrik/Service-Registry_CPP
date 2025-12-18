/**
*   \file Ugyfel.h
*   Az Ugyfel(et) leiro osztaly deklaracioja es tagfuggvenyeinek inline megvalositasa.
*
*   Az osztaly celja, hogy reprezentalja egy autoszerviz ugyfeleit,
*   beleertve a nevuket, elerhetosegeiket.
*
*   Az osztalyban szereplo osszes std::string tipusu adattag feltetelezi, hogy nem kell ekezetes betuket kezelnie.
*/

#ifndef UGYFEL_H
#define UGYFEL_H

#include <string>
#include <iostream>

class Ugyfel {
    std::string nev;            ///< Az ugyfel neve
    std::string telefonszam;    ///< Az ugyfel telefonszama
    std::string email;          ///< Az ugyfel e-mail cime
public:
    /*-------------------------------------------
            Konstruktorok es destruktor
    -------------------------------------------*/
    /// Alapertelmezett konstruktor
    Ugyfel();

    /// Parameteres konstruktor.
    /// @param n - Az ugyfel neve
    /// @param t - Az ugyfel telefonszama
    /// @param e - Az ugyfel e-mail cime
    Ugyfel(const std::string& n, const std::string& t, const std::string& e);

    /// Masolo konstruktor
    /// @param u - masolando Karbantartas objektum
    Ugyfel(const Ugyfel& u);

    /// Destruktor
    virtual ~Ugyfel() = default;



    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator
    /// @param u - masolando Vizsga objektum
    /// @return - Az aktualis objektum referenciaja
    Ugyfel& operator=(const Ugyfel& u);



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Az ugyfel nevenek lekerdezese.
    /// @return - Nev.
    const std::string& getNev() const;

    /// Az ugyfel telefonszamanak lekerdezese.
    /// @return - Telefonszam.
    const std::string& getTelefonszam() const;

    /// Az ugyfel e-mail cimenek lekerdezese.
    /// @return - E-mail cim.
    const std::string& getEmail() const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Az ugyfel nevenek beallitasa.
    /// @param n - Az uj nev.
    void setNev(const std::string& n);

    /// Az ugyfel telefonszamanak beallitasa.
    /// @param t - Az uj telefonszam.
    void setTel(const std::string& t);

    /// Az ugyfel e-mail cimenek beallitasa.
    /// @param e - Az uj e-mail cim.
    void setEmail(const std::string& e);



    /*-------------------------------------------
                Fontos tagmuveletek
    -------------------------------------------*/
    /// Masolo fuggveny (virtualis, tisztan absztrakt)
    /// @return - uj peldany
    virtual Ugyfel* clone() const;

    /// Kiirja az ugyfel adatait az adott ostream-re.
    /// @param os - A kimeneti adatfolyam.
    /// @return - Az ostream referenciaja (lancolashoz).
    void kiir(std::ostream& os) const;
};
/*-------------------------------------------
            Globalis operatorok
-------------------------------------------*/
/// Kimeneti operator Datum objektumhoz
/// @param os - kimeneti stream
/// @param u - kiirando Ugyfel objektum
/// @return - modositott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Ugyfel& u);

#endif // UGYFEL_H