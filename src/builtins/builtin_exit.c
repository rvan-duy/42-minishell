/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/14 15:32:55 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/18 17:46:11 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

static void	check_numeric_arguments(const char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == false)
		{
			ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
			ft_putstr_fd(": exit: ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(ERROR_CODE_NUMERIC_ARGS);
		}
		i++;
	}
	return ;
}

#include <stdio.h>

static t_status	my_special_atoi(const char *str, int *result)
{
	size_t	offset;
	int		is_neg;

	if (str == NULL)
		return (FAILURE);
	offset = 0;
	while (str[offset] != '\0' && ft_isspace(str[offset]))
		offset++;
	*result = 0;
	is_neg = (str[offset] == '-');
	if (is_neg || str[offset] == '+')
		offset++;
	while (str[offset])
	{
		if (!ft_isdigit(str[offset]))
			return (FAILURE);
		*result *= 10;
		*result -= str[offset] - '0';
		offset++;
	}
	return (SUCCESS);
}

// TODO: exit with alphabetic args must error DONE?
// TODO: exit with more then 255 must overfloat
// TODO: exit with more than 1 arg must error
// TODO: syntax error is 258 error code
t_status	builtin_exit(t_cmd_node *nodes)
{
	int	exit_code;

	exit_code = 0;
	if (nodes->argv[1] != NULL)
	{
		check_numeric_arguments(nodes->argv[1]);
		// check multiple arguments
		exit_code = ft_atoi(nodes->argv[1]);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_code);
	return (FAILURE);
}
