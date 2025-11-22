#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

// --- Dane konta powiazanego z klientem ---
class Konto {
private:
    double saldo;
    string waluta;
    string ostatniaOperacja;

public:
    Konto(double s = 0, string w = "PLN", string o = "Brak operacji.") :
        saldo(s),
        waluta(w),
        ostatniaOperacja(o)
    {}

    //Settery
    void setSaldo(double s) {saldo = s;}
    void setWaluta(string w) {waluta = w;}
    void setOstatniaOperacja(string o) {ostatniaOperacja = o;}
    void setKonto(double s, string w, string o) {
        saldo = s;
        waluta = w;
        ostatniaOperacja = o;
    }

    //Gettery
    double getSaldo() {return saldo;}
    string getWaluta() {return waluta;}
    string getOstatniaOperacja() {return ostatniaOperacja;}


    // --- Dodanie przychodu ---
    void dodajPrzychod() {
        cout << "Podaj kwote przychodu: " << endl;
        double kwota;
        cin >> kwota;
        saldo += kwota;
        if ((int)kwota == kwota)
        {
            ostatniaOperacja = "Dodano przychod: " + to_string((int)kwota) + " " + waluta;
            cout << ostatniaOperacja << endl;
        }
        else
        {
            ostatniaOperacja = "Dodano przychod: " + to_string(kwota) + " " + waluta;
            cout << ostatniaOperacja << endl;
        }
    }
    // --- Dodanie wydatku ---
    void dodajWydatek()
    {
        cout << "Podaj kwote wydatku: " << endl;
        double kwota;
        cin >> kwota;
        if (saldo - kwota < 0)
        {
            cout << "Brak srodkow!" << endl;
        }
        else
        {
            saldo -= kwota;
            if ((int)kwota == kwota)
            {
                ostatniaOperacja = "Dodano wydatek: " + to_string((int)kwota) + " " + waluta;
                cout << ostatniaOperacja << endl;
            }
            else
            {
                ostatniaOperacja = "Dodano wydatek: " + to_string(kwota) + " " + waluta;
                cout << ostatniaOperacja << endl;
            }
        }
    }
    // --- Wyswietlanie stanu konta ---
    void pokazSaldo()
    {
        cout << "===KONTO===\nTwoje saldo: " << saldo << " " << waluta << endl;
        cout << "\nOstatnia operacja:\n" << ostatniaOperacja << endl;
    }
    // --- Zmiana waluty konta ---
    void zmienWalute()
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
        if ((int)saldo == saldo)
        {
            ostatniaOperacja = "Konwertacja: " + to_string(int(stare_saldo)) + " " + stara_waluta + " => " + to_string(int(saldo)) + " " + waluta;
            cout << ostatniaOperacja << endl;
        }
        else
        {
            ostatniaOperacja = "Konwertacja: " + to_string(stare_saldo) + " " + stara_waluta + " => " + to_string(saldo) + " " + waluta;
            cout << ostatniaOperacja << endl;
        }
    }
};

// --- Dane podstawowe klienta ---
class Klient {
private:
    string imie;
    string problem;
    Konto konto;

public:
    Klient(string i = "", string p = "") : imie(i), problem(p) {}

    // Pomocnicze wypisywanie klienta
    const void pokaz() {
        cout << imie << " | problem: " << problem;
    }

    //Settery imię i problem
    void setKlient(string i, string p) {
        imie = i;
        problem = p;
    }

    //Settery dla Konto
    void setKonto(double s, string w, string o) {
        konto.setKonto(s, w, o);
    }

    //Gettery dla Klienta
    string getImie() {return imie;}
    string getProblem() {return problem;}

    //Gettery dla Konto
    double getSaldo() {return konto.getSaldo();}
    string getWaluta() {return konto.getWaluta();}
    string getOstatniaOperacja() {return konto.getOstatniaOperacja();}

    //Praca z kontem
    void dodajPrzychod() {konto.dodajPrzychod();}
    void dodajWydatek() {konto.dodajWydatek();}
    void pokazSaldo() {konto.pokazSaldo();}
    void zmienWalute() {konto.zmienWalute();}
};

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
                string plik_nazwa = "./data/" + imie + ".txt";
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
                            string plik_nazwa = "./data/" + aktywna.getImie() + ".txt";
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