/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:33:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/04/11 13:54:34 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <limits.h>

static int	ft_atoll_skipper(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	if ((*str)[0] == '+' || (*str)[0] == '-')
		return (1);
	return (0);
}

/**
 * Converts @p str to an integer
 * @param str
 * @return
 */
long long	ft_atoll(const char *str, bool *had_overflow)
{
	const long long	overflow_limit = INT64_MIN / 10;
	const long long	overflow_digit = -(INT64_MIN % 10);
	long long		result;
	int				offset;

	if (had_overflow != NULL)
		*had_overflow = false;
	result = 0;
	offset = ft_atoll_skipper(&str);
	while (ft_isdigit(str[offset]))
	{
		if (had_overflow != NULL && (result < overflow_limit || \
		(result == overflow_limit && str[offset] - '0' > overflow_digit)))
			*had_overflow = true;
		result *= 10;
		result -= str[offset] - '0';
		offset++;
	}
	if (str[0] == '-')
		return (result);
	if (result == INT64_MIN && had_overflow != NULL)
		*had_overflow = true;
	return (-result);
}
