#ifndef HEADER_H
#define HEADER_H
#define ANCHO 10
#define ALTO 10
#if (ANCHO<=0 || ALTO<=0)
#error valor invalido para matriz
#elif(ANCHO>50 || ALTO>50 || ANCHO*ALTO>1000)
#warning parametros muy altos, sera dificil de ver la matriz
#endif
void llenar_mat (int mat[ALTO][ANCHO]);//Funcion para llenar matriz
void inicio(int mat [ALTO][ANCHO]); //Funcion para meter valores vivos
void generacion( int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int tiempo); //Funcion loop para las generaciones
void nace (int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int i, int j);//Funcion que nace nuevas celulas
void muere (int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int i, int j);//Funcion que mata las anteriores
void print_mat (int mat[ALTO][ANCHO]);//Funcion para imprimir la matriz
int numero (void);//{asar de getchar a int
void copiar(int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO]);// Funcion para copiar matriz

#endif