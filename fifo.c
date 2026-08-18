/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:41:47 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/07/25 14:52:38 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int fifo(t_coder *coder, t_dongle *dongle)
{
	t_sim			*config;
	struct timespec	ts;

	config = coder->config;
	pthread_mutex_lock(&dongle->mutex);
	while (!dongle->available
		|| get_time_ms() < dongle->cooldown_end)
	{
		if (is_finished(config))
		{
			pthread_mutex_unlock(&dongle->mutex);
			return ;
		}
		ms_to_timespec(dongle, &ts);
		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
	}
	dongle->available = 0;
	log_action("has taken a dongle", coder);
	pthread_mutex_unlock(&dongle->mutex);
}
