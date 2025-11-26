#include "Klient.h"
#include <iostream>

// --- Konstruktor ---
Klient::Klient(string i, string p) : imie(i), problem(p) {}

// --- Wypisanie imieniu i problemu klienta ---
void Klient::pokaz() const {
    cout << imie << " | problem: " << problem;
}

// --- Settery imię i problem ---
void Klient::setKlient(string i, string p) {
    imie = i;
    problem = p;
}

// --- Settery dla Konto ---
void Klient::setKonto(double s, string w, string o, const vector<string>& wo) {
    konto.setKonto(s, w, o, wo);
}

// --- Gettery dla Klienta ---
string Klient::getImie() const {return imie;}
string Klient::getProblem() const {return problem;}

// --- Gettery dla Konto ---
double Klient::getSaldo() const {return konto.getSaldo();}
string Klient::getWaluta() const {return konto.getWaluta();}
string Klient::getOstatniaOperacja() const {return konto.getOstatniaOperacja();}
vector<string> Klient::getWyciagOperacji() const {return konto.getWyciagOperacji();}

// --- Praca z kontem ---
void Klient::dodajPrzychod() {konto.dodajPrzychod();}
void Klient::dodajWydatek() {konto.dodajWydatek();}
void Klient::pokazSaldo() const {konto.pokazSaldo();}
void Klient::wyciagWszystkichOperacji() const {konto.wyciagWszystkichOperacji();}
void Klient::zmienWalute() {konto.zmienWalute();}