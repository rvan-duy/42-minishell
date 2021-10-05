/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 11:11:05 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/11 13:56:36 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	char	*b;

	if (big == NULL || little == NULL)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	b = (char *)big;
	len_little = ft_strlen(little);
	while (len >= len_little)
	{
		len--;
		if (ft_memcmp(b, little, len_little) == 0)
			return (b);
		b++;
	}
	return (NULL);
}
