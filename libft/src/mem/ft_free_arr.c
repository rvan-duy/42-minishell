/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_arr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marius <marius@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 20:37:34 by marius        #+#    #+#                 */
/*   Updated: 2021/10/18 11:25:20 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_mem.h"

/**
 * e.g.: char *a[11];
 * a[10] = NULL;
 * ft_free_arr(&a);
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
