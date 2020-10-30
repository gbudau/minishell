/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:19:21 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/22 16:42:10 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			word_start = s;
			i++;
		}
		if ((state == IN && *(s + 1) == c) || (state == IN && *(s + 1) == '\0'))
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
