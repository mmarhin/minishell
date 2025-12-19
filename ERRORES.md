# 🔴 Lista de Errores del Tester - Minishell

## 📊 Resumen General

| Métrica | Valor |
|---------|-------|
| **Total Tests** | 958 |
| **Tests Pasados** | 708 |
| **Leaks** | 0 ✅ |
| **STD_OUT Fallidos** | 188 |
| **STD_ERR Fallidos** | 85 |
| **EXIT_CODE Fallidos** | 86 |
| **Total Checks Fallidos** | 359 |
| **Total Checks Pasados** | 2515 |

---

## 🔥 Errores Críticos por Categoría

### 1. COMPARE PARSING (0_compare_parsing.sh)
**Problema principal**: Expansión de variables y parsing de quotes

| Test | Error | Archivo:Línea |
|------|-------|---------------|
| 6 | STD_OUT ❌ | 0_compare_parsing.sh:16 |
| 7 | STD_OUT ❌ | 0_compare_parsing.sh:18 |
| 9 | STD_OUT ❌ | 0_compare_parsing.sh:22 |
| 10 | STD_OUT ❌ | 0_compare_parsing.sh:24 |
| 11 | STD_OUT ❌ | 0_compare_parsing.sh:26 |
| 12 | STD_OUT ❌ | 0_compare_parsing.sh:28 |
| 14 | STD_OUT ❌ | 0_compare_parsing.sh:32 |
| 15 | STD_OUT ❌ | 0_compare_parsing.sh:34 |
| 24-30 | STD_OUT ❌ | 0_compare_parsing.sh:52-64 |
| 42 | STD_OUT ❌ | 0_compare_parsing.sh:88 |
| 45-46 | STD_OUT ❌ | 0_compare_parsing.sh:94-96 |
| 48 | STD_OUT ❌ | 0_compare_parsing.sh:100 |
| 51 | STD_OUT ❌ | 0_compare_parsing.sh:106 |

**Posible causa**: Problema con concatenación de strings en quotes o expansión de `$VAR` pegadas a texto.

---

### 2. PARSING HELL (10_parsing_hell.sh)
**Problema principal**: Parsing complejo con quotes mixtas y exit codes

| Test | Error | Exit Code | Archivo:Línea |
|------|-------|-----------|---------------|
| 12 | STD_OUT ❌, EXIT_CODE ❌ | 127 vs 0 | 10_parsing_hell.sh:28 |
| 14 | STD_OUT ❌, EXIT_CODE ❌ | 127 vs 0 | 10_parsing_hell.sh:32 |
| 15 | STD_OUT ❌, EXIT_CODE ❌ | 127 vs 0 | 10_parsing_hell.sh:34 |
| 16 | EXIT_CODE ❌ | 0 vs 1 | 10_parsing_hell.sh:36 |
| 22, 25-31 | STD_OUT ❌ | - | Varias líneas |
| 41, 42 | STD_OUT ❌ | - | 10_parsing_hell.sh |
| 77, 78 | STD_OUT ❌ | - | 10_parsing_hell.sh |
| 112-114 | STD_OUT ❌ | - | 10_parsing_hell.sh |
| 120-121, 123-124 | STD_OUT ❌ | - | 10_parsing_hell.sh |

---

### 3. BUILTINS (1_builtins.sh)
**Problema principal**: exit, cd, export con argumentos especiales

#### 📌 CD y PATH
| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 8-9 | STD_OUT ❌ | - | :18-20 |
| 11-14 | STD_OUT ❌ | - | :24-32 |
| 16-17 | STD_OUT ❌ | - | :36-38 |

#### 📌 ECHO
| Test | Error | Línea |
|------|-------|-------|
| 27-33 | STD_OUT ❌ | :56-68 |
| 45 | STD_OUT ❌ | :92 |
| 47 | STD_OUT ❌ | :96 |

#### 📌 EXIT (Exit codes incorrectos)
| Test | Exit minishell vs bash | Línea |
|------|------------------------|-------|
| 102 | 1 vs 0 | :233 |
| 122 | 1 vs 0 | :290 |
| 140 | 0 vs 127 | :360 |
| 165, 170, 185 | 1 vs 2 | :420, :430, :460 |
| 200, 207-217 | 1 vs 0 | :490-538 |
| 224 | 1 vs 127 | :552 |
| 225-230 | 1 vs 0 | :554-564 |
| 231 | 1 vs 2 | :566 |

#### 📌 EXPORT (Salida incorrecta - 45 tests fallidos!)
| Tests | Error | Líneas |
|-------|-------|--------|
| 256-299 | STD_OUT ❌ | :631-717 |

**Causa probable**: El formato de `export` sin args debe mostrar `declare -x VAR="value"` pero minishell muestra otro formato.

---

### 4. PIPELINES (1_pipelines.sh)
**🔴 CRÍTICO: SEGFAULT (exit 139)**

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 1 | SEGFAULT 💀 | 139 vs 0 | :4 |
| 2 | SEGFAULT 💀 | 139 vs 0 | :6 |
| 15 | STD_OUT ❌ | - | :32 |
| 25 | STD_ERR ❌, EXIT_CODE ❌ | 127 vs 1 | :55 |
| 26-27 | STD_OUT ❌, EXIT_CODE ❌ | 127 vs 0 | :59-68 |
| 28, 30 | STD_OUT ❌, STD_ERR ❌ | - | :84, :110 |
| 29 | STD_OUT ❌, EXIT_CODE ❌ | 0 vs 2 | :96 |
| 38-40 | STD_OUT ❌, STD_ERR ❌ | - | :151-161 |

**⚠️ PRIORIDAD MÁXIMA**: Corregir los segfaults en tests 1 y 2.

---

### 5. REDIRECTIONS (1_redirs.sh)
**Problema principal**: Redirecciones con heredoc y combinaciones

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 80-88 | TODO ❌ | 127 vs 0 | :186-241 |
| 90 | STD_ERR ❌ | - | :250 |

**Causa probable**: Problema con redirecciones combinadas o con comandos vacíos.

---

### 6. SCMD - Simple Commands (1_scmds.sh)

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 26 | EXIT_CODE ❌ | 126 vs 127 | :84 |

**Causa**: Diferencia entre "command not found" (127) vs "permission denied" (126).

---

### 7. VARIABLES (1_variables.sh)
**Problema principal**: Expansión de `$?` y variables especiales

| Test | Error | Línea |
|------|-------|-------|
| 15-20 | STD_OUT ❌ | :40-50 |
| 25-26 | STD_OUT ❌ | :60-62 |
| 28 | STD_OUT ❌ | :66 |
| 41-43 | STD_OUT ❌ (+ STD_ERR en 43) | :103-120 |
| 45-58 | STD_OUT ❌ | :130-169 |

**Causa probable**: La expansión de `$?` o `$$` no funciona correctamente, o hay problemas con `$VAR` sin definir.

---

### 8. CORRECTION (2_correction.sh)
**Problema principal**: Tests de corrección oficial

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 17-24 | STD_OUT ❌ | 1 vs 2 en test 23 | :39-53 |
| 60-61, 63-70, 75-76, 78 | STD_OUT ❌ | - | :129-165 |
| 114 | STD_OUT ❌, STD_ERR ❌ | - | :277 |

---

### 9. PATH FAILS (2_path_check.sh)

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 1 | STD_OUT ❌, STD_ERR ❌ | - | :5 |
| 5 | TODO ❌ | 1 vs 0 | :26 |
| 11 | TODO ❌ | 0 vs 127 | :43 |
| 12 | STD_OUT ❌ | - | :47 |
| 14 | TODO ❌ | 0 vs 127 | :68 |

---

### 10. SYNTAX ERRORS (8_syntax_errors.sh)

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 15-16 | EXIT_CODE ❌ | 126 vs 127 | :33-35 |
| 17 | STD_ERR ❌, EXIT_CODE ❌ | 0 vs 2 | :37 |
| 20-22 | EXIT_CODE ❌ | 0 vs 2 | :43-49 |

---

### 11. WILD (9_go_wild.sh)

| Test | Error | Línea |
|------|-------|-------|
| 10 | STD_OUT ❌ | :30 |
| 13-15 | STD_OUT ❌ (+ STD_ERR en 14) | :46-52 |

---

### 12. ADSF.C (Tests adicionales)
**🔴 Muchos fallos con exit 127**

| Test | Error | Exit Code | Línea |
|------|-------|-----------|-------|
| 1-4 | STD_ERR ❌, EXIT_CODE ❌ | 127 vs 0 | :4-23 |
| 5 | STD_OUT ❌, EXIT_CODE ❌ | 0 vs 2 | :26 |
| 6 | EXIT_CODE ❌ | 127 vs 2 | :115 |
| 7-11 | STD_ERR ❌, EXIT_CODE ❌ | 127 vs 0 | :123-167 |
| 12-15 | TODO ❌ | 127 vs 0 | :180-403 |

---

## 🎯 Prioridades de Corrección

### 🔴 CRÍTICO (Corregir primero)
1. **SEGFAULTS en PIPELINES tests 1-2** - Exit code 139
2. **Exit codes de EXIT builtin** - Muchos tests fallan por esto
3. **Formato de EXPORT** - 45 tests fallan por formato incorrecto

### 🟠 ALTO
4. **Expansión de variables** - `$?`, variables sin definir
5. **Parsing de quotes** - Concatenación de strings
6. **Redirecciones combinadas** - Tests 80-88

### 🟡 MEDIO
7. **Exit codes 126 vs 127** - Permission denied vs not found
8. **CD con rutas especiales**
9. **Echo con flags**

---

## 📝 Comandos para ver tests específicos

```bash
# Ver el contenido de un test específico
head -n LINEA /home/mamarin-/42_minishell_tester/cmds/mand/ARCHIVO.sh | tail -n 5

# Ejemplo para ver test 1 de pipelines
head -n 6 /home/mamarin-/42_minishell_tester/cmds/mand/1_pipelines.sh | tail -n 3

# Re-ejecutar solo una categoría
mstest m builtins
```

---

## ✅ Categorías sin errores (o mínimos)
- REDIRS (1-79): ✅ Perfecto
- SCMD (1-25, 27-42): ✅ Casi perfecto (solo test 26)
- SYNTAX ERRORS (1-14, 18-19, 23-49): ✅ Mayoría bien
- WILD (1-9, 11-12, 16-17): ✅ Mayoría bien
