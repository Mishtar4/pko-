#ifndef KLIENT_H
#define KLIENT_H

#include "Konto.h"
#include <string>
using namespace std;

// --- Dane podstawowe klienta ---
class Klient {
private:
    string imie;
    string problem;
    Konto konto;

public:

    // --- Konstruktor ---
    Klient(string i = "", string p = "");

    // --- Wypisanie imieniu i problemu klienta ---
    const void pokaz();

    // --- Settery imię i problem ---
    void setKlient(string i, string p);

    // --- Settery dla Konto ---
    void setKonto(double s, string w, string o);

    // --- Gettery dla Klienta ---
    string getImie();
    string getProblem();

    // --- Gettery dla Konto ---
    double getSaldo();
    string getWaluta();
    string getOstatniaOperacja();

    // --- Praca z kontem ---
    void dodajPrzychod();
    void dodajWydatek();
    void pokazSaldo();
    void zmienWalute();
};

#endif //KLIENT_H