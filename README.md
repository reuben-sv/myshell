# mysh

A small Unix-like shell written in C, built from scratch as a personal learning project: an introduction to systems programming.

This is **not** a production shell. The goal is to understand how a shell works by building one: how processes are created, how programs get their arguments, how file descriptors and pipes connect programs, and how signals are handled.

**Target platform:** Linux (developed on Ubuntu via WSL2)

## Status

- [x] Milestone 0: C refresher (pointers, strings, `const`, tests)
- [x] Milestone 1: REPL (prompt, safe line reading, EOF handling)
- [ ] Milestone 2: Command parsing (tokeniser producing `argv`)
- [ ] Milestone 3: External command execution (`fork`, `execvp`, `waitpid`)
- [ ] Milestone 4: Built-ins (`cd`, `exit`, `help`, `pwd`)
- [ ] Milestone 5: Redirection (`>`, `>>`, `<`)
- [ ] Milestone 6: Pipes (`cmd1 | cmd2 | ...`)
- [ ] Milestone 7: Signals and process management
- [ ] Milestone 8: Advanced features (history, variable expansion, quoting, background jobs)

## Build and run

Requirements: GCC, GDB, Valgrind, strace (all optional except GCC).

```sh
gcc -g -O0 -Wall -Wextra -Wpedantic -Wcast-qual -std=c11 -o mysh mysh.c
./mysh
```

Exit with `Ctrl+D` on an empty prompt (and `exit` once built-ins are implemented).

## Usage

```
mysh> ls -la /tmp
```

Currently the shell reads a line and reports what it received. Command execution arrives in Milestone 3.

## Project layout

```
mysh/
├── mysh.c      # main loop and helpers (single file for now)
├── README.md
└── NOTES.md    # OS concepts and design decisions (see below)
```

The code will be split into multiple source and header files once the complexity justifies it, not before.

## Design decisions

Record the important choices here, with the reasoning and the trade-offs.

| Decision | Choice | Why |
|---|---|---|
| Over-long input lines | Reject with an error and discard the rest of the line | Running a truncated command could do something unintended |
| Error messages | Written to `stderr` | Keeps them out of redirected output |
| Tokeniser memory model | _to be decided in Milestone 2_ | |

## Testing

Tests are written alongside each feature and cover normal input, invalid input and edge cases.

Useful manual checks for line reading:

```sh
python3 -c "print('a'*1022)" | ./mysh | cut -c1-60
python3 -c "print('a'*1023)" | ./mysh | cut -c1-60
python3 -c "print('a'*1024)" | ./mysh | cut -c1-60
printf abc | ./mysh
```

Debugging tools used: `gdb` (stepping and crashes), `valgrind` (memory errors and leaks), `strace` (system calls).

## What I learned

Keep this section in your own words, and add to it at the end of each milestone.

- **Milestone 1:** `fgets` keeps the newline, so it must be checked rather than assumed. EOF is not a character; it is a `read` that returns 0. A terminal's Ctrl+D on a non-empty line only flushes the buffer.

## References

- `man 3 fgets`, `man 3 strcspn`, `man 3 isspace`
- `man 2 fork`, `man 2 execve`, `man 2 waitpid`, `man 2 pipe`, `man 2 dup2`, `man 2 sigaction`
- The GNU C Library manual