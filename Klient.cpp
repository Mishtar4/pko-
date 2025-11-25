#include "Klient.h"
#include <iostream>
using namespace std;

// --- Konstruktor ---
Klient::Klient(string i, string p) : imie(i), problem(p) {}

// --- Wypisanie imieniu i problemu klienta ---
const void Klient::pokaz() {
    cout << imie << " | problem: " << problem;
}

// --- Settery imię i problem ---
void Klient::setKlient(string i, string p) {
    imie = i;
    problem = p;
}

// --- Settery dla Konto ---
void Klient::setKonto(double s, string w, string o, vector<string> wo) {
    konto.setKonto(s, w, o, wo);
}

// --- Gettery dla Klienta ---
string Klient::getImie() {return imie;}
string Klient::getProblem() {return problem;}

// --- Gettery dla Konto ---
double Klient::getSaldo() {return konto.getSaldo();}
string Klient::getWaluta() {return konto.getWaluta();}
string Klient::getOstatniaOperacja() {return konto.getOstatniaOperacja();}
vector<string> Klient::getWyciagOperacji() {return konto.getWyciagOperacji();}

// --- Praca z kontem ---
void Klient::dodajPrzychod() {konto.dodajPrzychod();}
void Klient::dodajWydatek() {konto.dodajWydatek();}
void Klient::pokazSaldo() {konto.pokazSaldo();}
void Klient::wyciagWszystkichOperacji() {konto.wyciagWszystkichOperacji();}
void Klient::zmienWalute() {konto.zmienWalute();}