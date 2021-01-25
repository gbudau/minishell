/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:50:04 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/25 22:15:50 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"

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

static char			*advance_str(char *str, int (*fptr)(int))
{
	while (fptr(*str))
		str++;
	return (str);
}

long long			atoll_error(char *str, int *error)
{
	unsigned long long	n;
	long long			sign;

	str = advance_str(str, &ft_isspace);
	sign = 1;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : sign;
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
	str = advance_str(str, &ft_isblank);
	if (*str != '\0')
		*error = TRUE;
	return ((long long)n * sign);
}
