#include "functions.h"
#include <stdio.h>

//Valores de puntajes de cada categoría
#define ESCALERA_VALUE 35
#define FULL_VALUE 50
#define POKER_VALUE 75
#define GENERALA_VALUE 100
#define GENERALA_DOBLE_VALUE 120
#define LANZAMIENTOS_MAX 3
#define TURNOS_MAX 11

int main(){
    int dados[5];
    int categorias[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int cantidadJugadores = 0;
    char jugador1[20] = "";
    char jugador2[20] = "";

    printf("¡Hola!, bienvenido al juego de la Generala!\n");
    do{
        printf("Elija la cantidad de jugadores (1 o 2):\n");
        scanf("%d", &cantidadJugadores);
        if(cantidadJugadores != 1 && cantidadJugadores != 2){
            printf("¡Solo pueden jugar 1 o 2 jugadores!\n");
            printf("Inténtelo de nuevo.\n");
        }
    } while(cantidadJugadores != 1 && cantidadJugadores != 2);

    for(int i=1; i<=cantidadJugadores; i++){
        printf("Ingrese el nombre del jugador %d:\n", i);
        if(i==1){
            scanf("%s",jugador1);
            printf("Bienvenido %s!\n", jugador1);
        } else{
            scanf("%s",jugador2);
            printf("Bienvenido %s!\n", jugador2);           
        }
    }
    printf("A continuación %s tirará los 5 dados por primera vez.\n", jugador1);
    //do while turno<=11
    //Turno 1: 
    //
        //while (lanzamiento i=1; i++, i<=3)
        //cantidadDados=5
        //dadosUpdate[5] = [0,0,0,0,0]
        //Ejecutar tirar dados(5)
        //sobreEscribirDados(dados, dadosRef)
        //Mostrar resultados según indice = dado
        //¿Cuántos dados desea arrojar? x 2
        //  - 0 (Pasar y anotar categoría) (break)
        //  - 1-5 (cantidadDados) (for)
        //
        // Ingresar Índice de dados (1 a 5) (guardar en array dadosSelect)
        // Repeat while
    //Evaluando categorías...
    //Evaluar categorías posibles
    //switch
    //

    



    return 0;
}