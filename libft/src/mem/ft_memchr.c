/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 18:15:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/06/22 13:25:33 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Search for char `c` in `ptr` with lengh `n`
 */
void	*ft_memchr(const void *const_ptr, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*ptr;

	ptr = (unsigned char *)const_ptr;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)const_ptr + i);
		i++;
	}
	return (NULL);
}
