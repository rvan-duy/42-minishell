/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marius <marius@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 20:37:34 by marius        #+#    #+#                 */
/*   Updated: 2021/09/26 20:37:34 by marius        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_mem.h"

/**
 * \n
 * e.g.: char *a[11]; \n
 * a[10] = NULL; \n
 * ft_free_arr_n(&a);
 */
void	*ft_free_arr(void ***arr)
{
	int		i;
	void	**a;

	i = 0;
	a = *arr;
	while (a[i] != NULL)
	{
		ft_free_and_nullify(&a[i]);
		i++;
	}
	ft_free_and_nullify((void **)arr);
	return (NULL);
}
