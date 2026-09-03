/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:37:50 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:35:24 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_coder_burned(t_coder *coder, long now, t_config *config)
{
	long	last_meal;
	int		compiled_cnt;

	pthread_mutex_lock(&coder->time_mutex);
	last_meal = coder->time_compiled;
	compiled_cnt = coder->count;
	pthread_mutex_unlock(&coder->time_mutex);
	if (compiled_cnt < config->compiles_needed)
	{
		if ((now - last_meal) >= config->time_to_burnout)
			return (1);
	}
	return (0);
}

static int	burnout_check(t_config *config, long now)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		if (is_coder_burned(&config->coders[i], now, config))
		{
			pthread_mutex_lock(&config->over_lock);
			config->is_over = 1;
			pthread_mutex_unlock(&config->over_lock);
			wake_dongles(config);
			usleep(10);
			ft_log("burned out", &config->coders[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	wake_dongles(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_mutex_lock(&config->dongles[i].mutex);
		pthread_cond_broadcast(&config->dongles[i].cond);
		pthread_mutex_unlock(&config->dongles[i].mutex);
		i++;
	}
}

void	*monitor_routine(void *data)
{
	t_config	*config;

	config = (t_config *)data;
	while (end_simulation(config) == 0)
	{
		if (burnout_check(config, get_time()))
			break ;
		usleep(100);
	}
	return (NULL);
}
