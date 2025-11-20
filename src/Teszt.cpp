/**
*   \file Teszt.cpp
*   Ez a fajl a program alapveto funkcioinak teszteleset vegzi.
*   A modul ellenorzi, hogy a rendszer fobb kepessegei helyesen mukodnek, es segit a hibak kiszureseben a fejlesztes soran.
*/

#include "Gtest_lite.h"

#include "SzervizNyilvantartoRendszer.h"
#include "MainSegedFuggvenyek.h"
#include "Teszt.h"
#include "Javitas.h"
#include "Karbantartas.h"
#include "Vizsga.h"

/// Ellenorzi, hogy a megadott fajl letezik-e.
/// @param f - A vizsgalt fajl neve (eleresi utvonal is lehet).
/// @return - true, ha a fajl letezik, kulonben false.
bool tesztDBLetrehozas(SzervizNyilvantartoRendszer& aDB) {
    try {
        aDB.betoltesFajlbol("init_ugyfel_ufl.txt");
        aDB.betoltesFajlbol("init_auto_auo.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Hiba tortent a fajl beolvasasakor: " << e.what() << std::endl;
        return false;
    }
    return true;
}

/// A megadott int erteket unsigned int-re konvertalja.
unsigned int fromIntToUnsigned(int x) {
    return static_cast<unsigned int>(x);
}

/// A megadott size_t erteket unsigned int-re konvertalja.
unsigned int fromSizetToUnsigned(size_t x) {
    return static_cast<unsigned int>(x);
}

/// A tesztelesi funkciok futtatasara szolgalo fuggveny.
void tesztek() {
    MainSegedFuggvenyei segedFuggvenyekEleresehez;

    TEST(Listazas, UgyfelekEsAutok) {
        SzervizNyilvantartoRendszer aDB;

        aDB.ujUgyfel(Ugyfel("Kiss Bela", "+36 20 991 8873", "Budapest"));
        aDB.ujAuto(Auto("ANA406", "Toyota", "Corolla", 123000, Datum(2020, 5, 12), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Kiss Bela")));

        EXPECT_EQ(fromSizetToUnsigned(aDB.getUgyfelek().size()), 1u);
        EXPECT_EQ(fromSizetToUnsigned(aDB.getAutok().size()), 1u);
        EXPECT_EQ(aDB.keresAuto("ANA406").getMarka(), "Toyota");
    } END

    TEST(UjFelvetel, UgyfelEsAuto) {
        SzervizNyilvantartoRendszer aDB;
        Ugyfel ugyfel("Nagy Eva", "+36 20 441 0102", "nagyeva2001@gmail.com");

        aDB.ujUgyfel(ugyfel);
        aDB.ujAuto(Auto("XYZ789", "Opel", "Astra", 152000, Datum(2021, 3, 15), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Nagy Eva")));

        EXPECT_TRUE(aDB.vanUgyfel("Nagy Eva"));
        EXPECT_TRUE(aDB.vanAuto("XYZ789"));
        EXPECT_EQ(aDB.keresUgyfel("Nagy Eva").getTelefonszam(), "+36 20 441 0102");
    } END

    TEST(Frissites, UgyfelEsAuto) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Szabo Anna", "+36 70 779 9514", "anuskacsa@freemail.com"));

        Auto auto1("ABC123", "Ford", "Focus", 80000, Datum(2022, 6, 10), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Szabo Anna"));
        aDB.ujAuto(auto1);

        auto1.setKmOra(80500);
        EXPECT_TRUE(aDB.frissitAuto(auto1));
        EXPECT_EQ(fromIntToUnsigned(aDB.keresAuto("ABC123").getKmOra()), 80500u);
    } END

    TEST(Torles, UgyfelEsAuto) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Teszt Elek", "+36 30 111 2121", "elek-tesztel@gmail.com"));
        aDB.ujAuto(Auto("ABC123", "Toyota", "Corolla", 123456, Datum(2023, 1, 1), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Teszt Elek")));

        EXPECT_TRUE(aDB.torolUgyfel("Teszt Elek"));
        EXPECT_FALSE(aDB.vanUgyfel("Teszt Elek"));
        EXPECT_TRUE(aDB.torolAuto("ABC123") || !aDB.vanAuto("ABC123"));
    } END

    TEST(Szerviz, Rogzites) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Lakatos Bela", "+36 20 420 6969", "lakatosbelosz889@edu.bme.hu"));
        aDB.ujAuto(Auto("GHI789", "Suzuki", "Swift", 789456, Datum(2021, 11, 5), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Lakatos Bela")));

        Vizsga vizsga("Olajcsere", Datum(2025, 4, 20), 35000, 1500, true);

        EXPECT_TRUE(aDB.rogzitesVegzettMuvelet("GHI789", vizsga));
        EXPECT_EQ(fromSizetToUnsigned(aDB.keresAuto("GHI789").getSzervizMuveletek().size()), 1u);
    } END

    TEST(Kereses, UgyfelNevAlapjan) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Kovacs Anna", "+36 50 897 0012", "minecraft.mester20@outlook.com"));

        EXPECT_TRUE(aDB.vanUgyfel("Kovacs Anna"));
        EXPECT_EQ(aDB.keresUgyfel("Kovacs Anna").getTelefonszam(), "+36 50 897 0012");
    } END

    TEST(Kereses, AutoRendszamAlapjan) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Fekete Bela", "+36 50 666 7777", "fekete.vagyok@gmail.com"));
        aDB.ujAuto(Auto("XYZ789", "Honda", "Civic", 54321, Datum(2024, 2, 15), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Fekete Bela")));

        EXPECT_TRUE(aDB.vanAuto("XYZ789"));
        EXPECT_EQ(aDB.keresAuto("XYZ789").getTipus(), "Civic");
    } END

    TEST(Frissites, UgyfelAutoModositas) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Toth Jozsef", "+36 30 450 6721", "jozsikacaj@edu.bme.hu"));
        aDB.ujAuto(Auto("DEF456", "Opel", "Astra", 222222, Datum(2022, 5, 20), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Toth Jozsef")));

        EXPECT_TRUE(aDB.frissitUgyfel(Ugyfel("Toth Jozsef", "+36 30 450 6721", "jozsika-toth@gamil.com")));
        EXPECT_EQ(aDB.keresUgyfel("Toth Jozsef").getEmail(), "jozsika-toth@gamil.com");

        Auto modositott("DEF456", "Opel", "Astra G", 333333, Datum(2024, 3, 1), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Toth Jozsef"));
        EXPECT_TRUE(aDB.frissitAuto(modositott));
        EXPECT_EQ(aDB.keresAuto("DEF456").getTipus(), "Astra G");
    } END

    TEST(Szerviz, Listazas) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Balogh Emese", "+36 70 661 3501", "meseloemese41@gamergirl.com"));
        aDB.ujAuto(Auto("LMN321", "Mazda", "3", 120000, Datum(2022, 6, 6), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Balogh Emese")));

        Vizsga sz1("Vizsga 1", Datum(2025, 1, 15), 50000, 2000, true);
        Karbantartas sz2("Fekcsere", Datum(2025, 3, 10), 60000, 3000);

        EXPECT_TRUE(aDB.rogzitesVegzettMuvelet("LMN321", sz1));
        EXPECT_TRUE(aDB.rogzitesVegzettMuvelet("LMN321", sz2));

        const Vector<VegzettMuvelet*>& muveletek = aDB.keresAuto("LMN321").getSzervizMuveletek();
        EXPECT_EQ(fromSizetToUnsigned(muveletek.size()), 2u);
        EXPECT_EQ(muveletek[0]->getMuvelet(), "Vizsga 1");
        EXPECT_EQ(muveletek[1]->getMuvelet(), "Fekcsere");
    } END

    TEST(MuveletTorles, EgyMuveletTorlese) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Simon Gabor", "+36 20 555 7117", "sonka.gusztav-simon@gmail.com"));
        aDB.ujAuto(Auto("TTT123", "Renault", "Clio", 50000, Datum(2023, 7, 7), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Simon Gabor")));

        Vizsga vizsga1("Muszaki Vizsga", Datum(2025, 5, 1), 100000, 5000, true);
        Karbantartas karb1("Olajcsere", Datum(2025, 5, 2), 105000, 3000);

        aDB.rogzitesVegzettMuvelet("TTT123", vizsga1);
        aDB.rogzitesVegzettMuvelet("TTT123", karb1);

        EXPECT_EQ(fromSizetToUnsigned(aDB.keresAuto("TTT123").getSzervizMuveletek().size()), 2u);
        EXPECT_TRUE(aDB.torolMuvelet("TTT123", Datum(2025, 5, 2)));
        EXPECT_EQ(fromSizetToUnsigned(aDB.keresAuto("TTT123").getSzervizMuveletek().size()), 1u);
        EXPECT_EQ(aDB.keresAuto("TTT123").getSzervizMuveletek()[0]->getMuvelet(), "Muszaki Vizsga");
    } END

    TEST(SzervizMuveletTipusok, VizsgaEsKarbantartas) {
        SzervizNyilvantartoRendszer aDB;
        aDB.ujUgyfel(Ugyfel("Varga Noemi", "+36 20 102 3453", "varga.noemi@gmail.com"));
        aDB.ujAuto(Auto("BETA01", "BMW", "320d", 200000, Datum(2022, 9, 1), Vector<VegzettMuvelet*>(), &aDB.keresUgyfel("Varga Noemi")));

        Vizsga vizsga("Kotelezo vizsga", Datum(2025, 2, 2), 250000, 4500, false);
        Karbantartas karb("Fekolaj csere", Datum(2025, 2, 5), 255000, 2200);

        EXPECT_TRUE(aDB.rogzitesVegzettMuvelet("BETA01", vizsga));
        EXPECT_TRUE(aDB.rogzitesVegzettMuvelet("BETA01", karb));

        const Vector<VegzettMuvelet*>& muvek = aDB.keresAuto("BETA01").getSzervizMuveletek();
        EXPECT_EQ(fromSizetToUnsigned(muvek.size()), 2u);
        EXPECT_TRUE(dynamic_cast<Vizsga*>(muvek[0]) != nullptr || dynamic_cast<Karbantartas*>(muvek[0]) != nullptr);
        EXPECT_TRUE(dynamic_cast<Vizsga*>(muvek[1]) != nullptr || dynamic_cast<Karbantartas*>(muvek[1]) != nullptr);
    } END

    segedFuggvenyekEleresehez.varakozasEnterre("\nNyomj Entert a folytatashoz...");
    segedFuggvenyekEleresehez.torolKonzol();
}