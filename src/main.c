#include "funciones.h"
#include "shared.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>


pthread_mutex_t **mutex;

int main(int argc, char *argv[]){
	//Casilla **tabla;
	Foton **f;
	char *aux, *aux1, *aux2;
	time_t t;
	pthread_t *hebras;
	int numFotones, distMax, x, y, flag=0, cont=0;
	float delta;
	srand((unsigned) time(&t));
	//printf("antes get arguments\n");
	getArguments(argc, argv, &numFotones, &distMax, &x, &y, &delta, &flag);
	aux = (char *)malloc(5*sizeof(char));
	aux1 = (char *)malloc(5*sizeof(char));
	aux2 = (char *)malloc(5*sizeof(char));
	
	//Se iniciliza la matriz de mutex
	mutex = (pthread_mutex_t**)malloc(sizeof(pthread_mutex_t*)*x);
	for(int i=0;i<x;i++){
		mutex[i] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*y);
	}
	for(int i = 0; i<x; i++){
		for(int j = 0; j<y; j++){
			pthread_mutex_init(&mutex[i][j],NULL);
		}
	}	
	
	strcpy(aux1, "[");
	strcpy(aux2, "[");
	hebras = (pthread_t*)malloc(numFotones*sizeof(pthread_t)); 
	f = (Foton**)malloc(numFotones*sizeof(Foton*));
	for(int i=0;i<numFotones;i++){
		f[i] = (Foton*)malloc(sizeof(Foton));
		init_Foton(f[i], x, y, distMax,i, flag);
		}
	//printf("despues de get arguments uwu \n");
	darMemoria(&tablaE, x, y);
	initTabla(tablaE, x, y, delta);
	//printTabla(tablaE, x, y, delta, 1);
	
	while(cont<numFotones){
		pthread_create(&hebras[cont], NULL, transferenciaRadiactiva, (void *)f[cont]);
		cont++;
		}
	cont = 0;
	while(cont<numFotones){
		pthread_join(hebras[cont], NULL);
		cont++;
		}
	if (flag == 1){
		printTabla(tablaE, x, y, delta, 0);
	}
	
	//printf("Creando archivo salida...\n");
	crearSalida(tablaE,x, y);
	//printf("cerrando archivo...\n");
	free(aux);
	free(aux1);
	free(aux2);
	return 0;
}


