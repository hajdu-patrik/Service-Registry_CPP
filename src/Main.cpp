/**
 *  \file Main.cpp
 *  Ez a fajl az autoszerviz nyilvantarto rendszer belepesi pontja.
 */

#include "Applikacio.h"

int main() {
    Applikacio app;
    if (app.applikacio()) {
        return 0; // korrekt kilépés
    }
    return 0;  // szintén korrekt, de redundáns
}