/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 10:35:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/16 16:01:33 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

t_bool	contains_flag(const char *string, const char *flag)
{
	const unsigned char	flag_type = flag[1];

	if (string == NULL || ft_strlen(string) < 2)
		return (false);
	while (*flag && *string)
	{
		if (*flag != *string)
			return (false);
		string++;
		flag++;
	}
	while (*string)
	{
		if (*string != flag_type)
			return (false);
		string++;
	}
	return (true);
}