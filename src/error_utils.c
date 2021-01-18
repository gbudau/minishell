/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:43:43 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/18 01:42:47 by gbudau           ###   ########.fr       */
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

void	error_syntax_scanner(int error)
{
	const char	quotes[] = {'\0', '\'', '"', '\\'};

	if (error == NO_LEXER_ERR)
		return ;
	if (error == ERR_UNEXPECTED_TOKEN_DOUBLE_SEMICOLON)
		ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n",
																STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: syntax error: missing closing quote `",
																STDERR_FILENO);
		ft_putchar_fd(quotes[error], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
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

int		execve_error(t_list *environ, char *str)
{
	struct stat	statbuf;
	char		*path;

	path = get_env(environ, "PATH");
	if (path && *path && !ft_strchr(str, '/'))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free(path);
		return (127);
	}
	if (stat(str, &statbuf) != -1 && S_ISDIR(statbuf.st_mode))
		errno = EISDIR;
	errno = errno ? errno : ENOENT;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_perror(str);
	free(path);
	if (errno == EACCES || errno == EISDIR)
		return (126);
	else
		return (127);
}
