/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:51:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/08 17:26:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	cc;
	unsigned char	*ucsrc;
	char			*csrc;
	char			*cdst;

	cdst = (char *)dst;
	csrc = (char *)src;
	ucsrc = (unsigned char *)src;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		cdst[i] = csrc[i];
		if (ucsrc[i] == cc)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
