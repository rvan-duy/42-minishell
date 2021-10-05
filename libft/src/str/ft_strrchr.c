/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:58:19 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/08 17:26:17 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*cs;

	cc = (char)c;
	cs = (char *)s;
	i = ft_strlen(s) - 1;
	if (cc == '\0')
		return (cs + i + 1);
	while (i >= 0)
	{
		if (s[i] == cc)
			return (cs + i);
		i--;
	}
	return (NULL);
}
