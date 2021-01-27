/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmergesort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportela <fportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:27:42 by fportela          #+#    #+#             */
/*   Updated: 2021/01/27 21:10:33 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static t_list	*sortedmerge(t_list *a, t_list *b,
										int (*fcmp)(const void *, const void *))
{
	t_list	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (fcmp(a->content, b->content) <= 0)
	{
		result = a;
		result->next = sortedmerge(a->next, b, fcmp);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next, fcmp);
	}
	return (result);
}

void			ft_lstmergesort(t_list **alist,
										int (*fcmp)(const void *, const void *))
{
	t_list	*list;
	t_list	*a;
	t_list	*b;

	list = *alist;
	if ((list == NULL) || (list->next == NULL))
		return ;
	frontbacksplit(list, &a, &b);
	ft_lstmergesort(&a, fcmp);
	ft_lstmergesort(&b, fcmp);
	*alist = sortedmerge(a, b, fcmp);
}
