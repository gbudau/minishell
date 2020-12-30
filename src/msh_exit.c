/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:22 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/30 20:45:42 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			is_mult_overflow(unsigned long long *result, unsigned long long n,
		long long sign)
{
	if (sign > 0 && n > (LLONG_MAX / 10))
		return (TRUE);
	else if (sign < 0 && n > ((LLONG_MAX + 1ULL) / 10))
		return (TRUE);
	*result = n * 10;
	return (FALSE);
}

int			is_add_overflow(unsigned long long *result,
			unsigned long long a, long long b, long long sign)
{
	if (sign > 0 && a > (LLONG_MAX + 0ULL - b))
		return (TRUE);
	else if (sign < 0 && a > (LLONG_MAX + 1ULL - b))
		return (TRUE);
	*result = a + b;
	return (FALSE);
}

long long	exit_atoll(char *str, int *error)
{
	unsigned long long	n;
	unsigned long long	mult;
	long long			sign;

	n = 0;
	mult = 0;
	if (*str == '-' && str++)
		sign = -1;
	else
		sign = 1;
	while (ft_isdigit(*str))
	{
		*error = is_mult_overflow(&mult, n, sign);
		if (*error == TRUE)
			break ;
		*error = is_add_overflow(&n, mult, *str - '0', sign);
		if (*error == TRUE)
			break ;
		str++;
	}
	if (*str != '\0')
		*error = TRUE;
	return ((long long)n * sign);
}

void		print_numeric_argument_error(char *str, int *last_status)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	*last_status = 2;
	exit(*last_status);
}

int			msh_exit(t_command *cmd, t_list **environ, int *last_status)
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
