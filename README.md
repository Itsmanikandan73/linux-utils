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

- ### false and true
    - What it does: Literally does nothing except exit with a 0 (true) or 1 (false) status code
    - *Concepts learned*: Process exit codes.
