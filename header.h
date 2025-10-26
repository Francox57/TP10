#ifndef HEADER_H
#define HEADER_H
#define ANCHO 30
#define ALTO 30
#define MAXTHEMES 4
#if (ANCHO<=0 || ALTO<=0)
#error valor invalido para matriz
#elif(ANCHO>50 || ALTO>50 || ANCHO*ALTO>1000)
#warning parametros muy altos, sera disficil de ver la matriz
#endif
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
void llenar_mat (int mat[ALTO][ANCHO]);//Funcion para llenar matriz
void inicio(int mat [ALTO][ANCHO]); //Funcion para meter valores vivos
void generacion( int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int tiempo); //Funcion loop para las generaciones
void nace (int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int i, int j);//Funcion que nace nuevas celulas
void muere (int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int i, int j);//Funcion que mata las anteriores
void print_mat (int mat[ALTO][ANCHO]);//Funcion para imprimir la matriz
int numero (void);//asar de getchar a int
void copiar(int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO]);// Funcion para copiar matriz

// FUNCIONES PARA ALLEGRO 
void must_init(bool test, const char *descrpcion); // Se fija que inicialize bien todo
void dibujar_filycol(int dispAlto, int dispAncho,float lado,ALLEGRO_COLOR color); // dibuja las filas y columnas
void generacion_allegro( int mat[ALTO][ANCHO], int matReferencia[ALTO][ANCHO]); // pasa una generacion si se apreta enter

#endif