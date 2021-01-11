/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:43:43 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/11 01:00:56 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/errors.h"

void	error_exit(void)
{
	ft_perror("Error");
	exit(EXIT_FAILURE);
}

void	not_a_valid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

/*
** error = e_lexer_errors enum from lexer.h
**         Used as an index for quotes[] array
*/

void	error_missing_closing_quote(int error)
{
	const char	quotes[] = {'\0', '\'', '"', '\\'};

	if (error == NO_LEXER_ERR)
		return ;
	ft_putstr_fd("minishell: syntax error: missing closing quote `",
																STDERR_FILENO);
	ft_putchar_fd(quotes[error], STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

/*
** error = e_parser_errors enum from parser.h
**         Used as an index for tokens[] array
*/

void	error_unexpected_token(int error)
{
	const char	*tokens[] = {NULL, "|", ";", ">", "<", ">>", "newline"};

	if (error == NO_PARSER_ERROR)
		return ;
	ft_putstr_fd("minishell: syntax error near unexpected token `",
																STDERR_FILENO);
	ft_putstr_fd((char *)tokens[error], STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int		execve_error(char *str, int error)
{
	if (error == 0)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_perror(str);
	}
	if (errno == EACCES)
		return (126);
	else
		return (127);
}
