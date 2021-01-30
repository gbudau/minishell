/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 22:12:42 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/29 14:35:21 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/env.h"

static char	**create_argv_array(t_list *head)
{
	t_token	*token;
	char	**argv;
	int		i;
	int		len;

	len = ft_lstsize(head);
	if (len == 0)
		return (NULL);
	argv = ft_calloc((len + 1), sizeof(*argv));
	if (argv == NULL)
		error_exit();
	i = 0;
	while (head != NULL)
	{
		token = head->content;
		argv[i] = ft_strdup(token->str);
		if (argv[i] == NULL)
			error_exit();
		head = head->next;
		i++;
	}
	return (argv);
}

void		word_exp_argv(t_command *cmd, t_list *environ, int *last_status)
{
	t_list	*head;
	t_list	*word_list;
	int		i;

	i = 0;
	head = NULL;
	if (cmd->argv == NULL)
		return ;
	while (cmd->argv[i])
	{
		word_list = variable_expansion(&cmd->argv[i], environ, last_status);
		ft_lstadd_back(&head, word_list);
		i++;
	}
	cmd->argc = ft_lstsize(head);
	ft_free_strarr(cmd->argv);
	cmd->argv = create_argv_array(head);
	ft_lstclear(&head, clear_token);
}
