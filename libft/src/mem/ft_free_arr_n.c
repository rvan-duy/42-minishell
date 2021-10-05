/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arr_n.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marius <marius@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 21:12:17 by marius        #+#    #+#                 */
/*   Updated: 2021/09/26 21:12:17 by marius        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_mem.h"

/**
 * \n
 * e.g.: char *a[11]; \n
 * ft_free_arr_n(&a, 11);
 */
void	*ft_free_arr_n(void ***arr, size_t n)
{
	size_t	i;
	void	**a;

	i = 0;
	a = *arr;
	while (i < n)
	{
		ft_free_and_nullify(&a[i]);
		i++;
	}
	ft_free_and_nullify((void **)arr);
	return (NULL);
}
