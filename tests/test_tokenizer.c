/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/11/16 13:13:11 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	test_case(char *input)
{
	t_token	*tokens;

	printf("\nInput:  \"%s\"\n", input);
	tokens = tokenize(input);
	if (tokens)
	{
		printf("Tokens: ");
		print_tokens(tokens);
		free_tokens(tokens);
	}
	else
		printf("Error: tokenize returned NULL\n");
}

int	main(void)
{
	printf("=== TOKENIZER TESTS ===\n");
	test_case("echo hello world");
	test_case("ls | grep txt");
	test_case("cat < input.txt > output.txt");
	test_case("cat << EOF >> file.txt");
	test_case("echo    multiple   spaces");
	test_case("ls|grep|wc");
	test_case("echo test>file<input");
	test_case("   spaces   before   and   after   ");
	printf("\n=== ALL TESTS COMPLETED ===\n");
	return (0);
}
