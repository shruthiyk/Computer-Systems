// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<pthread.h>
#define NATHREADS 64

int count = 0;

void *thread_paint();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

char colors[64][64*3];

// Add your paint function here
void *thread_paint()
{

	int i;
	pthread_mutex_lock(&mutex1);
	for(i = 0; i < NATHREADS * 3; ++i)
	{
		colors[count][i] = count;
	}
	count++;

	pthread_mutex_unlock(&mutex1);
}

void save()
{
	FILE *fp;
	fp = fopen("image.ppm","w+");
	fputs("P3\n",fp);
	fputs("64 64\n",fp);
	fputs("255\n",fp);
	int i;
	for(i =0; i < 64;i++){
		int j;
		for(j =0; j < 64*3; j++){
			fprintf(fp,"%d",colors[i][j]);
			fputs(" ",fp);		
		}
		fputs("\n",fp);
	}
	fclose(fp);
}

int main()
{

        pthread_t thread_id[NATHREADS];
	int i, j ;

	for(i =0; i < NATHREADS; i++)
	{
		pthread_create(&thread_id[i],NULL,thread_paint, NULL);
	}

	for(j=0 ; j< NATHREADS ; j++)
	{
		pthread_join(thread_id[j], NULL);
	}

	save();
	return 0;
}
