/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_len.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:40:29 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/14 15:42:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_array_len(void **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
