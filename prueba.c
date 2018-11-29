#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct Casilla{
	float dist;
	int row;
	int col;
	int data;
	float infX;
	float supX;
	float infY;
	float supY;
	
	}Casilla;

typedef struct Foton{
	float x;
	float y;
	int coord_x;
	int coord_y;
	int distancia;
	int distMax;
	}Foton;

float random_float( float min, float max ){
    float range = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + range * (max - min);      /* [min, max] */
	}

void init_Foton(Foton *p, int row, int col, int dist, int distMax){
	float r1, r2, r3;
	r1 = random_float(0, row*dist);
	r2 = random_float(0, col*dist);
	r3 = random_float(0, distMax);
	p->x = r1;
	p->y = r2;
	p->distancia = r3;
	p->distMax = distMax;
	}
void absorcion(Foton *p, int row, int col, int dist, Casilla **tablero){
	int r1, r2, r3;
	p->distMax = p->distMax-p->distancia;
	r1 = random()%(row*dist);
	r2 = random()%(col*dist);
	r3 = random()%p->distMax;
	tablero[p->coord_x][p->coord_y].data++;
	p->x = r1;
	p->y = r2;
	p->distancia = r3;
	
	
	}
void difusion(Foton *p){
	
	}

void getArguments(int argc, char *argv[], int *numHijos, int *flag){
	int flags, opt;
	char *aux3;
	aux3 = malloc(10*sizeof(char));
	if(argc <3){//si se ingresa un numero de argumentos menor a 3, se finaliza la ejecucion del programa
		printf("Se ingreso un numero incorrecto de argumentos\n");
		exit(EXIT_FAILURE);
		}
	int nChild = -1;
	flags = 0;
	while ((opt = getopt(argc, argv, "mh:")) != -1) {
	   switch (opt) {
	   case 'm'://se busca el flag -m, en caso de ser encontrado se setea el valor flags = 1, no se considera lo que se ingrese despues del flag -m
		   flags = 1;
		   break;
	   case 'h': //se busca el flag -h
		   nChild = strtol(optarg, &aux3, 10);//se parsea el argumento ingresado junto al flag -h a entero
		   if(optarg!=0 && nChild==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-h nchild] [-m]\n", argv[0]);
				exit(EXIT_FAILURE);
			   }
		   //printf("optarg: %s\n", optarg);
		   break;
	   default: /* '?' */
		   fprintf(stderr, "Uso correcto: %s [-h nchild] [-m]\n",
				   argv[0]);
		   exit(EXIT_FAILURE);
	   }
	}

	if(flags==1){//si se encontro un flag -m, se setea la variable global flag = 1, respecto al scope del proceso principal
		(*flag) = 1;
		}
	(*numHijos) = nChild; //se iguala la variable numHijos a nChild
	if(nChild<0){
		fprintf(stderr, "Usage: %s [-h nchild] [-m]\n", argv[0]); //si la cantidad de hijos es negativa, se retorna un error
		exit(EXIT_FAILURE);
		}


}

void darMemoria(Casilla ***tabla, int row, int col){
	int i = 0;
	*tabla = (Casilla**)malloc(row*sizeof(Casilla));
	for(i=0;i<row;i++){
		(*tabla)[i] = (Casilla*)malloc(col*sizeof(Casilla));
		}
	
	}
void initTabla(Casilla **tabla, int row, int col, float dist){
	int i=0, j=0;
	float alto, ancho;
	alto = dist*row/2;
	ancho = dist*col/2;
	float iAlto = -alto, iAncho = -ancho;
	printf("alto %f - ancho %f\n", alto, ancho);
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			tabla[i][j].dist = dist;
			tabla[i][j].row = i;
			tabla[i][j].col = j;
			tabla[i][j].data = 0;
			tabla[i][j].infX = iAncho;
			tabla[i][j].supX = iAncho + dist;
			tabla[i][j].infY = iAlto;
			tabla[i][j].supY = iAlto + dist;
			iAncho = iAncho + dist;
			}
			iAncho = -ancho;
			iAlto = iAlto+dist;
		
		}
	}
void printTabla(Casilla **tabla, int row, int col, int dist){
	int i=0, j=0;
	for(i = 0; i<row; i++){
		for(j=0;j<col;j++){
				
			printf("[x1: %.2f x2: %.2f y1: %.2f y2: %.2f]", tabla[i][j].infX, tabla[i][j].supX, tabla[i][j].infY, tabla[i][j].supY);
			//printf("[%f	%f]", tabla[i][j].infX, tabla[i][j].supX);
			//printf("[	%f	]", tabla[i][j].infY);
			}
			printf("\n");
		
		
		}
	}
int main(){
	Casilla **tabla;
	Foton *f;
	f = (Foton*)malloc(sizeof(Foton));
	darMemoria(&tabla, 4, 4);
	initTabla(tabla, 4, 4, 1.5);
	printTabla(tabla, 4, 4, 1.5);
	init_Foton(f,5, 5, 2, 4);
	printf("Posicion foton: (%f-%f)\n", f->x, f->y);
	printf("Distancia foton %d\n", f->distancia);
	return 0;
}
