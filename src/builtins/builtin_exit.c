/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/14 15:32:55 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 14:26:28 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static void	print_numeric_arg_error(const char *arg)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(ERROR_CODE_NUMERIC_ARGS);
}

static void	check_numeric_arguments(const char *arg)
{
	size_t	i;

	i = 0;
	if (ft_strncmp("-", arg, 2) == 0)
		print_numeric_arg_error(arg);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == false)
			print_numeric_arg_error(arg);
		i++;
	}
	return ;
}

t_status	builtin_exit(t_cmd_node *nodes)
{
	int	exit_code;

	exit_code = 0;
	if (nodes->argv[1] != NULL)
	{
		check_numeric_arguments(nodes->argv[1]);
		if (nodes->argv[2] != NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
			ft_putendl_fd(": exit: too many arguments", STDERR_FILENO);
			g_exit_status = FAILURE;
			return (FAILURE);
		}
		exit_code = ft_atoi(nodes->argv[1]);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_code);
	return (FAILURE);
}
