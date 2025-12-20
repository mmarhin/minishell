/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:02:01 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 15:32:43 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		shell->exit_status = 1;
		return ;
	}
	ft_putendl_fd(buffer, 1);
	shell->exit_status = 0;
}
