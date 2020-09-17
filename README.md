## kash C shell

This is an implementaion of the Linux Shell in C that supports colon-separated inputs, history-logging and basic background process handling.

**Set-up Process**
1. Open this directory in terminal
2. Run `make` command in terminal to compile the files as given in `Makefile`
3. Start the shell by executing `./johnny_kash`

**Files/Functionality included**
1. Header Files
- `headers.h` - Collective list of all the header files required for the C files.
- `amp.h` - Contains struct definiton for the array that will store the background processes.
- `cd.h` - Contains function definitions for `cd.c`
- `echo.h` - Contains function definitions for `echo.c`
- `ls.h` - Contains function definitions for `ls.c`
- `pinfo.h` - Contains function definitions for `pinfo.c`
- `prompt.h` - Contains function definitions for `prompt.c`
- `pwd.h` - Contains function definitions for `pwd.c`

2. Program Files
- `prompt.h` - Formats and displays the command prompt and waits for input.
- `main.c` - The creatively named *main* program, recieves input from prompt, parses and tokenizes the input string, handles the function calls, and logs command history. Can run programs in the background if run with arguments `&`.
- `cd.h` - Implements cd command, lets you change current working directory.
- `echo.h` - Implements echo command, prints space separated arguments removing excess whitespace.
- `ls.h` - Implements ls command, prints names and/or details in given directories. Accepts -l, -a flags.
- `pinfo.h` - Displays the details of process corresponding to given process ID, by default displays pinfo of current(johnny_kash) process.
- `pwd.h` - Implements pwd command, prints present working directory.
