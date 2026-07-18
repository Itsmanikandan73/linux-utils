# linux-utils
Building my own version of classic Linux command-line utilities for understanding the the Linux API, file systems, and how operating system works under the hood. In this project there are four diffrent phases to complete it.

- phase1 *The Essentials(Warm-up)*
- phase2 *Fil*es and Directory Explores(Intermediate)*
- phase3 *Data Manipulators(Intermediate)*
- phase4 *System & Process Managers (Advanced)*

## 1.The Essentials(Warm-Up)
The utilites foucs on basic File I/O(Input/Output) and standard streams.

- ### cat ***(Concatenate)***
    - What it does: Reads files and prints their contents to the terminal.
    - *Concepts learned*: open(), read(), write(), close(), handling stdin (standard input)

- ### echo
    - What it does: Prints the arguments passed to it.
    - *Concepts learned*: Command-line argument parsing (argc, argv), handling escape sequences (like \n)

- ### true and false
    - What it does: Literally does nothing except exit with a 0 (true) or 1 (false) status code
    - *Concepts learned*: Process exit codes.

## 2.File and Directory Explorers(Intermediate)
These require interacting with the Linux file system structure and metadata.

- ### ls (List)
    - What it does: List directory contents. Start with just names, then add flags like -l (long format) and -a (hidden files).
    - *Concepts learned*: opendir(), readdir(), retrieving file metadata using stat(), formatting file permissions, users, and timestamps.

- ### pwn (Print Working Directory)
    - What it does: Outputs the absolute path of the current directory.
    - *Concepts learned*: getcwd() system call, or manually traversing parent directories(..) up to the root(/).

- ### mkdir (Make Directory)
    - What it does: Creates a new directory.
    - Concepts learned: mkdir() system call, file mode bits/permission (chmod concepts).

## 3.Data Manipulators (Intermediate)
These force you to manage memory effciency, line buffers, and basic string manipulation.
- ### wc **(Word Count)**
    - What it does: Counts lines, words, and bytes in a file.
    - Concepts learned: Character-by-character processing, tracking state(inside/outside a word),standard streams.

- ### head **and** tail
    - What it does: Prints the first or last N lines of a file.
    - Concepts learned: Ring buffers/circular queues (especially for *tail*, so you don't load a massive file entirely into memory)

- ### grep **(Global Regular Expression Print)**
    - What it does: Searches files for a specific string pattern.Start with basic string matching, then try integrating a simple regex library.
    - Concept learned: Line-by-line file reading (*getline()*), string searching algorithms.
    