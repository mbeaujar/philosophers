
#include "include/philosophers.h"


pthread_mutex_t lock;

void *exec_routine(void *vargp)
{
	int *nb = (int*)vargp;
	static int i = 0;

	pthread_mutex_lock(&lock);
	printf("thread debut %d indice : %d\n", ++*nb, ++i);

	printf("thread fin %d indice : %d\n", *nb,  ++i);
	pthread_mutex_unlock(&lock);
	//printf("test\n");
	return (NULL);
}

int main(void)
{
	pthread_t thread_id[2];
	struct timeval time;
	int ret;
	int nb;


	if (pthread_mutex_init(&lock, NULL) != 0)
		return (printf("mutex can't init\n"));
	nb = 0;
	gettimeofday(&time, NULL);
	printf("time in sec : %ld\tmicro second : %ld\n", (long)time.tv_sec, (long)time.tv_usec);
	gettimeofday(&time, NULL);
	printf("time in sec : %ld\tmicro second : %ld\n", (long)time.tv_sec, (long)time.tv_usec);
	for (int i = 0; i < 2; i++)
	{
		ret = pthread_create(&thread_id[i], NULL, exec_routine, &nb);
		if (ret != 0)
			return (printf("thread can't create : %d\n", i));
	}
	for (int i = 0; i < 2; i++)
		pthread_join(thread_id[i], NULL);
	pthread_mutex_destroy(&lock);
	return (1);
}