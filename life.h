#ifndef life_h
#define life_h

struct SdMatrix
{
	int actual,anterior,swN;
};
typedef struct SdMatrix dMatrix;

struct SlifeM
{
	int coloane,randuri;
	dMatrix **harta;
};
typedef struct SlifeM lifeM;

void deseneaza(lifeM *conway);
dMatrix **malloca(lifeM conway);
void dalloca(lifeM *conway);
void delay(int number_of_seconds);

void randomizeaza(lifeM *conway,int procent);
void evolueaza(lifeM *conway);
void muta(lifeM *conway);

int sumaV(lifeM *conway,int x,int y);
void masoara(lifeM *conway);
void afiseazaHeat(lifeM *conway);
int cautaMax(lifeM *conway);

#endif
