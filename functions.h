#include<time.h>

//Funciones útiles

void arrojarDados(int *dados){
    printf("Arrojando dados... \n");
    for(int i=0; i<=sizeof(dados); i++){
    dados[i] = srand(time(NULL));
    mostrarDado(i+1, dados[i]);
    }
}

void mostrarDado(int dadoId, int dado){
    printf("Dado %d: %d", dadoId, dado);
}

void seleccionarDados(int cantidadDados, int *dadosReemplazo){
    //Seleccionar dados
    for(int i=0; i<cantidadDados; i++){
    printf("Ingrese el número de dado que quiere relanzar (%d/%d) \n", i+1, cantidadDados);
    scanf("%d", dadosReemplazo[i]);
    }
}

//Reemplazar dados seleccionados
void actualizarDados(int *dadosActuales[], int indicesDadosNuevos[]){ 
    for(int i=0; i<sizeof(indicesDadosNuevos); i++){
    dadosActuales[indicesDadosNuevos[i]] = srand(time(NULL));
    mostrarDado(indicesDadosNuevos[i], dadosActuales[indicesDadosNuevos[i]]);
    }
}