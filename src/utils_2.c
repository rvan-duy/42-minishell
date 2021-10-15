/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 10:35:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 12:55:12 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include <criterion/criterion.h>

void	check_acces(const char *cmd, int oflag)
{
	if (access(cmd, oflag) < 0)
	{
		if (cmd == NULL)
			ft_putstr_fd("(acces) NULL: ", 2);
		perror(cmd);
		exit(EXIT_FAILURE);
	}
}

t_bool	contains_flag(const char *string, const char *flag)
{
	const unsigned char	flag_type = flag[1];

	if (ft_strlen(string) < 2)
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
