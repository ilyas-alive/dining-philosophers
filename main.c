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
	init_config(config);
	config->dongles[2].cooldown_time = (long)7;
	int i = 0;
	while(i < config->number_of_coders)
	{
		printf("this is %d, %ld\n",i ,  config->dongles[i].cooldown_time);
		i++;
	}
}
