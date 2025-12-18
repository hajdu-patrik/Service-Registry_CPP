/**
*   \file Datum.h
*   A Datummot leiro osztaly deklaracioja es tagfuggvenyeinek inline megvalositasa.
*/

#ifndef DATUM_H  
#define DATUM_H  

#include <iostream>
#include <iomanip>
#include <sstream>

class Datum {
    int ev;     ///< ev  
    int ho;     ///< Honap  
    int nap;    ///< Nap  

public:
    /*-------------------------------------------
            Konstruktorok es destruktor
    -------------------------------------------*/
    /// Alapertelmezett konstruktor
    /// 0-ra inicializalja az evet, honapot es napot.
    Datum();

    /// Parameteres konstruktor
    /// @param e - ev
    /// @param h - honap
    /// @param n - nap
    Datum(int e, int h, int n);

    /// Masolo konstruktor
    /// @param d - masolando Datum objektum
    Datum(const Datum& d);

    /// Destruktor
    ~Datum();



    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator
    /// @param d - masolando Datum objektum
    /// @return - az aktualis objektum referenciaja
    Datum& operator=(const Datum& d);

    /// osszehasonlito operator
    /// @param d - osszehasonlitando Datum objektum
    /// @return - true, ha az objektumok megegyeznek, kulonben false.
    bool operator==(const Datum& d) const;



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// ev lekerdezese
    /// @return - ev
    int getEv() const;

    /// Honap lekerdezese
    /// @return - honap
    int getHo() const;

    /// Nap lekerdezese
    /// @return - nap
    int getNap() const;

    /// Datum eltelt napok szamanak lekerdezese
    /// @param d - masik Datum objektum
    int elteltNap(const Datum& d) const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Datum beallitasa
    /// @param e - ev
    /// @param h - honap
    /// @param n - nap
    void setDatum(int e, int h, int n);



    /*-------------------------------------------
                   Segedfuggvenyek
    -------------------------------------------*/
    /// Letrehoz egy Datum objektumot egy stringbõl.
    /// A string formatuma: "eeee.HH.NN".
    /// @param str - A datumot tartalmazo string.
    /// @return - A letrehozott Datum objektum.
    static Datum parseFromString(const std::string& str);

    /// Egy Datum objektumot stringge alakit "eeee.HH.NN" formatumban.
    /// @return std::string A formazott datum szovegkent.
    const std::string toString() const;
};
/*-------------------------------------------
            Globalis operatorok
-------------------------------------------*/
/// Kimeneti operator Datum objektumhoz
/// @param os - kimeneti stream
/// @param d - kiirando Datum objektum
/// @return - modositott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Datum& d);

#endif // !DATUM_H