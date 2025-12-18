#ifndef GTEST_LITE_H
#define GTEST_LITE_H

/**
 * \file gtest_lite.h  (v3/2019)
 *
 * Google gtest keretrendszerhez hasonlo rendszer.
 * Sz.I. 2015., 2016., 2017. (_Has_X)
 * Sz.I. 2018 (template), ENDM, ENDMsg, nullptr_t
 * Sz.I. 2019 singleton
 * Sz.I. 2021 ASSERT.., STRCASE...
 * Sz.I. 2021 EXPEXT_REGEXP
 *
 * A teszteles legalapvetõbb funkcioit tamogato fuggvenyek es makrok.
 * Nem szalbiztos megvalositas.
 *
 *
 * Szabadon felhasznalhato, bõvithetõ.
 *
 * Hasznalati pelda:
 *   Teszteljuk az f(x)=2*x fuggvenyt:
 * int f(int x) { return 2*x; }
 *
 * int main() {
 *   TEST(TeszEsetNeve, TesztNeve)
 *     EXPECT_EQ(0, f(0));
 *     EXPECT_EQ(4, f(2)) << "A fuggveny hibas eredmenyt adott" << std::endl;
 *     ...
 *   END
 * ...
 * // Fatalis hiba eseten a teszteset nem fut tovabb. Ezek az ASSERT... makrok.
 * // Nem lehet a kiirasukhoz tovabbi uzenetet fûzni. PL:
 *   TEST(TeszEsetNeve, TesztNeve)
 *     ASSERT_NO_THROW(f(0));  // itt nem lehet << "duma"
 *     EXPECT_EQ(4, f(2)) << "A fuggveny hibas eredmenyt adott" << std::endl;
 *     ...
 *   END
 *  ...
 *
 * A mûkodes reszleteinek megertese szorgalmi feladat.
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <cstdlib>
#include <string>
#include <fstream>
#if __cplusplus >= 201103L
# include <iterator>
# include <regex>
#endif
#ifdef MEMTRACE
# include "memtrace.h"
#endif

 // Ket makro az egyes tesztek ele es moge:
 // A ket makro a kapcsos zarojelekkel egy uj blokkot hoz letre, amiben
 // a nevek lokalisak, igy elkerulhetõ a nevutkozes.

 /// Teszt kezdete. A makro parameterezese hasonlit a gtest
 /// parameterezesehez. igy az itt elkeszitett testek konnyen atemelhetõk
 /// a gtest keretrendszerbe.
 /// @param C - teszteset neve (csak a gtest kompatibilitas miatt van kulon neve az eseteknek)
 /// @param N - teszt neve
#define TEST(C, N) do { gtest_lite::test.begin(#C"."#N);

/// Teszteset vege.
#define END gtest_lite::test.end(); } while (false);

/// Teszteset vege allokalt blokkok szamanak osszehasonlitasaval
/// Ez az ellenõrzes nem bomba biztos.
#define ENDM gtest_lite::test.end(true); } while (false);

/// Teszteset vege allokalt blokkok szamanak osszehasonlitasaval
/// Ez az ellenõrzes nem bomba biztos.
/// Ha hiba van kiirja az uzenetet.
#define ENDMsg(t) gtest_lite::test.end(true) << t << std::endl; } while (false);

// Eredmenyek vizsgalatat segitõ makrok.
// A parameterek es a funkciok a gtest keretrendszerrel megegyeznek.

/// Sikeres teszt makroja
#define SUCCEED() gtest_lite::test.expect(true, __FILE__, __LINE__, "SUCCEED()", true)

/// Sikertelen teszt fatalis hiba makroja
#define FAIL() gtest_lite::test.expect(false, __FILE__, __LINE__, "FAIL()", true)

/// Sikertelen teszt makroja
#define ADD_FAILURE() gtest_lite::test.expect(false, __FILE__, __LINE__, "ADD_FAILURE()", true)

/// Azonossagot elvaro makro
#define EXPECT_EQ(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::eq, __FILE__, __LINE__, "EXPECT_EQ(" #expected ", " #actual ")" )

/// Elterest elvaro makro
#define EXPECT_NE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::ne, __FILE__, __LINE__, "EXPECT_NE(" #expected ", " #actual ")", "etalon" )

/// Kisebb, vagy egyenlõ relaciot elvaro makro
#define EXPECT_LE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::le, __FILE__, __LINE__, "EXPECT_LE(" #expected ", " #actual ")", "etalon" )

/// Kisebb, mint relaciot elvaro makro
#define EXPECT_LT(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::lt, __FILE__, __LINE__, "EXPECT_LT(" #expected ", " #actual ")", "etalon" )

/// Nagyobb, vagy egyenlõ relaciot elvaro makro
#define EXPECT_GE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::ge, __FILE__, __LINE__, "EXPECT_GE(" #expected ", " #actual ")", "etalon" )

/// Nagyobb, mint relaciot elvaro makro
#define EXPECT_GT(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::gt, __FILE__, __LINE__, "EXPECT_GT(" #expected ", " #actual ")", "etalon" )

/// Igaz erteket elvaro makro
#define EXPECT_TRUE(actual)  gtest_lite::EXPECT_(true, actual,  gtest_lite::eq, __FILE__, __LINE__, "EXPECT_TRUE(" #actual ")" )

/// Hamis erteket elvaro makro
#define EXPECT_FALSE(actual) gtest_lite::EXPECT_(false, actual, gtest_lite::eq, __FILE__, __LINE__, "EXPECT_FALSE(" #actual ")" )

/// Valos szamok azonossagat elvaro makro
#define EXPECT_FLOAT_EQ(expected, actual)  gtest_lite::EXPECT_(expected, actual, gtest_lite::almostEQ, __FILE__, __LINE__, "EXPECT_FLOAT_EQ(" #expected ", " #actual ")" )

/// Valos szamok azonossagat elvaro makro
#define EXPECT_DOUBLE_EQ(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::almostEQ, __FILE__, __LINE__, "EXPECT_DOUBLE_EQ(" #expected ", " #actual ")" )

/// C stringek (const char *) azonossagat tesztelõ makro
#define EXPECT_STREQ(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::eqstr, __FILE__, __LINE__, "EXPECT_STREQ(" #expected ", " #actual ")" )

/// C stringek (const char *) eltereset tesztelõ makro
#define EXPECT_STRNE(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::nestr, __FILE__, __LINE__, "EXPECT_STRNE(" #expected ", " #actual ")", "etalon" )

/// C stringek (const char *) azonossagat tesztelõ makro (kisbetû/nagybetû azonos)
#define EXPECT_STRCASEEQ(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::eqstrcase, __FILE__, __LINE__, "EXPECT_STRCASEEQ(" #expected ", " #actual ")" )

/// C stringek (const char *) eltereset tesztelõ makro (kisbetû/nagybetû azonos)
#define EXPECT_STRCASENE(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::nestrcase, __FILE__, __LINE__, "EXPECT_STRCASENE(" #expected ", " #actual ")", "etalon" )

/// Kivetelt varunk
#define EXPECT_THROW(statement, exception_type) try { gtest_lite::test.tmp = false; statement; } \
    catch (exception_type) { gtest_lite::test.tmp = true; } \
    catch (...) { } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott '"#exception_type"' kivetelt.")

/// Kivetelt varunk
#define EXPECT_ANY_THROW(statement) try { gtest_lite::test.tmp = false; statement; } \
    catch (...) { gtest_lite::test.tmp = true; } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott kivetelt.")

/// Nem varunk kivetelt
#define EXPECT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    EXPECTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")

/// Nem varunk kivetelt
#define ASSERT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    ASSERTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")

/// Kivetelt varunk es tovabbdobjuk -- ilyen nincs a gtest-ben
#define EXPECT_THROW_THROW(statement, exception_type) try { gtest_lite::test.tmp = false; statement; } \
    catch (exception_type) { gtest_lite::test.tmp = true; throw; } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott '"#exception_type"' kivetelt.")

/// Kornyezeti valtozohoz hasonlit -- ilyen nincs a gtest-ben
#define EXPECT_ENVEQ(expected, actual) gtest_lite::EXPECTSTR(std::getenv(expected), actual, gtest_lite::eqstr, __FILE__, __LINE__, "EXPECT_ENVEQ(" #expected ", " #actual ")" )

/// Kornyezeti valtozohoz hasonlit -- ilyen nincs a gtest-ben (kisbetû/nagybetû azonos)
#define EXPECT_ENVCASEEQ(expected, actual) gtest_lite::EXPECTSTR(std::getenv(expected), actual, gtest_lite::eqstrcase, __FILE__, __LINE__, "EXPECT_ENVCASEEQ(" #expected ", " #actual ")" )

#if __cplusplus >= 201103L
/// Regularis kifejezes illesztese
# define EXPECT_REGEXP(expected, actual, match, err) gtest_lite::EXPECTREGEXP(expected, actual, match, err, __FILE__, __LINE__, "EXPECT_REGEXP(" #expected ", " #actual ", " #match ")" )
#endif
////--------------------------------------------------------------------------------------------
/// ASSERT tipusu ellenõrzesek. CSak 1-2 van megvalositva. Nem ostream& -val ternek vissza !!!
/// Kivetelt varunk

/// Azonossagot elvaro makro
#define ASSERT_EQ(expected, actual) gtest_lite::ASSERT_(expected, actual, gtest_lite::eq, "ASSER_EQ")

/// Nem varunk kivetelt
#define ASSERT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    ASSERTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")


/// Segedmakro egy adattag, vagy tagfuggveny letezesenek tesztelesere futasi idõben
/// otlet:
/// https://cpptalk.wordpress.com/2009/09/12/substitution-failure-is-not-an-error-2
/// Hasznalat:
/// CREATE_Has_(size)
/// ... if (Has_size<std::string>::member)...
#define CREATE_Has_(X) \
template<typename T> struct _Has_##X {  \
    struct Fallback { int X; };         \
    struct Derived : T, Fallback {};    \
    template<typename C, C> struct ChT; \
    template<typename D> static char (&f(ChT<int Fallback::*, &D::X>*))[1]; \
    template<typename D> static char (&f(...))[2]; \
    static bool const member = sizeof(f<Derived>(0)) == 2; \
};

/// Segedfuggveny egy publikus adattag, vagy tagfuggveny letezesenek tesztelesere
/// forditasi idõben
inline void hasMember(...) {}

/// Segedsablon tipuskonverzio futas kozbeni ellenõrzesere
template <typename F, typename T>
struct _Is_Types {
    template<typename D> static char(&f(D))[1];
    template<typename D> static char(&f(...))[2];
    static bool const convertable = sizeof(f<T>(F())) == 1;
};

/// -----------------------------------
/// Belsõ megvalositashoz tartozo makrok, es osztalyok.
/// Nem celszerû kozvetlenul hasznalni, vagy modositani
/// -----------------------------------

/// EXPECTTHROW: kivetelkezeles
#define EXPECTTHROW(statement, exp, act) gtest_lite::test.expect(gtest_lite::test.tmp, __FILE__, __LINE__, #statement) \
    << "** Az utasitas " << (act) \
    << "\n** Azt vartuk, hogy " << (exp) << std::endl

#define ASSERTTHROW(statement, exp, act) gtest_lite::test.expect(gtest_lite::test.tmp, __FILE__, __LINE__, #statement) \
    << "** Az utasitas " << (act) \
    << "\n** Azt vartuk, hogy " << (exp) << std::endl; if (!gtest_lite::test.status) { gtest_lite::test.end(); break; }

#define ASSERT_(expected, actual, fn, op) EXPECT_(expected, actual, fn, __FILE__, __LINE__, #op "(" #expected ", " #actual ")" ); \
    if (!gtest_lite::test.status) { gtest_lite::test.end(); break; }

#ifdef CPORTA
#define GTINIT(is)  \
    int magic;      \
    is >> magic;
#else
#define GTINIT(IS)
#endif // CPORTA

#ifdef CPORTA
#define GTEND(os)  \
    os << magic << (gtest_lite::test.fail() ? " NO" : " OK?") << std::endl;
#else
#define GTEND(os)
#endif // CPORTA

/// gtest_lite: a keretrendszer fuggvenyinek es objektumainak nevtere
namespace gtest_lite {

    /// Tesztek allapotat tarolo osztaly.
    /// Egyetlen egy statikus peldany keletkezik, aminek a
    /// destruktora a futas vegen hivodik meg.
    struct Test {
        int sum;            ///< tesztek szamlaloja
        int failed;         ///< hibas tesztek
        int ablocks;        ///< allokalt blokkok szama
        bool status;        ///< eppen futo teszt statusza
        bool tmp;           ///< temp a kivetelkezeleshez;
        std::string name;   ///< eppen futo teszt neve
        std::fstream null;  ///< nyelõ, ha nem kell kiirni semmit
        static Test& getTest() {
            static Test instance;///< egyeduli (singleton) peldany
            return instance;
        }
    private:    /// singleton minta miatt
        Test() :sum(0), failed(0), status(false), null("/dev/null") {}
        Test(const Test&);
        void operator=(const Test&);
    public:
        /// Teszt kezdete
        void begin(const char* n) {
            name = n; status = true;
#ifdef MEMTRACE
            ablocks = memtrace::allocated_blocks();
#endif
#ifndef CPORTA
            std::cerr << "\n---> " << name << std::endl;
#endif // CPORTA
            ++sum;
        }
        /// Teszt vege
        std::ostream& end(bool memchk = false) {
#ifdef MEMTRACE
            if (memchk && ablocks != memtrace::allocated_blocks()) {
                status = false;
                return std::cerr << "** Lehet, hogy nem szabaditott fel minden memoriat! **" << std::endl;
            }
#endif
#ifdef CPORTA
            if (!status)
#endif // CPORTA
                std::cerr << (status ? "     SIKERES" : "** HIBAS ****") << "\t" << name << " <---" << std::endl;
            if (!status)
                return std::cerr;
            else
                return null;
        }

        bool fail() { return failed; }

        bool astatus() { return status; }

        /// Eredmenyt adminisztralo tagfuggveny True a jo eset.
        std::ostream& expect(bool st, const char* file, int line, const char* expr, bool pr = false) {
            if (!st) {
                ++failed;
                status = false;
            }
            if (!st || pr) {
                std::string str(file);
                size_t i = str.rfind("\\");
                if (i == std::string::npos) i = str.rfind("/");
                if (i == std::string::npos) i = 0; else i++;
                return std::cerr << "\n**** " << &file[i] << "(" << line << "): " << expr << " ****" << std::endl;
            }
            return null;
        }

        /// Destruktor
        ~Test() {
#ifdef CPORTA
            if (failed)
#endif // CPORTA
                std::cerr << "\n==== TESZT VEGE ==== HIBAS/OSSZES: " << failed << "/" << sum << std::endl;
        }
    };

    /// A statikus referencia minden forditasi egysegben keletkezik, de
    /// mindegyik egyetlen peldanyra fog hivatkozni a singleton minta miatt
    static Test& test = Test::getTest();

    /// altalanos sablon a vart ertekhez.
    template <typename T1, typename T2>
    std::ostream& EXPECT_(T1 exp, T2 act, bool (*pred)(T1, T2), const char* file, int line,
        const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << std::boolalpha << exp
            << "\n** " << rhs << ": " << std::boolalpha << act << std::endl;
    }

    /// pointerre specializalt sablon a vart ertekhez.
    template <typename T1, typename T2>
    std::ostream& EXPECT_(T1* exp, T2* act, bool (*pred)(T1*, T2*), const char* file, int line,
        const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << (void*)exp
            << "\n** " << rhs << ": " << (void*)act << std::endl;
    }

#if __cplusplus >= 201103L
    /// nullptr-re specializalt sablon a vart ertekhez.
    template <typename T1>
    std::ostream& EXPECT_(T1* exp, std::nullptr_t act, bool (*pred)(T1*, std::nullptr_t), const char* file, int line,
        const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << (void*)exp
            << "\n** " << rhs << ": " << (void*)act << std::endl;
    }
#endif

    /// stringek osszehasonlitasahoz.
    /// azert nem spec. mert a sima EQ-ra maskent kell mûkodnie.
    inline
        std::ostream& EXPECTSTR(const char* exp, const char* act, bool (*pred)(const char*, const char*), const char* file, int line,
            const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << (exp == NULL ? "NULL pointer" : std::string("\"") + exp + std::string("\""))
            << "\n** " << rhs << ": " << (act == NULL ? "NULL pointer" : std::string("\"") + act + std::string("\"")) << std::endl;
    }

#if __cplusplus >= 201103L
    /// regexp osszehasonlitashoz.
    template <typename E, typename S>
    int count_regexp(E exp, S str) {
        std::regex rexp(exp);
        auto w_beg = std::sregex_iterator(str.begin(), str.end(), rexp);
        auto w_end = std::sregex_iterator();
        return std::distance(w_beg, w_end);
    }

    template <typename E, typename S>
    std::ostream& EXPECTREGEXP(E exp, S str, int match, const char* err, const char* file, int line,
        const char* expr, const char* lhs = "regexp", const char* rhs = "string",
        const char* m = "elvart/illeszkedik") {
        int cnt = count_regexp(exp, str);
        if (match < 0) match = cnt;
        return test.expect(cnt == match, file, line, expr)
            << "** " << lhs << ": " << std::string("\"") + exp + std::string("\"")
            << "\n** " << rhs << ": " << (err == NULL ? std::string("\"") + str + std::string("\"") : err)
            << "\n** " << m << ": " << match << "/" << cnt << std::endl;
    }
#endif

    /// seged sablonok a relaciokhoz.
    /// azert nem STL (algorithm), mert csak a fuggveny lehet, hogy menjen a deduckcio
    template <typename T1, typename T2>
    bool eq(T1 a, T2 b) { return a == b; }

    inline
        bool eqstr(const char* a, const char* b) {
        if (a != NULL && b != NULL)
            return strcmp(a, b) == 0;
        return false;
    }

    inline
        bool eqstrcase(const char* a, const char* b) {
        if (a != NULL && b != NULL) {
            while (toupper(*a) == toupper(*b) && *a != '\0') {
                a++;
                b++;
            }
            return *a == *b;
        }
        return false;

    }

    template <typename T1, typename T2>
    bool ne(T1 a, T2 b) { return a != b; }

    inline
        bool nestr(const char* a, const char* b) {
        if (a != NULL && b != NULL)
            return strcmp(a, b) != 0;
        return false;
    }

    template <typename T1, typename T2>
    bool le(T1 a, T2 b) { return a <= b; }

    template <typename T1, typename T2>
    bool lt(T1 a, T2 b) { return a < b; }

    template <typename T1, typename T2>
    bool ge(T1 a, T2 b) { return a >= b; }

    template <typename T1, typename T2>
    bool gt(T1 a, T2 b) { return a > b; }

    /// Segedsablon valos szamok osszehasonlitasahoz
    /// Nem bombabiztos, de nekunk most jo lesz
    /// Elmeleti hater:
    /// http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
    template <typename T>
    bool almostEQ(T a, T  b) {
        // eps: ha a relativ, vagy abszolut hiba ettõl kisebb, akkor elfogadjuk
        T eps = 10 * std::numeric_limits<T>::epsilon(); // 10-szer a legkisebb ertek
        if (a == b) return true;
        if (fabs(a - b) < eps)
            return true;
        double aa = fabs(a);
        double ba = fabs(b);
        if (aa < ba) {
            aa = ba;
            ba = fabs(a);
        }
        return (aa - ba) < aa * eps;
    }

} // namespace gtest_lite

#endif // GTEST_LITE_H