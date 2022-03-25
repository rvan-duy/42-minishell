/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arr_dim.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marius <marius@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 20:37:34 by marius        #+#    #+#                 */
/*   Updated: 2022/03/17 16:16:30 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_mem.h"

/**
 * e.g.: char *a[11];
 * a[10] = NULL;
 * ft_free_arr_dim(&a, 2);
 * @param arr pointer to array
 * @param dim number of dimensions of array
 * (NOTE every * counts for a dimension (even char *))
 */
void	*ft_free_arr_dim(void *arr, unsigned int dim)
{
	int		i;
	void	**a;
	void	**a2;

	a = (void **)arr;
	a2 = *(void ***)arr;
	if (dim == 0)
		return (NULL);
	if (dim == 1)
		return (ft_free_and_nullify(a));
	i = 0;
	while (a2[i] != NULL)
	{
		ft_free_arr_dim(&a2[i], dim - 1);
		i++;
	}
	ft_free_and_nullify(a);
	return (NULL);
}
