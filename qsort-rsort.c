#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
// Partie 1:
struct timeval begin, end;

void affiche(size_t Tlen, const uint32_t T[Tlen]){
	printf("{");
	for(int i=0;i<Tlen-1;i++)
		printf("%u,",T[i]);
	printf("%u}",T[Tlen-1]);
}

int sorted(size_t Tlen, const uint32_t T[Tlen]){
	for(int i=0;i<Tlen-1;i++){
		if(T[i]>T[i+1]){
			return 0;
		}
	}
	return 1;
}

int compareFunction(uint32_t first, uint32_t second){
  return ( first -second );
}

/*int partition(size_t Tlen, uint32_t T[Tlen], int d, int f){ //x n'est pas utile car on l'initialise dans la fonction à partir de f
	uint32_t x = T[f];
	int n = f;
	for(int i = f-1; i >= d; i--){
		if(T[i] > x){
			T[n] = T[i];
			T[i] = T[n-1];
			n = n - 1;
		}
	}
	T[n] = x;
	return n;
}*/

int partition(size_t Tlen, uint32_t T[Tlen], int d, int f){ //x n'est pas utile car on l'initialise dans la fonction à partir de f
	srandom(time(NULL));
	int r = d+random()%(f-d+1);
	uint32_t x = T[r];
	int n = f;
	for(int i = f-1; i >= d; i--){
		if(T[i] > x){
			T[n] = T[i];
			T[i] = T[n-1];
			n = n - 1;
		}
	}
	T[n] = x;
	return n;
}

int partitiong(size_t Tlen, uint32_t T[Tlen], int d, int f){ //x n'est pas utile car on l'initialise dans la fonction à partir de f
	srandom(time(NULL));
	int r = d+random()%(f-d+1);
	uint32_t x = T[r];
	int n = f;
	for(int i = f-1; i >= d; i--){
		if(compareFunction(T[i],x) >0){
			T[n] = T[i];
			T[i] = T[n-1];
			n = n - 1;
		}
	}
	T[n] = x;
	return n;
}

void quicksortu(size_t Tlen,uint32_t T[Tlen], int d, int f){ //Tlen pas forcément utile
	if(f<=d){
		//printf("Fin de récursivité\n");
	}
	else{
	int n = partition(Tlen, T, d, f); //Renvoie n 
	quicksortu(Tlen, T, d, n-1);
	quicksortu(Tlen, T, n, f);
	//printf("Partition faite\n");
	}
}

void qsortu(size_t Tlen, uint32_t T[Tlen]){
	quicksortu(Tlen, T, 0, Tlen-1);	
}

void quicksortg(size_t Tlen,uint32_t T[Tlen], int d, int f){ //Tlen pas forcément utile
	if(f<=d){
		//printf("Fin de récursivité\n");
	}
	else{
	int n = partitiong(Tlen, T, d, f); //Renvoie n 
	quicksortg(Tlen, T, d, n-1);
	quicksortg(Tlen, T, n, f);
	//printf("Partition faite\n");
	}
}

void qsortg(size_t Tlen, uint32_t T[Tlen]){//,int (*compareFunction)( const void* first, const void* second)){
	quicksortg(Tlen, T, 0, Tlen-1);	
}


// Partie 2


uint32_t ExtractBit(int elen, int b, int i){
	unsigned mask;
	mask = ((1 << b) - 1) << i;
	unsigned isolatedbits = elen & mask;
	return isolatedbits;
}

uint32_t Max(size_t Tlen, uint32_t T[Tlen]){
	uint32_t max = T[0];
	for(int i = 1;i<Tlen;i++){
		if(max < T[i])
			max = T[i];
	}
	return max;
}

void denomsort(size_t Tlen, uint32_t T1[Tlen], uint32_t T2[Tlen],int b, int i){
	uint32_t *S = malloc(sizeof(uint32_t)*Tlen);
	for(int k = 0;k<Tlen;k++)	
		S[k] = ExtractBit(T1[k],b,i*b);
	//affiche(Tlen,S);
	//affiche(Tlen,T1);
	uint32_t max = Max(Tlen,S);
	uint32_t *C = malloc(sizeof(uint32_t)*(max+1));
	for(int k = 0; k < max+1; k++ )
		C[k] = 0;
	for(int k = 0; k < Tlen;k++){
		C[S[k]] += 1;
		}
	for(int k = 1;k<max+1;k++)
		C[k] += C[k-1];
	//affiche(Tlen,S);
	//affiche(Tlen,T1);
	for(int k = Tlen - 1; k >=0; k--){
		C[S[k]] = C[S[k]] -1;
		T2[C[S[k]]] = T1[k];
	}
	//affiche(Tlen,T2);
	free(S);
	free(C);
}

void denomsort2(size_t Tlen, uint32_t T1[Tlen], uint32_t T2[Tlen],int b, int i){ //à utiliser pour le dernier chiffre si il reste moins de b bits
	uint32_t *S = malloc(sizeof(uint32_t)*Tlen);
	for(int k = 0;k<Tlen;k++)	
		S[k] = ExtractBit(T1[k],32-(i*b),i*b);
	//affiche(Tlen,S);
	//affiche(Tlen,T1);
	uint32_t max = Max(Tlen,S);
	uint32_t *C = malloc(sizeof(uint32_t)*(max+1));
	for(int k = 0; k < max+1; k++ )
		C[k] = 0;
	for(int k = 0; k < Tlen;k++){
		C[S[k]] += 1;
		}
	for(int k = 1;k<max+1;k++)
		C[k] += C[k-1];
	//affiche(Tlen,S);
	//affiche(Tlen,T1);
	for(int k = Tlen - 1; k >=0; k--){
		C[S[k]] = C[S[k]] -1;
		T2[C[S[k]]] = T1[k];
	}
	//affiche(Tlen,T2);
	free(S);
	free(C);
}

void swap(size_t Tlen, uint32_t T1[Tlen], uint32_t T2[Tlen]){
	uint32_t *Te = malloc(sizeof(uint32_t)*Tlen);
	for(int k=0;k<Tlen;k++)
		Te[k]=T1[k];
	for(int k=0;k<Tlen;k++)
		T1[k]=T2[k];
	for(int k=0;k<Tlen;k++)
		T2[k]=Te[k];
	free(Te);
}

uint32_t radixsort(size_t Tlen, uint32_t T[Tlen], int b){
	int nlen = 32/b;
	uint32_t *T1 = malloc(sizeof(uint32_t)*Tlen);
	uint32_t *T2 = malloc(sizeof(uint32_t)*Tlen);
	for(int k=0;k<Tlen;k++)
		T1[k]=T[k];
	for(int k=0;k<Tlen;k++)
		T2[k]=T[k];
	//affiche(Tlen,T1);
	int c = 0;
	if(32%b==0){
		for(int i = 0;i<nlen;i++){
			denomsort(Tlen,T1,T2,b,i);
			swap(Tlen,T1,T2);
		}
	}
	else{
		for(int i = 0;i<nlen;i++){
		//printf("Test\n");
		denomsort(Tlen,T1,T2,b,i);
		swap(Tlen,T1,T2);
		c = c+1;
		}
		//printf("Test2\n");
		denomsort2(Tlen,T1,T2,32%c,0);
		swap(Tlen,T1,T2);	
	}
	for(int k=0;k<Tlen;k++)
		T[k]=T1[k];
	free(T1);
	free(T2);
	//affiche(Tlen,T);
}

//Fonctions de Test

//fonction pour calculer le temps d'execution
float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}



void testsorted(size_t Tlen, const uint32_t T[Tlen]){
	if(sorted(Tlen, T) == 1)
	{
		printf("Le tableau est trié\n");
	}
	else{
		printf("Le tableau n'est pas trié\n");
	}

}

void testqsortu(size_t Tlen, uint32_t T[Tlen]){
	gettimeofday(&begin, NULL);
	qsortu(Tlen,T);
	gettimeofday(&end, NULL);
	printf("%.4f\n",time_diff(&begin, &end));
	testsorted(Tlen,T);
	
	
}

void testqsortg(size_t Tlen, uint32_t T[Tlen]){
	gettimeofday(&begin, NULL);
	qsortg(Tlen,T);
	gettimeofday(&end, NULL);
	printf("%.4f\n",time_diff(&begin, &end));
	testsorted(Tlen,T);		
}

void testqsort(size_t Tlen, uint32_t T[Tlen]){
	gettimeofday(&begin, NULL);
	//qsort(T,Tlen,sizeof(uint32_t),compareFunction);
	gettimeofday(&end, NULL);
	printf("%.4f\n",time_diff(&begin, &end));
	testsorted(Tlen,T);		
}


void testqsorturandom(size_t Tlen, uint32_t Tmax){
	srandom(time(NULL));
	uint32_t *T = malloc(sizeof(uint32_t)*Tlen);
	for(int i = 0;i<Tlen;i++){
		T[i] = random()%Tmax;
	}
	
	//affiche(Tlen,T); //Pour voir le Tableau avant ou après
	if(sorted(Tlen,T)==0){
		testqsortu(Tlen,T);
	}
	//affiche(Tlen,T);
	free(T);
}

void testqsortgrandom(size_t Tlen, uint32_t Tmax){
	srandom(time(NULL));
	uint32_t *T = malloc(sizeof(uint32_t)*Tlen);
	for(int i = 0;i<Tlen;i++){
		T[i] = random()%Tmax;
	}
	
	//affiche(Tlen,T); //Pour voir le Tableau avant ou après
	if(sorted(Tlen,T)==0){
		testqsortg(Tlen,T);
	}
	//affiche(Tlen,T);
	free(T);
}

void testqsortrandom(size_t Tlen, uint32_t Tmax){
	srandom(time(NULL));
	uint32_t *T = malloc(sizeof(uint32_t)*Tlen);
	for(int i = 0;i<Tlen;i++){
		T[i] = random()%Tmax;
	}
	
	//affiche(Tlen,T); //Pour voir le Tableau avant ou après
	if(sorted(Tlen,T)==0){
		testqsort(Tlen,T);
	}
	//affiche(Tlen,T);
	free(T);
}

void testqsortudecr(size_t Tlen){
	uint32_t *T = malloc(sizeof(uint32_t)*Tlen);
	for(int i = 0;i<Tlen;i++){
		T[i] = Tlen-i;
	}
	//affiche(Tlen,T); //Pour voir le Tableau avant ou après
	if(sorted(Tlen,T)==0){
		testqsortu(Tlen,T);
	}
	//affiche(Tlen,T);
	free(T);
}

void testdenomsort(size_t Tlen, uint32_t T1[Tlen], uint32_t T2[Tlen],int b,int i){
	gettimeofday(&begin, NULL);
	denomsort(Tlen,T1,T2,b,i);
	gettimeofday(&end, NULL);
	printf("%.4f\n",time_diff(&begin, &end));
	testsorted(Tlen,T2);
}

void testdenomsortrandom(size_t Tlen, uint32_t Tmax,int b,int i){
	srandom(time(NULL));
	uint32_t *T = malloc(sizeof(uint32_t)*Tlen);
	for(int i = 0;i<Tlen;i++){
		T[i] = random()%Tmax;
	}
	uint32_t *Te = malloc(sizeof(uint32_t)*Tlen);
	for(int k=0;k<Tlen;k++)
		Te[k]=T[k];
	//affiche(Tlen,T); //Pour voir le Tableau avant ou après
	if(sorted(Tlen,T)==0){
		testdenomsort(Tlen,T,Te,b,i);
	}
	//affiche(Tlen,T);
	free(Te);
	free(T);
}
void testradixsort(size_t Tlen, uint32_t T[Tlen],int b){
	gettimeofday(&begin, NULL);
	radixsort(Tlen,T,b);
	gettimeofday(&end, NULL);
	printf("%.4f\n",time_diff(&begin, &end));
	testsorted(Tlen,T);
}

void testradixsortrandom(size_t Tlen, uint32_t Tmax,int b){
	srandom(time(NULL));
	uint32_t *T = malloc(sizeof(uint32_t)*Tlen);
	for(int i = 0;i<Tlen;i++){
		T[i] = random()%Tmax;
	}
	//affiche(Tlen,T); //Pour voir le Tableau avant ou après
	if(sorted(Tlen,T)==0){
		testradixsort(Tlen,T,b);
	}
	//affiche(Tlen,T);
	free(T);
}


int main(){
	
		
	///Tests de sorted
	uint32_t T[] = {1,2,3,4};
	uint32_t L[] = {8,6,7,2,5,3,9,4};
	//testsorted(4,T);
	//testsorted(8,L);
	//Test de qsortu
	//testqsortu(8,L);
	///Test qsortu tableau aléatoire
	/*for(int i = 0;i<3;i++){ //Tableau de 1000000 d'éléments allant jusqu'à 100000
		testqsorturandom(1000000,100000);
	}*/
	/*for(int i = 0;i<3;i++){ //Tableau de 1000000 d'éléments allant jusqu'à 10000000
		testqsorturandom(10000000,1000000);
	}*/
	uint32_t A[] = {5,8,7,13,6,4,256,2,1};
	uint32_t B[] = {4,3,0,2,1};
	uint32_t Ap[] = {5,8,7,13,6,4,256,2,1};
	uint32_t Bp[] = {4,3,0,2,1};
	//testqsortu(9,A);
	//testqsortu(4,B);
	//testqsortudecr(50);
	//testqsorturandom(1000000,1000000);
	//testqsortgrandom(1000000,1000000);
	//testqsortudecr(1000000);
	//testqsorturandom(1000000,1000000);
	//Max(9,A);
	//testdenomsortrandom(10000,16777215,24,0);
	//testradixsortrandom(240000000,4294967295,16);
	//testdenomsort(9,A,Ap,24,0);
	//testdenomsort(5,B,Bp,24,0);
	//testradixsort(9,A,5);
	//testradixsort(5,B,5);
	testqsorturandom(240000000,16777215);
	testradixsortrandom(240000000,16777215,12);
	uint32_t number = 9, b = 10, i = 2;
  	printf("Le nombre obtenu est %u\n",ExtractBit(number, b,i));	

	
}


