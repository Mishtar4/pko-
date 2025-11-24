#ifndef CALLCENTER_H
#define CALLCENTER_H

#include <queue>
#include <stack>
#include <string>
#include <vector>
#include "Klient.h"
using namespace std;

class CallCenter {
public:

    // --- Konstruktor ---
    CallCenter(const string& dataDir = "./data/");

    // --- Główna pętla programu ---
    void run();

private:
    queue <Klient> oczekujacy; // FIFO: nowi klienci trafiają na koniec
    stack <Klient> wstrzymani; // LIFO: ostatnio wstrzymany wraca jako pierwszy
    vector <Klient> zakonczone; // log zakończonych rozmów

    bool maAktywna;
    Klient aktywna;
    string dataDir;

    // --- Menu ---
    void pokazMenu();
    void obsluzWybor(int wybor);

    // --- Operacji call centra ---
    void noweZgloszenie();
    void rozpocznijRozmowe();
    void wstrzymajRozmowe();
    void wznowRozmowe();
    void zakonczRozmowe();
    void podgladStanu();
    void dodanieLosowegoKlienta();
    void menuKonta();

    // --- Operacja z plikami ---
    void wczytajKontoJesliIstnieje(Klient& kl, const string& imie);
    void zapiszKontoAktywnego();
};

#endif //CALLCENTER_H