/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_print_nodes.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/06 16:45:07 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/08 14:43:28 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints out all the command nodes and its content
 * @param nodes pointer to `t_cmd_node *`
 * @return nothing
 */
void	print_nodes(t_cmd_node *nodes)
{
	size_t	node_number;
	size_t	i;

	node_number = 1;
	while (nodes)
	{
		i = 0;
		printf("-------------- NODE [%zu] --------------\n", node_number);
		printf("address: %p\n", nodes);
		printf("cmd: %s\n", nodes->cmd);
		printf("argv: ");
		while (nodes->argv[i])
			printf("[%s] ", nodes->argv[i++]);
		printf("\n");
		printf("pipe_to: %p\n", nodes->pipe_to);
		nodes = nodes->pipe_to;
		node_number++;
	}
	printf("-------------- END --------------\n");
}
