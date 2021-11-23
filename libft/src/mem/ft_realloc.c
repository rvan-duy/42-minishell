/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:17:49 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/20 13:56:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_len, size_t new_len, size_t size)
{
	void	*newptr;

	newptr = malloc(new_len * size);
	if (newptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(newptr, ptr, old_len * size);
	free(ptr);
	return (newptr);
}
