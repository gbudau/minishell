/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:01:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/27 18:12:44 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		*expand_words(char *words, t_list **word_list, t_list *environ)
{
	t_token	*token;

	(void)environ;
	token = malloc(sizeof(*token));
	if (token == NULL)
		error_exit();
	token->type = TOKEN_WORD;
	token->str = ft_strdup(words);
	if (token->str == NULL)
		error_exit();
	*word_list = ft_lstnew(token);
	if (*word_list == NULL)
		error_exit();
	return (0);
}

void	expansion(t_list **tokens, t_list *environ)
{
	t_list	*trav;
	t_list	*sublist;
	t_list	*tmp;
	t_token	*token;

	while ((trav = *tokens))
	{
		token = trav->content;
		if (token->type == TOKEN_WORD)
		{
			tmp = trav->next;
			expand_words(token->str, &sublist, environ);
			*tokens = sublist;
			sublist = ft_lstlast(*tokens);
			sublist->next = tmp;
			tokens = &sublist->next;
			ft_lstdelone(trav, clear_token);
		}
		else
			tokens = &trav->next;
	}
}

void	parse(t_shell *shell, char *input)
{
	t_list	*tokens;

	tokens = tokenize(input);
	expansion(&tokens, shell->environ);
	print_tokens(tokens);
	ft_lstclear(&tokens, clear_token);
}
