# 🏦 Bank Management System (C++ OOP)

A lightweight, console-based **Bank Management System** developed in C++ using Object-Oriented Programming (OOP) principles. This project simulates core banking operations, including account creation, fund deposits and withdrawals, money transfers, and administrative oversight.

---

## ✨ Features

- **User & Account Management**
  - Create new bank accounts (Savings or Checking)
  - Search, display, and update customer profiles
  - Close/delete existing accounts
- **Transactions**
  - Deposit funds into accounts
  - Withdraw funds with real-time balance validation
  - Perform secure inter-account fund transfers
  - View real-time balances and transaction records
- **Administrative Capabilities**
  - View list of all registered accounts
  - Inspect aggregate bank balance and operational logs
- **Data Persistence**
  - Save and restore account details using local file handling (`.txt` / `.dat`)

---

## 🛠️ OOP Principles Demonstrated

- **Encapsulation:** Sensitive data (e.g., balance, PIN, personal info) is encapsulated using `private`/`protected` modifiers and exposed via secure getters/setters.
- **Inheritance:** A general `Account` base class extended by specialized derived classes like `SavingsAccount` and `CheckingAccount`.
- **Polymorphism:** Overridden methods (e.g., `withdraw()` and `calculateInterest()`) provide custom behavior based on account type.
- **Abstraction:** Complex implementation details like data parsing and file I/O are hidden behind clean class interfaces.

---

## 🚀 Getting Started

### Prerequisites

- C++ Compiler (GCC, Clang, or MSVC supporting **C++11** or higher)
- Optional: C++ IDE (VS Code, CLion, Visual Studio, Code::Blocks)

### Build & Run Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/amive/Bank-System-Using-OOP-CPP
   cd Bank-System-Using-OOP-CPP
   ```

2. **Compile the code:**
   ```bash
   g++ -std=c++17 main.cpp -o BankSystem
   ```

3. **Launch the application:**
   ```bash
   ./BankSystem
   ```

---

---
