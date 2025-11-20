/**
*   \file Datum.cpp
*   A datum osztaly tagfuggvenyeinek megvalositasa.
*/

#include "Datum.h"

/*-------------------------------------------
        Konstruktorok es destruktor
-------------------------------------------*/
/// Alapertelmezett konstruktor
/// 0-ra inicializalja az evet, honapot es napot.
Datum::Datum() : ev(0), ho(0), nap(0) {}

/// Parameteres konstruktor
/// @param e - ev
/// @param h - honap
/// @param n - nap
Datum::Datum(int e, int h, int n) : ev(e), ho(h), nap(n) {}

/// Masolo konstruktor
/// @param d - masolando Datum objektum
Datum::Datum(const Datum& d) : ev(d.ev), ho(d.ho), nap(d.nap) {}

/// Destruktor
Datum::~Datum() {}



/*-------------------------------------------
                Operatorok
-------------------------------------------*/
/// ertekado operator
/// @param d - masolando Datum objektum
/// @return - az aktualis objektum referenciaja
Datum& Datum::operator=(const Datum& d) {
    if (this != &d) {
        ev = d.ev;
        ho = d.ho;
        nap = d.nap;
    }
    return *this;
}

/// osszehasonlito operator
/// @param d - osszehasonlitando Datum objektum
/// @return - true, ha az objektumok megegyeznek, kulonben false.
bool Datum::operator==(const Datum& d) const {
    return ev == d.ev && ho == d.ho && nap == d.nap;
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// ev lekerdezese
/// @return - ev
int Datum::getEv() const { return ev; }

/// Honap lekerdezese
/// @return - honap
int Datum::getHo() const { return ho; }

/// Nap lekerdezese
/// @return - nap
int Datum::getNap() const { return nap; }

/// Datum eltelt napok szamanak lekerdezese
/// @param d - masik Datum objektum
int Datum::elteltNap(const Datum& d) const {
    int e = d.getEv() - ev;
    int h = d.getHo() - ho;
    int n = d.getNap() - nap;
    return e * 365 + h * 30 + n;
}



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Datum beallitasa
/// @param e - ev
/// @param h - honap
/// @param n - nap
void Datum::setDatum(int e, int h, int n) {
    ev = e;
    ho = h;
    nap = n;
}



/*-------------------------------------------
               Segedfuggvenyek
-------------------------------------------*/
/// Letrehoz egy Datum objektumot egy stringbol.
/// A string formatuma: "EEEE.HH.NN".
/// @param str - A datumot tartalmazo string.
/// @return - A letrehozott Datum objektum.
Datum Datum::parseFromString(const std::string& str) {
    int e, h, n;
    char dot1, dot2;
    std::istringstream iss(str);

    if (!(iss >> e >> dot1 >> h >> dot2 >> n) || dot1 != '.' || dot2 != '.')
        throw std::runtime_error("Hibas datum formatum! (parseFromString)");

    return Datum(e, h, n);
}

/// Egy Datum objektumot stringge alakit "EEEE.HH.NN" formatumban.
/// @return std::string A formazott datum szovegkent.
const std::string Datum::toString() const {
    std::ostringstream oss;

    oss << std::setw(4) << std::setfill('0') << ev << "."
        << std::setw(2) << std::setfill('0') << ho << "."
        << std::setw(2) << std::setfill('0') << nap;

    return oss.str();
}




/*-------------------------------------------
            Globalis operatorok
-------------------------------------------*/
/// Kimeneti operator Datum objektumhoz
/// @param os - kimeneti stream
/// @param d - kiirando Datum objektum
/// @return - modositott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Datum& d) {
    return os << std::setw(4) << std::setfill('0') << d.getEv() << "."
        << std::setw(2) << std::setfill('0') << d.getHo() << "."
        << std::setw(2) << std::setfill('0') << d.getNap();
}