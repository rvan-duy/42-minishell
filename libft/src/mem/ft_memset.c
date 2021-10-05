/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:46:34 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/11 13:32:47 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	while (len)
	{
		((unsigned char *)b)[len - 1] = (unsigned char)c;
		len--;
	}
	return (b);
}
