# Readlite

**Readlite** is a minimalistic reimplementation of *GNU Readline*, written in C.
It provides basic line-editing and command history features for terminal-based programs — without external dependencies or heavy abstractions.

This project was built for learning purposes, to better understand how input handling and terminal control work at a low level.

---

## 🧩 Features

### Core Functionality

- ✅ **Custom prompt** — Set your own prompt string
- ✅ **Cursor movement** — Navigate the input line with LEFT/RIGHT arrows
- ✅ **Signal handling** — Proper handling of Ctrl+C, Ctrl+D, Ctrl+Z...
- ✅ **Input history** — Navigate through previous commands with UP/DOWN arrows

### Potential Features

- ⏳ **Tab completion** — Autocomplete file paths and commands
- ⏳ **Multiline support** — Handle input spanning multiple lines

---

## 🚀 Getting Started

### Prerequisites

This application is developed and tested on Linux.
It may work on other POSIX-compliant systems, but this has not been tested.

- GCC or Clang compiler
- Make (optional, for build automation)

### Building

```bash
# Clone the repository
git clone https://github.com/mr-akoton/readlite.git
cd readlite

# Compile
make
```

This will generate:

- `libreadlite.a` — Static library
- `libreadlite.so` — Shared library

### Usage

**Linking with the static library:**
```bash
gcc -o myprogram myprogram.c -L. -lreadlite -static
```

**Linking with the shared library:**
```bash
gcc -o myprogram myprogram.c -L. -lreadlite
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH  # So the system can find the .so
./myprogram
```

```c
#include <readlite.h>

int main(void) {
	char	*line;

	while ((line = readlite(">> ")) != NULL) {
		printf("You entered: %s\n", line);
		free(line);
	}

	return (0);
}
```

---

## ⚙️ How It Works

Readlite operates at a low level by:

1. **Raw Terminal Mode** — Disabling canonical mode and echo to read input character by character
2. **Manual Buffering** — Maintaining an internal buffer to track the current input line
3. **ANSI Escape Sequences** — Using escape codes to move the cursor and manipulate the display
4. **History Management** — Storing previous commands in a simple linked list or array structure

The library intercepts keystrokes before they reach the shell, allowing complete control over editing behavior — similar to how full-featured readline libraries work.

---

## 🎯 Project Goals

This project aims first to personal achievement, and alongside to:
- Understand low-level terminal I/O operations
- Learn about raw mode, escape sequences, and signal handling
- Build a functional, lightweight alternative to GNU Readline

---

## 📝 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

Inspired by:
- [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
- Various terminal emulation resources and ANSI escape code documentation

---

## 📖 Resources

- [ANSI Escape Codes](https://en.wikipedia.org/wiki/ANSI_escape_code)
- [Termios Programming](https://man7.org/linux/man-pages/man3/termios.3.html)
- [GNU Readline Documentation](https://tiswww.case.edu/php/chet/readline/readline.html)
