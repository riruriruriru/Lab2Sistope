#include "casilla.h"
#include "foton.h"

#ifndef FUNCIONES_H
#define FUNCIONES_H
float random_float( float min, float max );
int assign_coord(Casilla **tabla, Foton *p);
void vector_dist(Foton *p, Casilla **tabla);
void init_Foton(Foton *p, int row, int col, int distMax, int id, int flag);
int absorcion(Foton *p, int row, int col, Casilla **tablero);
int difusion(Foton *p, Casilla **tablero);
void getArguments(int argc, char *argv[], int *numFotones, int *distMax, int *x, int *y, float *delta, int *flag);
void darMemoria(Casilla ***tabla, int row, int col);
void initTabla(Casilla **tabla, int row, int col, float dist);
void printTabla(Casilla **tabla, int row, int col, int dist, int flag);
void *transferenciaRadiactiva(void *f);
void crearSalida(Casilla **tabla, int x, int y);

#endif
