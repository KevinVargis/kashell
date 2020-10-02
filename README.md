## kash C shell

This is an implementaion of the Linux Shell in C that supports colon-separated inputs, input-output redirection and piping.
Includes functionality for history-logging and basic background jobs and signal handling.

**Set-up Process**
1. Open this directory in terminal
2. Run `make` command in terminal to compile the files as given in `Makefile`
3. Start the shell by executing `./johnny_kash`

**Files/Functionality included**
1. Header Files
- `headers.h` - Collective list of all the header files required for the C files.
- `builtins.h` - List of headers files defining all the functions.
- `amp.h` - Contains struct definiton for the array that will store the background processes.
- `cd.h` - Contains function definitions for `cd.c`
- `echo.h` - Contains function definitions for `echo.c`
- `ls.h` - Contains function definitions for `ls.c`
- `pinfo.h` - Contains function definitions for `pinfo.c`
- `prompt.h` - Contains function definitions for `prompt.c`
- `exec.h` - Contains function definitions for `exec.c`
- `fg.h` - Contains function definitions for `fg.c`
- `bg.h` - Contains function definitions for `bg.c`
- `handlers.h` - Contains function definitions for `handlers.c`
- `kjob.h` - Contains function definitions for `kjob.c`

2. Program Files
- `prompt.c` - Formats and displays the command prompt and waits for input.
- `main.c` - The creatively named *main* program, recieves input from prompt, parses and tokenizes the input string, calls `exec()`, and logs command history.
- `cd.c` - Implements cd command, lets you change current working directory. Supports `.`,`..`,`~` and `-` flags,
- `echo.c` - Implements echo command, prints space separated arguments removing excess whitespace.
- `ls.c` - Implements ls command, prints names and/or details in given directories. Accepts -l, -a flags.
- `pinfo.c` - Displays the details of process corresponding to given process ID, by default displays pinfo of current(johnny_kash) process.
- `pwd.c` - Implements pwd command, prints present working directory.
- `exec.c` - Handles the function calls for all the builtin functions and calls execvp for the rest. Can run programs in the background if run with arguments `&`.
- `fg.c` - `fg()` allows you to bring a stopped/running background process from the jobs list to the foreground and start it.
- `bg.c` - Contains misc. functions needed for background process handling.
    - `jobs()` - Displays all the background process in the jobs list.
    - `bg()` - Toggles a stopped bg process to running.
    - `add_bg()` - Add new bg process.
    - `del_bg(int pno)` - Deletes the bg process numbered pno.
    -`overkill` - Deletes all bg processes.
- `handlers.c` - Contains signal handlers for `SIGINT`, `SIGSTP` and `SIGCHLD`.
- `kjob.c` - Sends a particular process a signal depending on the parameters
