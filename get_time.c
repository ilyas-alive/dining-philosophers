/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 19:36:36 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/18 19:36:51 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	ms_to_timespec(t_dongle *dongle, struct timespec *ts)
{
	struct timeval	tv;
	long			current_time;
	long			remaining_ms;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
	remaining_ms = (dongle->cooldown_end - current_time) + 1;
	if (remaining_ms < 1)
		remaining_ms = 1;
	ts->tv_sec = tv.tv_sec + (remaining_ms / 1000L);
	ts->tv_nsec = (tv.tv_usec * 1000L) + ((remaining_ms % 1000L) * 1000000L);
	if (ts->tv_nsec >= 1000000000L)
	{
		ts->tv_sec += ts->tv_nsec / 1000000000L;
		ts->tv_nsec = ts->tv_nsec % 1000000000L;
	}
}

void	ft_sleep(long ms, t_config *config)
{
	long	wake_time;

	wake_time = get_time() + ms;
	while (get_time() < wake_time)
	{
		if (end_simulation(config))
			break ;
		usleep(100);
	}
}

