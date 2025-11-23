#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include "Klient.h"
using namespace std;

int main() {
    queue <Klient> oczekujacy; // FIFO: nowi klienci trafiają na koniec
    stack <Klient> wstrzymani; // LIFO: ostatnio wstrzymany wraca jako pierwszy
    vector <Klient> zakonczone; // log zakończonych rozmów

    bool maAktywna = false; // czy trwa rozmowa?
    Klient aktywna;
    // aktualnie obsługiwany klient (jeśli jest)

    int wybor;
    while (true) {
        cout << "\n==== CALL CENTER ====\n" <<
        "1. Nowe zgloszenie\n" <<
        "2. Rozpocznij rozmowe (z kolejki)\n" <<
        "3. Wstrzymaj aktywna rozmowe (na stos)\n" <<
        "4. Wznow rozmowe (ze stosu)\n" <<
        "5. Zakoncz aktywna rozmowe\n" <<
        "6. Podglad stanu\n";
        if (maAktywna) {
            cout << "7. Operacja na koncie aktywnego klienta" <<  endl;
        }
        cout << "0. Wyjdz\n" << "Wybor: ";
        cin >> wybor;
        cin.ignore();

        if (!maAktywna && wybor == 7) {
            cout << "Nie ma takiej opcji." << endl;
            continue;
        }
        switch (wybor) {
            case 1: {
                // Nowe zgłoszenie trafia do kolejki
                cout << "Wpisz imie: ";
                string imie;
                getline(cin, imie);

                //Tworzenie nowego klienta
                Klient kl;

                //Sprawdzanie istnienia klienta
                string plik_nazwa = "../data/" + imie + ".txt";
                ifstream file(plik_nazwa);

                //Odczyt stanu konta, jezeli klient istnieje
                if (file.is_open()) {
                    double s;
                    string w, o;
                    file >> s;
                    file.ignore();
                    getline(file, w);
                    getline(file, o);

                    kl.setKonto(s, w, o);

                    file.close();
                }
                cout << "Opisz problem: ";
                string problem;
                getline(cin, problem);
                kl.setKlient(imie, problem);
                oczekujacy.push(kl);
                break;
            }
            case 2: {
                // Rozpocznij rozmowę tylko, jeśli nie ma aktywnej
                if (maAktywna) {
                    cout << "Juz trwa rozmowa!\n";
                }
                else if (oczekujacy.empty()) {
                    cout << "Brak klientow w kolejce.\n";
                }
                else {
                    // Pobieramy klienta z kolejki
                    aktywna = oczekujacy.front();
                    oczekujacy.pop();

                    maAktywna = true;

                    cout << "Rozmowa rozpoczeta: ";
                    aktywna.pokaz();
                    cout << "\n" << endl;
                    aktywna.pokazSaldo();
                    cout << endl;
                }
                break;
            }
            case 3: {
                // Wstrzymaj aktywną (przenieś na stos)
                if (!maAktywna) {
                    cout << "Rozmowa nie trwa!" << endl;
                } else {
                    cout << "Rozmowa z klientem " << aktywna.getImie() << " jest wstrzymana." << endl;
                    wstrzymani.push(aktywna);
                    aktywna = Klient();
                    maAktywna = false;
                }
                break;
            }
            case 4: {
                // Wznów ostatnio wstrzymaną (ze stosu)
                if (maAktywna) {
                    cout << "Juz rozmawiasz. Nie mozesz rozmawiac z obydwoma jednoczesnie!\n";
                } else if (wstrzymani.empty()) {
                    cout << "Brak wstrzymanych rozmow.\n";
                }
                else {
                    aktywna = wstrzymani.top();
                    wstrzymani.pop();
                    maAktywna = true;
                    cout << "Teraz rozmawiasz z ";
                    aktywna.pokaz();
                    cout << endl;
                }
                break;
            }
            case 5: {
                // Zakończ aktywną (zapisz do logu)
                if (!maAktywna) {
                    cout << "Rozmowa nie trwa!" << endl;
                } else {
                    cout << "Rozmowa z " << aktywna.getImie() << " zostala zakonczona." << endl;
                    zakonczone.push_back(aktywna);
                    aktywna = Klient();
                    maAktywna = false;
                }
                break;
            }
            case 6: {
                // Podgląd stanu systemu
                cout << "\n-- Aktywna rozmowa --\n";
                if (!maAktywna) {
                    cout << "Rozmowa nie trwa!" << endl;
                } else {
                    aktywna.pokaz();
                    cout << endl;
                }

                cout << "\n-- Kolejka oczekujacych --\n";
                if (oczekujacy.empty()) {
                    cout << "Brak oczekujacych klientow.\n";
                } else {
                    queue<Klient> kopiaKolejki = oczekujacy;
                    int licznik1 = 1;
                    while (!kopiaKolejki.empty()) {
                        cout << licznik1 << ". ";
                        kopiaKolejki.front().pokaz();
                        cout << endl;
                        kopiaKolejki.pop();
                        licznik1++;
                    }
                }
                cout << "\n-- Stos wstrzymanych --\n";
                if (wstrzymani.empty()) {
                    cout << "Brak wstrzymanych rozmow.\n";
                } else {
                    stack<Klient> kopiaStosu = wstrzymani;
                    int licznik2 = 1;
                    while (!kopiaStosu.empty()) {
                        cout << licznik2 << ". ";
                        kopiaStosu.top().pokaz();
                        cout << endl;
                        kopiaStosu.pop();
                        licznik2++;
                    }
                }

                cout << "\n-- Zakonczone rozmowy -- "  << endl;
                if (zakonczone.empty()) {
                    cout << "Brak zakonczonych rozmow.\n";
                } else {
                    int licznik3 = 1;
                    for (auto x : zakonczone) {
                        cout << licznik3 << ". ";
                        x.pokaz();
                        cout << endl;
                        licznik3++;
                    }
                    cout << endl;
                }
                break;
            }
            case 7: {
                int op;
                bool case5 = false;
                while (true) {
                    cout << "\n==== Operacji z kontem ====\n" <<
                    "1. Dodaj przychod\n" <<
                    "2. Dodaj wydatek\n" <<
                    "3. Pokaz aktualne saldo\n" <<
                    "4. Zmien walute\n" <<
                    "0. Zakoncz dzialanie\n" <<
                    "Wybor: ";
                    cin >> op;
                    switch (op) {
                        case 1: aktywna.dodajPrzychod(); break;
                        case 2: aktywna.dodajWydatek(); break;
                        case 3: aktywna.pokazSaldo(); break;
                        case 4: aktywna.zmienWalute(); break;
                        case 0: {
                            case5 = true;
                            string plik_nazwa = "../data/" + aktywna.getImie() + ".txt";
                            ofstream file(plik_nazwa);
                            if (file.is_open()) {
                                file << aktywna.getSaldo() << endl;
                                file << aktywna.getWaluta() << endl;
                                file << aktywna.getOstatniaOperacja() << endl;
                                file.close();
                            } else {
                                cout << "Nie udalo sie nadpisac pliku." << endl;
                            }
                            break;
                        }
                        default: {
                            cout << "Nie ma takiej opcji." << endl;
                            break;
                        }
                    }
                    if (case5) {
                        cout << "Koniec pracy z kontem." << endl;
                        break;
                    }
                }
                break;
            }
            case 0: {
                cout << "Koniec pracy." << endl;
                return 0;
            }
            default: {
                cout << "Nie ma takiej opcji." << endl;
                break;
            }
        }
    }
}