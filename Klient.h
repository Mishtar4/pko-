#ifndef KLIENT_H
#define KLIENT_H

#include "Konto.h"
#include <string>
#include <vector>

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
    void pokaz() const;

    // --- Settery imię i problem ---
    void setKlient(string i, string p);

    // --- Settery dla Konto ---
    void setKonto(double s, string w, string o, const vector<string>& wo);

    // --- Gettery dla Klienta ---
    string getImie() const;
    string getProblem() const;

    // --- Gettery dla Konto ---
    double getSaldo() const;
    string getWaluta() const;
    string getOstatniaOperacja() const;
    vector<string> getWyciagOperacji() const;

    // --- Praca z kontem ---
    void dodajPrzychod();
    void dodajWydatek();
    void pokazSaldo() const;
    void wyciagWszystkichOperacji() const;
    void zmienWalute();
};

#endif //KLIENT_H