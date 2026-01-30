<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/330px-42_Logo.svg.png" alt="42 Logo" width="100"/>
</p>

<h1 align="center">
  Minishell
</h1>


<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="C"/>
  <img src="https://img.shields.io/badge/42-Málaga-black?style=for-the-badge" alt="42 Málaga"/>
</p>

<p align="center">
  A minimalist UNIX command interpreter written in C, inspired by <b>bash</b>.
  <br/>
  Developed as part of the <b>42</b> school curriculum.
</p>

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Architecture](#architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Makefile Commands](#makefile-commands)
- [Authors](#authors)

---

## About the Project

**Minishell** is a simplified UNIX shell implementation that replicates the essential behavior of bash. This project is part of the 42 common core curriculum and aims to deepen understanding of fundamental operating system concepts such as:

- Process management (`fork`, `exec`, `wait`)
- File descriptor handling
- Interprocess communication (pipes)
- UNIX signal handling
- Environment variables

```
 __  __ ___ _   _ ___ ____  _   _ _____ _     _
|  \/  |_ _| \ | |_ _/ ___|| | | | ____| |   | |
| |\/| || ||  \| || |\___ \| |_| |  _| | |   | |
| |  | || || |\  || | ___) |  _  | |___| |___| |___
|_|  |_|___|_| \_|___|____/|_| |_|_____|_____|_____|

                by mmarhin & lanton-m
```

---

## Features

### Implemented Functionalities

| Feature | Description |
|:---|:---|
| **Pipes** `\|` | Command chaining |
| **Redirections** | `<` `>` `>>` input/output |
| **Heredoc** `<<` | Here documents with delimiter |
| **Variable expansion** | `$VAR` and `$?` (exit status) |
| **Single quotes** `'...'` | Literal text without expansion |
| **Double quotes** `"..."` | Variable expansion inside |
| **Mixed quotes** | Combination of quote types |
| **Signals** | `Ctrl+C`, `Ctrl+D`, `Ctrl+\` |
| **History** | Arrow key navigation (readline) |
| **Dynamic prompt** | Shows last command exit code |
| **Non-interactive mode** | Execution from scripts/pipes |

### Builtins

All builtins work exactly like in bash:

| Command | Description |
|:---|:---|
| `echo` | Prints arguments with `-n` support |
| `cd` | Changes the working directory |
| `pwd` | Prints the current directory |
| `export` | Defines/modifies environment variables |
| `unset` | Removes environment variables |
| `env` | Displays the current environment |
| `exit` | Exits the shell with optional code |

---

## Architecture

The project follows a modular 4-phase architecture inspired by compiler design:

```
┌─────────────────────────────────────────────────────────────────────┐
│                          MINISHELL                                  │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  ┌──────────────┐    ┌──────────────┐    ┌──────────────────────┐   │
│  │   INPUT      │───▶│  TOKENIZER   │───▶│      PARSER          │   │
│  │  (readline)  │    │ (lexer)      │    │ (AST builder)        │   │
│  └──────────────┘    └──────────────┘    └──────────────────────┘   │
│                                                   │                 │
│                                                   ▼                 │
│  ┌──────────────┐    ┌──────────────┐    ┌──────────────────────┐   │
│  │   OUTPUT     │◀───│   BUILTINS   │◀───│     EXECUTOR         │   │
│  │              │    │              │    │ (fork/exec/pipes)    │   │
│  └──────────────┘    └──────────────┘    └──────────────────────┘   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Project Structure

```
minishell/
├── Makefile                 # Build system
├── README.md                # Documentation
├── includes/
│   └── minishell.h          # Headers and structures
├── libs/
│   └── libft/               # 42 utility library
└── src/
    ├── main.c               # Entry point and main loop
    ├── tokenizator/         # Lexical analysis (10 files)
    │   ├── tokenizator.c    # Main tokenizer engine
    │   ├── tokenizator_quotes.c
    │   ├── tokenizator_operators.c
    │   ├── tokenizator_heredoc.c
    │   └── ...
    ├── parser/              # Syntactic analysis (4 files)
    │   ├── parser.c         # Command tree construction
    │   ├── parser_args.c
    │   ├── parser_heredoc.c
    │   └── parser_utils.c
    ├── exec/                # Command execution (9 files)
    │   ├── executor.c       # Execution engine
    │   ├── pipes.c          # Pipeline management
    │   ├── redirections.c   # I/O redirections
    │   ├── commands_expansion.c
    │   └── ...
    ├── builtins/            # Built-in commands (10 files)
    │   ├── cd.c, echo.c, pwd.c
    │   ├── export.c, unset.c, env.c
    │   └── exit.c
    ├── signals/             # Signal handling
    │   └── signals.c
    └── utils/               # General utilities
        ├── enviroment.c     # Environment management
        ├── cleaners.c       # Memory deallocation
        └── banner.c         # Visual interface
```

### Main Data Structures

```c
// Token generated by the lexer
typedef struct s_token {
    t_token_type    type;       // WORD, PIPE, REDIR_IN, etc.
    char            *value;     // Token content
    t_quote_type    quote;      // Quote type used
    struct s_token  *next;      // Linked list
} t_token;

// Parsed command
typedef struct s_cmd {
    char            **args;     // Command arguments
    t_redir         *redirs;    // Redirection list
    struct s_cmd    *next;      // Next command in pipeline
} t_cmd;

// Global shell state
typedef struct s_shell {
    char    **envp;             // Environment variables
    int     exit_status;        // Exit code ($?)
    int     interactive;        // Interactive mode?
    char    *last_path;         // OLDPWD for cd -
} t_shell;
```

---

## Installation

### Requirements

- **Operating System**: Linux
- **Compiler**: `cc` (clang or gcc)
- **Libraries**: `readline`, `ncurses`

### Compilation

```bash
# Clone the repository
git clone https://github.com/mmarhin/minishell.git
cd minishell

# Compile
make

# Clean compilation (rebuild everything)
make re
```

### Dependencies (if needed)

```bash
# Ubuntu/Debian
sudo apt-get install libreadline-dev
```

---

## Usage

### Interactive Mode

```bash
./minishell
```

The shell will display a prompt with the last command's exit code:

```
minishell [0] > echo "Hello, 42!"
Hello, 42!
minishell [0] > 
```

### Non-Interactive Mode

```bash
# From a file
./minishell < script.sh

# With echo
echo "ls -la | grep minishell" | ./minishell
```

### Keyboard Shortcuts

| Shortcut | Action |
|:---|:---|
| `Ctrl+C` | Interrupts the current command |
| `Ctrl+D` | Exits the shell (EOF) |
| `Ctrl+\` | Ignored (like bash) |
| `↑` / `↓` | Navigate through history |

---

## Examples

### Pipes and Redirections

```bash
# Simple pipeline
minishell> ls -la | grep ".c" | wc -l

# Multiple pipes
minishell> cat file.txt | sort | uniq | head -5

# Redirections
minishell> echo "content" > output.txt
minishell> cat < input.txt > output.txt
minishell> echo "append" >> output.txt

# Heredoc
minishell> cat << EOF
> Line 1
> Line 2
> EOF
```

### Variable Expansion

```bash
minishell> export NAME="42 Málaga"
minishell> echo "Hello, $NAME"
Hello, 42 Málaga

minishell> echo 'No expansion: $NAME'
No expansion: $NAME

minishell> ls nonexistent_file
minishell> echo "Exit status: $?"
Exit status: 1
```

### Quotes

```bash
# Single: literal text
minishell> echo 'Hello $USER'
Hello $USER

# Double: with expansion
minishell> echo "Hello $USER"
Hello your_username

# Mixed
minishell> echo "It's a 'wonderful' world"
It's a 'wonderful' world
```

---

## Makefile Commands

| Command | Description |
|:---|:---|
| `make` | Compiles the project |
| `make clean` | Removes object files |
| `make fclean` | Removes objects and executable |
| `make re` | Recompiles everything from scratch |

---

## Authors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/mmarhin">
        <img src="https://github.com/mmarhin.png" width="100px;" alt=""/><br/>
        <sub><b>Mario Marín</b></sub>
      </a>
      <br/>
      <sub>mmarhin</sub>
    </td>
    <td align="center">
      <a href="https://github.com/coderris">
        <img src="https://github.com/coderris.png" width="100px;" alt=""/><br/>
        <sub><b>Luis Antón</b></sub>
      </a>
      <br/>
      <sub>lanton-m</sub>
    </td>
  </tr>
</table>

---

<p align="center">
  <b>42 Málaga • January 2026</b>
</p>
