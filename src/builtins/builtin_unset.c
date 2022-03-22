/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 13:17:20 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/22 12:16:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include "builtins.h"
#include <unistd.h>

static int	check_valid_identifier(char *identifier)
{
	size_t	i;

	if (ft_isalpha(identifier[0]) == 0)
		return (UNVALID);
	i = 0;
	while (identifier[i])
	{
		if (ft_isalnum(identifier[i]) == 0 && identifier[i] != '_')
			return (UNVALID);
		i++;
	}
	return (VALID);
}

static void	print_identifier_error(char *identifier)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_exit_status = FAILURE;
}

t_status	buitlin_unset(t_cmd_node *nodes, t_env_var *envp)
{
	size_t	i;

	g_exit_status = SUCCESS;
	if (nodes->argv[1] == NULL)
		return (SUCCESS);
	i = 1;
	while (nodes->argv[i] != NULL)
	{
		if (check_valid_identifier(nodes->argv[i]) == UNVALID)
			print_identifier_error(nodes->argv[i]);
		else
			env_node_del(nodes->argv[i], &envp);
		i++;
	}
	return (SUCCESS);
}
