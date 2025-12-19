/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:52:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/19 17:02:32 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RED "\001\033[1;91m\002"
#define RESET "\001\033[0m\002"

void	print_banner(void)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd(" __  __ ___ _   _ ___ ____  _   _ _____ _     _", 1);
	ft_putendl_fd("|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |", 1);
	ft_putendl_fd("| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |", 1);
	ft_putendl_fd("| |  | || || |\\  || | ___) |  _  | |___| |___| |___", 1);
	ft_putendl_fd("|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("           by mmarhin & lanton-m", 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd(RESET, 1);
}

char	*get_prompt(int exit_status)
{
	char	*code;
	char	*tmp;
	char	*prompt;

	code = ft_itoa(exit_status);
	tmp = ft_strjoin(RED "minishell [", code);
	free(code);
	prompt = ft_strjoin(tmp, "] > " RESET);
	free(tmp);
	return (prompt);
}
