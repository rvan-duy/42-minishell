/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 18:15:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/28 11:39:33 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Search for char `c` in `ptr` with length `n` starting from the end
 */
void	*ft_memrchr(const void *const_ptr, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)const_ptr;
	while (n > 0)
	{
		n--;
		if (ptr[n] == (unsigned char)c)
			return ((void *)const_ptr + n);
	}
	return (NULL);
}
