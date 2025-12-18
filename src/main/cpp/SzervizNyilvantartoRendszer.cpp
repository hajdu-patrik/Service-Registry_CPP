/**
*   \file SzervizNyilvantartoRendszer.cpp
*   A SzervizNyilvantartoRendszer osztaly tagfuggvenyeinek megvalositasa.
*/

#ifdef MEMTRACE
#include "Memtrace.h"
#endif

#include <fstream>
#include <sstream>
#include <cctype>

#include "SzervizNyilvantartoRendszer.h"
#include "Auto.h"
#include "Ugyfel.h"
#include "VegzettMuvelet.h"
#include "Vizsga.h"
#include "Karbantartas.h"
#include "Javitas.h"

/*-------------------------------------------
		Konstruktorok es destruktor
-------------------------------------------*/
/// Alapertelmezett konstruktor.
/// ures vektort hoz letre, elore lefoglalt kapacitassal.
SzervizNyilvantartoRendszer::SzervizNyilvantartoRendszer() : autok(), ugyfelek() {}

/// Parameteres konstruktor
/// @param a - Az auto peldany
/// @param u - Az ugyfel peldany
SzervizNyilvantartoRendszer::SzervizNyilvantartoRendszer(const Auto& a, const Ugyfel& u) {
	autok.push_back(a);
	ugyfelek.push_back(u);
}

/// Masolo konstruktor.
/// @param v - Masolando SzervizNyilvantartoRendszer peldany
SzervizNyilvantartoRendszer::SzervizNyilvantartoRendszer(const SzervizNyilvantartoRendszer& v) {
	for (size_t i = 0; i < v.autok.size(); i++)
		autok.push_back(v.autok.at(i));
	for (size_t i = 0; i < v.ugyfelek.size(); i++)
		ugyfelek.push_back(v.ugyfelek.at(i));
}

/// Destruktor.
/// Ez jelzi, hogy nem kell semmi egyedi a destruktorba, mert a tagok destruktora magatol elintezi.
SzervizNyilvantartoRendszer::~SzervizNyilvantartoRendszer() = default;



/*-------------------------------------------
				Getter
-------------------------------------------*/
/// Visszaadja az osszes auto objektumot.
/// @return - Egy Vector<Auto> peldany, amely az osszes jelenleg nyilvantartott autot tartalmazza.
Vector<Auto>& SzervizNyilvantartoRendszer::getAutok() {
	return autok;
}

/// Visszaadja az osszes auto objektumot (const valtozat).
/// @return - Egy const Vector<Auto> peldany, amely az osszes jelenleg nyilvantartott autott tartalmazza.
const Vector<Auto>& SzervizNyilvantartoRendszer::getAutok() const {
	return autok;
}

/// Visszaadja az osszes ugyfel objektumot.
/// @return - Egy Vector<Ugyfel> peldany, amely az osszes jelenleg nyilvantartott ugyfelet tartalmazza.
Vector<Ugyfel>& SzervizNyilvantartoRendszer::getUgyfelek() {
	return ugyfelek;
}

/// Visszaadja az osszes ugyfel objektumot (const valtozat).
/// @return - Egy const Vector<Ugyfel> peldany, amely az osszes jelenleg nyilvantartott ugyfelet tartalmazza.
const Vector<Ugyfel>& SzervizNyilvantartoRendszer::getUgyfelek() const {
	return ugyfelek;
}



/*-------------------------------------------
				Bovito tagfuggvenyek
-------------------------------------------*/
/// uj auto hozzaadasa az adatbazishoz.
/// @param a - Az uj auto peldany.
/// @return - True, ha az auto sikeresen hozzaadva, false, ha mar letezik.
bool SzervizNyilvantartoRendszer::ujAuto(const Auto& a) {
	if (!vanAuto(a.getRendszam())) {
		autok.push_back(a);
		return true;
	}
	return false;
}


/// uj ugyfel hozzaadasa az adatbazishoz.
/// @param u - Az uj ugyfel peldany.
/// @return - True, ha az ugyfel sikeresen hozzaadva, false, ha mar letezik.
bool SzervizNyilvantartoRendszer::ujUgyfel(const Ugyfel& u) {
	if (!vanUgyfel(u.getNev())) {
		ugyfelek.push_back(u);
		return true;
	}
	return false;
}



/*-------------------------------------------
			Frissito tagfuggvenyek
-------------------------------------------*/
/// Egy auto adatainak frissitese a rendszeren belul.
/// Ha a rendszeren belul mar letezik az auto (rendszam alapjan), akkor az adatai frissulnek.
/// @param a - Az auto uj adatai.
/// @return - True, ha az auto sikeresen frissitve lett, false, ha nem talalhato.
bool SzervizNyilvantartoRendszer::frissitAuto(const Auto& a) {
	for (auto& autoRef : autok) {
		if (autoRef.getRendszam() == a.getRendszam()) {
			autoRef = a;
			return true;
		}
	}
	return false;
}

/// Egy ugyfel adatainak frissitese a rendszeren belul.
/// Ha a rendszeren belul mar letezik az ugyfel (nev alapjan), akkor az adatai frissulnek.
/// @param u - Az ugyfel uj adatai.
/// @return - True, ha az ugyfel sikeresen frissitve lett, false, ha nem talalhato.
bool SzervizNyilvantartoRendszer::frissitUgyfel(const Ugyfel& u) {
	for (auto& ugyfelRef : ugyfelek) {
		if (ugyfelRef.getNev() == u.getNev()) {
			ugyfelRef = u;
			return true;
		}
	}
	return false;
}



/*-------------------------------------------
			Torlo tagfuggvenyek
-------------------------------------------*/
/// Egy auto torlese rendszam alapjan.
/// @param r - A torlendo auto rendszama.
/// @return - True, ha az auto torolve lett, false, ha nem talalhato.
bool SzervizNyilvantartoRendszer::torolAuto(const std::string& r) {
	for (auto it = autok.begin(); it != autok.end(); it++) {
		if (it->getRendszam() == r) {
			autok.erase(it);
			return true;
		}
	}
	return false;
}

/// Egy ugyfel torlese nev alapjan.
/// @param n - A torlendo ugyfel neve.
/// @return - True, ha az ugyfel torolve lett, false, ha nem talalhato.
bool SzervizNyilvantartoRendszer::torolUgyfel(const std::string& n) {
	bool torolve = false;

	// Toroljuk az ugyfelhez tartozo autokat
	for (auto jt = autok.begin(); jt != autok.end(); ) {
		if (jt->getTulajdonos()->getNev() == n) {
			jt = autok.erase(jt);
			torolve = true;
		}
		else {
			++jt;
		}
	}

	// Toroljuk az ugyfelet
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); ) {
		if (it->getNev() == n) {
			it = ugyfelek.erase(it);
			torolve = true;
		}
		else {
			it++;
		}
	}

	return torolve;
}

/// Egy adott rendszamu autohoz tartozo szervizmuvelet torlese a megadott datum alapjan.
/// @param r - Az auto rendszama.
/// @param d - A torlendo muvelet datuma.
/// @return - True, ha a muvelet sikeresen torolve lett, false, ha az auto vagy a megadott datumu muvelet nem talalhato.
bool SzervizNyilvantartoRendszer::torolMuvelet(const std::string& r, const Datum& d) {
	for (auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			auto& muveletek = autoObj.getSzervizMuveletek();
			for (size_t i = 0; i < muveletek.size(); ++i) {
				if (muveletek[i]->getDatum() == d) {
					autoObj.torolVegzettSzerviz(i);
					return true;
				}
			}
			return false; // Az auto letezik, de nincs ilyen datumu muvelet
		}
	}
	return false; // Nincs ilyen rendszamu auto
}



/*-------------------------------------------
		  Kereso tagfuggvenyek
-------------------------------------------*/
/// Auto keresese rendszam alapjan.
/// @param r - A keresett auto rendszama (teljes egyezes).
/// @return - Az auto referenciaja, ha megtalalta.
/// @throw - Hibat dob ha nem talalt meg a kerest rendszamu autot
Auto& SzervizNyilvantartoRendszer::keresAuto(const std::string& r) {
	for (auto it = autok.begin(); it != autok.end(); it++) {
		if (it->getRendszam() == r) {
			return *it;
		}
	}
	throw std::runtime_error("Nincs ilyen rendszamu auto!");
}

/// ugyfel keresese nev alapjan.
/// @param n - A keresett ugyfel neve (teljes egyezes).
/// @return - Az ugyfel referenciaja, ha megtalalta.
/// @throw - Hibat dob ha nem talalt meg a kerest nevu embert
Ugyfel& SzervizNyilvantartoRendszer::keresUgyfel(const std::string& n) {
	for (auto it = ugyfelek.begin(); it != ugyfelek.end(); it++) {
		if (it->getNev() == n) {
			return *it;
		}
	}
	throw std::runtime_error("Nincs ilyen nevu ugyfel!");
}

/// Auto letezesenek ellenorzese nev alapjan.
/// @param r - A keresett auto rendszama (teljes egyezes).
/// @return - True, ha az auto megtalalhato a rendszerben, false egyebkent.
bool SzervizNyilvantartoRendszer::vanAuto(const std::string& r) const {
	for (const auto& a : autok)
		if (a.getRendszam() == r)
			return true;
	return false;
}

/// ugyfel letezesenek ellenorzese nev alapjan.
/// @param n - A keresett ugyfel neve (teljes egyezes).
/// @return - True, ha az ugyfel megtalalhato a rendszerben, false egyebkent.
bool SzervizNyilvantartoRendszer::vanUgyfel(const std::string& n) const {
	for (const auto& u : ugyfelek)
		if (u.getNev() == n)
			return true;
	return false;
}



/*-------------------------------------------
			Fontos tagmuveletek
-------------------------------------------*/
/// Egy vegzett szervizmuvelet rogzitese adott autohoz.
/// @param r - Az auto rendszama.
/// @param m - A vegzett szervizmuvelet.
/// @return - True, ha a muvelet sikeresen rogzitve lett, false, ha az auto nem talalhato.
bool SzervizNyilvantartoRendszer::rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m) {
	for (auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			VegzettMuvelet* ujMuvelet = m.clone();
			autoObj.addVegzettSzerviz(ujMuvelet);
			return true;
		}
	}
	return false;
}

/// Lekerdezi az adott autohoz tartozo szervizmuveleteket.u
/// @param os - A kimeneti adatfolyam.
/// @param r - Az auto rendszama.
void SzervizNyilvantartoRendszer::lekeroVegzettMuvelet(std::ostream& os, const std::string& r) const {
	for (const auto& autoObj : autok) {
		if (autoObj.getRendszam() == r) {
			const auto& muveletek = autoObj.getSzervizMuveletek();
			for (const auto& muvelet : muveletek) {
				muvelet->kiir(os);
			}
			return;
		}
	}
}

/// Figyelmezteteseket general az auto allapota alapjan.
/// @param os - A kimeneti adatfolyam.
/// @param a - Az auto peldany.
void SzervizNyilvantartoRendszer::figyelmeztetesek(std::ostream& os, const Auto& a) const {
	int hanyDBHiba = 0; // Hiba szamlalo
	for (const auto& autoObj : autok) {
		if (autoObj == a) {
			const auto& muveletek = autoObj.getSzervizMuveletek();
			if (muveletek.empty()) {
				os << "\tA " << a.getRendszam() << " rendszamu autohoz nincsenek rogzitett szervizmuveletek!" << std::endl;
				return;
			}

			// Az utolso szervizmuvelet:
			VegzettMuvelet* utolso = muveletek.back();

			// Datum alapu figyelmeztetes
			if (utolso->getDatum().elteltNap(Datum(2025, 4, 14)) > (365 * 2)) { // Tobb mint 2 eve
				os << "\tA " << a.getRendszam() << " rendszamu auto muszaki vizsgaja lejart! (Utolso vizsga: " << utolso->getDatum() << ")" << std::endl;
				hanyDBHiba++;
			}

			// Km alapu figyelmeztetes
			int elteltKm = autoObj.getKmOra() - utolso->getAktKmOra();
			if (elteltKm > 10000) {
				os << "\tA " << a.getRendszam() << " rendszamu auto szervizelesre esedekes! (Utolso szerviz ota " << elteltKm << " km telt el)" << std::endl;
				hanyDBHiba++;
			}

			if (hanyDBHiba == 0) {
				os << "\tNincsenek figyelmeztetesek!" << std::endl;
			}
		}
	}
}



/*-------------------------------------------
		 Fajlkezelo tagfuggvenyek
-------------------------------------------*/
/// Lecsereli a szovegben talalhato alahuzasjeleket (_) szokozokre.
/// A fuggveny static kulcsszoval van ellatva, mert csak a jelenlegi forditasi egysegen (fajlban) belul hasznaljuk, igy nem szukseges kivulrol elerhetove tenni.
/// @param str - A bemeneti string, amelyet formazni szeretnenk.
/// @return - std::string
static std::string trim(const std::string& str) {
	std::string result;
	for (char c : str) {
		if (c == '_') result += ' ';
		else result += c;
	}
	return result;
}

/// Lecsereli a szovegben talalhato szokozjeleket ("_") alahuzasra.
/// A fuggveny static kulcsszoval van ellatva, mert csak a jelenlegi forditasi egysegen (fajlban) belul hasznaljuk, igy nem szukseges kivulrol elerhetove tenni.
/// @param str - A bemeneti string, amelyet formazni szeretnenk.
/// @return - std::string
static std::string reverse_trim(const std::string& str) {
	std::string result;
	for (char c : str) {
		if (c == ' ') result += '_';
		else result += c;
	}
	return result;
}

/// Rendszeradatok betoltese fajlbol.
/// @param f - A forrasfajl neve.
void SzervizNyilvantartoRendszer::betoltesFajlbol(const std::string& f) {
	std::ifstream fp(f);
	if (!fp.is_open()) throw std::runtime_error("Nem sikerult megnyitni a fajlt! (betoltesFajlbol)");

	/* --- std::string.find() ---
	   - Megkeresi egy adott reszszoveg (karakter vagy string) elso elofordulasanak helyet egy masik stringben.
	   - Ha nem talalja meg:A find() visszaadja a specialis erteket: std::string::npos
	*/
	bool ugyfelFajl = f.find("_ufl.txt") != std::string::npos; // A std::string::npos egy specialis konstans ertek, amit a C++ std::string tipus hasznal arra, hogy jelezze: valamit nem talalt meg.
	bool autoFajl = f.find("_auo.txt") != std::string::npos;
	if (!ugyfelFajl && !autoFajl) throw std::invalid_argument("Ismeretlen fajlformatum! (betoltesFajlbol)");

	std::string sor;
	/* --- std::getline() ---
	   - Sor beolvasasa szovegbol (akar fajlbol, akar mas streambol).
	   - Megadott elvalaszto karakterig olvas('\n' az alapertelmezett), de lehet mast is adni
	*/
	while (std::getline(fp, sor)) {
		if (sor.empty()) continue;

		if (ugyfelFajl) {
			std::istringstream iss(sor);
			std::string nevStr, telStr, emailStr;

			std::getline(iss, nevStr, '-');
			std::getline(iss, telStr, '-');
			std::getline(iss, emailStr);

			nevStr = trim(nevStr);
			telStr = trim(telStr);

			if (vanUgyfel(nevStr)) {
				// Frissitjuk az ugyfel adatait
				Ugyfel& letezoUgyfel = keresUgyfel(nevStr);
				letezoUgyfel.setTel(telStr);
				letezoUgyfel.setEmail(emailStr);
			}
			else {
				// uj ugyfel hozzaadasa
				ugyfelek.push_back(Ugyfel(nevStr, telStr, emailStr));
			}
		}
		else if (autoFajl) {
			std::string rendszamStr, markaStr, tipusStr, kmOraStr, datumStr, muveletekStr, tulajNevStr;
			std::istringstream iss(sor);
			std::getline(iss, rendszamStr, '-');
			std::getline(iss, markaStr, '-');
			std::getline(iss, tipusStr, '-');
			std::getline(iss, kmOraStr, '-');
			std::getline(iss, datumStr, '-');

			std::string muveletekTulajStr;
			std::getline(iss, muveletekTulajStr);

			// Az utolso '-' jel alapjan vagjuk kette: muveletekStr - tulajNev
			size_t utolsoKotojelHelye = muveletekTulajStr.rfind('-');
			if (utolsoKotojelHelye == std::string::npos)
				throw std::runtime_error("Hibas sorformatum, nem talalhato tulajdonos neve! (betoltesFajlbol)");

			muveletekStr = muveletekTulajStr.substr(0, utolsoKotojelHelye);
			tulajNevStr = muveletekTulajStr.substr(utolsoKotojelHelye + 1);

			// Azokat a mezoket, ahol alulvonas("_") karaktert hasznaltunk szokoz helyett, visszaalakitjuk szokozokke(" ") a megjelenes egysegesitese erdekeben.
			markaStr = trim(markaStr);
			tipusStr = trim(tipusStr);
			muveletekStr = trim(muveletekStr);
			tulajNevStr = trim(tulajNevStr);
			int kmOra = std::stoi(kmOraStr);
			Datum uzembeHelyezes = Datum::parseFromString(datumStr);

			Vector<VegzettMuvelet*> szervizLista;
			if (muveletekStr != "nincs") {
				std::stringstream muveletTempStream(muveletekStr);
				std::string muveletElem;

				while (std::getline(muveletTempStream, muveletElem, ';')) {
					muveletElem = trim(muveletElem);
					if (muveletElem.empty()) continue;

					char tipus = muveletElem[0];
					std::string extraStr; // deklaraljuk itt, de erteket csak akkor adunk, ha kell
					std::string leirasStr, datumStr, arStr, kmStr;

					std::string tartalomStr = muveletElem.substr(2);
					std::stringstream adatSS(tartalomStr);
					std::getline(adatSS, leirasStr, ',');
					std::getline(adatSS, datumStr, ',');
					std::getline(adatSS, arStr, ',');
					std::getline(adatSS, kmStr, ',');

					if (tipus == 'V') {
						std::getline(adatSS, extraStr); // csak akkor olvassuk be, ha van ilyen mezo
					}

					leirasStr = trim(leirasStr);
					extraStr = trim(extraStr);
					Datum datum = Datum::parseFromString(datumStr);
					int ar = std::stoi(arStr);
					int km = std::stoi(kmStr);

					if (tipus == 'J') {
						szervizLista.push_back(new Javitas(leirasStr, datum, ar, km));
					}
					else if (tipus == 'K') {
						szervizLista.push_back(new Karbantartas(leirasStr, datum, ar, km));
					}
					else if (tipus == 'V') {
						bool sikeresE = extraStr == "sikeres";
						szervizLista.push_back(new Vizsga(leirasStr, datum, ar, km, sikeresE));
					}
				}
			}

			if (vanUgyfel(tulajNevStr)) {
				Ugyfel& tulajStr = keresUgyfel(tulajNevStr);
				autok.push_back(Auto(rendszamStr, markaStr, tipusStr, kmOra, uzembeHelyezes, szervizLista, &tulajStr));
			}
			else {
				// tulajdonos meg nincs, letrehozas + beszuras
				ugyfelek.push_back(Ugyfel(tulajNevStr, "", ""));
				Ugyfel& ujTulaj = ugyfelek.back();
				autok.push_back(Auto(rendszamStr, markaStr, tipusStr, kmOra, uzembeHelyezes, szervizLista, &ujTulaj));
			}
		}
	}
	fp.close();
}

/// Az aktualis rendszeradatok mentese fajlba.
/// @param f - A celfajl neve.
void SzervizNyilvantartoRendszer::mentesFajlba(const std::string& f) const {
	std::ofstream fp(f);
	if (!fp.is_open()) throw std::runtime_error("Nem sikerult megnyitni a fajlt! (mentesFajlba)");

	bool ugyfelFajl = f.find("_ufl.txt") != std::string::npos;
	bool autoFajl = f.find("_auo.txt") != std::string::npos;
	if (!ugyfelFajl && !autoFajl) throw std::invalid_argument("Ismeretlen fajlformatum! (mentesFajlba)");

	if (ugyfelFajl) {
		for (const auto& ugyfelObj : ugyfelek) {
			fp << reverse_trim(ugyfelObj.getNev()) << "-"
				<< reverse_trim(ugyfelObj.getTelefonszam()) << "-"
				<< ugyfelObj.getEmail() << '\n';
		}
	}
	else if (autoFajl) {
		for (const auto& autoObj : autok) {
			fp << autoObj.getRendszam() << "-"
				<< reverse_trim(autoObj.getMarka()) << "-"
				<< reverse_trim(autoObj.getTipus()) << "-"
				<< autoObj.getKmOra() << "-"
				<< autoObj.getUzembeHelyezes().toString() << "-";

			const Vector<VegzettMuvelet*> muveletek = autoObj.getSzervizMuveletek();
			if (muveletek.empty()) {
				fp << "nincs";
			}
			else {
				for (size_t i = 0; i < muveletek.size(); i++) {
					const VegzettMuvelet* m = muveletek[i];
					std::string tipusBetu;

					if (dynamic_cast<const Javitas*>(m)) tipusBetu = "J";
					else if (dynamic_cast<const Karbantartas*>(m)) tipusBetu = "K";
					else if (dynamic_cast<const Vizsga*>(m)) tipusBetu = "V";
					else throw std::runtime_error("Ismeretlen muvelet tipus a mentesFajlba fuggvenyben! (mentesFajlba)");

					fp << tipusBetu << ":"
						<< reverse_trim(m->getMuvelet()) << ","
						<< m->getDatum().toString() << ","
						<< m->getAr() << ","
						<< m->getAktKmOra();

					if (const auto* vizsga = dynamic_cast<const Vizsga*>(m)) {
						fp << "," << (vizsga->getSikeres() ? "sikeres" : "sikertelen");
					}

					if (i < muveletek.size() - 1) fp << ";";
				}
			}

			// Tulajdonos ellenorzes
			if (autoObj.getTulajdonos() == nullptr) {
				throw std::runtime_error("Auto tulajdonosa nullptr! Hibas adatstruktura. (mentesFajlba)");
			}

			fp << "-" << reverse_trim(autoObj.getTulajdonos()->getNev()) << '\n';
		}
	}

	fp.close();
}