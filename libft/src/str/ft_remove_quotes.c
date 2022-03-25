/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_remove_quotes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 12:02:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/07 17:34:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_quotes(const char *str, int skip_unclosed_check)
{
	char	quote;
	int		count;
	int		i;

	quote = '\0';
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			count++;
			if (quote == '\0')
				quote = str[i];
			else if (str[i] == quote)
				quote = '\0';
			else
				count--;
		}
		i++;
	}
	if (quote != '\0' && !skip_unclosed_check)
		return (-1);
	return (count);
}

static void	remove_quotes(const char *str, char *new_str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			while (str[i + 1] != quote && str[i + 1] != '\0')
			{
				new_str[j] = str[i + 1];
				i++;
				j++;
			}
			if (str[i + 1] == '\0' || str[i + 2] == '\0')
				return ;
			i += 2;
		}
		new_str[j] = str[i];
		j++;
		i++;
	}
}

/**
 * DOES NOT HANDLE ESCAPED QUOTES
 */
char	*ft_remove_quotes(const char *str, int skip_unclosed_check)
{
	int		quotes;
	char	*new_str;

	if (str == NULL)
		return (NULL);
	quotes = count_quotes(str, skip_unclosed_check);
	if (quotes < 0)
		return (NULL);
	new_str = malloc((ft_strlen(str) - quotes + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[ft_strlen(str) - quotes] = '\0';
	remove_quotes(str, new_str);
	return (new_str);
}
