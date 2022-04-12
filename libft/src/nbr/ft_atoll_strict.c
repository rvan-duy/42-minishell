/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll_strict.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:33:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/04/11 11:17:49 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static void	ft_atoll_strict_skipper(char *str, size_t *i, size_t *non_digits)
{
	while (ft_isspace(str[*i]))
	{
		(*non_digits)++;
		(*i)++;
	}
	if (str[*i] == '+' || str[*i] == '-')
	{
		(*non_digits)++;
		(*i)++;
	}
	while (ft_isdigit(str[*i]))
		(*i)++;
	while (ft_isspace(str[*i]))
	{
		(*non_digits)++;
		(*i)++;
	}
}

/**
 * Converts @p str to an integer
 * @param str
 * @param result_ptr
 * @return
 */
bool	ft_atoll_strict(char *str, long long *result_ptr, bool *had_overflow)
{
	size_t	i;
	size_t	non_digits;

	*had_overflow = false;
	if (str == NULL)
		return (false);
	non_digits = 0;
	i = 0;
	ft_atoll_strict_skipper(str, &i, &non_digits);
	if (i == non_digits || str[i] != '\0')
		return (false);
	*result_ptr = ft_atoll(str, had_overflow);
	return (true);
}
