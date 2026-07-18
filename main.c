/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:18:46 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/04/11 11:58:47 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "codexion.h"

int	main(int argc, char **argv)
{

	t_codex	*config;
	t_node *queue = NULL;

	config = malloc(sizeof(t_codex));
	if (check_input(argc, argv) == 1)
		make_config(config, argv);
	else
	{
		printf("wrong");
		exit(1);
	}
	if (last_check(config) == 0)
	{
		printf("wrong\n");
		exit(1);
	}

	t_node *node1 = ft_new_node(1);
	t_node *node2 = ft_new_node(2);
	t_node *node3 = ft_new_node(3);
	t_node *node4 = ft_new_node(4);

	ft_add_back(&queue, node1);
	ft_add_back(&queue, node2);
	ft_add_back(&queue, node3);
	ft_add_back(&queue, node4);

}
