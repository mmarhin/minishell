# Minishell 🐚

```
 __  __ ___ _   _ ___ ____  _   _ _____ _     _
|  \/  |_ _| \ | |_ _/ ___|| | | | ____| |   | |
| |\/| || ||  \| || |\___ \| |_| |  _| | |   | |
| |  | || || |\  || | ___) |  _  | |___| |___| |___
|_|  |_|___|_| \_|___|____/|_| |_|_____|_____|_____|

           by mmarhin & lanton-m
```

> As beautiful as a shell 🐚

Un shell simple escrito en C que replica el comportamiento de bash.

---

## ✅ Features

| Feature | Estado |
|---------|--------|
| Pipes `\|` | ✅ |
| Redirecciones `< > >> <<` | ✅ |
| Expansión de variables `$VAR $?` | ✅ |
| Comillas simples y dobles | ✅ |
| Builtins (cd, echo, pwd, env, export, unset, exit) | ✅ |
| Señales (Ctrl+C, Ctrl+D, Ctrl+\\) | ✅ |
| Prompt con exit code | ✅ |
| Norminette | ✅ |
| Tests: **146/146** | ✅ |

---

## 🚀 Uso

```bash
# Compilar
make

# Ejecutar
./minishell

# Limpiar
make fclean

# Verificar norminette
norminette src includes
```

---

## 📁 Estructura

```
minishell/
├── includes/minishell.h
├── libs/libft/
├── src/
│   ├── main.c
│   ├── builtins/   (cd, echo, pwd, env, export, unset, exit)
│   ├── exec/       (executor, pipes, redirections, expansion)
│   ├── parser/     (parser, parser_utils, parser_args)
│   ├── tokenizator/(tokenizator, token_utils, quotes, operators)
│   ├── signals/    (signals.c)
│   └── utils/      (cleaners, enviroment, banner)
└── Makefile
```

---

## ✨ Autores

| Autor | GitHub |
|-------|--------|
| **Mario Marín** (mmarhin) | [@mmarhin](https://github.com/mmarhin) |
| **Luis Antón** (lanton-m) | [@coderris](https://github.com/coderris) |

---

*42 Málaga - Enero 2026*
