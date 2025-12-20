/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:02:19 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/20 12:25:11 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	valid_arg(char *key)
{
	int	i;

	i = 1;
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	while (key[i])
	{
		if (key[i] == '=')
			return (0);
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
*/
void	ft_unset(t_shell *shell, char **args)
{
	int		i;

	i = 1;
	if (!shell)
		return ;
	if (args[1])
	{
		while (args[i])
		{
			unset_env(shell, args[i]);
			i++;
		}
	}
	shell->exit_status = 0;
}
