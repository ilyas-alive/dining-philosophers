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
	printf("%d\n", config->number_of_coders);
	printf("%d\n", config->time_to_burnout);
	printf("%d\n", config->time_to_compile);
	printf("%d\n", config->time_to_debug);
	printf("%d\n", config->time_to_refactor);
	printf("%d\n", config->number_of_compiles_required);
	printf("%d\n", config->dongle_cooldown);
	printf("%d\n", config->scheduler);
}
