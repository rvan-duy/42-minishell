/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_check_and_exec.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 16:19:24 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/25 17:28:52 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "libft.h"

/**
 * Checks if the cmd is a builtin command available in the project
 * @param cmd pointer to `const char *`
 * @return true or false
 */
bool	builtin_check(const char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1))
		return (true);
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1))
		return (true);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1))
		return (true);
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1))
		return (true);
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1))
		return (true);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		return (true);
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
		return (true);
	return (false);
}

/**
 * Checks if the node is a builtin command, if so: executes it
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return 0 if success - 1 in case of error - 2 if node is not a builtin command
 */
int	builtin_check_and_exec(t_cmd_node *nodes, t_env_var *envp)
{
	if (!ft_strncmp(nodes->cmd, "echo", ft_strlen(nodes->cmd) + 1))
		return (builtin_echo(nodes));
	if (!ft_strncmp(nodes->cmd, "pwd", ft_strlen(nodes->cmd) + 1))
		return (builtin_pwd());
	if (!ft_strncmp(nodes->cmd, "cd", ft_strlen(nodes->cmd) + 1))
		return (builtin_cd(nodes, envp));
	if (!ft_strncmp(nodes->cmd, "export", ft_strlen(nodes->cmd) + 1))
		return (builtin_export(nodes, envp));
	if (!ft_strncmp(nodes->cmd, "unset", ft_strlen(nodes->cmd) + 1))
		return (buitlin_unset(nodes, envp));
	if (!ft_strncmp(nodes->cmd, "env", ft_strlen(nodes->cmd) + 1))
		return (builtin_env(envp));
	if (!ft_strncmp(nodes->cmd, "exit", ft_strlen(nodes->cmd) + 1))
		return (builtin_exit(nodes));
	return (NO_BUILTIN);
}
