![build](https://github.com/calheb/conch/actions/workflows/build.yml/badge.svg)

<img align="left" style="width:260px" src="https://github.com/user-attachments/assets/cb9f5408-ce5e-4fae-a604-4a7e2e20e647" width="288px">

**conch**

A simple, extensible, and customizable shell.

conch is a [UNIX](https://en.wikipedia.org/wiki/Unix) [shell](https://en.wikipedia.org/wiki/Unix_shell) written in [K&R](https://en.wikipedia.org/wiki/The_C_Programming_Language) style [C89](https://en.wikipedia.org/wiki/ANSI_C), designed from the ground up to be [POSIX](https://en.wikipedia.org/wiki/POSIX) compatible and extensible. It's early in development;
the goal is to build something fast, portable, and shaped by those who use it.

> [!WARNING]
> conch has extremely limited functionality.

---

<br>

> What I cannot create, I do not understand. - Richard Feynman

## Features
- Interactive prompt showing current working directory
- `cd`, `exit`, and `showpid` builtins
- External command execution
- Tracks recent background process IDs

## Building & Running
> [!NOTE]
> Requires a C compiler ([gcc](https://gcc.gnu.org/) or [clang](https://clang.llvm.org/)).

```sh
git clone https://github.com/calheb/conch.git && cd conch
make
./conch
```

### Nix
If you have [Nix](https://nixos.org/) with flakes enabled, you can run conch directly without cloning:

```sh
nix run github:calheb/conch --no-write-lock-file
```

## Roadmap
- Command history
- Pipes and I/O redirection
- Job control and signal handling
- Tab completion
- Plugin/extension API
- POSIX sh compatibility 

## Contributing
Contributions are very much welcome in the form of [issues](https://github.com/calheb/conch/issues), [discussions](https://github.com/calheb/conch/discussions), and [pull requests](https://github.com/calheb/conch/pulls).

## License 
conch is licensed under the [MIT](LICENSE) license.
