/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:59:01 by gbudau            #+#    #+#             */
/*   Updated: 2020/12/12 23:24:31 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ioredirection.h"

int			print_error_io(char *str)
{
	char	*joined;

	joined = ft_strjoin("minishell: ", str);
	if (joined == NULL)
		error_exit();
	perror(joined);	
	free(joined);
	return (1);
}

int			set_redirections(t_command *cmd)
{
	int	out_fd;
	int	in_fd;

	if (cmd->input)
	{
		in_fd = open(cmd->input, O_RDONLY);
		if (in_fd < 0)
			return (print_error_io(cmd->input));
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->output)
	{
		if (cmd->redirect_type == REDIRECTION_APPEND)
			out_fd = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		else
			out_fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (out_fd < 0)
			return (print_error_io(cmd->output));
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return (0);
}
