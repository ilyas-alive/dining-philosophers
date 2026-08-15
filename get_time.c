#include "codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	ms_sleep(long sleep_time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < sleep_time)
		usleep(100);
}
