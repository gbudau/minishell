/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:38:31 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/23 23:14:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/wordexp.h"
#include "../include/command.h"

void		*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

/*
** Checks if there is an error while opening a file
** pathname = path to the file
** redirect_mode = open the file in one of the following mode
**        	REDIRECTION_INPUT = open in read mode
**        	REDIRECTION_OUTPUT = open in write truncate mode
**        	REDIRECTION_APPEND = open in write append mode
** Returns TRUE and prints an error if there was an error or FALSE otherwise
*/

static int	open_error(char *pathname, int redirect_mode)
{
	int		fd;
	int		flags;
	mode_t	mode;

	mode = 0;
	if (redirect_mode == REDIRECTION_INPUT)
		flags = O_RDONLY;
	else
	{
		mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
		if (redirect_mode == REDIRECTION_OUTPUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	if (!mode)
		fd = open(pathname, flags);
	else
		fd = open(pathname, flags, mode);
	if (fd == -1 || close(fd) == -1)
	{
		print_error_io(pathname);
		return (TRUE);
	}
	return (FALSE);
}

int			io_expand_open(char **word, t_shell *shell, int redirect_mode)
{
	int	error;

	error = expand_word(word, shell->environ, &shell->last_status);
	if (error)
		return (TRUE);
	error = open_error(*word, redirect_mode);
	if (error)
		return (TRUE);
	return (FALSE);
}
