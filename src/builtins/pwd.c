/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:02:01 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/15 01:47:21 by lanton-m         ###   ########.fr       */
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
