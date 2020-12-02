/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:01:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/02 21:23:10 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** The flag variable control if ft_isdigit is used or not
** This is because POSIX specifies that
** environmental variables don't begin with a digit
** https://pubs.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap08.html
*/

int		is_env_format(char c, int flag)
{
	return (ft_isalpha(c) || c == '_' || (flag && ft_isdigit(c)));
}

char	*env_value(char **words, size_t *i, t_list *environ)
{
	size_t	len;
	char	*env_name;
	char	*tmp;

	(*i)++;
	len = *i;
	while (is_env_format((*words)[len], 1))
		len++;
	if ((env_name = ft_strndup(*words + *i, len - *i)) == NULL)
		error_exit();
	tmp = env_name;
	env_name = get_env(environ, env_name);
	free(tmp);
	if (env_name == NULL)
	{
		env_name = ft_strdup("");
		if (env_name == NULL)
			error_exit();
	}
	*i += (len - *i);
	return (env_name);
}

size_t	substitute_env(char **words, size_t *i, t_list *environ)
{
	char	*beginning;
	char	*middle;
	char	*end;

	if ((*words)[*i + 1] == '\0' || !is_env_format((*words)[*i + 1], 0))
		return (0);
	if ((beginning = ft_strndup(*words, *i)) == NULL)
		error_exit();
	middle = env_value(words, i, environ);
	if ((end = ft_strndup(*words + *i, ft_strlen(*words + *i))) == NULL)
		error_exit();
	*i = ft_strlen(beginning) + ft_strlen(middle);
	free(*words);
	if ((*words = ft_strjoin_free(beginning, middle, FREE_BOTH)) == NULL)
		error_exit();
	if ((*words = ft_strjoin_free(*words, end, FREE_BOTH)) == NULL)
		error_exit();
	return (1);
}

void	skip_single_quote(char **words, size_t *i)
{
	(*i)++;
	while ((*words)[*i] && (*words)[*i] != '\'')
		(*i)++;
	if ((*words)[*i])
		(*i)++;
}

size_t	parse_double_quotes(char **words, size_t *i, t_list *environ)
{
	size_t	expanded;

	expanded = 0;
	(*i)++;
	while ((*words)[*i] != '\0' && (*words)[*i] != '"')
	{
		if ((*words)[*i] == '\\')
			*i += 2;
		else if ((*words)[*i] == '$')
			expanded = substitute_env(words, i, environ);
		else if ((*words)[*i])
			(*i)++;
	}
	return (expanded);
}

/*
**	t_token	*token;
**
**	(void)environ;
**	token = malloc(sizeof(*token));
**	if (token == NULL)
**		error_exit();
**	token->type = TOKEN_WORD;
**	token->str = ft_strdup(words);
**	if (token->str == NULL)
**		error_exit();
**	*word_list = ft_lstnew(token);
**	if (*word_list == NULL)
**		error_exit();
*/

int		expand_words(char **words, t_list **word_list, t_list *environ)
{
	size_t	expanded;
	size_t	i;

	(void)word_list;
	expanded = 0;
	i = 0;
	while ((*words)[i])
	{
		if ((*words)[i] == '\'')
			skip_single_quote(words, &i);
		else if ((*words)[i] == '"')
			expanded = parse_double_quotes(words, &i, environ);
		else if ((*words)[i] == '\\')
			i += 2;
		else if ((*words)[i] == '$')
			expanded = substitute_env(words, &i, environ);
		else if ((*words)[i])
			i++;
	}
	return (expanded);
}

/*
** //t_list	*tmp;
**
**
** tmp = trav->next;
** if (expand_words(&token->str, &sublist, environ))
** {
** 	*tokens = sublist;
** 	sublist = ft_lstlast(*tokens);
** 	sublist->next = tmp;
** 	tokens = &sublist->next;
** 	ft_lstdelone(trav, clear_token);
** }
*/

void	expansion(t_list **tokens, t_list *environ)
{
	t_list	*trav;
	t_list	*sublist;
	t_token	*token;

	while ((trav = *tokens))
	{
		token = trav->content;
		if (token->type == TOKEN_WORD)
		{
			expand_words(&token->str, &sublist, environ);
			tokens = &trav->next;
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
