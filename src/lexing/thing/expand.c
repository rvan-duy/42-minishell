/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 12:17:23 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/04 12:16:58 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "thing.h"
#include <stdlib.h>

t_status	expand_thing(t_list	*arg_symbols, char **out)
{
	t_symbol	*symbol;
	size_t		len;
	t_list		*symbols;
	char		*cur;
	t_list		*next;

	len = 0;
	symbols = arg_symbols;
	while (symbols != NULL)
	{
		symbol = symbols->content;
		len += ft_strlen(symbol->value);
		symbols = symbols->next;
	}
	*out = malloc((len + 1) * sizeof(char));
	if (*out == NULL)
		return (FAILURE);
	(*out)[len] = '\0';
	cur = *out;
	while (arg_symbols != NULL)
	{
		symbol = arg_symbols->content;
		cur += ft_strlcpy(cur, symbol->value, len + 1);
		next = arg_symbols->next;
		free(symbol->value);
		free(symbol);
		free(arg_symbols);
		arg_symbols = next;
	}
	return (SUCCESS);
}

// void	do_thing_single_arg(t_cmd_node ***node, char **cmd, int i)
// {
// 	t_list	*lst;

// 	**node = malloc(sizeof(t_cmd_node));
// 	lst = thing(*cmd, cmd);
// 	fix_thing(lst, &(**node)->files);
// 	expand_thing(lst, &(**node)->argv[i]);
// }

void	list_to_argv(t_list *args, char ***argv)
{
	size_t	len;
	t_list	*next;

	len = ft_lstsize(args);
	*argv = malloc((len + 1) * sizeof(char *));
	(*argv)[len] = NULL;
	while (len > 0)
	{
		len--;
		(*argv)[len] = args->content;
		next = args->next;
		free(args);
		args = next;
	}
}

void	do_thing_single(t_cmd_node **node, char **cmd)
{
	t_list	*lst;
	t_list	*args;
	char	*str;

	lst = thing(*cmd, cmd);
	args = NULL;
	*node = malloc(sizeof(t_cmd_node));
	(*node)->files = NULL;
	(*node)->pipe_to = NULL;
	while (lst != NULL && ((t_symbol *)lst->content)->type != STRUCT_PIPE)
	{
		fix_thing(&lst, &(*node)->files);
		if (lst != NULL)
		{
			expand_thing(lst, &str);
			ft_lstnew_front(str, &args);
		}
		lst = thing(*cmd, cmd);
	}
	if (lst != NULL && ((t_symbol *)lst->content)->type == STRUCT_PIPE)
	{
		free(((t_symbol *)lst->content)->value);
		free(lst->content);
		free(lst);
	}
	list_to_argv(args, &(*node)->argv);
}

void	do_thing2(char *cmd, t_cmd_node **node)
{
	while (cmd[0] != '\0')
	{
		do_thing_single(node, &cmd);
		ft_lstreverse(&(*node)->files);
		node = &(*node)->pipe_to;
	}
}

// void	do_thing2(char *cmd, t_cmd_node **node)
// {
// 	t_list				*lst;
// 	int					i;

// 	while (cmd[0] != '\0')
// 	{
// 		i = 0;
// 		lst = thing(cmd, &cmd);
// 		while (((t_symbol *)lst->content)->type != STRUCT_PIPE)
// 		{
// 			*node = malloc(sizeof(t_cmd_node));
// 			(*node)->files = NULL;
// 			fix_thing(&lst, &(*node)->files);
// 			expand_thing(lst, &(*node)->argv[i]);
// 			lst = thing(cmd, &cmd);
// 			i++;
// 		}
// 		node = &(*node)->pipe_to;
// 	}
// }
