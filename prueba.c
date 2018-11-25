#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Casilla{
	int dist;
	int row;
	int col;
	int data;
	
	}Casilla;

void darMemoria(Casilla ***tabla, int row, int col){
	int i = 0;
	*tabla = (Casilla**)malloc(row*sizeof(Casilla));
	for(i=0;i<row;i++){
		(*tabla)[i] = (Casilla*)malloc(col*sizeof(Casilla));
		}
	
	}
void initTabla(Casilla **tabla, int row, int col, int dist){
	int i=0, j=0;
	for(i=0;i<row;i++){
		for(j=0;j<row;j++){
			tabla[i][j].dist = dist;
			tabla[i][j].row = i;
			tabla[i][j].col = j;
			tabla[i][j].data = 0;
			}
		
		}
	}
void printTabla(Casilla **tabla, int row, int col, int dist){
	int i=0, j=0;
	for(i = 0; i<row; i++){
		for(j=0;j<col;j++){
			printf("%d ", tabla[i][j].data);
			}
		printf("\n");
		
		}
	}
int main(){
	Casilla **tabla;
	darMemoria(&tabla, 5, 5);
	initTabla(tabla, 5, 5, 2);
	printTabla(tabla, 5, 5, 2);
	
	
	return 0;
}
