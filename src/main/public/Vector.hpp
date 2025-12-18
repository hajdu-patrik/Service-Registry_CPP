/**
*   \file Vector.hpp
*   Ez egy template osztalyt leiro fajl, amely dinamikus tombot valosit meg.
*   Az osztaly celja, hogy kulonbozo tipusu elemeket taroljon dinamikusan mint az std::vector.
*/

#ifndef VECTOR_HPP  
#define VECTOR_HPP 

#ifdef MEMTRACE
#include "Memtrace.h"
#endif

#include <stdexcept>

/// Tipusjellemzo sablon struktura, amely meghatarozza, hogy egy tipus pointer-e.
/// @tparam T A vizsgalt tipus.
/// @note Alapertelmezetten false, azaz a tipus nem pointer.
template <typename T>
struct IsPointer {
    enum { value = false };
};

/// Tipusjellemzo specializacio pointer tipusokra.
/// @tparam T A tipus, amelynek pointer valtozata a specializacio celja.
/// @note Ez a specializacio akkor aktivalodik, ha T pointer tipus (pl. int*), es true-t ad vissza.
template <typename T>
struct IsPointer<T*> {
    enum { value = true };
};

/// Sablon alapu dinamikus tombosztaly, amely kulon kezeli pointer es nem-pointer tipusokat.
/// @tparam T A tarolt tipus.
/// @tparam VECTOR_MERET A vektor kezdeti kapacitasa, alapertelmezes szerint 100.
template <typename T, size_t VECTOR_MERET = 100>
class Vector {
    size_t kapacitas; ///< Az aktualisan lefoglalt tarhely merete.
    size_t meret;     ///< Az aktualisan tarolt elemek szama.
    T* tomb;          ///< A dinamikusan foglalt tomb mutatoja.

    /// Masolo fuggveny, amely delegal a tipusnak megfelelo implementacios valtozatra.
    /// @param src - A masolando Vector peldany.
    void copy_elements(const Vector& src) {
        copy_elements_impl(src, std::integral_constant<bool, IsPointer<T>::value>());
        /*  Itt az std::integral_constant<bool, IsPointer<T>::value>() egy tipus szintu dispatcher: ha pointer tipus, akkor true_type, kulonben false_type.
            Ez azt jelenti, hogy tipus alapjan kivalasztjuk, melyik copy_elements_impl() vagy delete_elements_impl() fuggveny hivodjon meg — tehat:
            Dispatcheles = donteshozatal a fuggvenyhivasrol(futasi vagy forditasi idoben)
        */
    }

    /// Pointer tipusokra specializalt masolo logika. Mely masolatot keszit clone() segitsegevel.
    /// @param src - A forras vektor.
    /// @param is_ptr - std::true_type jelzi, hogy pointer tipusrol van szo.
    void copy_elements_impl(const Vector& src, std::true_type) {
        for (size_t i = 0; i < src.meret; i++)
            tomb[i] = src.tomb[i] ? src.tomb[i]->clone() : nullptr;
    }

    /// Nem-pointer tipusokra specializalt masolo logika. Egyszeru ertekadas tortenik.
    /// @param src - A forras vektor.
    /// @param is_ptr - std::false_type jelzi, hogy nem pointer tipusrol van szo.
    void copy_elements_impl(const Vector& src, std::false_type) {
        for (size_t i = 0; i < src.meret; i++)
            tomb[i] = src.tomb[i];
    }

    /// Elemfelszabadito fuggveny, amely delegal a tipusfuggo implementaciora.
    void delete_elements() {
        delete_elements_impl(std::integral_constant<bool, IsPointer<T>::value>());
    }

    /// Pointer tipus eseten felszabaditja a mutatott objektumokat.
    /// @param is_ptr - std::true_type jelzi, hogy pointer tipusrol van szo.
    void delete_elements_impl(std::true_type) {
    for (size_t i = 0; i < meret; i++) {
        if (tomb[i]) {
            delete tomb[i];
            tomb[i] = nullptr;
        }
    }
}

    /// Nem-pointer tipus eseten nem vegez semmilyen muveletet.
    /// @param is_ptr - std::false_type jelzi, hogy nem pointer tipusrol van szo.
    void delete_elements_impl(std::false_type) { /* Nem csinalunk semmit! */ }

public:
    /// Alapertelmezett konstruktor. Inicializalja az ures vektort.
    Vector() : kapacitas(VECTOR_MERET), meret(0), tomb(new T[kapacitas]) {}

    /// Masolo konstruktor. Mely vagy sekely masolatot keszit a tipus alapjan.
    /// @param v - A masolando vektor peldany.
    Vector(const Vector& v) : kapacitas(v.kapacitas), meret(0), tomb(new T[kapacitas]) {
        copy_elements(v);
        meret = v.meret;
    }

    /// Destruktor.
    ~Vector() {
        delete_elements();
        delete[] tomb;
    }


    /*-------------------------------------------
                Iterator tamogatas
    -------------------------------------------*/
    /// Mutato az elso elemre (iterator kezdete)
    /// @return - Pointer az elso elemre
    T* begin() { return tomb; }

    /// Konstans mutato az elso elemre (konstans iterator kezdete)
    /// @return - Konstans pointer az elso elemre
    const T* begin() const { return tomb; }

    /// Mutato az utolso elem utani teruletre (iterator vege)
    /// @return Pointer az utolso elem utani teruletre
    T* end() { return tomb + meret; }

    /// Konstans mutato az utolso elem utani teruletre (konstans iterator vege)
    /// @return Konstans pointer az utolso elem utani teruletre
    const T* end() const { return tomb + meret; }



    /*-------------------------------------------
                    Operatorok
    -------------------------------------------*/
    /// ertekado operator.
    /// @param v - Masolando vector peldany
    /// @return - Az aktualis objektum referenciaja
    Vector& operator=(const Vector& v) {
        if (this != &v) {
            delete_elements();
            delete[] tomb;  // Az eddigi memória felszabadítása elõtt kezeljük a pointereket

            kapacitas = v.kapacitas;
            tomb = new T[kapacitas];
            copy_elements(v);  // Az új vektor elemeit másoljuk át
            meret = v.meret;
        }
        return *this;
    }

    /// Egyenlosegvizsgalo operator
    /// @param v - osszehasonlitando vector
    /// @return true - ha a vektorok tartalma megegyezik
    bool operator==(const Vector& v) const {
        if (meret != v.meret) return false;
        for (size_t i = 0; i < meret; i++) {
            if (tomb[i] != v.tomb[i]) return false;
        }
        return true;
    }

    /// Indexelo operator
    /// @param idx - Index
    /// @return - Az adott indexu elem referenciaja
    /// @note - Nincs hatarellenorzes!
    T& operator[](size_t idx) { return tomb[idx]; }

    /// Konstans indexelo operator
    /// @param idx - Index
    /// @return - Az adott indexu elem konstans referenciaja
    /// @note - Nincs hatarellenorzes!
    const T& operator[](size_t idx) const { return tomb[idx]; }



    /*-------------------------------------------
        Kapacitassal kapcsolatos muveletek
    -------------------------------------------*/
    /// Visszaadja a vektorban tarolt elemek szamat.
    /// @return - Az aktualis elemszam (meret)
    size_t size() const { return meret; }

    /// Visszaadja a vektor kapacitasat.
    /// @return - A kapacitas (kapacitas)
    size_t capacity() const { return kapacitas; }

    /// Megvizsgalja, hogy a vektor ures-e.
    /// @return true - ha nincs benne elem, kulonben false
    bool empty() const { return meret == 0; }

    /// Megvaltoztatja a vektor meretet
    /// @param ns - Az uj meret
    /// @param v - Az uj elemek erteke (opcionalis)
    void resize(size_t ns, const T& v = T()) {
        if (ns > kapacitas) {
            reserve(ns);
        }

        if (IsPointer<T>::value) {
            // Ha pointer típus, akkor az új elemeket másoljuk
            for (size_t i = meret; i < ns; i++)
                tomb[i] = v ? v->clone() : nullptr;
        }
        else {
            // Ha nem pointer típus, akkor egyszerû értékadás
            for (size_t i = meret; i < ns; i++)
                tomb[i] = v;
        }

        meret = ns;
    }

    /// Foglal memoriat a megadott kapacitasra
    /// @param m - uj kapacitas
    void reserve(size_t m) {
        if (m <= kapacitas) return;

        T* new_tomb = new T[m];
        for (size_t i = 0; i < meret; i++) {
            new_tomb[i] = tomb[i];
        }
        delete[] tomb;
        tomb = new_tomb;
        kapacitas = m;
    }

    /// Csokkenti a kapacitast a jelenlegi elemszamra.
    void shrink_to_fit() {
        if (kapacitas == meret) return;

        T* new_tomb = new T[meret];
        for (size_t i = 0; i < meret; i++) {
            new_tomb[i] = tomb[i];
        }
        delete[] tomb;
        tomb = new_tomb;
        kapacitas = meret;
    }



    /*-------------------------------------------
            Elem-hozzaferesi muveletek
    -------------------------------------------*/
    /// Biztonsagos elemhozzaferes
    /// @param idx - Index
    /// @return - Az adott indexu elem referenciaja
    /// @throws - std::out_of_range Ha az index ervenytelen
    T& at(size_t idx) {
        if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (at)");
        return tomb[idx];
    }

    /// Biztonsagos konstans elemhozzaferes
    /// @param idx - Index
    /// @return - Az adott indexu elem konstans referenciaja
    /// @throws - std::out_of_range Ha az index ervenytelen
    const T& at(size_t idx) const {
        if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (const at)");
        return tomb[idx];
    }

    /// Az elso elem referenciaja
    /// @return - Az elso elem referenciaja
    /// @throws - std::out_of_range Ha a vektor ures
    T& front() {
        if (empty()) throw std::out_of_range("Ures vector! (front)");
        return tomb[0];
    }

    /// Az utolso elem referenciaja
    /// @return - Az utolso elem referenciaja
    /// @throws - std::out_of_range Ha a vektor ures
    T& back() {
        if (empty()) throw std::out_of_range("Ures vector! (back)");
        return tomb[(meret - 1)];
    }

    /// Az elso elem konstans referenciaja
    /// @return - Az elso elem konstans referenciaja
    /// @throws - std::out_of_range Ha a vektor ures
    const T& front() const {
        if (empty()) throw std::out_of_range("Ures vector! (const front)");
        return tomb[0];
    }

    /// Az utolso elem konstans referenciaja
    /// @return - Az utolso elem konstans referenciaja
    /// @throws - std::out_of_range Ha a vektor ures
    const T& back() const {
        if (empty()) throw std::out_of_range("Ures vector! (const back)");
        return tomb[(meret - 1)];
    }



    /*-------------------------------------------
                Modosito muveletek
    -------------------------------------------*/
    /// uj elem hozzaadasa a vegere
    /// @param v - A hozzaadando ertek
    void push_back(const T& v) {
        if (meret >= kapacitas) {
            reserve(kapacitas * 2);
        }
        tomb[meret++] = v;
    }

    /// Utolso elem torlese
    /// @throws - std::out_of_range Ha a vektor ures
    void pop_back() {
        if (empty()) throw std::out_of_range("Ures vector! (pop_back)");
        --meret;
    }

    /// Elem beszurasa a megadott poziciora
    /// @param p - Beszurasi pozicio (iterator)
    /// @param v - A beszurando ertek
    /// @return - Iterator az uj elemre
    /// @throws - std::out_of_range Ha a pozicio ervenytelen
    T* insert(T* p, const T& v) {
        size_t idx = p - tomb;
        if (idx > meret) throw std::out_of_range("Ervenytelen pozicio! (insert)");

        if (meret >= kapacitas) {
            reserve(kapacitas == 0 ? 1 : kapacitas * 2);
            p = tomb + idx;  // Frissitjuk a poziciot, mert a tomb ujra lett foglalva
        }

        for (size_t i = meret; i > idx; --i) {
            tomb[i] = tomb[i - 1];
        }
        tomb[idx] = v;
        meret++;
        return tomb + idx;
    }

    /// Elem torlese a megadott poziciorol
    /// @param p - Torlendo elem pozicioja (iterator)
    /// @return - Iterator a torolt elem utani elemre
    /// @throws - std::out_of_range Ha a pozicio ervenytelen
    T* erase(T* p) {
        size_t idx = p - tomb;
        if (idx >= meret) throw std::out_of_range("Ervenytelen pozicio! (erase)");

        for (size_t i = idx; i < (meret - 1); i++) {
            tomb[i] = tomb[i + 1];
        }
        --meret;
        return tomb + idx;
    }

    /// Minden elem torlese
    void clear() {
        delete_elements();  // Felszabadítja az objektumokat, ha pointer típus
        meret = 0;
    }
};

#endif // !VECTOR_HPP