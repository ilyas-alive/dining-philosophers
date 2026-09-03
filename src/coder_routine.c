/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 13:03:59 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/09/01 13:42:20 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	odd_first(t_coder *coder)
{
	if ((coder->id % 2) != 0)
		usleep(500);
}

void	add_to_queue(t_dongle *dongle, t_node *node, int is_edf)
{
	if (is_edf != 0)
		ft_add_sorted(&dongle->queue, node);
	else
		ft_add_back(&dongle->queue, node);
}

int	compiling(t_coder *coder)
{
	t_config	*config;

	config = coder->config;
	if (!get_dongles(coder))
		return (0);
	if (end_simulation(config))
	{
		release_dongles(coder);
		return (0);
	}
	pthread_mutex_lock(&coder->time_mutex);
	coder->time_compiled = get_time();
	pthread_mutex_unlock(&coder->time_mutex);
	ft_log("is compiling", coder);
	ft_sleep(config->time_to_compile, config);
	release_dongles(coder);
	return (safe_count(coder));
}

static int	coder_cycle_step(t_coder *coder, t_config *config)
{
	if (!compiling(coder) || end_simulation(config))
		return (0);
	ft_log("is debugging", coder);
	ft_sleep(config->time_to_debug, config);
	if (end_simulation(config))
		return (0);
	ft_log("is refactoring", coder);
	ft_sleep(config->time_to_refactor, config);
	usleep(100);
	return (1);
}

void	*coder_routine(void *data)
{
	t_coder		*coder;
	t_config	*config;

	coder = (t_coder *)data;
	config = coder->config;
	odd_first(coder);
	while (!end_simulation(config))
	{
		if (!coder_cycle_step(coder, config))
			break ;
	}
	return (NULL);
}
