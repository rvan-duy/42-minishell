/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstinsert_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 13:20:54 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/02/24 17:05:37 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_lstinsert(t_list **lst, t_list *new, unsigned int i)
{
	t_list	*l;

	if (lst == NULL || new == NULL)
		return (0);
	if (i == 0)
	{
		new->next = *lst;
		*lst = new;
		return (1);
	}
	l = *lst;
	while (i - 1 > 0 && l != NULL)
	{
		i--;
		l = l->next;
	}
	if (l == NULL)
		return (0);
	new->next = l->next;
	l->next = new;
	return (1);
}
