/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:02:19 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 15:34:12 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_unset(t_shell *shell, char **args)
{
	int		i;
	int		err_cod;

	i = 1;
	err_cod = 0;
	if (!shell)
		return ;
	if (args[1])
	{
		while (args[i])
		{
			if (valid_arg(args[i]))
				unset_env(shell, args[i]);
			else
			{
				ft_putstr_fd("unset: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				err_cod = 1;
			}
			i++;
		}
	}
	shell->exit_status = err_cod;
}
