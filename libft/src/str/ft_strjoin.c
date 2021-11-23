/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 11:30:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/03 14:07:34 by rvan-duy      ########   odam.nl         */
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

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	newstr = ft_calloc(len1 + len2 + len3 + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, len1 + 1);
	ft_strlcat(newstr, s2, len1 + len2 + 1);
	ft_strlcat(newstr, s3, len1 + len2 + len3 + 1);
	return (newstr);
}
