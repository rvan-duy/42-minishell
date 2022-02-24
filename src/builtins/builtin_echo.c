/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 15:30:01 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/23 17:11:11 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

t_status	builtin_echo(t_cmd_node *nodes)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (contains_flag(nodes->argv[i], "-n") == true)
	{
		n_flag = true;
		i++;
	}
	while (nodes->argv[i] != NULL)
	{
		ft_putstr_fd(nodes->argv[i], STDOUT_FILENO);
		if (nodes->argv[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_status = SUCCESS;
	return (SUCCESS);
}
