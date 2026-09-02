/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 04:42:36 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/09/01 13:44:06 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

static void	add_to_queue(t_dongle *dongle, t_node *node, int is_edf)
{
	if (is_edf != 0)
		ft_add_sorted(&dongle->queue, node);
	else
		ft_add_back(&dongle->queue, node);
}

static int	wait_for_turn(t_coder *coder, t_dongle *dongle)
{
	struct timespec	ts;

	while (1)
	{
		if (end_simulation(coder->config))
		{
			ft_remove_node(&dongle->queue, coder);
			pthread_mutex_unlock(&dongle->mutex);
			return (0);
		}
		if (dongle->queue && dongle->queue->coder == coder
			&& dongle->available && get_time() >= dongle->cooldown_end)
			break ;
		ms_to_timespec(dongle, &ts);
		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
	}
	return (1);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	t_node	*node;

	node = ft_new_node(coder);
	if (!node)
		return (0);
	pthread_mutex_lock(&coder->time_mutex);
	node->priority = coder->time_compiled + coder->config->time_to_burnout;
	pthread_mutex_unlock(&coder->time_mutex);
	pthread_mutex_lock(&dongle->mutex);
	add_to_queue(dongle, node, coder->config->is_edf);
	if (!wait_for_turn(coder, dongle))
		return (0);
	ft_pop_node(&dongle->queue);
	dongle->available = 0;
	pthread_mutex_unlock(&dongle->mutex);
	ft_log("has taken a dongle", coder);
	return (1);
}

int	get_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->id == (coder->config->number_of_coders - 1))
	{
		first = coder->rdongle;
		second = coder->ldongle;
	}

	else
	{
		first = coder->ldongle;
		second = coder->rdongle;
	}

	if (!take_dongle(coder, first))
		return (0);
	if (coder->config->number_of_coders == 1)
	{
		while (!end_simulation(coder->config))
			usleep(200);
		release_dongle(first, coder->config);
		return (0);
	}
	if (!take_dongle(coder, second))
	{
		release_dongle(first, coder->config);
		return (0);
	}
	return (1);
}
