/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:16:20 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/25 22:19:45 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"
#include "../include/libft.h"

static int	is_valid_shlvl(char *str)
{
	if (*str == '\0')
		return (FALSE);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (FALSE);
	while (ft_isdigit(*str))
		str++;
	while (ft_isblank(*str))
		str++;
	return (*str == '\0');
}

static int	print_shlvl_too_high(int shlvl)
{
	char	*str;

	str = ft_itoa(shlvl);
	if (str == NULL)
		error_exit();
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
	free(str);
	return (1);
}

static int	get_shlvl(char *old_shlvl)
{
	int	error;
	int	shlvl;

	atoll_error(old_shlvl, &error);
	if (error)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(old_shlvl);
		shlvl++;
	}
	return (shlvl);
}

void		set_shlvl(t_list **environ)
{
	char	*old_shlvl;
	char	*new_shlvl;
	int		shlvl;

	old_shlvl = get_env(*environ, "SHLVL");
	new_shlvl = NULL;
	if (old_shlvl == NULL || !is_valid_shlvl(old_shlvl))
		create_and_set_env(environ, "SHLVL", "1");
	else
	{
		shlvl = get_shlvl(old_shlvl);
		if (shlvl < 0)
			shlvl = 0;
		else if (shlvl > 999)
			shlvl = print_shlvl_too_high(shlvl);
		new_shlvl = ft_itoa(shlvl);
		if (new_shlvl == NULL)
			error_exit();
		create_and_set_env(environ, "SHLVL", new_shlvl);
	}
	free(old_shlvl);
	free(new_shlvl);
}
