/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:01:10 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 22:27:43 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/command.h"

int					skip_semicolon_token(t_list **tokens, t_command *cmd)
{
	t_token *t;

	if (*tokens != NULL)
	{
		t = (*tokens)->content;
		if (t->type == TOKEN_SEMICOLON)
		{
			if (cmd->argv == NULL && cmd->output == NULL && cmd->input == NULL)
				return (ERR_UNEXPECTED_TOKEN_SEMICOLON);
			*tokens = (*tokens)->next;
		}
	}
	if (cmd->redirection_error)
		return (ERR_REDIRECTION);
	return (NO_PARSER_ERROR);
}

int					parse_error_token_type(int token_type)
{
	if (token_type == TOKEN_SEMICOLON)
		return (ERR_UNEXPECTED_TOKEN_SEMICOLON);
	else if (token_type == TOKEN_PIPE)
		return (ERR_UNEXPECTED_TOKEN_PIPE);
	else if (token_type == TOKEN_LESS)
		return (ERR_UNEXPECTED_TOKEN_LESS);
	else if (token_type == TOKEN_GREAT)
		return (ERR_UNEXPECTED_TOKEN_GREAT);
	else if (token_type == TOKEN_DGREAT)
		return (ERR_UNEXPECTED_TOKEN_DGREAT);
	return (NO_PARSER_ERROR);
}

static t_command	*create_new_command(void)
{
	t_command *cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		error_exit();
	ft_bzero(cmd, sizeof(*cmd));
	return (cmd);
}

static void			create_commands(t_list *tokens, t_shell *shell)
{
	t_command	*cmd;
	t_list		*node;
	int			error;

	while (tokens != NULL)
	{
		cmd = create_new_command();
		if (cmd == NULL)
			error_exit();
		node = ft_lstnew(cmd);
		if (node == NULL)
			error_exit();
		ft_lstadd_front(&shell->commands, node);
		error = add_command(&tokens, shell);
		if (error && error != ERR_REDIRECTION)
		{
			error_unexpected_token(error);
			ft_lstclear(&shell->commands, clear_command);
			shell->last_status = 2;
			return ;
		}
	}
	ft_lstrev(&shell->commands);
}

void				parse(t_shell *shell, char *input)
{
	t_list	*tokens;

	tokens = tokenize(input, &shell->last_status);
	create_commands(tokens, shell);
	ft_lstclear(&tokens, clear_token);
}
