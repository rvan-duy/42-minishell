/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 18:15:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/27 14:54:27 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Search for char `c` in `ptr` with lengh `n` starting from the end
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
