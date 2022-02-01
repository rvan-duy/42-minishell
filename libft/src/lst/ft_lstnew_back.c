/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 11:12:42 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/01 11:12:53 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_back(void *content, t_list **lst)
{
	t_list	*new;

	new = ft_lstnew(content);
	ft_lstadd_back(lst, new);
	return (new);
}
