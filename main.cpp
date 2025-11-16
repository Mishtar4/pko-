#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// --- Dane podstawowe klienta ---

// --- Dane konta powiazanego z klientem ---
struct Konto {
    double saldo;
    string waluta;
    string ostatniaOperacja;

    Konto(double s = 0, string w = "PLN", string o = "Brak operacji.") :
        saldo(s),
        waluta(w),
        ostatniaOperacja(o)
    {}
};

struct Klient {
    string imie;
    string problem;
    Konto konto;

    Klient(string i = "", string p = "") : imie(i), problem(p) {}

    // Pomocnicze wypisywanie klienta
    const void pokaz() {
        cout << imie << " | problem: " << problem;
    }
};

int main() {
    queue <Klient> oczekujacy; // FIFO: nowi klienci trafiają na koniec
    stack <Klient> wstrzymani; // LIFO: ostatnio wstrzymany wraca jako pierwszy
    vector <Klient> zakonczone; // log zakończonych rozmów

    bool maAktywna = false; // czy trwa rozmowa?
    Klient aktywna("", "");
    // aktualnie obsługiwany klient (jeśli jest)

    int wybor;
    while (true) {
        cout << "\n==== CALL CENTER ====\n" <<
        "1. Nowe zgloszenie\n" <<
        "2. Rozpocznij rozmowe (z kolejki)\n" <<
        "3. Wstrzymaj aktywna rozmowe (na stos)\n" <<
        "4. Wznow rozmowe (ze stosu)\n" <<
        "5. Zakoncz aktywna rozmowe\n" <<
        "6. Podglad stanu\n" <<
        "7. Wyjdz\n" <<
        "Wybor: ";
        cin >> wybor;
        cin.ignore();
        switch (wybor) {
            case 1: {
                // Nowe zgłoszenie trafia do kolejki
                cout << "Wpisz imie: ";
                string imie;
                getline(cin, imie);
                //Tworzenie nowego klienta
                Klient kl;

                //Sprawdzanie istnienia klienta
                string plik_nazwa = imie + ".txt";
                ifstream file(plik_nazwa);

                //Odczyt stanu konta, jezeli klient istnieje
                if (file.is_open()) {
                    string linia;
                    file >> kl.konto.saldo;
                    cin.ignore();
                    getline(file, kl.konto.waluta);
                    getline(file, kl.konto.ostatniaOperacja);
                    file.close();
                }
                cout << "Opisz problem: ";
                string problem;
                getline(cin, problem);
                kl = (imie, problem);
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
                    cout << endl;
                }
                break;
            }
            case 3: {
                // Wstrzymaj aktywną (przenieś na stos)
                if (!maAktywna) {
                    cout << "Rozmowa nie trwa!" << endl;
                } else {
                    cout << "Rozmowa z klientem " << aktywna.imie << " jest wstrzymana." << endl;
                    wstrzymani.push(aktywna);
                    aktywna = Klient("", "");
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
                    cout << "Rozmowa z " << aktywna.imie << " zostala zakonczona." << endl;
                    zakonczone.push_back(aktywna);
                    aktywna = Klient("", "");
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