/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:59:01 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/07 12:51:18 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ioredirection.h"

static int	print_error_io(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_perror(str);
	return (1);
}

static int	set_input_redirection(t_command *cmd)
{
	int	in_fd;

	if (cmd->input)
	{
		in_fd = open(cmd->input, O_RDONLY);
		if (in_fd < 0)
			return (print_error_io(cmd->input));
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	return (0);
}

static int	set_output_redirection(t_command *cmd)
{
	int	out_fd;

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

int			set_redirections(t_command *cmd)
{
	int	error;

	if (cmd->redirection_order == REDIRECT_INPUT_FIRST)
	{
		error = set_input_redirection(cmd);
		if (error)
			return (1);
		error = set_output_redirection(cmd);
		if (error)
			return (1);
	}
	else
	{
		error = set_output_redirection(cmd);
		if (error)
			return (1);
		error = set_input_redirection(cmd);
		if (error)
			return (1);
	}
	return (0);
}
