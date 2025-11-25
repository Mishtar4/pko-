#include "Konto.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// --- Konstruktor ---
Konto::Konto(double s, string w, string o) : saldo(s), waluta(w), ostatniaOperacja(o) {}

// --- Settery ---
void Konto::setKonto(double s, string w, string o, vector<string> wyciag) {
    saldo = s;
    waluta = w;
    ostatniaOperacja = o;
    wyciagOperacji = wyciag;
};

// --- Gettery ---
double Konto::getSaldo() {return saldo;}
string Konto::getWaluta() {return waluta;}
string Konto::getOstatniaOperacja() {return ostatniaOperacja;}
vector<string> Konto::getWyciagOperacji() {return wyciagOperacji;}

// --- Usunięcie zerówek na końcu liczby ---
string Konto::trimZeros(double value) {
    string s = to_string(value);

    // Usuwamy zbędne zera z końca
    s.erase(s.find_last_not_of('0') + 1, string::npos);

    // Jeśli na końcu pozostała kropka — usunąć
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }

    return s;
}

// --- Dodanie przychodu ---
void Konto::dodajPrzychod() {
    cout << "Podaj kwote przychodu: " << endl;
    double kwota;
    cin >> kwota;
    saldo += kwota;
    ostatniaOperacja = "Dodano przychod: " + trimZeros(kwota) + " " + waluta;
    wyciagOperacji.push_back(ostatniaOperacja);
    cout << ostatniaOperacja << endl;
}

// --- Dodanie wydatku ---
void Konto::dodajWydatek()
{
    cout << "Podaj kwote wydatku: " << endl;
    double kwota;
    cin >> kwota;
    if (saldo - kwota < 0) {cout << "Brak srodkow!" << endl;}
    else
    {
        saldo -= kwota;
        ostatniaOperacja = "Dodano wydatek: " + trimZeros(kwota) + " " + waluta;
        wyciagOperacji.push_back(ostatniaOperacja);
        cout << ostatniaOperacja << endl;
    }
}

// --- Wyswietlanie stanu konta ---
void Konto::pokazSaldo()
{
    cout << "===KONTO===\nTwoje saldo: " << saldo << " " << waluta << endl;
    cout << "\nOstatnia operacja:\n" << ostatniaOperacja << endl;
}

// --- Wyciąg wszystkich operacji na koncie kliental ---
void Konto::wyciagWszystkichOperacji() {
    vector<string> copy;
    copy = wyciagOperacji;
    cout << "== Wyciag wszystkich operacji == " << endl;
    reverse(copy.begin(), copy.end());
    if (copy.empty()) {cout << "Brak operacji." << endl;}
    for (auto i : copy) {
        cout << i << endl;
    }
}

// --- Zmiana waluty konta ---
void Konto::zmienWalute()
{
    int wybor;
    string stara_waluta = waluta;
    unordered_map<string, unordered_map<string, double>> kurs = {
        {"PLN", {{"EUR", 0.24}, {"USD", 0.27}, {"UAH", 11.49}}},
        {"EUR", {{"PLN", 4.24}, {"USD", 1.15}, {"UAH", 48.67}}},
        {"USD", {{"PLN", 3.68}, {"EUR", 0.87}, {"UAH", 42.25}}},
        {"UAH", {{"PLN", 0.087}, {"EUR", 0.021}, {"USD", 0.024}}}
    };
    cout << "(1.PLN, 2.EUR, 3.USD, 4.UAH)\nWybor: ";
    cin >> wybor;
    switch (wybor) {
        case 1: {waluta = "PLN"; break;}
        case 2: {waluta = "EUR"; break;}
        case 3: {waluta = "USD"; break;}
        case 4: {waluta = "UAH"; break;}
        default: {cout << "Nie ma takiej waluty!" << endl; break;}
    }
    double stare_saldo = saldo;
    saldo *= kurs[stara_waluta][waluta];
    ostatniaOperacja = "Konwertacja: " + trimZeros(stare_saldo) + " " + stara_waluta + " => " + trimZeros(saldo) + " " + waluta;
    wyciagOperacji.push_back(ostatniaOperacja);
    cout << ostatniaOperacja << endl;
}