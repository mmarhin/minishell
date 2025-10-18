# Minishell - Proyecto 42

**Autores:** Mario & Luis  
**Fecha de inicio:** Octubre 2025  
**Shell base:** Desarrollada por Mario hace 1 año

---

## 📈 Progreso General

| Categoría | Estado | Completado |
|-----------|--------|------------|
| 🔧 Refactorización Base | 🔴 Pendiente | 0% |
| 📦 Setup & Makefile | 🔴 Pendiente | 0% |
| 📝 Parsing & Tokenización | 🔴 Pendiente | 0% |
| 🛠️ Built-ins | 🟡 Parcial (2/7) | 28% |
| 💲 Variables & Expansión | 🔴 Pendiente | 0% |
| 🔀 Pipes | 🔴 Pendiente | 0% |
| 📂 Redirecciones | 🟡 Parcial (2/4) | 50% |
| 🚦 Señales | 🟡 Parcial | 40% |
| 🔍 PATH & Ejecutables | 🔴 Pendiente | 0% |
| 🧹 Testing & Leaks | 🔴 Pendiente | 0% |
| **TOTAL OBLIGATORIO** | 🔴 | **~15%** |
| ⭐ Bonus | 🔴 | **0%** |

---

## 📋 Descripción del Proyecto

Recrear un shell simple similar a bash que permita ejecutar comandos, gestionar procesos, redirecciones, pipes y variables de entorno.

### 🎯 Estado Actual

- ✅ **Lo que tenemos**: Código base con ejecución básica, 2 built-ins (cd, exit), redirecciones simples (<, >)
- ⚠️ **Problema**: El código usa funciones NO permitidas por el subject
- 🚧 **Falta**: Built-ins, pipes, heredoc, comillas, expansión de variables, PATH

---

## ⚠️ Funciones Permitidas vs Usadas

### ✅ Funciones PERMITIDAS (Subject)
```
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
add_history, printf, malloc, free, write, access, open, read, close
fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset
kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2
pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot
ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
```

### ❌ Funciones NO PERMITIDAS (usadas en proyecto base)

| Función | Archivo | Solución |
|---------|---------|----------|
| `execvp()` | Shell_project.c:158 | Crear función para buscar en PATH + usar `execve()` |
| `fprintf()` | Shell_project.c, parse_redir.h | Usar `write()` o `printf()` |
| `fflush()` | Shell_project.c:69 | Eliminar (innecesario) |
| `strcmp()` | Shell_project.c:79,87 parse_redir.h:25,26 | Crear `ft_strcmp()` |

### ⚠️ Funciones usadas NO en la lista (verificar si permitidas)

| Función | Archivo | Estado | Nota |
|---------|---------|--------|------|
| `setpgid()` | Shell_project.c:111 | ⚠️ No listada | Necesaria para grupos de procesos |
| `tcsetpgrp()` | Shell_project.c:118,166,179 | ⚠️ No listada | Necesaria para control terminal |
| `getpid()` | Shell_project.c:109,118,179 | ⚠️ No listada | Obtener PID del proceso |
| `sigprocmask()` | job_control.c:98 | ⚠️ No listada | Para bloquear/desbloquear señales |

**Nota**: Estas funciones relacionadas con control de terminal y procesos probablemente SÍ están permitidas aunque no aparezcan explícitamente en la lista. Verificar con evaluadores.

---

## 🎯 Estado del Proyecto

### ⚠️ ACCIÓN REQUERIDA: Refactorizar Código Base

El proyecto base usa funciones NO permitidas. Antes de continuar:

#### 🔧 Cambios necesarios:

1. **`execvp()` → `execve()`**
   - Crear función `find_in_path()` que busque el ejecutable en PATH
   - Usar `access()` para verificar permisos de ejecución
   - Pasar `environ` como tercer argumento a `execve()`

2. **`fprintf()` → `write()` o `printf()`**
   - Para stderr: `write(2, "mensaje", longitud)`

3. **`fflush()` → Eliminar**
   - No necesario

4. **`strcmp()` → `ft_strcmp()`**
   - Crear en libft

---

### ✅ Lo que YA tenemos implementado (Shell Base de Mario)

#### Funcionalidades Básicas
- [x] Prompt de comandos (`COMMAND->`)
- [x] Lectura de línea de comandos (`get_command`)
- [x] Parsing básico de argumentos
- [x] Ejecución de comandos externos con `execvp()`
- [x] Gestión de procesos con `fork()` y `waitpid()`
- [x] Control de trabajos en foreground y background (operador `&`)
- [x] Gestión de grupos de procesos (`setpgid`)
- [x] Control del terminal (`tcsetpgrp`)

#### Built-ins Implementados
- [x] `cd` (cambio de directorio, relativo y absoluto)
- [x] `exit` (salir del shell)

#### Redirecciones Básicas
- [x] Redirección de entrada `<` (archivo → stdin)
- [x] Redirección de salida `>` (stdout → archivo, modo truncate)
- [x] Parsing de redirecciones (parse_redir.h)

#### Señales
- [x] Ignorar señales del terminal en el proceso padre (SIGINT, SIGQUIT, SIGTSTP, SIGTTIN, SIGTTOU)
- [x] Restaurar señales por defecto en procesos hijos
- [x] Manejador básico de SIGCHLD (recogida de procesos zombies)
- [x] Bloqueo/desbloqueo de SIGCHLD

---

## 🚧 Lo que FALTA implementar (Parte Obligatoria)

### 📚 Librería Readline
- [ ] Integrar librería `readline` para el prompt interactivo
- [ ] Implementar historial de comandos (`add_history`, `rl_clear_history`)

### 🔧 Built-ins Faltantes
- [ ] `echo` con opción `-n`
- [ ] `pwd` sin opciones
- [ ] `export` sin opciones
- [ ] `unset` sin opciones
- [ ] `env` sin opciones ni argumentos

### 💲 Variables de Entorno y Expansión
- [ ] Crear copia local de `environ`
- [ ] Expandir variables de entorno (`$VAR`) en el parser
- [ ] Expandir `$?` (exit status del último comando)
- [ ] Implementar búsqueda en env local con `getenv()`

### 🔀 Pipes (Tuberías)
- [ ] Implementar pipe simple entre 2 comandos
- [ ] Gestionar múltiples pipes en cadena
- [ ] Manejo correcto de file descriptors con `dup2()` y `pipe()`

### 📂 Redirecciones Avanzadas
- [ ] Heredoc `<<` (leer hasta delimitador, sin actualizar historial)
- [ ] Append `>>` (redirigir salida en modo de adición)

### 🎭 Manejo de Comillas
- [ ] Comillas simples `'` (evitar interpretación de metacaracteres)
- [ ] Comillas dobles `"` (evitar metacaracteres EXCEPTO `$`)
- [ ] Detección de comillas sin cerrar (error)

### 🚦 Señales Interactivas (Modo Interactivo)
- [ ] `ctrl-C`: Imprimir nueva línea y mostrar nuevo prompt
- [ ] `ctrl-D`: Salir del shell limpiamente
- [ ] `ctrl-\`: No hacer nada (ignorar SIGQUIT)

### 🔍 Búsqueda de Ejecutables (⚠️ CRÍTICO)
- [ ] Buscar en la variable `PATH` (función propia para reemplazar `execvp`)
- [ ] Soportar rutas relativas (`./programa`)
- [ ] Soportar rutas absolutas (`/bin/ls`)
- [ ] Usar `access()` para verificar permisos de ejecución

### 📝 Parsing Avanzado
- [ ] Tokenizador completo (lexer)
- [ ] Parser de sintaxis (syntax analyzer)
- [ ] Detectar caracteres especiales no especificados (`;`, `\`) y reportar error
- [ ] Validación de sintaxis de comandos
- [ ] Manejo robusto de espacios y tabs

### 🧹 Gestión de Memoria
- [ ] Asegurar que NO hay leaks de memoria (excepto readline)
- [ ] Liberar todas las estructuras de datos
- [ ] Validar con `valgrind`
- [ ] Crear funciones de limpieza (`free_all`, `free_tokens`, etc.)

### 🌍 Variable Global de Señales
- [ ] Usar **máximo UNA variable global** para señales
- [ ] Solo puede almacenar el número de señal recibida
- [ ] NO usar estructuras tipo "norm" como variables globales
- [ ] Ejemplo: `volatile sig_atomic_t g_signal = 0;`

### 📦 Build System
- [ ] Makefile completo con reglas: `NAME`, `all`, `clean`, `fclean`, `re`
- [ ] Flags: `-Wall -Werror -Wextra`
- [ ] Compilar con `cc`
- [ ] Evitar relink innecesario
- [ ] Integrar libft si se usa

---

## ⭐ Bonus (Solo si la parte obligatoria está PERFECTA)

### Operadores Lógicos
- [ ] Operador AND `&&` (ejecutar siguiente comando solo si el anterior tuvo éxito)
- [ ] Operador OR `||` (ejecutar siguiente comando solo si el anterior falló)
- [ ] Paréntesis `()` para establecer prioridades
- [ ] Modificar parser para soportar precedencia de operadores

### Wildcards
- [ ] Wildcard `*` para el directorio actual
- [ ] Expansión de patrones de archivos con `opendir/readdir`
- [ ] Manejo de patrones múltiples (`*.c`, `file*.txt`)

---

## 📂 Estructura del Proyecto

```
minishell/
├── Makefile                    # ⚠️ PENDIENTE: Configurar reglas completas
├── README.md                   # ✅ Este archivo
├── includes/                   # Header files principales
│   └── minishell.h            # ⚠️ PENDIENTE: Crear
├── src/                       # Código fuente principal
│   ├── main.c                 # ⚠️ PENDIENTE: Migrar desde proyecto_base
│   ├── parser/                # ⚠️ PENDIENTE: Tokenización y parsing
│   │   ├── lexer.c           # Tokenización
│   │   ├── parser.c          # Análisis sintáctico
│   │   ├── quotes.c          # Manejo de comillas
│   │   └── expander.c        # Expansión de variables
│   ├── executor/              # ⚠️ PENDIENTE: Ejecución de comandos
│   │   ├── executor.c        # Ejecutor principal
│   │   ├── pipes.c           # Gestión de pipes
│   │   ├── redirections.c    # Gestión de redirecciones
│   │   └── path.c            # Búsqueda en PATH
│   ├── builtins/              # ⚠️ PENDIENTE: Built-in commands
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── pwd.c
│   │   ├── export.c
│   │   ├── unset.c
│   │   ├── env.c
│   │   └── exit.c
│   ├── signals/               # ⚠️ PENDIENTE: Gestión de señales
│   │   └── signals.c
│   ├── env/                   # ⚠️ PENDIENTE: Variables de entorno
│   │   ├── env_manager.c     # Gestión de environ
│   │   └── env_utils.c       # Búsqueda y modificación
│   └── utils/                 # ⚠️ PENDIENTE: Funciones auxiliares
│       ├── errors.c          # Manejo de errores
│       ├── free.c            # Liberación de memoria
│       └── utils.c           # Utilidades generales
├── libft/                     # ⚠️ PENDIENTE: Librería propia
│   ├── Makefile
│   └── *.c                   # Funciones de string, etc.
├── proyecto_base/             # ✅ Shell base de Mario (referencia)
│   ├── Shell_project.c
│   ├── job_control.c
│   ├── job_control.h
│   └── parse_redir.h
└── obj/                       # Archivos objeto compilados
```

### 🏗️ Arquitectura del Sistema (Flujo de Ejecución)

```
┌─────────────────────────────────────────────────────────────────┐
│                         MINISHELL                               │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│  1. READLINE: Leer input del usuario                            │
│     → prompt: "COMMAND->"                                       │
│     → add_history()                                             │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│  2. LEXER: Tokenización                                         │
│     Input:  echo "hello $USER" > file.txt                       │
│     Output: [WORD:echo] [DQUOTE:hello $USER] [REDIR:>]         │
│             [WORD:file.txt]                                     │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│  3. EXPANDER: Expansión de variables                            │
│     Input:  [DQUOTE:hello $USER]                                │
│     Output: [WORD:hello mario]                                  │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│  4. PARSER: Análisis sintáctico                                 │
│     Crear estructura de comandos:                               │
│     cmd: {args: ["echo", "hello mario"],                        │
│          redir_out: "file.txt", redir_type: TRUNC}              │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│  5. EXECUTOR: Ejecución                                         │
│     │                                                            │
│     ├─ Es built-in? → Ejecutar directamente                     │
│     │                                                            │
│     └─ Es externo?   → fork() + execve()                        │
│                          ├─ Buscar en PATH                      │
│                          ├─ Configurar redirecciones (dup2)     │
│                          ├─ Configurar pipes                    │
│                          └─ execve(ruta, args, environ)         │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│  6. WAIT: Esperar finalización                                  │
│     → waitpid() si foreground                                   │
│     → actualizar $?                                             │
│     → liberar memoria                                           │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
                     [Volver al paso 1]
```

---

## 🔨 Compilación

```bash
# Compilar el proyecto
make

# Limpiar archivos objeto
make clean

# Limpiar todo (incluyendo ejecutable)
make fclean

# Recompilar todo
make re

# Compilar con bonus
make bonus
```

---

## 🚀 Uso

```bash
# Ejecutar minishell
./minishell

# Ejemplos de comandos
COMMAND-> ls -la
COMMAND-> cat file.txt | grep "text" | wc -l
COMMAND-> echo "Hello $USER"
COMMAND-> cd /tmp
COMMAND-> export VAR=value
COMMAND-> echo $VAR
COMMAND-> exit
```

---

## 📚 Funciones Permitidas

### Readline
- `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`

### I/O
- `printf`, `write`, `read`, `open`, `close`, `access`

### Procesos
- `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `execve`, `exit`

### Señales
- `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`

### Archivos y Directorios
- `stat`, `lstat`, `fstat`, `unlink`, `opendir`, `readdir`, `closedir`

### File Descriptors
- `dup`, `dup2`, `pipe`, `isatty`, `ttyname`, `ttyslot`, `ioctl`

### Sistema
- `getcwd`, `chdir`, `getenv`, `strerror`, `perror`

### Terminal
- `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### Memoria
- `malloc`, `free`

---

## 🎓 Conceptos Clave a Estudiar

1. **Procesos y Fork**: Creación de procesos hijo
2. **File Descriptors**: stdin (0), stdout (1), stderr (2)
3. **Redirecciones**: dup2, open, close
4. **Pipes**: Comunicación entre procesos
5. **Señales**: SIGINT, SIGQUIT, SIGTSTP, SIGCHLD
6. **Variables de entorno**: getenv, setenv, environ
7. **Parsing**: Tokenización, análisis léxico/sintáctico
8. **Control de terminal**: tcsetpgrp, setpgid
9. **Exit status**: $? y códigos de retorno

---

## 🧪 Testing

### 📋 Tabla de Comandos de Test por Funcionalidad

| Categoría | Comando de Test | Resultado Esperado | Prioridad |
|-----------|----------------|-------------------|-----------|
| **Básico** | `ls` | Listar archivos | Alta |
| **Básico** | `/bin/ls` | Listar archivos (ruta absoluta) | Alta |
| **Básico** | `./minishell` | Error o ejecutar si existe | Alta |
| **Built-in** | `echo hola` | `hola` | Alta |
| **Built-in** | `echo -n hola` | `hola` (sin \n) | Alta |
| **Built-in** | `pwd` | Directorio actual | Alta |
| **Built-in** | `cd /tmp && pwd` | `/tmp` | Alta |
| **Built-in** | `cd ..` | Subir directorio | Media |
| **Built-in** | `export VAR=42` | Sin output | Alta |
| **Built-in** | `env \| grep VAR` | Mostrar VAR | Alta |
| **Built-in** | `unset VAR` | Sin output | Media |
| **Built-in** | `exit` | Salir | Alta |
| **Variable** | `echo $HOME` | Tu home | Alta |
| **Variable** | `echo $USER` | Tu usuario | Alta |
| **Variable** | `echo $?` | Exit code anterior | Alta |
| **Variable** | `echo "$USER"` | Expandir dentro de "" | Media |
| **Variable** | `echo '$USER'` | NO expandir en '' | Media |
| **Redir <** | `cat < file.txt` | Contenido del archivo | Alta |
| **Redir >** | `echo test > out.txt` | Crear/sobreescribir | Alta |
| **Redir >>** | `echo test >> out.txt` | Append | Media |
| **Heredoc** | `cat << EOF` | Leer hasta EOF | Media |
| **Pipe** | `ls \| wc -l` | Número de archivos | Alta |
| **Pipe** | `cat file \| grep txt \| wc -l` | Pipe múltiple | Alta |
| **Mix** | `cat < in \| grep a > out` | Redir + pipe | Alta |
| **Señal** | `sleep 10` + ctrl-C | Interrumpir | Media |
| **Señal** | ctrl-D (prompt vacío) | Salir | Alta |
| **Señal** | ctrl-\ | No hacer nada | Baja |
| **Comillas** | `echo "hola 'mundo'"` | `hola 'mundo'` | Media |
| **Comillas** | `echo 'hola "mundo"'` | `hola "mundo"` | Media |
| **Error** | `comandonoexiste` | Error + $?=127 | Media |
| **Error** | `cat archivonoexiste` | Error + mensaje | Media |

### Tests Básicos
```bash
# Built-ins
echo "Test de echo"
echo -n "Sin salto de linea"
cd /tmp && pwd
export TEST=42 && echo $TEST
env | grep TEST
unset TEST
exit
```

### Tests de Redirección
```bash
# Input/Output
echo "texto" > file.txt
cat < file.txt
echo "append" >> file.txt
cat file.txt

# Heredoc
cat << EOF
linea 1
linea 2
EOF
```

### Tests de Pipes
```bash
ls -l | grep ".c" | wc -l
cat file.txt | head -5 | tail -2
```

### Tests de Señales
```bash
# Ejecutar comando largo y probar:
# - ctrl-C (debe interrumpir y mostrar nuevo prompt)
# - ctrl-D (debe salir del shell)
# - ctrl-\ (no debe hacer nada)
sleep 100
```

### Tests de Comillas
```bash
echo 'Comillas simples $USER'        # No expande
echo "Comillas dobles $USER"         # Expande
echo "Mix 'de' comillas"
```

### Tests de Variables
```bash
echo $HOME
echo $USER
echo $PATH
echo $?    # Exit status del último comando
```

---

## 🐛 Memory Leaks

```bash
# Verificar memory leaks (ignorar los de readline)
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Suprimir leaks de readline
valgrind --leak-check=full --suppressions=readline.supp ./minishell
```

---

## 📌 Notas Importantes

- ⚠️ **UNA sola variable global** permitida (para señales)
- ⚠️ Usar **bash como referencia** en caso de dudas
- ⚠️ Los leaks de `readline()` NO cuentan como leaks del proyecto
- ⚠️ NO implementar funcionalidades no solicitadas
- ⚠️ La parte obligatoria debe estar **PERFECTA** para evaluar bonus

---

## 🔄 Plan de Trabajo

### Fase 1: Setup y Refactorización
- [ ] Crear estructura de directorios
- [ ] Configurar Makefile
- [ ] **⚠️ Refactorizar funciones no permitidas**
- [ ] Integrar readline y historial
- [ ] Setup de libft

### Fase 2: Parsing
- [ ] Diseñar estructura del tokenizador
- [ ] Implementar lexer básico
- [ ] Manejo de comillas simples y dobles
- [ ] Parser de sintaxis
- [ ] Detección de errores sintácticos

### Fase 3: Built-ins y Variables
- [ ] Gestión de environ (copia local)
- [ ] Built-ins: echo, pwd, cd, env, export, unset, exit
- [ ] Expansión de `$VAR`
- [ ] Expansión de `$?`

### Fase 4: Pipes y Redirecciones
- [ ] Pipe simple
- [ ] Pipes múltiples
- [ ] Heredoc `<<`
- [ ] Append `>>`

### Fase 5: Ejecutor y PATH
- [ ] Búsqueda en PATH
- [ ] Rutas relativas y absolutas
- [ ] Integración con `execve()`

### Fase 6: Señales
- [ ] Variable global de señales
- [ ] ctrl-C, ctrl-D, ctrl-\

### Fase 7: Testing y Pulido
- [ ] Tests exhaustivos
- [ ] Corrección de leaks
- [ ] Edge cases
- [ ] Comparación con bash

---

## 🎯 Prioridades

### 🚨 Crítico (hacer primero)
1. Refactorizar funciones no permitidas
2. Implementar búsqueda en PATH
3. Tokenizador básico
4. Gestión de environ

### 🔶 Importante (funcionalidad core)
5. Sistema de pipes
6. Expansión de variables
7. Manejo de comillas
8. Heredoc

### 🔷 Necesario (completitud)
9. Built-ins faltantes
10. Señales interactivas
11. Testing exhaustivo

---

## 📖 Referencias

- **Manual de bash**: `man bash`
- **System calls**: `man 2 <función>`
- **Library functions**: `man 3 <función>`
- **Readline**: `man readline`
- **Tutorial UNIX**: https://www.gnu.org/software/bash/manual/

---

## ✅ Checklist de Evaluación

### Parte Obligatoria
- [ ] Prompt funcional con readline
- [ ] Historial funcional
- [ ] Búsqueda y ejecución desde PATH
- [ ] Máximo UNA variable global
- [ ] Comillas simples `'`
- [ ] Comillas dobles `"`
- [ ] Redirecciones `<`, `>`, `<<`, `>>`
- [ ] Pipes `|`
- [ ] Variables de entorno `$VAR`
- [ ] Exit status `$?`
- [ ] Señales interactivas (ctrl-C, ctrl-D, ctrl-\)
- [ ] Built-ins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- [ ] Sin memory leaks (excepto readline)
- [ ] Makefile correcto
- [ ] Sin errores de norminette

### Parte Bonus
- [ ] Operadores `&&` y `||`
- [ ] Paréntesis `()`
- [ ] Wildcards `*`

---

## 📞 Contacto y Colaboración

**Mario**: Shell base y arquitectura inicial  
**Luis**: Colaborador en desarrollo de funcionalidades

> 💡 **Tip**: Usar este README como guía de progreso. Ir marcando los checkboxes conforme se completen las tareas.

---

## 💡 Tips y Consejos

### � Por dónde empezar
1. Refactorizar el código base (funciones no permitidas)
2. Configurar Makefile y estructura
3. Implementar tokenizador (base de todo)

### 🔍 Testing incremental
```bash
# Comandos simples
./minishell
COMMAND-> ls
COMMAND-> /bin/ls

# Built-ins
COMMAND-> pwd
COMMAND-> cd /tmp && pwd

# Variables
COMMAND-> echo $HOME
COMMAND-> export TEST=42 && echo $TEST

# Redirecciones
COMMAND-> echo "test" > file.txt
COMMAND-> cat < file.txt

# Pipes
COMMAND-> ls | wc -l

# Comillas
COMMAND-> echo 'hola $USER'
COMMAND-> echo "hola $USER"
```

### 🐛 Errores Comunes

- **Memory leaks**: Liberar strings duplicados, cuidado con tokens del parser
- **File descriptors**: Cerrar TODOS los fds después de `dup2()`
- **Pipes**: Cerrar ambos extremos del pipe en padre si no los usa
- **Señales**: Variable global debe ser `volatile sig_atomic_t`
- **PATH**: `execve()` necesita ruta completa + `environ` como 3er argumento

### � Debugging
```bash
# Valgrind
valgrind --leak-check=full --track-fds=yes ./minishell

# GDB
gdb ./minishell
(gdb) run
(gdb) backtrace
```

### 📚 Recursos
- `man bash` - Referencia principal
- `man 2 <función>` - System calls
- `man 7 signal` - Señales
- Testers de 42: mpanic, minishell_tester

---

##  Git Workflow

```bash
# Crear ramas por funcionalidad
git checkout -b feature/parser
git checkout -b feature/pipes

# Commits descriptivos
git commit -m "feat: add tokenizer"
git commit -m "fix: memory leak in pipes"
git commit -m "refactor: replace execvp"
```

---

## ✅ Checklist de Entrega
- [ ] Código compila sin warnings con -Wall -Werror -Wextra
- [ ] Norminette pasa en todos los archivos
- [ ] Makefile tiene todas las reglas requeridas
- [ ] No hay memory leaks (excepto readline)
- [ ] Todos los built-ins funcionan correctamente
- [ ] Pipes múltiples funcionan
- [ ] Redirecciones funcionan (incluyendo heredoc)
- [ ] Comillas funcionan correctamente
- [ ] Variables de entorno se expanden
- [ ] $? funciona correctamente
- [ ] Señales interactivas funcionan (ctrl-C, ctrl-D, ctrl-\)
- [ ] PATH funciona correctamente
- [ ] Comportamiento igual a bash en casos normales
- [ ] Manejo de errores similar a bash
- [ ] Una sola variable global (señales)
- [ ] README actualizado
- [ ] Código documentado

---

**Última actualización**: 18 de octubre de 2025

> 💪 **¡Buena suerte!** Paso a paso, feature por feature. 🚀
