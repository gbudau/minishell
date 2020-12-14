/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:01:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/14 16:10:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/command.h"

t_command	*create_new_command(void)
{
	t_command *cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		error_exit();
	ft_bzero(cmd, sizeof(*cmd));
	return (cmd);
}

void		skip_semicolon_tokens(t_list **tokens)
{
	t_token *t;

	while (*tokens != NULL)
	{
		t = (*tokens)->content;
		if (t->type != TOKEN_SEMICOLON)
			break ;
		*tokens = (*tokens)->next;
	}
}

void		add_argument(t_list **tokens, t_command *cmd)
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

int			add_pipe(t_list **tokens, t_command *cmd)
{
	t_token	*token;

	*tokens = (*tokens)->next;
	if (cmd->argc == 0 || *tokens == NULL)
		return (1);
	token = (*tokens)->content;
	if (token->type != TOKEN_WORD)
		return (1);
	cmd->ispipe = 1;
	return (0);
}

int			add_input_redirection(t_list **tokens, t_command *cmd)
{
	t_token	*token;

	*tokens = (*tokens)->next;
	if (tokens == NULL || cmd->input != NULL)
		return (1);
	token = (*tokens)->content;
	if (token->type != TOKEN_WORD)
		return (1);
	cmd->input = ft_strdup(token->str);
	if (cmd->input == NULL)
		error_exit();
	*tokens = (*tokens)->next;
	return (0);
}

int			add_output_redirection(t_list **tokens, t_command *cmd,
		int redirect_type)
{
	t_token *token;

	*tokens = (*tokens)->next;
	if (tokens == NULL || cmd->output != NULL)
		return (1);
	token = (*tokens)->content;
	if (token->type != TOKEN_WORD)
		return (1);
	cmd->output = ft_strdup(token->str);
	if (cmd->output == NULL)
		error_exit();
	cmd->redirect_type = redirect_type;
	*tokens = (*tokens)->next;
	return (0);
}

int			add_command(t_list **tokens, t_command *cmd)
{
	t_token	*token;
	int		error;

	error = FALSE;
	while (*tokens != NULL && !error)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_SEMICOLON)
			break ;
		else if (token->type == TOKEN_PIPE)
		{
			error = add_pipe(tokens, cmd);
			break ;
		}
		else if (token->type == TOKEN_WORD)
			add_argument(tokens, cmd);
		else if (token->type == TOKEN_LESS)
			error = add_input_redirection(tokens, cmd);
		else if (token->type == TOKEN_GREAT)
			error = add_output_redirection(tokens, cmd, REDIRECTION_OUTPUT);
		else if (token->type == TOKEN_DGREAT)
			error = add_output_redirection(tokens, cmd, REDIRECTION_APPEND);
	}
	if (cmd->argc == 0)
		error = TRUE;
	return (error == TRUE ? -1 : 0);
}

void		create_commands(t_list *tokens, t_list **commands)
{
	t_command	*cmd;
	t_list		*node;

	while (tokens != NULL)
	{
		skip_semicolon_tokens(&tokens);
		if (tokens == NULL)
			break ;
		cmd = create_new_command();
		if (cmd == NULL)
			error_exit();
		node = ft_lstnew(cmd);
		if (node == NULL)
			error_exit();
		ft_lstadd_front(commands, node);
		if (add_command(&tokens, (*commands)->content) == -1)
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			ft_lstclear(commands, clear_command);
			break ;
		}
	}
	ft_lstrev(commands);
}

void		print_commands(t_list *commands)
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
** TODO: Remove printing of tokens and commands before submitting
*/

void		parse(t_shell *shell, char *input)
{
	t_list	*tokens;

	tokens = tokenize(input);
	word_expansion(&tokens, shell->environ, shell->last_status);
	if (FALSE)
		print_tokens(tokens);
	create_commands(tokens, &shell->commands);
	if (FALSE)
		print_commands(shell->commands);
	ft_lstclear(&tokens, clear_token);
}
