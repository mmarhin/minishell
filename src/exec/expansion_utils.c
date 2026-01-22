/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:40:00 by lanton-m         #+#    #+#             */
/*   Updated: 2025/12/19 15:33:13 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*final_result(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (free(s1), NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	free(s1);
	return (result);
}

char	*append_char(char *result, char c)
{
	char	str[2];
	char	*new_res;

	str[0] = c;
	str[1] = '\0';
	new_res = ft_strjoin(result, str);
	if (!new_res)
		return (NULL);
	return (free(result), new_res);
}

char	*expand_tilde(char *str, t_shell *shell, t_quote_type quote)
{
	char	*home;
	char	*result;

	if (quote != NO_QUOTE)
		return (ft_strdup(str));
	if (str[0] != '~')
		return (ft_strdup(str));
	if (str[1] != '\0' && str[1] != '/')
		return (ft_strdup(str));
	home = get_env(shell, "HOME");
	if (!home)
		return (ft_strdup(str));
	if (str[1] == '\0')
		result = ft_strdup(home);
	else
		result = ft_strjoin(home, str + 1);
	return (result);
}

char	*get_var_name(char **str)
{
	size_t		key_len;
	char		*key;

	key_len = 0;
	if (**str == '?')
		return ((*str)++, ft_strdup("?"));
	if (!ft_isalpha((*str)[key_len]) && (*str)[key_len] != '_')
		return (NULL);
	while ((*str)[key_len])
	{
		if (!ft_isalpha((*str)[key_len]) && !ft_isdigit((*str)[key_len])
			&& (*str)[key_len] != '_')
			break ;
		key_len++;
	}
	if (!key_len)
		return (NULL);
	key = malloc(sizeof(char) * (key_len + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, *str, key_len + 1);
	*str += key_len;
	return (key);
}

char	*expand_variable(char *var_name, t_shell *shell)
{
	if (!var_name)
		return (ft_strdup("$"));
	if (*var_name == '?')
		return (ft_itoa(shell->exit_status));
	if (!get_env(shell, var_name))
		return (ft_strdup(""));
	return (ft_strdup(get_env(shell, var_name)));
}
