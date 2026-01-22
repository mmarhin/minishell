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

char	*final_result(char *s1, char *s2, char *s3);
char	*append_char(char *result, char c);
char	*expand_tilde(char *str, t_shell *shell, t_quote_type quote);
char	*get_var_name(char **str);
char	*expand_variable(char *var_name, t_shell *shell);

static char	*process_expansion(char **str, char *result, t_shell *shell)
{
	char	*key;
	char	*value;

	if ((*str)[1] == '"' || (*str)[1] == '\'')
	{
		result = append_char(result, '$');
		(*str)++;
		return (result);
	}
	(*str)++;
	key = get_var_name(str);
	value = expand_variable(key, shell);
	result = final_result(result, value, "");
	return (free(key), free(value), result);
}

static char	*handle_backslash(char **src, char *result, t_quote_type quote)
{
	(*src)++;
	if (!**src)
		return (append_char(result, '\\'));
	if (quote == NO_QUOTE || **src == '$' || **src == '\\'
		|| (quote == DOUBLE_QUOTE && **src == '"'))
	{
		result = append_char(result, **src);
		(*src)++;
	}
	else
		result = append_char(result, '\\');
	return (result);
}

static char	*expand_vars_loop(char *src, t_shell *shell, t_quote_type quote)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*src)
	{
		if (*src == '\\' && (quote == DOUBLE_QUOTE || quote == NO_QUOTE))
			result = handle_backslash(&src, result, quote);
		else if (*src == '$' && (quote == DOUBLE_QUOTE || quote == NO_QUOTE))
			result = process_expansion(&src, result, shell);
		else
		{
			result = append_char(result, *src);
			src++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*expand_string(char *str, t_shell *shell, t_quote_type quote)
{
	char	*tilde_exp;
	char	*result;

	if (quote == SINGLE_QUOTE || quote == MIXED_QUOTE)
		return (ft_strdup(str));
	if (str[0] == '$' && !ft_isalpha(str[1]) && str[1] != '_' && str[1] != '?')
		return (ft_strdup(str));
	tilde_exp = expand_tilde(str, shell, quote);
	if (!tilde_exp)
		return (NULL);
	result = expand_vars_loop(tilde_exp, shell, quote);
	free(tilde_exp);
	return (result);
}
