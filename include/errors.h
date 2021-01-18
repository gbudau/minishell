/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:14:05 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/18 01:30:04 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

void	not_a_valid_identifier(char *str);
void	error_exit(void);
int		execve_error(t_list *environ, char *str);
void	error_missing_closing_quote(int error);
void	error_unexpected_token(int error);

#endif
