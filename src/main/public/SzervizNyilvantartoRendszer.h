/**
*   \file SzervizNyilvantartoRendszer.h
*   A SzervizNyilvantartoRendszer adatait leiro osztaly.
*
*   Az osztaly az autokhoz kapcsolodo szervizmuveletek nyilvantartasara szolgal.
*   Felelos az autok adatainak kezeleseert, uj szervizmuveletek rogziteseert,
*   meglevo adatok lekerdezeseert es modositasaert.
*/

#ifndef SZERVIZNYILVANTARTORENDSZER_H
#define SZERVIZNYILVANTARTORENDSZER_H

#include <string>

#include "Vector.hpp"
#include "Auto.h"
#include "Ugyfel.h"

class SzervizNyilvantartoRendszer {
	Vector<Auto> autok;			///< Az autok listaja
	Vector<Ugyfel> ugyfelek;	///< Az ugyfelek listaja
public:
	/*-------------------------------------------
			Konstruktorok es destruktor
	-------------------------------------------*/
	/// Alapertelmezett konstruktor.
	/// ures vektort hoz letre, elore lefoglalt kapacitassal.
	SzervizNyilvantartoRendszer();

	/// Parameteres konstruktor
	/// @param a - Az auto peldany
	/// @param u - Az ugyfel peldany
	SzervizNyilvantartoRendszer(const Auto& a, const Ugyfel& u);

	/// Masolo konstruktor.
	/// @param v - Masolando SzervizNyilvantartoRendszer peldany
	SzervizNyilvantartoRendszer(const SzervizNyilvantartoRendszer& v);

	/// Destruktor.
	/// Ez jelzi, hogy nem kell semmi egyedi a destruktorba, mert a tagok destruktora magatol elintezi.
	~SzervizNyilvantartoRendszer();



	/*-------------------------------------------
					Getter
	-------------------------------------------*/
	/// Visszaadja az osszes auto objektumot.
	/// @return - Egy Vector<Auto> peldany, amely az osszes jelenleg nyilvantartott autot tartalmazza.
	Vector<Auto>& getAutok();

	/// Visszaadja az osszes auto objektumot (const valtozat).
	/// @return - Egy const Vector<Auto> peldany, amely az osszes jelenleg nyilvantartott autott tartalmazza.
	const Vector<Auto>& getAutok() const;

	/// Visszaadja az osszes ugyfel objektumot.
	/// @return - Egy Vector<Ugyfel> peldany, amely az osszes jelenleg nyilvantartott ugyfelet tartalmazza.
	Vector<Ugyfel>& getUgyfelek();

	/// Visszaadja az osszes ugyfel objektumot (const valtozat).
	/// @return - Egy const Vector<Ugyfel> peldany, amely az osszes jelenleg nyilvantartott ugyfelet tartalmazza.
	const Vector<Ugyfel>& getUgyfelek() const;



	/*-------------------------------------------
				Bovito tagfuggvenyek
	-------------------------------------------*/
	/// uj auto hozzaadasa az adatbazishoz.
	/// @param a - Az uj auto peldany.
	/// @return - True, ha az auto sikeresen hozzaadva, false, ha mar letezik.
	bool ujAuto(const Auto& a);

	/// uj ugyfel hozzaadasa az adatbazishoz.
	/// @param u - Az uj ugyfel peldany.
	/// @return - True, ha az ugyfel sikeresen hozzaadva, false, ha mar letezik.
	bool ujUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				Frissito tagfuggvenyek
	-------------------------------------------*/
	/// Egy auto adatainak frissitese a rendszeren belul.
	/// Ha a rendszeren belul mar letezik az auto (rendszam alapjan), akkor az adatai frissulnek.
	/// @param a - Az auto uj adatai.
	/// @return - True, ha az auto sikeresen frissitve lett, false, ha nem talalhato.
	bool frissitAuto(const Auto& a);

	/// Egy ugyfel adatainak frissitese a rendszeren belul.
	/// Ha a rendszeren belul mar letezik az ugyfel (nev alapjan), akkor az adatai frissulnek.
	/// @param u - Az ugyfel uj adatai.
	/// @return - True, ha az ugyfel sikeresen frissitve lett, false, ha nem talalhato.
	bool frissitUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				Torlo tagfuggvenyek
	-------------------------------------------*/
	/// Egy auto torlese rendszam alapjan.
	/// @param r - A torlendo auto rendszama.
	/// @return - True, ha az auto torolve lett, false, ha nem talalhato.
	bool torolAuto(const std::string& r);

	/// Egy ugyfel torlese nev alapjan.
	/// @param n - A torlendo ugyfel neve.
	/// @return - True, ha az ugyfel torolve lett, false, ha nem talalhato.
	bool torolUgyfel(const std::string& n);

	/// Egy adott rendszamu autohoz tartozo szervizmuvelet torlese a megadott datum alapjan.
	/// @param r - Az auto rendszama.
	/// @param d - A torlendo muvelet datuma.
	/// @return - True, ha a muvelet sikeresen torolve lett, false, ha az auto vagy a megadott datumu muvelet nem talalhato.
	bool torolMuvelet(const std::string& r, const Datum& d);



	/*-------------------------------------------
			  Kereso tagfuggvenyek
	-------------------------------------------*/
	// Auto keresese rendszam alapjan.
	/// @param r - A keresett auto rendszama (teljes egyezes).
	/// @return - Az auto referenciaja, ha megtalalta.
	/// @throw - Hibat dob ha nem talalt meg a kerest rendszamu autot
	Auto& keresAuto(const std::string& r);

	/// ugyfel keresese nev alapjan.
	/// @param n - A keresett ugyfel neve (teljes egyezes).
	/// @return - Az ugyfel referenciaja, ha megtalalta.
	/// @throw - Hibat dob ha nem talalt meg a kerest nevu embert
	Ugyfel& keresUgyfel(const std::string& n);

	/// Auto letezesenek ellenorzese nev alapjan.
	/// @param r - A keresett auto rendszama (teljes egyezes).
	/// @return - True, ha az auto megtalalhato a rendszerben, false egyebkent.
	bool vanAuto(const std::string& r) const;

	/// ugyfel letezesenek ellenorzese nev alapjan.
	/// @param n - A keresett ugyfel neve (teljes egyezes).
	/// @return - True, ha az ugyfel megtalalhato a rendszerben, false egyebkent.
	bool vanUgyfel(const std::string& n) const;



	/*-------------------------------------------
				Fontos tagmuveletek
	-------------------------------------------*/
	/// Egy vegzett szervizmuvelet rogzitese adott autohoz.
	/// @param r - Az auto rendszama.
	/// @param m - A vegzett szervizmuvelet.
	/// @return - True, ha a muvelet sikeresen rogzitve lett, false, ha az auto nem talalhato.
	bool rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m);

	/// Lekerdezi az adott autohoz tartozo szervizmuveleteket.u
	/// @param os - A kimeneti adatfolyam.
	/// @param r - Az auto rendszama.
	void lekeroVegzettMuvelet(std::ostream& os, const std::string& r) const;

	/// Figyelmezteteseket general az auto allapota alapjan.
	/// @param os - A kimeneti adatfolyam.
	/// @param a - Az auto peldany.
	void figyelmeztetesek(std::ostream& os, const Auto& a) const;



	/*-------------------------------------------
			 Fajlkezelo tagfuggvenyek
	-------------------------------------------*/
	/// Az aktualis rendszeradatok mentese fajlba.
	/// @param f - A celfajl neve.
	void mentesFajlba(const std::string& f) const;

	/// Rendszeradatok betoltese fajlbol.
	/// @param f - A forrasfajl neve.
	void betoltesFajlbol(const std::string& f);

	/**
	 * Fontos tudnivalok a fajlkezelo fuggvenyek mukodeserol:
	 *
	 * A fajlokban tarolt adatoknak pontosan meg kell felelniuk az elore definialt szabalyoknak, melyek a kovetkezok:
	 *
	 * Fajlnevek:
	 *   - ugyfel tipusu fajl eseten a fajlnevnek tartalmaznia kell az "_ufl.txt" vegzodest.
	 *   - Auto tipusu fajl eseten a fajlnevnek "_auo.txt" vegzodest kell tartalmaznia.
	 *
	 * Fajlstruktura:
	 *   - ugyfelek eseten a sorok formatuma: "ugyfel_neve-telefonszam-email"
	 *   - Autok eseten a formatum: "rendszam-marka-tipus-kmora-uzembe_helyezes_datuma-szervizmuveletek-tulajdonos_neve"
	 *
	 * Megjegyzesek az autos adatokhoz:
	 *   - A "szervizmuveletek" mezoben szerepelhet:
	 *     - a "nincs" szo, ha nem tortent szervizeles,
	 *     - vagy egy felsorolas az elvegzett muveletekrol, az alabbi formatumban:
	 *       "tipus,leiras,datum,ar,kmora,extra;"
	 *       ahol:
	 *         - tipus: 'J' (javitas), 'K' (karbantartas), vagy 'V' (vizsga),
	 *         - az "extra" mezo kizarolag vizsga eseten tartalmazza a „sikeres” vagy „sikertelen” erteket.
	 *		   - a mezok kozotti elvalaszto karakter a vesszo (,) es a vegen pontosvesszo (;) ha van tovabbi szervizmuvelet.
	 *		   - azt is elvarjuk, hogy a kmora ertekek mindig pozitiv egesz szamok legyenek amik minden esettben <= mint az azt megelozo "szervizmuvelet kmora" erteke
	 *
	 * Tovabbi szabaly:
	 *   - Amennyiben az autohoz tartozo tulajdonos meg nem szerepel a rendszerben, az uj ugyfelet automatikusan felvesszuk, viszont a telefonszam es e-mail mezoi uresen maradnak.
	 */
};

#endif // SZERVIZNYILVANTARTORENDSZER_H