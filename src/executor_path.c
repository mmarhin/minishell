/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:35:46 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/24 00:35:46 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

extern char **environ;

static int is_executable(const char *path) {
    return (access(path, X_OK) == 0);
}

// Une "dir" + "/" + "cmd"
static char *join_path(const char *dir, const char *cmd) {
    size_t ld = strlen(dir), lc = strlen(cmd);
    char *out = malloc(ld + 1 + lc + 1);
    if (!out) return NULL;
    memcpy(out, dir, ld);
    out[ld] = '/';
    memcpy(out + ld + 1, cmd, lc + 1);
    return out;
}

// Devuelve malloc() con ruta completa o NULL si no está en PATH
char *find_in_path(const char *cmd)
{
    if (!cmd || !*cmd)
		return NULL;
    // ya es ruta absoluta o relativa con '/'
    if (ft_strchr(cmd, '/'))
	{
        if (is_executable(cmd)) 
			return strdup(cmd);
        return NULL;
    }
    const char *path = getenv("PATH");
    if (!path || !*path)
		return NULL;
    // copiamos PATH porque vamos a tokenizar
    char *copy = strdup(path);
    if (!copy) 
		return NULL;
    char *saveptr = NULL;
    char *dir = strtok_r(copy, ":", &saveptr);
    while (dir)
	{
        char *full = join_path(dir, cmd);
        if (full && is_executable(full)) {
            free(copy);
            return full; // caller libera
        }
        free(full);
        dir = strtok_r(NULL, ":", &saveptr);
    }
    free(copy);
    return NULL;
}

// En el hijo:
void exec_external(char *const argv[])
{
    char *path;
	
	path = find_in_path(argv[0]);
    if (!path)
	{
        // Mensaje estilo bash: "cmd: command not found"
        dprintf(2, "%s: command not found\n", argv[0]);
        _exit(127);
    }
    execve(path, argv, environ);
    // Si seguimos aquí es error de execve
    dprintf(2, "%s: %s\n", argv[0], strerror(errno));
    free(path);
    _exit(errno == ENOENT ? 127 : 126);
}