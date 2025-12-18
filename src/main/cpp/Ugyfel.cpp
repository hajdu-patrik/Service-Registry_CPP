/**
*   \file Ugyfel.cpp
*   Az ugyfel osztaly tagfuggvenyeinek megvalositasa.
*/

#ifdef MEMTRACE
#include "Memtrace.h"
#endif
#include "Ugyfel.h"

/*-------------------------------------------
        Konstruktorok es destruktor
-------------------------------------------*/
/// Alapertelmezett konstruktor
Ugyfel::Ugyfel() : nev(""), telefonszam(""), email("") {}

/// Parameteres konstruktor.
/// @param n - Az ugyfel neve
/// @param t - Az ugyfel telefonszama
/// @param e - Az ugyfel e-mail cime
Ugyfel::Ugyfel(const std::string& n, const std::string& t, const std::string& e) : nev(n), telefonszam(t), email(e) {}

/// Masolo konstruktor
/// @param u - masolando Karbantartas objektum
Ugyfel::Ugyfel(const Ugyfel& u) : nev(u.nev), telefonszam(u.telefonszam), email(u.email) {}



/*-------------------------------------------
                Operatorok
-------------------------------------------*/
/// ertekado operator
/// @param u - masolando Vizsga objektum
/// @return - Az aktualis objektum referenciaja
Ugyfel& Ugyfel::operator=(const Ugyfel& u) {
    if (this != &u) {
        nev = u.nev;
        telefonszam = u.telefonszam;
        email = u.email;
    }
    return *this;
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// Az ugyfel nevenek lekerdezese.
/// @return - Nev.
const std::string& Ugyfel::getNev() const { return nev; }

/// Az ugyfel telefonszamanak lekerdezese.
/// @return - Telefonszam.
const std::string& Ugyfel::getTelefonszam() const { return telefonszam; }

/// Az ugyfel e-mail cimenek lekerdezese.
/// @return - E-mail cim.
const std::string& Ugyfel::getEmail() const { return email; }



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Az ugyfel nevenek beallitasa.
/// @param n - Az uj nev.
void Ugyfel::setNev(const std::string& n) { nev = n; }

/// Az ugyfel telefonszamanak beallitasa.
/// @param t - Az uj telefonszam.
void Ugyfel::setTel(const std::string& t) { telefonszam = t; }

/// Az ugyfel e-mail cimenek beallitasa.
/// @param e - Az uj e-mail cim.
void Ugyfel::setEmail(const std::string& e) { email = e; }



/*-------------------------------------------
            Fontos tagmuveletek
-------------------------------------------*/
/// Masolo fuggveny (virtualis, tisztan absztrakt)
/// @return - uj peldany
Ugyfel* Ugyfel::clone() const {
   return new Ugyfel(*this);
}

/// Kiirja az ugyfel adatait az adott ostream-re.
/// @param os - A kimeneti adatfolyam.
/// @return - Az ostream referenciaja (lancolashoz).
void Ugyfel::kiir(std::ostream& os) const {
    os << "\tNev: " << nev << "\n"
        << "\tTelefonszam: " << telefonszam << "\n"
        << "\tEmail: " << email << "\n"
        << std::endl;
}



/*-------------------------------------------
            Globalis operatorok
-------------------------------------------*/
/// Kimeneti operator Datum objektumhoz
/// @param os - kimeneti stream
/// @param u - kiirando Ugyfel objektum
/// @return - modositott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Ugyfel& u) {
    u.kiir(os);
    return os;
}