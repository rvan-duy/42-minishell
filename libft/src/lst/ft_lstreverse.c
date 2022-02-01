/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstreverse.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 11:01:09 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/30 15:11:26 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstreverse(t_list **lst)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*next;

	cur = *lst;
	prev = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*lst = prev;
}
