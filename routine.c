/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 04:42:36 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/04/11 11:58:47 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int get_dongles(t_coder *coder)
{
    t_dongle    *first;
    t_dongle    *second;
    t_config       *config;

    config = coder->config;
    if (coder->id % 2 != 0)
    {
        first = coder->ldongle;
        second = coder->rdongle;
    }
    else
    {
        first = coder->rdongle;
        second = coder->ldongle;
    }
    place_dongle(first, coder)
    place_dongle(second, coder)
    return (1);
}

int place_dongle(t_dongle *dongle, t_coder *coder)
{
    t_config   *config;

    config = coder->config;
    if (config->is_edf)
        edf(dongle, coder);
    else
        fifo(dongle, coder);
    return (1);
}
int	compiling(t_coder *coder)
{
	t_config	*config;

	config = coder->config;
	get_dongles(coder);
	pthread_mutex_lock(&coder->lcs_mutex);
	coder->time_compiled = get_time_ms();
	pthread_mutex_unlock(&coder->time_mutex);
	log_action("is compiling", coder);
	precise_sleep(config->time_to_compile, config);
	release_dongles(coder);
	return (1);
}


void	*coder_routine(void *arg)
{
	t_config	*config;
	t_coder	*coder;

	coder = (t_coder *)arg;
	config = coder->config;
	check_and_sleep(coder);
	while (1)
	{
		compile_phase(coder)
		log_action("is debugging", coder);
		precise_sleep(sim->time_to_debug, sim);
		log_action("is refactoring", coder);
		precise_sleep(sim->time_to_refactor, sim);
		if (!safe_count(coder))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}


 

