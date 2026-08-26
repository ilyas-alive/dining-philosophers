/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 15:24:44 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:36:16 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	end_simulation(t_config *config)
{
	int	status;

	pthread_mutex_lock(&config->over_lock);
	status = config->is_over;
	pthread_mutex_unlock(&config->over_lock);
	return (status);
}

int	safe_count(t_coder *coder)
{
	t_config	*config;
	int			completed;
	int			all_done;

	config = coder->config;
	pthread_mutex_lock(&coder->time_mutex);
	coder->count += 1;
	completed = (coder->count >= config->compiles_needed);
	pthread_mutex_unlock(&coder->time_mutex);
	if (!completed)
		return (1);
	pthread_mutex_lock(&config->over_lock);
	config->coders_finished += 1;
	all_done = (config->coders_finished >= config->number_of_coders);
	if (all_done)
		config->is_over = 1;
	pthread_mutex_unlock(&config->over_lock);
	if (all_done)
		wake_dongles(config);
	return (0);
}

void	ft_log(char *message, t_coder *coder)
{
	t_config	*config;
	long		timestamp;
	int			simulation_ended;

	config = coder->config;
	simulation_ended = end_simulation(config);
	timestamp = get_time() - config->start_time;
	pthread_mutex_lock(&config->print_lock);
	if (!simulation_ended || strcmp(message, "burned out") == 0)
		printf("%ld %d %s\n", timestamp, coder->id + 1, message);
	pthread_mutex_unlock(&config->print_lock);
}

void	release_dongle(t_dongle *dongle, t_config *config)
{
	long	release_timestamp;

	release_timestamp = get_time();
	pthread_mutex_lock(&dongle->mutex);
	dongle->available = 1;
	dongle->cooldown_end = release_timestamp + config->dongle_cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_dongles(t_coder *coder)
{
	release_dongle(coder->ldongle, coder->config);
	release_dongle(coder->rdongle, coder->config);
}
