/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:22 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/02 18:12:15 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int			is_mult_overflow(unsigned long long a, unsigned long long b,
																long long sign)
{
	if (sign > 0 && a > ((LLONG_MAX + 0ULL) / b))
		return (TRUE);
	else if (sign < 0 && a > ((LLONG_MAX + 1ULL) / b))
		return (TRUE);
	return (FALSE);
}

static int			is_add_overflow(unsigned long long a, unsigned long long b,
																long long sign)
{
	if (sign > 0 && a > (LLONG_MAX + 0ULL - b))
		return (TRUE);
	else if (sign < 0 && a > (LLONG_MAX + 1ULL - b))
		return (TRUE);
	return (FALSE);
}

static long long	exit_atoll(char *str, int *error)
{
	unsigned long long	n;
	long long			sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : sign;
		str++;
	}
	n = 0;
	while (ft_isdigit(*str))
	{
		*error = is_mult_overflow(n, 10, sign);
		if (*error == TRUE)
			break ;
		n = n * 10;
		*error = is_add_overflow(n, *str - '0', sign);
		if (*error == TRUE)
			break ;
		n = n + *str - '0';
		str++;
	}
	if (*str != '\0')
		*error = TRUE;
	return ((long long)n * sign);
}

static void			print_numeric_argument_error(char *str, int *last_status)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	*last_status = 2;
	exit(*last_status);
}

int					msh_exit(t_command *cmd, t_list **environ, int *last_status)
{
	int			error;
	long long	n;

	(void)environ;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->argc == 1)
		exit(*last_status);
	error = FALSE;
	n = exit_atoll(cmd->argv[1], &error);
	if (error == TRUE)
		print_numeric_argument_error(cmd->argv[1], last_status);
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		*last_status = 1;
		return (*last_status);
	}
	if (n >= 0)
		n = n % 256;
	else
		n = n % 256 + 256;
	*last_status = (int)n;
	exit(*last_status);
	return (*last_status);
}
