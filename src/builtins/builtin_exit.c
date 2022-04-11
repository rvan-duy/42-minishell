/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/14 15:32:55 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/11 13:57:57 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static void	print_numeric_arg_error(const char *arg)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(ERROR_CODE_NUMERIC_ARGS);
}

t_status	builtin_exit(t_cmd_node *nodes)
{
	long long	exit_status;
	bool		had_overflow;

	if (nodes->argv[1] != NULL)
	{
		if (!ft_atoll_strict(nodes->argv[1], &exit_status, &had_overflow) \
		|| had_overflow)
			print_numeric_arg_error(nodes->argv[1]);
		if (nodes->argv[2] != NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
			ft_putendl_fd(": exit: too many arguments", STDERR_FILENO);
			g_exit_status = FAILURE;
			return (FAILURE);
		}
		g_exit_status = exit_status;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(g_exit_status);
	return (FAILURE);
}
