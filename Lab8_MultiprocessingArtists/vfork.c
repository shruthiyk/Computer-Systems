// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char colors[64][64*3];

// Add your paint function here
void paint(int workid)
{
	int j;
	for(j = 0; j < 64; ++j)
	{
		colors[workid][j] = workid;
	}
	return;
}

void save()
{
	FILE *fp;
	fp = fopen("masterpiece.ppm","w+");
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

int main(int argc, char** argv){

        int numberOfArtists = 64;
	int status;
	int i;
	for(i =0; i < numberOfArtists; i++){

		pid_t p = vfork();
		if(p == 0)
		{
			printf("This is a child process.\n");
			paint(i);
			exit(0);
		}
		else
		{
			printf("Child id = %d\n", p);
		}
	}
	save();
	printf("parent is exiting(last artist out!)\n");

	return 0;
}
