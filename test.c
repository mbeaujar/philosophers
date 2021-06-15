
#include "philosophers.h"


pthread_mutex_t lock;

void *exec_routine(void *vargp)
{
	int *nb = (int*)vargp;
	static int i = 0;

	pthread_mutex_lock(&lock);
	printf("thread debut %d indice : %d\n", ++*nb, ++i);

	sleep(1);
	printf("thread fin %d indice : %d\n", *nb,  ++i);
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int main(void)
{
	pthread_t thread_id[2];
	int ret;
	int nb;


	if (pthread_mutex_init(&lock, NULL) != 0)
		return (printf("mutex can't init\n"));
	nb = 0;
	for (int i = 0; i < 2; i++)
	{
		ret = pthread_create(&thread_id[i], NULL, exec_routine, &nb);
		if (ret != 0)
			return (printf("thread can't create : %d\n", i));
		//sleep(1);
	}
	//sleep(1);
	//nb++;
	for (int i = 0; i < 2; i++)
		pthread_join(thread_id[i], NULL);
	pthread_mutex_destroy(&lock);
	return (1);
}