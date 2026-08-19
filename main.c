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

static void	abort_threads(t_config *config, int count)
{
	pthread_mutex_lock(&config->over_lock);
	config->is_over = 1;
	pthread_mutex_unlock(&config->over_lock);
	wake_dongles(config);
	while (count > 0)
	{
		count--;
		pthread_join(config->coders[count].thread, NULL);
	}
	pthread_join(config->monitor, NULL);
}

int	start_threads(t_config *config)
{
	int	idx;

	if (pthread_create(&config->monitor, NULL, monitor_routine, config) != 0)
		return (0);
	idx = 0;
	while (idx < config->number_of_coders)
	{
		if (pthread_create(&config->coders[idx].thread, NULL,
				coder_routine, &config->coders[idx]) != 0)
		{
			abort_threads(config, idx);
			return (0);
		}
		idx++;
	}
	return (1);
}

void	wait_threads(t_config *config)
{
	int	idx;

	idx = 0;
	while (idx < config->number_of_coders)
	{
		pthread_join(config->coders[idx].thread, NULL);
		idx++;
	}
	pthread_join(config->monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_config	config;

	memset(&config, 0, sizeof(t_config));
	if (check_input(argc, argv) == 0)
	{
		write(2, "Error: invalid arguments\n", 25);
		return (1);
	}
	make_config(&config, argv);
	if (last_check(&config) == 0)
	{
		write(2, "Error: invalid arguments\n", 25);
		return (1);
	}
	init_config(&config);
	if (start_threads(&config) == 0)
	{
		free_config(&config);
		return (1);
	}
	wait_threads(&config);
	free_config(&config);
	return (0);
}
