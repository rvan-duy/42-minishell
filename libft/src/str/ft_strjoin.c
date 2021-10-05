/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 11:30:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2020/11/11 13:56:45 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*dst;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(len * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, len);
	ft_strlcat(dst, s2, len);
	return (dst);
}
