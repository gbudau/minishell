/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:01:10 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/05 20:03:38 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
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

void		create_commands(t_list *tokens, t_list **commands, int *last_status)
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
			*last_status = 2;
			return ;
		}
	}
	ft_lstrev(commands);
}

void		parse(t_shell *shell, char *input)
{
	t_list	*tokens;

	tokens = tokenize(input, &shell->last_status);
	word_expansion(&tokens, shell->environ, &shell->last_status);
	create_commands(tokens, &shell->commands, &shell->last_status);
	ft_lstclear(&tokens, clear_token);
}
