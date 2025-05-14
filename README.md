# 🕸️ Multi-threaded Web Crawler (Single-threaded Phase) – CS Project

This project is a **web crawler and text analyzer**, implemented in **C**, currently using a **single-threaded** model. It:

- Downloads plain text files from a list of URLs.
- Counts the number of **sentences**, **words**, and the **frequency of characters (a-z)**.
- Prints per-URL stats.

---

## 📁 Project Structure

```
├── constants/
│ └── urls.txt # List of URLs (Plain text only, like Project Gutenberg)
│
├── include/ # Header files
│ ├── downloader.h
│ ├── processor.h
│ ├── utils.h
│
├── src/ # Source files
│ ├── main.c
│ ├── downloader.c
│ ├── processor.c
│ ├── utils.c
│
├── build/ # Build output (object files)
│
├── .gitignore
├── Makefile
└── README.md
```

---

## 🧰 Prerequisites

### 💻 WSL Setup (Ubuntu)

Install WSL on Windows if not already installed:

```bash
wsl --install
```

### 📦 Install Dependencies

```bash
sudo apt update
sudo apt install build-essential libcurl4-openssl-dev
```

### 📂 Clone the Repository

```bash
git clone https://github.com/Shuja-ud-din/OS-Project.git
cd OS-Project
```

### 📦 Build the Project

```bash
make
```

### 🚀 Run Instructions

#### 🧪 1. Dev Mode – Build + Run

```bash
make dev
```

#### ▶️ 2. Run Only (Binary must already exist)

```bash
make run
```

#### 🧹 3. Clean Build

```bash
make clean
```
