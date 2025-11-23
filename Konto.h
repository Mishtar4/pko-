#ifndef KONTO_H
#define KONTO_H

#include <string>
using namespace std;

// --- Dane konta powiazanego z klientem ---
class Konto {
private:
    double saldo;
    string waluta;
    string ostatniaOperacja;

public:

    // --- Konstruktor ---
    Konto(double s = 0, string w = "PLN", string o = "Brak operacji.");

    // --- Settery ---
    void setSaldo(double s);
    void setWaluta(string w);
    void setOstatniaOperacja(string o);
    void setKonto(double s, string w, string o);

    // --- Gettery ---
    double getSaldo();
    string getWaluta();
    string getOstatniaOperacja();

    // --- Usunięcie zerówek na końcu liczby ---
    string trimZeros(double value);

    // --- Dodanie przychodu ---
    void dodajPrzychod();

    // --- Dodanie wydatku ---
    void dodajWydatek();

    // --- Wyswietlanie stanu konta ---
    void pokazSaldo();

    // --- Zmiana waluty konta ---
    void zmienWalute();
};

#endif //KONTO_H