/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:28:41 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/07/25 14:34:40 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex, NULL);


}

int take_dongles(t_coder *coder)
{
	t_dongle *first;
	t_dongle *second;
	if (coder->id % 2)
	{
		first = coder->ldongle
		second = coder->rdongle;
	}
	else
	{
		first = coder->rdongle;
		second = coder->ldongle

	}
	take_dongle(coder, first);
	take_dongle(coder, second);

}

int simulation_is_over(t_config *config)
{

}

void *routine(void *data)
{
	t_coder *coder;
	t_config *config:
	coder = (t_coder *)data;
	config = coder->config;
	
	while(1)
	{
		if (simulation_is_over(config))
			break ;

	}
}

