/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:27:42 by fportela          #+#    #+#             */
/*   Updated: 2020/12/30 18:41:37 by fportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		frontbacksplit(t_list *source, t_list **frontref,
	t_list **backref)
{
	t_list	*fast;
	t_list	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}

static t_list	*sortedmerge(t_list *a, t_list *b)
{
	t_list	*result;
	char	**a_str;
	char	**b_str;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	a_str = a->content;
	b_str = b->content;
	if (ft_strcmp(a_str[ENV_NAME], b_str[ENV_NAME]) <= 0)
	{
		result = a;
		result->next = sortedmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next);
	}
	return (result);
}

void			mergesort(t_list **alist)
{
	t_list	*list;
	t_list	*a;
	t_list	*b;

	list = *alist;
	if ((list == NULL) || (list->next == NULL))
		return ;
	frontbacksplit(list, &a, &b);
	mergesort(&a);
	mergesort(&b);
	*alist = sortedmerge(a, b);
}
