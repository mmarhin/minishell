# Minishell - 42 Project

## 📋 Descripción del Proyecto

Implementación de un shell simple en C que replica el comportamiento básico de bash, cumpliendo con los requisitos del proyecto Minishell de 42.

---

## ✅ Progreso Actual

| Área | Estado |
|------|--------|
| Bucle principal / core | ✅ Completo |
| Tokenizador / lexer | ✅ Completo |
| Parser | ✅ Completo |
| Redirecciones (`<`, `>`, `>>`, `<<`) | ✅ Completo |
| Gestión de entorno | ✅ Completo |
| Ejecución de comandos externos | ✅ Completo |
| Señales (SIGINT, SIGQUIT) | ✅ Completo |
| Builtin: `cd` | ✅ Completo |
| Builtin: `exit` | ✅ Completo |
| Builtin: `echo` | 🚧 Pendiente |
| Builtin: `pwd` | 🚧 Pendiente |
| Builtin: `env` | 🚧 Pendiente |
| Builtin: `export` | 🚧 Pendiente |
| Builtin: `unset` | 🚧 Pendiente |
| Pipes `\|` | 🚧 Pendiente |
| Expansión de variables `$VAR` | 🚧 Pendiente |
| Norminette | ✅ OK |

---

## 🚀 Características Implementadas

### ✅ Core del Shell
- Bucle principal con `readline`
- Historial de comandos
- Prompt personalizado `minishell> `
- Gestión de señales en modo interactivo

### ✅ Tokenizador
- Separación por espacios
- Detección de operadores (`|`, `<`, `>`, `>>`, `<<`)
- Manejo de comillas simples y dobles
- Tokens para palabras y operadores

### ✅ Parser
- Construcción de lista de comandos (`t_cmd`)
- Extracción de redirecciones (`t_redir`)
- Detección de pipes
- Manejo de errores de sintaxis

### ✅ Redirecciones
- `<` - Redirección de entrada
- `>` - Redirección de salida (trunca)
- `>>` - Redirección de salida (append)
- `<<` - Heredoc

### ✅ Gestión de Entorno
- `copy_environ` - Copia del entorno
- `get_env` - Obtener variable
- `set_env` - Crear/actualizar variable
- `unset_env` - Eliminar variable

### ✅ Ejecución
- Búsqueda de ejecutables en PATH
- `fork` + `execve`
- Captura de exit status
- Soporte para redirecciones en comandos externos

---

## 🚧 Pendiente de Implementación

### Builtins
- [ ] `echo` con opción `-n`
- [ ] `pwd`
- [ ] `env`
- [ ] `export`
- [ ] `unset`

### Funcionalidades
- [ ] Pipes `|` (múltiples comandos)
- [ ] Expansión de variables `$VAR`
- [ ] Exit status `$?`

---

## 🛠️ Compilación y Uso

```bash
# Compilar
make

# Ejecutar
./minishell

# Limpiar
make clean
make fclean

# Recompilar
make re

# Verificar norminette
norminette src
```

---

## 🧪 Tests

```bash
# Test de redirecciones
bash tests/test_redirections.sh

# Test de tokenizador
cc -Wall -Wextra -Werror -I./includes -I./libs/libft/includes \
   tests/test_tokenizer.c obj/*.o -L./libs/libft -lft -o test_tokenizer
./test_tokenizer
```

---

## 📁 Estructura del Proyecto

```
minishell/
├── includes/
│   └── minishell.h
├── libs/
│   └── libft/
├── src/
│   ├── main.c
│   ├── builtins/
│   │   ├── builtins.c
│   │   ├── cd.c
│   │   ├── exit.c
│   │   ├── echo.c, pwd.c, env.c, export.c, unset.c
│   ├── exec/
│   │   ├── executor.c
│   │   ├── executor_path.c
│   │   └── redirections.c
│   ├── parser/
│   │   ├── parser.c
│   │   ├── parser_utils.c
│   │   └── parser_args.c
│   ├── tokenizator/
│   │   ├── tokenizator.c
│   │   ├── token_utils.c
│   │   ├── tokenizator_helpers.c
│   │   ├── tokenizator_operators.c
│   │   └── tokenizator_quotes.c
│   ├── signals/
│   │   └── signals.c
│   └── utils/
│       ├── cleaners.c
│       ├── enviroment.c
│       └── enviroment_utils.c
├── tests/
│   ├── test_redirections.sh
│   └── test_tokenizer.c
└── Makefile
```

---

## ✨ Autores

**Luis** - Parsing, Expansión, Builtins  
**Mario** - Redirecciones, Pipes, Tokenización

---

*Última actualización: 14 de Diciembre, 2024*
