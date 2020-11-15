/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:19:21 by gbudau            #+#    #+#             */
/*   Updated: 2020/11/15 16:49:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** While inside a word check if next character is a delimiter or end of string
** s = string of words separated by a delimiter
** state = state of current scan
** c = delimiter character
*/

static int		next_is_delimiter_or_end(const char *s, int state, char c)
{
	return ((state == STATE_IN_WORD && *(s + 1) == c) ||
			(state == STATE_IN_WORD && *(s + 1) == '\0'));
}

/*
** Assign substrings separated by any char in delim into split array
** Return the array of substrings or NULL in case of error
*/

static char		**ft_strtomatr(char **split, const char *s, char c)
{
	char const	*word_start;
	int			i;
	size_t		state;

	i = -1;
	state = 0;
	while (*s != '\0')
	{
		if (*s == c)
			state = STATE_OUT_WORD;
		else if (state == STATE_OUT_WORD)
		{
			state = STATE_IN_WORD;
			word_start = s;
			i++;
		}
		if (next_is_delimiter_or_end(s, state, c))
			if ((split[i] = ft_strndup(word_start, s - word_start + 1)) == NULL)
			{
				ft_free_strarr(split);
				return (NULL);
			}
		s++;
	}
	return (split);
}

/*
** Split the s string into substrings separated by
** any character found in delim
** Return the array of substrings or NULL in case of error
*/

char			**ft_split(const char *s, char c)
{
	size_t		i;
	char		**split;

	if (s == NULL)
		return (NULL);
	i = ft_str_count_c(s, c);
	if (!(split = ft_calloc(i + 1, sizeof(char *))))
		return (NULL);
	return (ft_strtomatr(split, s, c));
}
