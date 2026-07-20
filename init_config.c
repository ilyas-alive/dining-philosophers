/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 10:59:08 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/07/20 11:16:29 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"


void dongle_init(t_dongle *dongle, long cooldown_time)
{
	dongle->cooldown_time = cooldown_time;
	pthread_mutex_init(&dongle->mutex, NULL);
	pthread_cond_init(&dongle->cond, NULL);
}


void init_dongles(t_codex *config)
{
	int i = 0;

	config->dongles = (t_dongle *)malloc(config->number_of_coders * sizeof(t_dongle));
	while(i < config->number_of_coders)
	{
		dongle_init(&config->dongles[i], config->dongle_cooldown);
		i++;
	}
}

void coder_init(t_coder *coder, t_codex *config, int position)
{
	coder->config = config;
	coder->rdongle = &config->dongles[(position+1) % config->number_of_coders]; 
	coder->ldongle = &config->dongles[(position) % config->number_of_coders]; 
	coder->id = position;
	coder->count = 0;
}

void init_coders(t_codex *config)
{
	int i = 0;
	config->coders = (t_coder *)malloc(config->number_of_coders * sizeof(t_coder));
	while(i < config->number_of_coders)
	{
		coder_init(&config->coders[i], config, i);
		i++;
	}

}



void init_config(t_codex *config)
{
	init_dongles(config);
	init_coders(config);
}
