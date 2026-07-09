# The Secure Banking Sim

A lightweight, console-based retail banking application written in C. This project simulates fundamental banking operations—including account registration, secure authentication, deposits, and withdrawals—while emphasizing defensive programming and input validation.

## 🚀 Features

*   **Secure Gateway**: User account creation with strict character length validation.
*   **Persistent Storage**: Data states are saved and loaded dynamically from a local storage file.
*   **Mathematical Guardrails**: Active runtime protection against integer overflow attacks during financial transactions.
*   **Robust Input Handling**: Isolated memory buffers and input stream flushing to prevent input bleeding and menu-skipping bugs.
*   **Audit Logging**: Comprehensive, timestamped system logs (`bank_logs.txt`) tracking user registration, authentication events, and financial transactions.

---

## 🛠️ Security Engineering Controls

To live up to its name, **The Secure Banking Sim** incorporates specific defensive programming techniques:

1.  **Integer Overflow Protection**: The deposit system validates transaction boundaries mathematically (`INT_MAX - amount < balance`) before modifying memory.
2.  **Buffer Overflow Mitigation**: Employs bound-restricted string operations and manual null-termination overrides to protect memory spaces.
3.  **Strict Buffer Sizing**: Logging arrays are sized dynamically to completely eliminate string truncation vulnerability risks.
4.  **Input Stream Isolation**: Targeted stream-clearing routines prevent trailing newline characters from disrupting sequential program logic.

---

## 📂 Project Architecture

*   `secure_banking_sim.c`: The core application code housing user structures, state logic, and operational sub-routines.
*   `database.txt`: Flat-file flat storage maintaining current user profiles (automatically created upon first registration).
*   `bank_logs.txt`: The system security log tracking backend audit events.

---

## 🛠️ Dev Environment & Tools Setup

*   **Editor**: Visual Studio Code
*   **C Compiler Toolchain**: MinGW GCC x64 Installation
*   **Version Control**: GitHub Desktop App
*   **Operating System Platform**: Windows 11 Home Execution

---

## 📈 My Next Career Milestones

*   [x] Establish Git repository architecture
*   [x] Complete basic logic scripts (Arrays, Loops, Math Operations)
*   [ ] Finish C Programming foundational training at institute
*   [ ] Initialize Python Automation Course (Launching July 13th)
*   [ ] Complete Google Cyber Security Professional Certificate Track

---

## 💻 Getting Started

### Prerequisites
*   A C compiler installed on your system (e.g., `gcc` or `clang`).
*   Standard terminal environment.

### Installation & Compilation
1. Clone or download the project files into your local directory.
2. Open your terminal and navigate to the project folder.
3. Compile the source code using standard optimization flags:

```bash
gcc -O2 -Wall secure_banking_sim.c -o secure_banking_sim
```

### Running the Application
Launch the compiled binary directly from your terminal:

```bash
./secure_banking_sim
```

