#ifndef KONTO_H
#define KONTO_H

#include <string>
#include <vector>
using namespace std;

// --- Dane konta powiazanego z klientem ---
class Konto {
private:
    double saldo;
    string waluta;
    string ostatniaOperacja;
    vector<string> wyciagOperacji;
public:

    // --- Konstruktor ---
    Konto(double s = 0, string w = "PLN", string o = "Brak operacji.");

    // --- Settery ---
    void setKonto(double s, string w, string o, const vector<string>& wo);

    // --- Gettery ---
    double getSaldo() const;
    string getWaluta() const;
    string getOstatniaOperacja() const;
    vector<string> getWyciagOperacji() const;

    // --- Usunięcie zerówek na końcu liczby ---
    string trimZeros(double value);

    // --- Dodanie przychodu ---
    void dodajPrzychod();

    // --- Dodanie wydatku ---
    void dodajWydatek();

    // --- Wyswietlanie stanu konta ---
    void pokazSaldo() const;

    // --- Wyciąg wszystkich operacji na koncie kliental ---
    void wyciagWszystkichOperacji() const;

    // --- Zmiana waluty konta ---
    void zmienWalute();
};

#endif //KONTO_H