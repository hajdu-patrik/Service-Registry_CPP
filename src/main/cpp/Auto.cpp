/**
*   \file Auto.cpp
*   Az auto osztaly tagfuggvenyeinek megvalositasa.
*/

#ifdef MEMTRACE
#include "Memtrace.h"
#endif
#include <string>

#include "Auto.h"
#include "Datum.h"
#include "Ugyfel.h"
#include "Vector.hpp"
#include "VegzettMuvelet.h"

/*-------------------------------------------
        Konstruktorok es destruktor
-------------------------------------------*/
/// Alapertelmezett konstruktor.
Auto::Auto() : rendszam(""), marka(""), tipus(""), kmOra(0), uzembeHelyezes(Datum()), tulajdonos(nullptr) {}

/// Parameteres konstruktor.  
/// @param r - Az auto rendszama  
/// @param m - Az auto markaja  
/// @param t - Az auto tipusa  
/// @param k - A kilometerora allasa  
Auto::Auto(const std::string& r, const std::string& m, const std::string& t, int k) : rendszam(r), marka(m), tipus(t), kmOra(k), uzembeHelyezes(), tulajdonos(nullptr) {}

/// Parametres 2 konstruktor.
/// Parameteres konstruktor.  
/// @param r - Az auto rendszama  
/// @param m - Az auto markaja  
/// @param t - Az auto tipusa  
/// @param k - A kilometerora allasa  
/// @param d - Az uzembe helyezes datuma  
/// @param v - Az autohoz tartozo szervizmuveletek listaja  
/// @param u - Az auto tulajdonosa  
Auto::Auto(const std::string& r, const std::string& m, const std::string& t, int k, const Datum& d, const Vector<VegzettMuvelet*>& v, Ugyfel* u) : rendszam(r), marka(m), tipus(t), kmOra(k), uzembeHelyezes(d), tulajdonos(u) {
    for (size_t i = 0; i < v.size(); i++)
        vegzettSzervizMuveletek.push_back(v.at(i)->clone());
}

/// Masolo konstruktor.
/// @param a - masolando Auto objektum
Auto::Auto(const Auto& a) : rendszam(a.rendszam), marka(a.marka), tipus(a.tipus), kmOra(a.kmOra), uzembeHelyezes(a.uzembeHelyezes), tulajdonos(a.tulajdonos) {
    for (size_t i = 0; i < a.vegzettSzervizMuveletek.size(); i++)
        vegzettSzervizMuveletek.push_back(a.vegzettSzervizMuveletek[i]->clone());
}

/// Destruktor
Auto::~Auto() { 
    vegzettSzervizMuveletek.clear();
}



/*-------------------------------------------
                Operatorok
-------------------------------------------*/
/// Ertekado operator.
/// @param a - masolando Auto objektum
/// @return - Az aktualis objektum referenciaja
Auto& Auto::operator=(const Auto& a) {
    if (this != &a) {
        rendszam = a.rendszam;
        marka = a.marka;
        tipus = a.tipus;
        kmOra = a.kmOra;
        uzembeHelyezes = a.uzembeHelyezes;
        tulajdonos = a.tulajdonos;

        vegzettSzervizMuveletek.clear();

        for (size_t i = 0; i < a.vegzettSzervizMuveletek.size(); i++)
            vegzettSzervizMuveletek.push_back(a.vegzettSzervizMuveletek[i]->clone());
    }
    return *this;
}


/// Egyenloseg operator tultoltese az Auto osztalyhoz.
/// @param a - Az osszehasonlitando Auto objektum.
/// @return - true, ha az objektumok megegyeznek, kulonben false.
bool Auto::operator==(const Auto& a) const {
    return rendszam == a.rendszam &&
        marka == a.marka &&
        tipus == a.tipus &&
        kmOra == a.kmOra &&
        uzembeHelyezes == a.uzembeHelyezes &&
        tulajdonos->getNev() == a.tulajdonos->getNev() &&
        tulajdonos->getTelefonszam() == a.tulajdonos->getTelefonszam() &&
        tulajdonos->getEmail() == a.tulajdonos->getEmail();
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// Visszaadja az auto rendszamat.
/// @return - Rendszam
const std::string& Auto::getRendszam() const {
    return rendszam;
}

/// Visszaadja az auto markajat.
/// @return - Marka.
const std::string& Auto::getMarka() const {
    return marka;
}

/// Visszaadja az auto tipusat.
/// @return - Tipus.
const std::string& Auto::getTipus() const {
    return tipus;
}

/// Visszaadja a kilometerora aktualis erteket.
/// @return - Km ora erteke.
int Auto::getKmOra() const {
    return kmOra;
}

/// Visszaadja az uzembe helyezes datumot.
/// @return - Datum.
const Datum& Auto::getUzembeHelyezes() const {
    return uzembeHelyezes;
}

/// Visszaadja az autohoz tartozo szervizmuveletek listajat.
/// @return - Szervizmuveletek vektora.
Vector<VegzettMuvelet*>& Auto::getSzervizMuveletek() {
    return vegzettSzervizMuveletek;
}

/// Visszaadja az autohoz tartozo szervizmuveletek listajat (const valtozat).
/// @return - Szervizmuveletek vektora.
const Vector<VegzettMuvelet*>& Auto::getSzervizMuveletek() const {
    return vegzettSzervizMuveletek;
}

// Visszaadja az auto tulajdonosat.
/// @return - Az auto tulajdonosa.
Ugyfel* Auto::getTulajdonos() {
    return tulajdonos;
}

// Visszaadja az auto tulajdonosat (const valtozat).
/// @return - Az auto tulajdonosa.
const Ugyfel* Auto::getTulajdonos() const {
    return tulajdonos;
}



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Beallitja az auto rendszamat.
/// @param r - Az uj rendszam
void Auto::setRendszam(const std::string& r) {
    rendszam = r;
}

/// Beallitja a kilometerora erteket.
/// @param k - Az uj km ora ertek
void Auto::setKmOra(int k) {
    if (k >= kmOra) kmOra = k;
}

/// Beallitja a tulajdonost.
/// @param u - Az uj tulajdonos.
void Auto::setTulajdonos(Ugyfel* u) {
    tulajdonos = u;
}



/*-------------------------------------------
            Fontos tagmuveletek
-------------------------------------------*/
/// Masolo fuggveny (virtualis, tisztan absztrakt)
/// @return - uj peldany
Auto* Auto::clone() const {
    return new Auto(*this);
}

/// Hozzaad egy szervizmuveletet az auto szervizlistajahoz.
/// @param m - A hozzadando szervizmuvelet pointere
void Auto::addVegzettSzerviz(VegzettMuvelet* m) {
    vegzettSzervizMuveletek.push_back(m);
}

/// Torli a megadott indexu szervizmuveletet a listabol.
/// @param idx - A torlendo muvelet pozicioja
void Auto::torolVegzettSzerviz(size_t idx) {
    if (idx < vegzettSzervizMuveletek.size()) {
        delete vegzettSzervizMuveletek[idx];
        vegzettSzervizMuveletek.erase(vegzettSzervizMuveletek.begin() + idx);
    }
}

void Auto::kiir(std::ostream& os) const {
    os << "\tRendszam: " << rendszam << "\n"
        << "\tMarka: " << marka << "\n"
        << "\tTipus: " << tipus << "\n"
        << "\tKm ora: " << kmOra << "\n"
        << "\tUzembe helyezes: " << uzembeHelyezes << "\n"
        << "\tTulajdonos: ";
    if (tulajdonos)
        os << tulajdonos->getNev();
    else
        os << "nincs megadva";
    os << "\n"
        << "\tSzervizmuveletek:" << (vegzettSzervizMuveletek.size() == 0 ? " nincs" : "") << "\n";

    for (size_t i = 0; i < vegzettSzervizMuveletek.size(); i++) {
        vegzettSzervizMuveletek.at(i)->kiir(os);
    }

    os << std::endl;
}



/*-------------------------------------------
            Globalis operatorok
-------------------------------------------*/
/// Kimeneti operator Datum objektumhoz
/// @param os - kimeneti stream
/// @param a - kiirando Auto objektum
/// @return - modositott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Auto& a) {
    a.kiir(os);
    return os;
}