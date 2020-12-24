/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:31:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/23 15:26:18 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** The flag variable control if ft_isdigit is used or not
** If it's set to 1 will check if the char is digit else will not check
** This is because POSIX specifies that
** environmental variables don't begin with a digit
** https://pubs.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap08.html
*/

int		is_env_format(char c, int flag)
{
	return (ft_isalpha(c) || c == '_' || (flag && ft_isdigit(c)));
}

/*
** Verify if the environmental variable is in a proper format
** Return -1 in case of allocation error
** Return -2 in case '=' is not found in the string,
** this means the env only has a name and no value set
** Return the index of the '=' char otherwise
** Example str -> "TEST=ok" returns 4
*/

int		verify_env(const char *str)
{
	int	i;

	i = 0;
	while (is_env_format(str[i], i > 0))
		i++;
	if (str[i] == '=')
		return (i);
	else if (str[i] == '\0')
		return (-2);
	return (-1);
}

/*
** Return a string array that is splitted at the index
** Example str - "TEST=ok" and idx = 4
** Returns an array made of "TEST" and "ok"
** Return NULL in case of allocation error or any other error
*/

char	**split_env(const char *str, int idx)
{
	char	**str_array;
	int		env_with_no_value;

	str_array = ft_calloc(sizeof(*str_array), 3);
	if (str_array == NULL)
		return (NULL);
	env_with_no_value = idx < 0;
	if (env_with_no_value)
		idx = 0;
	str_array[0] = ft_strndup(str, idx);
	if (str_array[0] == NULL)
		return (NULL);
	if (env_with_no_value == FALSE)
	{
		str_array[1] = ft_strdup(&str[idx + 1]);
		if (str_array[1] == NULL)
			return (NULL);
	}
	return (str_array);
}

int		compare_env(const void *content, const void *match)
{
	const char	**env;
	const char	*str;

	env = (const char **)content;
	str = match;
	return (ft_strcmp(env[ENV_NAME], str));
}

void	add_env_front(t_list **environ, char **env)
{
	t_list	*node;

	node = ft_lstnew(env);
	if (node == NULL)
		error_exit();
	ft_lstadd_front(environ, node);
}
