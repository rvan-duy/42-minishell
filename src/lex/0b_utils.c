/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   0b_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 14:35:05 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/25 14:46:03 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <unistd.h>
#include <stdlib.h>

static char	*get_err_str(t_error_code err)
{
	static char	*err_str[] = {
	[MALLOC_FAIL] = "Malloc failed",
	[MISSING_SINGLE_QUOTE] = "Unexpected EOL while looking for matching (\')",
	[MISSING_DOUBLE_QUOTE] = "Unexpected EOL while looking for matching (\")",
	[AMBIGUOUS_REDIRECT] = "Ambiguous redirect",
	[INVALID_SEQUENCE] = "Invalid sequence"
	};

	return (err_str[err]);
}

void	warn_or_error(t_error_code err)
{
	if (err == MALLOC_FAIL)
		error(err);
	warn(err);
}

void	warn(t_error_code err)
{
	ft_putendl_fd(get_err_str(err), STDERR_FILENO);
}

void	error(t_error_code err)
{
	ft_putendl_fd(get_err_str(err), STDERR_FILENO);
	exit(err);
}
