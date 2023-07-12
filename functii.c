#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>
#include <time.h>
#include "life.h"

void deseneaza(lifeM *conway)
{
	int i,j;

	for(i=0;i<conway->randuri+2;i++)
	{
		for(j=0;j<conway->coloane+2;j++)
		{
			if((i==0)||(j==0)||(i==conway->randuri+1)||(j==conway->coloane+1))
			{
				//printf("#");
				printf("⬜");
			}
			else
			{
				//printf("%d",conway->harta[i-1][j-1].actual);
				if(conway->harta[i-1][j-1].actual==0)
				{
					//printf("☠");
					printf("💀");
				}
				else
				{
					//printf("O");
					printf("💙");
				}
			}
		}	
		printf("\n");
	}
}

dMatrix **malloca(lifeM conway)
{
	int i;
	conway.harta=(dMatrix **)malloc(conway.randuri*sizeof(dMatrix *));
	if(conway.harta==0)
	{
		fprintf(stderr,"Memorie insuficienta.\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<conway.randuri;i++)
	{
		conway.harta[i]=(dMatrix *)malloc(conway.coloane*sizeof(dMatrix));
		if(conway.harta[i]==0)
		{
			fprintf(stderr,"Memorie insuficienta.\n");
			exit(EXIT_FAILURE);
		}
	}

	return conway.harta;
}

void dalloca(lifeM *conway)
{
	int i;

	for(i=0;i<conway->randuri;i++)
	{
		free(conway->harta[i]);
		conway->harta[i]=0;
	}

	free(conway->harta);
	conway->harta=0;
}

void randomizeaza(lifeM *conway,int procent)
{
	int i,j,r;

	for(i=0;i<conway->randuri;i++)
	{
		for(j=0;j<conway->coloane;j++)
		{
			r=rand()%100;
			if(r>=procent)
			{
				conway->harta[i][j].actual=0;
			}
			else
			{
				conway->harta[i][j].actual=1;
			}
			conway->harta[i][j].swN=0;
		}
	}
}

void evolueaza(lifeM *conway)
{
	int i,j,s;

	for(i=0;i<conway->randuri;i++)
	{
		for(j=0;j<conway->coloane;j++)
		{
			s=sumaV(conway,i,j);
			if(conway->harta[i][j].actual==1)
			{
				if(s==2||s==3)
				{
					conway->harta[i][j].anterior=1;		
				}
				else
				{
					conway->harta[i][j].anterior=0;		
				}
			}
			else if(conway->harta[i][j].actual==0)
			{
				if(s==3)
				{
					conway->harta[i][j].anterior=1;		
				}
				else
				{
					conway->harta[i][j].anterior=0;		
				}
			}
		}
	}
}

int sumaV(lifeM *conway,int x,int y)
{
	int s=0,i,j;
	{
		for(i=-1;i<2;i++)
		{
			for(j=-1;j<2;j++)
			{	
				if(!(
					(
					(x+i<0)||(y+j<0))||
					((x+i>=conway->randuri-1)||(y+j>=conway->coloane-1))||
					(i==0&&j==0)
					)
				   )
				{
					s+=conway->harta[x+i][y+j].actual;
				}
			}	
		}
	}

	return s;
}

void muta(lifeM *conway)
{
	int i,j,x;

	for(i=0;i<conway->randuri;i++)
	{
		for(j=0;j<conway->coloane;j++)
		{
			x=conway->harta[i][j].actual;	
			conway->harta[i][j].actual=conway->harta[i][j].anterior;	
			conway->harta[i][j].anterior=x;
		}
	}
}

void masoara(lifeM *conway)
{
	int i,j,x;

	for(i=0;i<conway->randuri;i++)
	{
		for(j=0;j<conway->coloane;j++)
		{	
			if(conway->harta[i][j].actual!=conway->harta[i][j].anterior)
			{
				conway->harta[i][j].swN++;
			}
		}
	}
}

void delay(int mseconds)
{
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + mseconds)
        ;
}

int cautaMax(lifeM *conway)
{
	int i,j,H;
	H=conway->harta[0][0].swN;

	for(i=0;i<conway->randuri;i++)
	{
		for(j=0;j<conway->coloane;j++)
		{
			if(conway->harta[i][j].swN>H)
			{
				H=conway->harta[i][j].swN;
			}
		}	
	}

	return H;
}

void afiseazaHeat(lifeM *conway)
{
	int i,j;
	int H=cautaMax(conway);

	for(i=0;i<conway->randuri+2;i++)
	{
		for(j=0;j<conway->coloane+2;j++)
		{
			if((i==0)||(j==0)||(i==conway->randuri+1)||(j==conway->coloane+1))
			{
				printf("⬜");
			}
			else
			{
				if(conway->harta[i-1][j-1].swN==0)
				{
					printf("⚪");
				}
				else if(conway->harta[i-1][j-1].swN<H/10)
				{
					printf("🔵");
				}
				else if(conway->harta[i-1][j-1].swN<H/5)
				{
					printf("🔴");
				}
				else if(conway->harta[i-1][j-1].swN==H)
				{
					printf("🌟");
				}
				else 
				{
					printf("⚫");
				}
			}
		}	
		printf("\n");
	}
}
