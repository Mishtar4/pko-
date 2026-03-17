# 📞 Call Center Banking System

A console-based **call center simulation** with integrated client bank account management, written in **C++14**.

Developed independently in **2 weeks** as a personal project during the 1st semester of Computer Science studies — before OOP was formally introduced in the curriculum.

---

## ✨ Features

- **Call queue management** — new requests are added to a FIFO queue
- **Call hold stack** — active calls can be suspended and resumed via LIFO stack
- **Session log** — all completed calls are stored in a vector log
- **Bank account operations** — deposit, withdraw, check balance, view transaction history
- **Multi-currency support** — PLN, EUR, USD, UAH
- **Persistent storage** — client account state is saved to and loaded from `.txt` files between sessions
- **Random client generator** — quickly populate the queue for testing

---

## 🏗️ Architecture

The project is built around 3 classes with full encapsulation:

```
CallCenter          – main program loop, queue/stack/log management, file I/O
│
├── Klient          – client data (name, problem description)
│   └── Konto       – bank account (balance, currency, transaction history)
```

### Data structures used
| Structure | Role |
|-----------|------|
| `std::queue<Klient>` | FIFO queue of waiting clients |
| `std::stack<Klient>` | LIFO stack of suspended calls |
| `std::vector<Klient>` | Log of completed sessions |
| `std::unordered_map` | Exchange rate table for currency conversion |

---

## 🚀 How to build and run

### Requirements
- C++14 compiler (g++ / clang++)
- CMake 4.0+

### Build
```bash
git clone https://github.com/Mishtar4/pko-.git
cd pko-
mkdir build && cd build
cmake ..
make
./pko_
```

### Data directory
The program reads and writes client data from `./data/`.
Make sure the `data/` folder exists in the same directory as the executable:
```bash
mkdir data
```

---

## 🖥️ Usage

```
==== CALL CENTER ====
1. Nowe zgloszenie          – add a new client to the queue
2. Rozpocznij rozmowe       – start call with next client in queue
3. Wstrzymaj rozmowe        – suspend active call (push to stack)
4. Wznow rozmowe            – resume last suspended call (pop from stack)
5. Zakoncz rozmowe          – end active call (save to log)
6. Podglad stanu            – view queue, stack, and log
7. Dodanie losowego klienta – add a random client for testing
8. Operacja na koncie       – manage active client's bank account (visible only during active call)
0. Wyjdz                    – exit
```

### Account operations (option 8)
```
1. Dodaj przychod     – deposit funds
2. Dodaj wydatek      – withdraw funds (blocked if insufficient balance)
3. Pokaz saldo        – display current balance and last operation
4. Wszystkie operacje – full transaction history (newest first)
5. Zmien walute       – convert balance to another currency
0. Zakoncz            – save account state and return to main menu
```

---

## 📁 Project structure

```
.
├── main.cpp          – entry point
├── CallCenter.h/.cpp – main controller, queue/stack/log, file I/O
├── Klient.h/.cpp     – client model
├── Konto.h/.cpp      – bank account model with all financial operations
├── CMakeLists.txt    – build configuration
└── data/
    ├── Mikolaj.txt   – example saved client
    └── Mykhailo.txt  – example saved client
```

---

## 🛠️ Technologies

- **Language:** C++14
- **Build system:** CMake
- **STL:** `queue`, `stack`, `vector`, `unordered_map`, `fstream`
- **Paradigm:** Object-Oriented Programming (OOP)

---

## 👨‍💻 Author

**Mykhailo Chernata**
[github.com/Mishtar4](https://github.com/Mishtar4)
