# 🛡️ AVHash - Signature-Based Antivirus

A fast and efficient malware detection system using advanced data structures (AVL Tree) and hybrid automation (C++ and Python).

![Badge C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Badge Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)

## 📖 About the Project

**AVHash** is a security tool developed to detect malicious files by comparing their SHA-256 hashes with a database of known signatures.

The project's distinguishing feature is its performance and architecture:
* **C++ Core:** Uses an **AVL Tree** (self-balancing) to guarantee logarithmic time searches $O(\log n)$, allowing thousands of signatures to be verified instantly.

* **Python Automation:** Auxiliary scripts manage the automatic download of new signatures (via MalwareBazaar) and monitor the Downloads folder in real time.

## 🚀 Features

* **Manual Scan:** Verification of individual files via command line.
* **Real-Time Monitoring:** "Watches" the Downloads folder and scans for new files automatically.
* **Smart Update:** Downloads new malware signatures automatically (only if the local database is more than 24 hours out of date).
* **Real Database:** Uses the [MalwareBazaar](https://bazaar.abuse.ch/) API to obtain hashes of recent threats.
* **Efficient Data Structure:** Proprietary implementation of AVL Tree in C++.

## 🛠️ Technologies Used

* **C++:** Main logic, Hash calculation (SHA-256) and Data Structure (AVL).
* **Python 3:** Update scripts (`urllib`) and file system monitoring (`watchdog`).
* **`PicoSHA2`:** Header-only library for cryptography in C++.

## 📦 Prerequisites

Before you begin, make sure you have the following installed:
* C++ compiler (g++)
* Python 3.x
* Python `watchdog` library:

```bash
pip install watchdog
# Se estiver no Linux e der erro, use:
sudo apt install python3-watchdog
```

## 💻 Installation and execution
Clone the repository and run the command:
```bash
g++ AVHash.cpp -o AVHash
```

### Usage Modes:
1. Automatic Monitoring:
Allows you to analyze a file as soon as it is placed in the downloads folder.

```bash
python3 monitor.py
```

2. Manual scan:
Analyzes a specific file.

```bash
./AVHash <file>
```

## 📝 License
This project has the [MIT](https://choosealicense.com/licenses/mit/) license.
