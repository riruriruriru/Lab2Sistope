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

typedef struct Casilla{
	float dist;
	int row;
	int col;
	int data;
	float infX;
	float supX;
	float infY;
	float supY;
	int t_row;
	int t_col;
	}Casilla;

typedef struct Foton{
	float x;
	float y;
	int coord_x;
	int coord_y;
	float distancia;
	int distMax;
	}Foton;

float random_float( float min, float max ){
    float range = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + range * (max - min);      /* [min, max] */
	}

void assign_coord(Casilla **tabla, Foton *p){
	int i = 0, j = 0;
	for(i = 0; i<tabla[0][0].t_row; i++){
		for(j = 0;j<tabla[0][0].t_col;j++){
			if(p->x>=tabla[i][j].infX && p->x<=tabla[i][j].supX && p->y>=tabla[i][j].infY &&p->y>=tabla[i][j].supY){
				p->coord_x = j;
				p->coord_y = i;
				printf("i-j -> %d %d\n", i, j);
				//printf("j-i -> %d %d\n", j, i);
				printf("[x1: %.2f x2: %.2f y1: %.2f y2: %.2f]\n", tabla[i][j].infX, tabla[i][j].supX, tabla[i][j].infY, tabla[i][j].supY);
				}
			}
		}
	}
	
void vector_dist(Foton *p, Casilla **tabla){
	float r1, r2, r3, r, rr, m;
	time_t t;
	srand((unsigned) time(&t));
	r = (double)rand() / (double)RAND_MAX;
	printf("random: %f\n", r);
	srand((unsigned) time(&t));
	r1 = cos(random());
	r2 = sin(random());
	m = sqrt(r1*r1 + r2*r2);
	r1 = r1/m;
	r2 = r2/m;
	printf("modulo vector: %f\n", sqrt(r1*r1 + r2*r2));
	printf("x: %f - y: %f\n", r1, r2);
	rr = 1-r;
	printf("1-r: %f\n", rr);
	r3 = -(log(rr));
	printf("log: %f\n", r3);
	p->x = r1*r3;
	p->y = r2*r3;
	p->distancia = r3;
	printf("vector final: %f --- %f\n", p->x, p->y);
	}

void init_Foton(Foton *p, int row, int col, int distMax){
	p->x = 0;
	p->y = 0;
	p->distancia = 0;
	p->distMax = distMax;
	p->coord_x = 0;
	p->coord_y = 0;
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

void getArguments(int argc, char *argv[], int *numFotones, int *distMax, int *x, int *y, float *delta, int *flag){
	int flags, opt;
	char *aux3;
	aux3 = malloc(10*sizeof(char));
	if(argc <7){//si se ingresa un numero de argumentos menor a 7, se finaliza la ejecucion del programa
		printf("Se ingreso un numero incorrecto de argumentos\n");
		exit(EXIT_FAILURE);
		}
	int nFotones = -1, cX, cY, auxDist;
	float auxDelta;
	flags = 0;
	printf("dentro opt arg antes del while uwu\n");
	while ((opt = getopt(argc, argv, "nLXYdb:")) != -1) {
		printf("dentro while\n");
		strcpy(aux3,"\0");
		printf("owo\n");
		switch (opt) {
			case 'b'://se busca el flag -b, en caso de ser encontrado se setea el valor flags = 1, no se considera lo que se ingrese despues del flag -m
			   printf("caso b\n");
			   flags = 1;
			   break;
			case 'n': //se busca el flag -n, cantidad de fotones
			   printf("caso n, %s\n", optarg);
			   nFotones = strtol(optarg, &aux3, 10);//se parsea el argumento ingresado junto al flag -h a entero
			   if(optarg!=0 && nFotones==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
					fprintf(stderr, "Uso correcto: %s [-n nfotones] [-b]\n", argv[0]);
					exit(EXIT_FAILURE);
				   }
			   //printf("optarg: %s\n", optarg);
			   break;
			case 'L': //se busca el flag -L, distancia maxima foton
			   printf("caso L\n");
			   auxDist = strtol(optarg, &aux3, 10);//se parsea el argumento ingresado junto al flag -h a entero
			   if(optarg!=0 && auxDist==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
					fprintf(stderr, "Uso correcto: %s [-L distMax] [-b]\n", argv[0]);
					exit(EXIT_FAILURE);
				   }
			   //printf("optarg: %s\n", optarg);
			   break;
			case 'X': //se busca el flag -X, dimension X de la grilla 
			   printf("caso X\n");
			   cX = strtol(optarg, &aux3, 10);//se parsea el argumento ingresado junto al flag -h a entero
			   if(optarg!=0 && cX==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
					fprintf(stderr, "Uso correcto: %s [-h nchild] [-m]\n", argv[0]);
					exit(EXIT_FAILURE);
				   }
			   //printf("optarg: %s\n", optarg);
			   break;
			case 'Y': //se busca el flag -h
				printf("caso Y\n");
			   cY = strtol(optarg, &aux3, 10);//se parsea el argumento ingresado junto al flag -h a entero
			   if(optarg!=0 && cY==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
					fprintf(stderr, "Uso correcto: %s [-h nchild] [-m]\n", argv[0]);
					exit(EXIT_FAILURE);
				   }
			   //printf("optarg: %s\n", optarg);
			   break;
			case 'd': //se busca el flag -d, delta entre casillas de la grilla
				printf("caso d\n");
				printf("%s\n", optarg);
			   auxDelta = atof(optarg);//se parsea el argumento ingresado junto al flag -h a entero
			   if(optarg!=0 && auxDelta==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
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
	(*numFotones) = nFotones; //se iguala la variable numHijos a nChild
	(*distMax) = auxDist;
	(*x) = cX;
	(*y) = cY;
	(*delta) = auxDelta;
	if(nFotones<=0){
		fprintf(stderr, "Usage: %s [-h nFotones] [-m]\n", argv[0]); //si la cantidad de fotones es negativa, se retorna un error
		exit(EXIT_FAILURE);
		}
	if(cX%2!=0 || cY%2 !=0){
		fprintf(stderr, "Usage: %s [-h nFotones] [-m]\n", argv[0]); //si la cantidad de fotones es negativa, se retorna un error
		exit(EXIT_FAILURE);
		}
	if(auxDelta<=0){
		fprintf(stderr, "Usage: %s [-h nFotones] [-m]\n", argv[0]); //si la cantidad de fotones es negativa, se retorna un error
		exit(EXIT_FAILURE);
		}
	if(auxDist<=0){
		fprintf(stderr, "Usage: %s [-h nFotones] [-m]\n", argv[0]); //si la cantidad de fotones es negativa, se retorna un error
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
	printf("radio: %f\n", alto);
	float iAlto = -alto, iAncho = -ancho;
	printf("alto %f - ancho %f\n", alto, ancho);
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			tabla[i][j].dist = dist;
			tabla[i][j].row = i;
			tabla[i][j].col = j;
			tabla[i][j].t_row = row;
			tabla[i][j].t_col = col;
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
				
			//printf("[x1: %.2f x2: %.2f y1: %.2f y2: %.2f]", tabla[i][j].infX, tabla[i][j].supX, tabla[i][j].infY, tabla[i][j].supY);
			//printf("[%f	%f]", tabla[i][j].infX, tabla[i][j].supX);
			//printf("[	%f	]", tabla[i][j].infY);
			printf("[%d %d]", i, j);
			}
			printf("\n");
		
		
		}
	}
int main(int argc, char *argv[]){
	Casilla **tabla;
	Foton *f;
	f = (Foton*)malloc(sizeof(Foton));
	int numFotones, distMax, x, y, flag;
	float delta;
	printf("antes get arguments\n");
	getArguments(argc, argv, &numFotones, &distMax, &x, &y, &delta, &flag); 
	printf("despues de get arguments uwu \n");
	darMemoria(&tabla, x, y);
	initTabla(tabla, x, y, delta);
	printTabla(tabla, x, y, delta);
	init_Foton(f,x, y, distMax);
	printf("Posicion foton: (%f-%f)\n", f->x, f->y);
	vector_dist(f, tabla);
	printf("Distancia foton %f\n", f->distancia);
	assign_coord(tabla, f);
	return 0;
}
