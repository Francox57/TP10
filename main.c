#include <stdio.h>
#include "header.h"



int main (void){
    int mat [ALTO][ANCHO];//Matriz original, la cual va a ser usada para mostrar en pantalla
    int matReferencia [ALTO][ANCHO]; // Matriz que copia el estado de la matriz original, se utiliza esta matriz para calcular el estado siguiente de la matriz original
    int tiempo;//Variable ingresada por usuario de cantidad de generaciones
    long int gen =0; //Variable que guarda el total de generaciones que se introdujeron
    llenar_mat(mat);//llena la matriz con espacios (puntos muertos)
    print_mat(mat);//Imprime la matriz
    inicio(mat);//Elegir el valor vivo
    copiar(mat,matReferencia);// Copiar la matriz original a matriz referencia
    tiempo = numero ();//Pasamos tiempo a variable int
    while(tiempo != 'q' ){//Mientras no aprete q el usuario
        if(tiempo>=0){//Si se ingreso un valor valido
            gen+=tiempo;
            printf("Pasaron %ld generaciones\n", gen);//Se imprime la cantidad de generaciones que pasaron
            generacion(mat,matReferencia,tiempo);
            printf("Cuantas generaciones ¿desea que pase? Para avanzar solo una generacion apretar enter o coma.\n");
            printf("Para salir del programa apretar q.\n");
        }
        else{
            printf("Ingresar valor valido.\n");
        }
        tiempo = numero ();
    }
    return 0;
}

