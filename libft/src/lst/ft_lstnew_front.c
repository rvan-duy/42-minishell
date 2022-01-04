/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 11:10:40 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/02 11:19:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_front(void *content, t_list **lst)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new != NULL)
		ft_lstadd_front(lst, new);
	return (new);
}
