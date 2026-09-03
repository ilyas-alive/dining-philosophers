/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 18:25:09 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:33:00 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	destroy_elements(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_mutex_destroy(&config->dongles[i].mutex);
		pthread_cond_destroy(&config->dongles[i].cond);
		pthread_mutex_destroy(&config->coders[i].time_mutex);
		i++;
	}
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	destroy_elements(config);
	if (config->dongles)
	{
		free(config->dongles);
		config->dongles = NULL;
	}
	if (config->coders)
	{
		free(config->coders);
		config->coders = NULL;
	}
	pthread_mutex_destroy(&config->over_lock);
	pthread_mutex_destroy(&config->print_lock);
}
