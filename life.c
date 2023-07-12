#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

#include "life.h"

int main (int argc, char *argv[ ])
{
	int i,nrIteratii,procent;
	lifeM conway;

	printf("Cate repetitii doriti ?\n");
	scanf("%d",&nrIteratii);
	printf("Densitatea vietii la inceput ?\n");
	scanf("%d",&procent);

	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	//printf ("lines %d\n", w.ws_row);
  	//printf ("columns %d\n", w.ws_col);
	conway.randuri=(int)w.ws_row/(1.4);
	conway.coloane=(int)(w.ws_col/2.2);
	conway.harta=malloca(conway);
	randomizeaza(&conway,procent);
	

	while(nrIteratii>0)
	{
		
		deseneaza(&conway);
		evolueaza(&conway);
		muta(&conway);
		masoara(&conway);

		delay(100000);
		system("clear");
		nrIteratii--;

		printf("T-%d\n",nrIteratii);
	}

	afiseazaHeat(&conway);
	printf("Cele mai fierbinti celule au avut %d comutari.\n",cautaMax(&conway));

	dalloca(&conway);

	return 0;
}
