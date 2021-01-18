/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:16:30 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/17 21:09:56 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/command.h"

static void	add_argument(t_list **tokens, t_command *cmd)
{
	t_token	*token;
	char	**tmp_argv;
	size_t	i;

	tmp_argv = cmd->argv;
	cmd->argv = ft_calloc(sizeof(*cmd->argv), cmd->argc + 2);
	if (cmd->argv == NULL)
		error_exit();
	i = 0;
	while (tmp_argv && tmp_argv[i])
	{
		cmd->argv[i] = ft_strdup(tmp_argv[i]);
		if (cmd->argv[i] == NULL)
			error_exit();
		i++;
	}
	ft_free_strarr(tmp_argv);
	token = (*tokens)->content;
	cmd->argv[cmd->argc] = ft_strdup(token->str);
	cmd->argc++;
	*tokens = (*tokens)->next;
}

static int	add_pipe(t_list **tokens, t_command *cmd)
{
	t_token	*token;

	*tokens = (*tokens)->next;
	if (cmd->argv == NULL && cmd->input == NULL && cmd->output == NULL)
		return (ERR_UNEXPECTED_TOKEN_PIPE);
	if (*tokens == NULL)
		return (ERR_UNEXPECTED_NEWLINE);
	token = (*tokens)->content;
	if (token->type == TOKEN_PIPE || token->type == TOKEN_SEMICOLON)
		return (parse_error_token_type(token->type));
	if (cmd->argv != NULL)
		cmd->ispipe = 1;
	return (NO_PARSER_ERROR);
}

static int	add_input_redirection(t_list **tokens, t_command *cmd)
{
	t_token	*token;

	*tokens = (*tokens)->next;
	if (*tokens == NULL)
		return (ERR_UNEXPECTED_NEWLINE);
	if (cmd->input != NULL)
		return (ERR_UNEXPECTED_TOKEN_LESS);
	if (cmd->output == NULL)
		cmd->redirection_order = REDIRECT_INPUT_FIRST;
	token = (*tokens)->content;
	if (token->type != TOKEN_WORD)
		return (parse_error_token_type(token->type));
	cmd->input = ft_strdup(token->str);
	if (cmd->input == NULL)
		error_exit();
	*tokens = (*tokens)->next;
	return (NO_PARSER_ERROR);
}

static int	add_output_redirection(t_list **tokens, t_command *cmd,
		int redirect_type)
{
	t_token *token;

	*tokens = (*tokens)->next;
	if (*tokens == NULL)
		return (ERR_UNEXPECTED_NEWLINE);
	if (cmd->output != NULL)
	{
		if (redirect_type == REDIRECTION_OUTPUT)
			return (ERR_UNEXPECTED_TOKEN_GREAT);
		else if (redirect_type == REDIRECTION_APPEND)
			return (ERR_UNEXPECTED_TOKEN_DGREAT);
	}
	if (cmd->input == NULL)
		cmd->redirection_order = REDIRECT_OUTPUT_FIRST;
	token = (*tokens)->content;
	if (token->type != TOKEN_WORD)
		return (parse_error_token_type(token->type));
	cmd->output = ft_strdup(token->str);
	if (cmd->output == NULL)
		error_exit();
	cmd->redirect_type = redirect_type;
	*tokens = (*tokens)->next;
	return (NO_PARSER_ERROR);
}

int			add_command(t_list **tokens, t_command *cmd)
{
	t_token	*token;
	int		error;

	error = NO_PARSER_ERROR;
	while (*tokens != NULL && !error)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_SEMICOLON)
			return (skip_semicolon_token(tokens, cmd));
		else if (token->type == TOKEN_PIPE)
			return (add_pipe(tokens, cmd));
		else if (token->type == TOKEN_WORD)
			add_argument(tokens, cmd);
		else if (token->type == TOKEN_LESS)
			error = add_input_redirection(tokens, cmd);
		else if (token->type == TOKEN_GREAT)
			error = add_output_redirection(tokens, cmd, REDIRECTION_OUTPUT);
		else if (token->type == TOKEN_DGREAT)
			error = add_output_redirection(tokens, cmd, REDIRECTION_APPEND);
	}
	return (error);
}
