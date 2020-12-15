/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:48:29 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/15 19:53:16 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** TODO:
** Remove this function when submiting the project
*/

void	print_commands(t_list *commands)
{
	t_command	*cmd;
	size_t		i;

	setvbuf(stdout, NULL, _IONBF, 0);
	while (commands != NULL)
	{
		cmd = commands->content;
		printf("\nArguments counter = %d\n", cmd->argc);
		printf("Command arguments:\n");
		i = 0;
		if (cmd->argc != 0)
		{
			while (cmd->argv[i])
				printf("%s\n", cmd->argv[i++]);
		}
		if (cmd->input)
			printf("Input file: %s\n", cmd->input);
		if (cmd->output)
			printf("Output file: %s\n", cmd->output);
		printf("Command is piped: %d \n", cmd->ispipe);
		printf("Exit status of the previous command: %d\n", cmd->status);
		printf("Output redirect type: %d\n", cmd->redirect_type);
		commands = commands->next;
	}
}

/*
** TODO:
** Remove this function when submiting the project
*/

void	print_tokens(t_list *tokens)
{
	t_token				*token;
	const char			*token_types[] = {"TOKEN_PIPE",
		"TOKEN_SEMICOLON",
		"TOKEN_SINGLE_QUOTE",
		"TOKEN_DOUBLE_QUOTE",
		"TOKEN_GREAT",
		"TOKEN_LESS",
		"TOKEN_DGREAT",
		"TOKEN_WORD"};

	if (tokens == NULL)
		return ;
	while (tokens != NULL)
	{
		token = tokens->content;
		printf("%s = %s\n", token_types[token->type], token->str);
		tokens = tokens->next;
	}
}
