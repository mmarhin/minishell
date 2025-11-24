# Minishell - 42 Project

## 📋 Descripción del Proyecto

Implementación de un shell simple en C que replica el comportamiento básico de bash, cumpliendo con los requisitos del proyecto Minishell de 42.

---

## ✅ Progreso Actual


| Área                                      | Progreso aproximado |
|------------------------------------------|----------------------|
| Bucle principal / core de la shell       | 80%                  |
| Gestión de entorno (`env`, `export`...)  | 75%                  |
| Tokenizador / lexer                      | 80%                  |
| Parser (creación de estructuras de cmds) | 70%                  |
| Ejecutor (pipes, paths, redirecciones)   | 70%                  |
| Builtins obligatorios                    | 90%                  |
| Señales y modo interactivo               | 70%                  |
| Limpieza de memoria / errores            | 60%                  |
| Infraestructura (Makefile, includes)     | 85%                  |
| Libft                                    | 100%                 |
| Tests, depuración y casos límite         | 40%                  |
| Bonus                                    | 0% (no iniciado / N/A) |

### Completado

#### 🔧 Infraestructura Base
- [x] Estructura del proyecto organizada
- [x] Makefile funcional
- [x] Gestión de señales (SIGINT, SIGQUIT)
- [x] Bucle principal con readline
- [x] Historial de comandos

#### 🌍 Gestión de Entorno
- [x] Copia del entorno (`copy_environ`)
- [x] Obtener variables (`get_env`)
- [x] Crear/actualizar variables (`set_env`)
- [x] Eliminar variables (`unset_env`)
- [x] Liberación de memoria del entorno

#### ⚙️ Ejecución de Comandos
- [x] Búsqueda de ejecutables en PATH
- [x] Ejecución de comandos externos con `fork` y `execve`
- [x] Captura de exit status
- [x] Gestión básica de procesos

#### 🧹 Utilidades
- [x] Liberación de arrays (`ft_freesplit`)
- [x] Gestión de memoria

---

## 🚧 Pendiente de Implementación

### 📝 Parsing y Tokenización (Prioridad Alta)
- [x] Tokenizador (lexer)
- [x] Parser de comandos
- [x] Manejo de quotes (simples y dobles)
- [ ] Expansión de variables `$VAR`
- [ ] Expansión de `$?` (exit status)

### 🔨 Builtins
- [ ] `echo` con opción `-n`
- [x] `cd` (con path relativo/absoluto)
- [ ] `pwd` (sin opciones)
- [ ] `export` (sin opciones)
- [ ] `unset`
- [ ] `env` (sin opciones ni argumentos)
- [x] `exit`

### 🔀 Operadores y Redirecciones
- [ ] Pipes `|`
- [ ] Redirección entrada `<`
- [ ] Redirección salida `>`
- [ ] Redirección append `>>`
- [ ] Heredoc `<<`

### 🎯 Funcionalidades Avanzadas
- [ ] Manejo de múltiples pipes
- [ ] Variables de entorno `$VAR` en comandos
- [ ] Exit status `$?`
- [ ] CTRL-C, CTRL-D, CTRL-\ según contexto

---

## 👥 División de Trabajo (Por Features Completas)

### 🟦 Luis - Comandos Simples + Builtins

**Feature 1: Parser Simple (Solo comandos sin pipes)**
- [ ] Crear `src/parsing/simple_parser.c`
- [ ] Split por espacios y manejo básico de quotes
- [ ] Expansión de `$VAR` y `$?`
- [ ] Retornar `char **args` simple
- [ ] Testing: imprimir arrays parseados

**Feature 2: Todos los Builtins**
- [ ] `echo` (con `-n`)
- [ ] `pwd`
- [ ] `env`
- [ ] `export`
- [ ] `unset`
- [ ] `cd` (actualizar PWD/OLDPWD)
- [ ] `exit`
- [ ] Dispatcher en `builtins.c`

**Feature 3: Quotes Completas**
- [ ] Quotes simples `'sin expansion'`
- [ ] Quotes dobles `"$VAR expansion"`
- [ ] Manejo de espacios: `echo "hello world"`

**Testing completo:**
```bash
> echo hello $USER
> echo "test $PWD"
> pwd
> cd /tmp
> export VAR=value
> unset VAR
> exit
```

**Ventajas:** Tienes un minishell funcional SIN pipes ni redirecciones. Puedes probarlo end-to-end.

---

### 🟩 Mario - Redirecciones + Pipes

**Feature 1: Redirecciones Simples**
- [ ] Parser para detectar `<`, `>`, `>>`, `<<`
- [ ] Extraer nombre de archivo
- [ ] Implementar redirección input `<`
- [ ] Implementar redirección output `>` y `>>`
- [ ] Implementar heredoc `<<`

**Feature 2: Sistema de Pipes**
- [ ] Parser para detectar `|` y separar comandos
- [ ] Pipe simple entre 2 comandos
- [ ] Múltiples pipes (N comandos)
- [ ] Gestión de procesos y wait

**Feature 3: Integración Total**
- [ ] Combinar redirecciones + pipes
- [ ] Builtins en pipes
- [ ] Edge cases

**Testing completo:**
```bash
> cat < input.txt
> ls > output.txt
> cat << EOF
> ls | grep txt
> cat file | grep test | wc -l
> cat < in | grep x > out
```

**Ventajas:** Trabajas con el executor existente, añades capas progresivamente.

---

## 📊 Estimación de Carga

| Componente | Luis | Mario |
|-----------|------|-------|
| Parser simple | 100% | 0% |
| Builtins (7) | 100% | 0% |
| Quotes | 100% | 0% |
| Redirecciones | 0% | 100% |
| Pipes | 0% | 100% |
| Integración | 50% | 50% |

**Carga total:** ~50% cada uno

**Ventaja:** Cada uno tiene su minishell funcional antes de integrar.

---

## 🔄 Integración Final

**Cuando ambos terminen sus features:**

1. **Luis:** Mejora el parser para detectar pipes y redirecciones
2. **Mario:** Adapta sus funciones para usar el parser de Luis
3. **Juntos:** Testing completo de comandos complejos

**Ejemplo de integración:**
```bash
# Luis puede testear:
> echo "hello $USER"
> cd /tmp && pwd
> export X=1

# Mario puede testear:
> cat < file | grep test > out
> ls | wc -l

# Integrado:
> echo "$USER" | grep root > result.txt
```

---

## 🛠️ Comandos de Compilación

```bash
make          # Compilar proyecto
make clean    # Limpiar objetos
make fclean   # Limpieza completa
make re       # Recompilar todo
```

---

## 📚 Recursos

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- Testers: minishell_tester, 42_minishell_tester

---

## ✨ Autores

**Luis** - Parsing, Tokenización, Expansión, Builtins  
**Mario** - Redirecciones, Pipes, Integración de Ejecución

---

*Última actualización: 16 de Noviembre, 2025*

/* Dejo subido el parser, está practicamente completo, lo único que hace falta es hacer las funciones de limpieza*/
