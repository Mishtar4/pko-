#include "CallCenter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// --- Konstruktor ---
CallCenter::CallCenter(const string& dir) : maAktywna(false), aktywna() , dataDir(dir) {}

// --- Główna pętla programu ---
void CallCenter::run() {
    int wybor;
    while (true) {
        pokazMenu();
        cin >> wybor;
        cin.ignore();

        if (!maAktywna && wybor == 8) {
            cout << "Nie ma takiej opcji." << endl;
            continue;
        }
        if (wybor == 0) {
            cout << "Koniec pracy." << endl;
            return;
        }
        obsluzWybor(wybor);
    }
}

// --- Menu ---
void CallCenter::pokazMenu() {
    cout << "\n==== CALL CENTER ====\n" <<
            "1. Nowe zgloszenie\n" <<
            "2. Rozpocznij rozmowe (z kolejki)\n" <<
            "3. Wstrzymaj aktywna rozmowe (na stos)\n" <<
            "4. Wznow rozmowe (ze stosu)\n" <<
            "5. Zakoncz aktywna rozmowe\n" <<
            "6. Podglad stanu\n" <<
            "7. Dodanie losowego klienta\n";
    if (maAktywna) {
        cout << "8. Operacja na koncie aktywnego klienta" << endl;
    }
    cout << "0. Wyjdz\n" << "Wybor: ";
}

// --- Wybór opcji ---
void CallCenter::obsluzWybor(int wybor) {
    switch (wybor) {
        case 1: noweZgloszenie(); break;
        case 2: rozpocznijRozmowe(); break;
        case 3: wstrzymajRozmowe(); break;
        case 4: wznowRozmowe(); break;
        case 5: zakonczRozmowe(); break;
        case 6: podgladStanu(); break;
        case 7: dodanieLosowegoKlienta(); break;
        case 8: menuKonta(); break;
        default: cout << "Nie ma takiej opcji." << endl; break;
    }
}

// --- Tworzenie nowego zgłoszenia ---
void CallCenter::noweZgloszenie() {
    // Nowe zgłoszenie trafia do kolejki
    cout << "Wpisz imie: ";
    string imie;
    getline(cin, imie);

    //Tworzenie nowego klienta
    Klient kl;

    wczytajKontoJesliIstnieje(kl, imie);

    cout << "Opisz problem: ";
    string problem;
    getline(cin, problem);

    // --- Identyfikacja klienta ---
    kl.setKlient(imie, problem);
    oczekujacy.push(kl);
}

// --- Sprawdza istnienia klienta w dyrektorji "data" ---
void CallCenter::wczytajKontoJesliIstnieje(Klient& kl, const string& imie) {
    //Sprawdzanie istnienia klienta
    string plik_nazwa = dataDir + imie + ".txt";
    ifstream file(plik_nazwa);

    //Odczyt stanu konta, jezeli klient istnieje
    if (file.is_open()) {
        // s - saldo, w - waluta, o - ostatniaOperacja, i - tymczasowa zmienna, wo - wszystkie operacje
        double s;
        string w, o, i;
        vector<string> wo;
        file >> s;
        file.ignore();
        getline(file, w);
        while (getline(file, i)) {
            wo.push_back(i);
        }
        if (!wo.empty()) {o = wo.back();}

        // --- Ustawienie konta istniejącego klienta ---
        kl.setKonto(s, w, o, wo);

        file.close();
    }
}

// --- Zaczyna rozmowę z pierwszym klientem z kolejki ---
void CallCenter::rozpocznijRozmowe() {
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
}

// --- Wstrzymanie rozmowy z aktywnym klientem ---
void CallCenter::wstrzymajRozmowe() {
    // Wstrzymaj aktywną (przenieś na stos)
    if (!maAktywna) {
        cout << "Rozmowa nie trwa!" << endl;
    } else {
        cout << "Rozmowa z klientem " << aktywna.getImie() << " jest wstrzymana." << endl;
        wstrzymani.push(aktywna);
        aktywna = Klient();
        maAktywna = false;
    }
}

// --- Powrót klienta do aktywnej rozmowy ---
void CallCenter::wznowRozmowe() {
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
}

// --- Zakończenie rozmowy ---
void CallCenter::zakonczRozmowe() {
    // Zakończ aktywną (zapisz do logu)
    if (!maAktywna) {
        cout << "Rozmowa nie trwa!" << endl;
    } else {
        cout << "Rozmowa z " << aktywna.getImie() << " zostala zakonczona." << endl;
        zakonczone.push_back(aktywna);
        aktywna = Klient();
        maAktywna = false;
    }
}

// --- Przegląd wszystkiego stanu rozmów ---
void CallCenter::podgladStanu() {

    // -- Stan aktywnej rozmowy --
    cout << "\n-- Aktywna rozmowa --\n";
    if (!maAktywna) {
        cout << "Rozmowa nie trwa!" << endl;
    } else {
        aktywna.pokaz();
        cout << endl;
    }

    // -- Przegląd kolejki oczekujących --
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

    // -- Wstrzymani klienci --
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

    // -- Lista zakończonych rozmów --
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
}

// --- Dodanie losowego klienta (żeby szybko zobaczyć działanie programu) ---
void CallCenter::dodanieLosowegoKlienta() {
    //Dodanie losowego klienta
    srand(time(0));
    vector<string> imiona = {"Marcin", "Adam", "Mikolaj", "Ola", "Jan"};
    vector<string> problemy = {
        "Konwertacja w EUR",
        "Oplata za prad 200 PLN",
        "Oplata czynszu najmu mieszkania",
        "Nie otrzymano pensji.",
        "Przelew na komorke"
    };
    string i = imiona[rand() % imiona.size()];
    string p = problemy[rand() % problemy.size()];
    Klient kl;
    kl.setKlient(i, p);
    kl.setKonto(rand()%1000, "PLN", "Brak operacji.", {});
    oczekujacy.push(kl);
    cout << "Dodano losowego klienta: " << i << " | " << p << endl;
}

// --- Menu konta klienta ---
void CallCenter::menuKonta() {
    int op;
    bool wyjdz = false;
    while (true) {
        cout << "\n==== Operacji z kontem ====\n" <<
        "1. Dodaj przychod\n" <<
        "2. Dodaj wydatek\n" <<
        "3. Pokaz aktualne saldo\n" <<
        "4. Wszystkie operacje\n" <<
        "5. Zmien walute\n" <<
        "0. Zakoncz dzialanie\n" <<
        "Wybor: ";
        cin >> op;
        switch (op) {
            case 1: aktywna.dodajPrzychod(); break;
            case 2: aktywna.dodajWydatek(); break;
            case 3: aktywna.pokazSaldo(); break;
            case 4: aktywna.wyciagWszystkichOperacji(); break;
            case 5: aktywna.zmienWalute(); break;
            case 0: {
                wyjdz = true;
                zapiszKontoAktywnego();
                break;
            }
            default: cout << "Nie ma takiej opcji." << endl; break;
        }
        if (wyjdz) {cout << "Koniec pracy z kontem." << endl; break;}
    }
}

// --- Po wyboru '0' w Menu konta działa zapisanie konta do pliku ---
void CallCenter::zapiszKontoAktywnego() {
    string plik_nazwa = dataDir + aktywna.getImie() + ".txt";
    ofstream file(plik_nazwa);
    if (file.is_open()) {
        file << aktywna.getSaldo() << endl;
        file << aktywna.getWaluta() << endl;
        // file << aktywna.getOstatniaOperacja() << endl;
        for (auto i : aktywna.getWyciagOperacji()) {
            file << i << endl;
        }
        file.close();
    } else {
        cout << "Nie udalo sie nadpisac pliku." << endl;
    }
}