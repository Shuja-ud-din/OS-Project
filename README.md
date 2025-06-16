# 🕸️ Multi-threaded Web Crawler – CS Project

This project is a **web crawler and text analyzer**, implemented in **C** using **pthreads** for parallel processing. It:

- Downloads plain text files from a list of URLs in parallel
- Counts the number of **sentences**, **words**, and the **frequency of characters (a-z)**
- Prints per-URL stats and execution time
- Uses thread synchronization for safe concurrent processing

---

## 📁 Project Structure

```
├── constants/
│ └── urls.txt # List of URLs (Plain text only, like Project Gutenberg)
│
├── include/ # Header files
│ ├── downloader.h    # URL downloading functionality
│ ├── processor.h     # Text analysis and shared data structures
│ ├── thread_pool.h   # Thread pool implementation
│ └── utils.h         # Utility functions
│
├── src/ # Source files
│ ├── main.c          # Main program entry point
│ ├── downloader.c    # URL downloading implementation
│ ├── processor.c     # Text analysis implementation
│ ├── thread_pool.c   # Thread pool implementation
│ └── utils.c         # Utility functions implementation
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

---

## 🔧 Implementation Details

### Threading Model

The project uses a thread pool pattern with the following features:

- Configurable number of worker threads (default: 2)
- Work distribution using chunk-based partitioning
- Thread-safe shared data structures using mutex locks
- Efficient memory management with proper cleanup

### Performance Features

- Parallel URL downloading
- Concurrent text analysis
- Thread-safe statistics collection
- Execution time measurement

### Data Structures

- `SharedStats`: Thread-safe container for analysis results
- `UrlContent`: Stores downloaded content and metadata
- `CharFrequency`: Tracks character frequency statistics

---

## 📊 Output Format

The program outputs:

1. Number of loaded URLs
2. Word counts per URL
3. Sentence counts per URL
4. Character frequency analysis
5. Total execution time

Example output:

```
Loaded 5 URLs

--- Word Counts ---
https://example.com/1: 1500 words
https://example.com/2: 2000 words
...

--- Sentence Counts ---
https://example.com/1: 75 sentences
https://example.com/2: 100 sentences
...

--- Character Frequencies (a-z) ---
a: 15000
b: 5000
...

Execution time: 2.345 seconds
```
