/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_from_arr.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 15:16:16 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/01 15:27:52 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_from_arr(void **arr)
{
	t_list	*lst;
	size_t	i;

	lst = NULL;
	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_lstnew_front(arr[i], &lst) == NULL)
		{
			ft_lstclear(&lst, NULL);
			return (NULL);
		}
		i++;
	}
	ft_lstreverse(&lst);
	return (lst);
}
