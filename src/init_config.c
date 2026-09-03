/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 10:59:08 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:34:52 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

void	dongle_init(t_dongle *dongle, long cooldown_time)
{
	memset(dongle, 0, sizeof(t_dongle));
	dongle->available = 1;
	dongle->cooldown_time = cooldown_time;
	pthread_mutex_init(&dongle->mutex, NULL);
	pthread_cond_init(&dongle->cond, NULL);
}

void	init_dongles(t_config *config)
{
	int	i;

	config->dongles = malloc(sizeof(t_dongle) * config->number_of_coders);
	if (!config->dongles)
		return ;
	i = 0;
	while (i < config->number_of_coders)
	{
		dongle_init(&config->dongles[i], config->dongle_cooldown);
		i++;
	}
}

void	coder_init(t_coder *coder, t_config *config, int position)
{
	int	left_i;
	int	right_i;

	left_i = position;
	right_i = (position + 1) % config->number_of_coders;
	coder->id = position;
	coder->count = 0;
	coder->time_compiled = config->start_time;
	coder->config = config;
	coder->ldongle = &config->dongles[left_i];
	coder->rdongle = &config->dongles[right_i];
	pthread_mutex_init(&coder->time_mutex, NULL);
}

void	init_coders(t_config *config)
{
	int	i;

	config->coders = malloc(sizeof(t_coder) * config->number_of_coders);
	if (!config->coders)
		return ;
	i = 0;
	while (i < config->number_of_coders)
	{
		coder_init(&config->coders[i], config, i);
		i++;
	}
}

void	init_config(t_config *config)
{
	config->start_time = get_time();
	config->coders_finished = 0;
	config->is_over = 0;
	pthread_mutex_init(&config->over_lock, NULL);
	pthread_mutex_init(&config->print_lock, NULL);
	init_dongles(config);
	init_coders(config);
}
