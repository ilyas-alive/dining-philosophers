#include <pthread.h>
#include <stdio.h>
long counter = 0;
long end = 1000000;
pthread_mutex_t lock;

void *increase_to_million(void *arg)
{
	(void)arg;
	while(counter < end)
	{
		pthread_mutex_lock(&lock);
		if (counter > end - 1)
		{
			pthread_mutex_unlock(&lock);
			return NULL;
		}
		counter++;
		printf("%ld\n", counter);
		pthread_mutex_unlock(&lock);
	}
	return NULL;

}



int main()
{
	pthread_t threads[5];
	pthread_mutex_init(&lock, NULL);

	int i = 0;
	while(i < 5)
	{
		pthread_create(&threads[i], NULL, increase_to_million, NULL);
		i++;
	}
	i = 0;
	while(i < 5)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
