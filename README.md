![build](https://github.com/calheb/conch/actions/workflows/build.yml/badge.svg)

<img align="left" style="width:260px" src="https://github.com/user-attachments/assets/cb9f5408-ce5e-4fae-a604-4a7e2e20e647" width="288px">

**conch**

A simple, extensible, and customizable shell.

conch is a UNIX shell written in K&R style C89, designed from the ground up to be POSIX compliant. It's early in development;
the goal is to build something fast, portable, and shaped by those who use it.

> [!WARNING]
> conch has limited functionality and is likely riddled with bugs.


---

<br>
<br>

> What I cannot create, I do not understand. - Richard Feynman

## Features

- Interactive prompt showing current working directory
- `cd`, `exit`, and `showpid` builtins
- External command execution
- Tracks recent background process IDs

## Building & Running

> [!NOTE]
> Requires a C89-compatible compiler (gcc or clang).

```sh
git clone https://github.com/calheb/conch.git && cd conch
make
./conch
```

## Roadmap
- Command history
- Pipes and I/O redirection
- Job control and signal handling
- Tab completion
- Plugin/extension API
- Full POSIX sh compliance

## Contributing
Contributions are very much welcome in the form of issues, discussions, and pull requests.
