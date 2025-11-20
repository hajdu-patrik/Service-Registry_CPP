/**
*	\file MuveletAllapot.h
*   Ez a fajl a menurendszer allapotait definialja.
*/

#ifndef MUVELETALLAPOT_H
#define MUVELETALLAPOT_H

/// A muvelet vegrehajtasanak allapotat jelzo enum.
enum class MuveletAllapot {
    Siker,
    Kilepes,
    Hiba
};

#endif // !MUVELETALLAPOT_H