/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:33:20 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/16 13:33:20 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char **str)
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
		if (!ft_isalpha((*str)[key_len]) && !ft_isdigit((*str)[key_len]) && (*str)[key_len] != '_')
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

static char	*expand_variable(char *var_name, t_shell *shell)
{
	if (!var_name)
		return (ft_strdup("$"));
	if (*var_name == '?')
		return (ft_itoa(shell->exit_status));
	if (!get_env(shell, var_name))
		return (ft_strdup(""));
	return (ft_strdup(get_env(shell, var_name)));

}

static char	*final_result(char *s1, char *s2, char *s3)
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

static char	*process_expansion(char **str, char *result, t_shell *shell)
{
	char	*key;
	char	*value;

	(*str)++;
	key = get_var_name(str);
	value = expand_variable(key, shell);
	result = final_result(result, value, "");
	return (free(key), free(value), result);
}

static char	*append_char(char *result, char c)
{
	char	str[2];
	char	*new_res;

	str[0] = c;
	str[1] = '\0';
	new_res = ft_strjoin(result, str);
	if (!new_res)
		return (NULL);
	return(free(result), new_res);
}

char	*expand_string(char *str, t_shell *shell, t_quote_type quote)
{
	char	*result;
	char	*ptr;

	if (quote == SINGLE_QUOTE)
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '$' && (quote == DOUBLE_QUOTE || quote == NO_QUOTE))
			result = process_expansion(&ptr, result, shell);
		else
		{
			result = append_char(result, *ptr);
			ptr++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}
