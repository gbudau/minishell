/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_exp_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 21:50:31 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 23:15:16 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/env.h"

static void	set_word_to_node_content(char **word, t_list *word_list)
{
	t_token *token;

	free(*word);
	token = word_list->content;
	*word = ft_strdup(token->str);
	if (*word == NULL)
		error_exit();
}

static int	print_ambiguous_redirect(char *str, int *last_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	*last_status = 1;
	return (-1);
}

int			expand_word(char **word, t_list *environ, int *last_status)
{
	char	*copy;
	int		error;
	t_list	*word_list;

	if (*word == NULL)
		return (0);
	copy = ft_strdup(*word);
	if (copy == NULL)
		error_exit();
	error = 0;
	word_list = NULL;
	variable_expansion(word, &word_list, environ, last_status);
	if (ft_lstsize(word_list) == 1)
		set_word_to_node_content(word, word_list);
	else
		error = print_ambiguous_redirect(copy, last_status);
	ft_lstclear(&word_list, clear_token);
	free(copy);
	return (error);
}
