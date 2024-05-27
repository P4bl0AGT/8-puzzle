#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tdas/list.h"
#include "tdas/queue.h"
#include "tdas/stack.h"

//ESTRUCTURA DE MIS ESTADOS
typedef struct
{
  int tablero[3][3];
  int iVacio;
  int jVacio;
  int profundidad;
  List *acciones;
  int movimientos[4];
  int clave;
} tipoEstado;

//FUNCION QUE CALCULA UNA CLAVE UNICA PARA CADA TABLERO
int calcularClave(tipoEstado *estado)
{
  int numero = 0;
  int exponente = 1;
  for(int i = 0 ; i < 3 ; i++)
    for(int j = 0 ; j < 3 ; j++)
    {
      numero += estado->tablero[i][j] * exponente;
      exponente *= 10;
    }
  return numero;
}

//FUNCION QUE INICIALIZA UN ESTADO CON 0
tipoEstado *iniciarEstado()
{
  tipoEstado *estado = (tipoEstado *) malloc(sizeof(tipoEstado));
  estado->iVacio = 0;
  estado->jVacio = 0;
  estado->profundidad = 0;
  estado->acciones = list_create();
  for(int i = 0 ; i < 4 ; i++)
    estado->movimientos[i] = 0;
  return estado;
}

//FUNCION QUE CALCULA EN QUE POSICION SE ENCUENTRA EL 0 DEL TABLERO
void calcularCasillaVacia(tipoEstado *estado)
{
  for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
      {
        if(estado->tablero[i][j] == 0)
        {
          estado->iVacio = i;
          estado->jVacio = j;
          return;
        }
      }
}

//FUNCION QUE CALCULA LOS MOVIMIENTOS VALIDOS DEL TABLERO
void calcularMovimientosValidos(tipoEstado *estado)
{
  if(estado->iVacio > 0) //SE PUEDE MOVER EL BLOQUE DE ARRIBA HACIA LA POSICION VACIA
    estado->movimientos[0] += 1;
  if(estado->iVacio < 2) //SE PUEDE MOVER EL BLOQUE DE ABAJO HACIA LA POSICION VACIA
    estado->movimientos[1] += 1;
  if(estado->jVacio > 0) //SE PUEDE MOVER EL BLOQUE DE IZQUIERDA HACIA LA POSICION VACIA
    estado->movimientos[2] += 1;
  if(estado->jVacio < 2) //SE PUEDE MOVER EL BLOQUE DE DERECHA HACIA LA POSICION VACIA
    estado->movimientos[3] += 1;
}

//FUNCION QUE IMPRIME EN PANTALLA EL TABLERO
void mostrarEstado(tipoEstado *estado)
{
  for(int i = 0 ; i < 3 ; i++)
  {
    for(int j = 0 ; j < 3 ; j++)
      printf("%i ", estado->tablero[i][j]);
    printf("\n");
  }
  printf("\n");
}

//FUNCION QUE GENERA UN NUEVO ESTADO CON UN NUEVO TABLERO A PARTIR DE UN ESTADO ENTREGADO Y UN MOVIMIENTO VALIDO
void moverBloque(tipoEstado *estado, int movimiento)
{
  int iVacio = estado->iVacio;
  int jVacio = estado->jVacio;
  //
  if(movimiento == 0) //MOVER EL BLOQUE DE ARRIBA AL ESPACIO VACIO
  {
    estado->tablero[iVacio][jVacio] = estado->tablero[iVacio-1][jVacio]; //EL BLOQUE VACIO DARLE EL VALOR DEL ADYACENTE CORRESPONDIENTE
    estado->tablero[iVacio-1][jVacio] = 0; //EL BLOQUE ADYACENTE DARLE EL VALOR DE 0
    estado->iVacio--;//MODIFICAR LA CASILLA VACIA
    estado->movimientos[1] = -1;//ANULAR MOVIMIENTO PARA QUE NO VUELVA AL ESTADO ANTERIOR
  }
  else if(movimiento == 1) //MOVER EL BLOQUE DE ABAJO AL ESPACIO VACIO
  {
    estado->tablero[iVacio][jVacio] = estado->tablero[iVacio+1][jVacio];//EL BLOQUE VACIO DARLE EL VALOR DEL ADYACENTE CORRESPONDIENTE
    estado->tablero[iVacio+1][jVacio] = 0;//EL BLOQUE ADYACENTE DARLE EL VALOR DE 0
    estado->iVacio++;//MODIFICAR LA CASILLA VACIA
    estado->movimientos[0] = -1;//ANULAR MOVIMIENTO PARA QUE NO VUELVA AL ESTADO ANTERIOR
  }
  else if(movimiento == 2) //MOVER EL BLOQUE DE ABAJO AL ESPACIO VACIO
  {
    estado->tablero[iVacio][jVacio] = estado->tablero[iVacio][jVacio-1];//EL BLOQUE VACIO DARLE EL VALOR DEL ADYACENTE CORRESPONDIENTE
    estado->tablero[iVacio][jVacio-1] = 0;//EL BLOQUE ADYACENTE DARLE EL VALOR DE 0
    estado->jVacio--;//MODIFICAR LA CASILLA VACIA
    estado->movimientos[3] = -1;//ANULAR MOVIMIENTO PARA QUE NO VUELVA AL ESTADO ANTERIOR
  }
  else if(movimiento == 3) //MOVER EL BLOQUE DE ABAJO AL ESPACIO VACIO
  {
    estado->tablero[iVacio][jVacio] = estado->tablero[iVacio][jVacio+1];//EL BLOQUE VACIO DARLE EL VALOR DEL ADYACENTE CORRESPONDIENTE
    estado->tablero[iVacio][jVacio+1] = 0;//EL BLOQUE ADYACENTE DARLE EL VALOR DE 0
    estado->jVacio++;//MODIFICAR LA CASILLA VACIA
    estado->movimientos[2] = -1;//ANULAR MOVIMIENTO PARA QUE NO VUELVA AL ESTADO ANTERIOR
  }
  
  //AGREGAR LA ACCION CORRESPONDIENTE A LA LISTA DE ACCIONES
  int *accion = malloc(sizeof(int));
  *accion = movimiento;
  list_pushBack(estado->acciones, accion);
}

//FUNCION QUE OBTIENE LOS NODOS ADYACENTES DE UN ESTADO
List *obtenerAdyacentes(tipoEstado *estado)
{
  //SE CREA LA LISTA
  List *lista = list_create();
  for(int i = 0 ; i < 4 ; i++)
  {
    //SI EL MOVIMIENTO ES VALIDO
    if(estado->movimientos[i] == 1)
    {
      //GENERAMOS UN ESTADO VACIO
      tipoEstado *nuevoEstado = iniciarEstado();
      //COPIAMOS EL TABLERO
      for(int j = 0 ; j < 3 ; j++)
        for(int k = 0 ; k < 3 ; k++)
            nuevoEstado->tablero[j][k] = estado->tablero[j][k];
      //COPIAMOS LOS PARAMETROS DEL ANTIGUO TABLERO
      nuevoEstado->iVacio = estado->iVacio;
      nuevoEstado->jVacio = estado->jVacio;
      //AUMENTAMOS LA PROFUNDIDAD
      nuevoEstado->profundidad = estado->profundidad + 1;
      // CREAMOS UNA LISTA AUX PARA COPIAR LAS ACCIONES DEL ANTIGUO ESTADO AL ACTUAL
      List *listAux = estado->acciones;
      int *accionAux = list_first(listAux);
      // CODIGO PARA COPIAR LA LISTA DEL ANTIGUO ESTADO AL NUEVO ESTADO
      while(accionAux != NULL)
      {
        int *accionCopia = malloc(sizeof(int));
        *accionCopia = *accionAux;
        list_pushBack(nuevoEstado->acciones, accionCopia);
        accionAux = list_next(listAux);
      }
     // MOVEMOS LOS BLOQUES CORRESPONDIENTES AL MOVIMIENTO, CALCULAMOS LOS MOVIMIENTOS VALIDOS Y LE CALCULAMOS LA CLAVE
      moverBloque(nuevoEstado, i);
      calcularMovimientosValidos(nuevoEstado);
      nuevoEstado->clave = calcularClave(nuevoEstado);
      //METEMOS EL ESTADO ADYACENTE A LA LISTA
      list_pushBack(lista, nuevoEstado);
      
    }
  }
  //RETORNAMOS LA LISTA
  return lista;
}

//FUNCION QUE IMPRIME LAS ACCIONES DE UN ESTADO
void imprimirAcciones(List *acciones)
{
  int *accion = (int *)list_first(acciones);
  while(accion != NULL)
  {
    if(*accion == 0)
      printf("MOVER ARRIBA\n");
    else if(*accion == 1)
      printf("MOVER ABAJO\n");
    else if(*accion == 2)
      printf("MOVER IZQUIERDA\n");
    else if(*accion == 3)
      printf("MOVER DERECHA\n");
    accion = list_next(acciones);
  }
}

//FUNCION QUE REVISA SI UN ESTADO ES EL ESTADO FINAL
bool esEstadoFinal(tipoEstado *estado)
{
  if(estado->clave == 876543210)
    return true;
  return false;
}

//BUSQUEDA EN PROFUNDIDAD
bool DFS(tipoEstado *estado, int limite)
{
  //CREAMOS LA PILA
  Stack *pila = stack_create(pila);
  //METEMOS EL PRIMER ESTADO EN LA PILA
  stack_push(pila, estado);

  
  while(stack_top(pila) != NULL)
  {
    //SACAMOS UN ESTADO DE LA PILA
    tipoEstado *estadoActual = stack_pop(pila);
    //SI EL ESTADO ES EL FINAL IMPRIMIMOS Y SALIMOS DE LA FUNCION
    if(esEstadoFinal(estadoActual))
    {
      stack_clean(pila);
      free(pila);
      imprimirAcciones(estadoActual->acciones);
      printf("\nESTADO FINAL:\n");
      mostrarEstado(estadoActual);
      return true;
    }
    //SI EL ESTADO TIENE UNA PROFUNDIDAD MAYOR AL LIMITE PASAMOS AL SIGUIENTE NODO
    if(estadoActual->profundidad > limite)
    {
      continue;
    }
    //OBTENEMOS Y AGREGAMOS LOS NODOS ADYACENTES A LA PILA
    List *listaAdj = obtenerAdyacentes(estadoActual);
    tipoEstado *estadoAdj = list_first(listaAdj);
    while(estadoAdj != NULL)
    {
      stack_push(pila, estadoAdj);
      estadoAdj = list_next(listaAdj);
    }
    free(estadoAdj);
    list_clean(listaAdj);
    free(listaAdj);
  }
  stack_clean(pila);
  free(pila);
  return false;
}

//BUSQUEDA EN ANCHURA
void BFS(tipoEstado *estado)
{
  //CREAMOS LA COLA
  Queue *cola = queue_create(cola);
  //METEMOS EL PRIMER ESTADO EN LA COLA
  queue_insert(cola, estado);
  
  while(queue_front(cola) != NULL)
  {
    //SACAMOS UN ESTADO DE LA COLA
    tipoEstado *estadoActual = queue_remove(cola);
    //SI EL ESTADO ES EL FINAL IMPRIMIMOS Y SALIMOS DE LA FUNCION
    if(esEstadoFinal(estadoActual))
    {
      queue_clean(cola);
      free(cola);
      imprimirAcciones(estadoActual->acciones);
      printf("\nESTADO FINAL:\n");
      mostrarEstado(estadoActual);
      return;
    }

    //OBTENEMOS Y AGREGAMOS LOS NODOS ADYACENTES A LA COLA
    List *listaAdj = obtenerAdyacentes(estadoActual);
    tipoEstado *estadoAdj = list_first(listaAdj);
    while(estadoAdj != NULL)
    {
      queue_insert(cola, estadoAdj);
      estadoAdj = list_next(listaAdj);
    }
    free(estadoAdj);
    list_clean(listaAdj);
    free(listaAdj);
  }
  
  queue_clean(cola);
  free(cola);
}

void mostrarMenu()
{
  printf("========================================\n");
  printf("       Escoge método de búsqueda\n");
  printf("========================================\n");
  printf("(1) Búsqueda en Profundidad\n");
  printf("(2) Buscar en Anchura\n");
  printf("(3) Salir\n");
  printf("Ingrese una opción: ");

}

int main(void)
{
  // INICIAR ESTADO //
  tipoEstado *estadoInicial = iniciarEstado();
  FILE *archivo = fopen("puzzle.txt", "r");
  for(int i = 0 ; i < 3 ; i++)
    for(int j = 0 ; j < 3 ; j++)
      fscanf(archivo, "%i", &estadoInicial->tablero[i][j]);
  fclose(archivo);
  calcularCasillaVacia(estadoInicial);
  calcularMovimientosValidos(estadoInicial);
  estadoInicial->clave = calcularClave(estadoInicial);
  // INICIAR ESTADO //

  // BUCLE //
  char opcion;
  while(1)
  {
    //LIMPIAR, IMPRIMIR EL MENU, PEDIRLE LA OPCION AL USUARIO Y MOSTRAR ESTADO INICIAL
    system("clear");
    mostrarMenu();
    fscanf(stdin, "%c", &opcion);
    while(getchar() != '\n');
    system("clear");
    printf("ESTADO INICIAL:\n");
    mostrarEstado(estadoInicial);

    //BUSQUEDA EN PROFUNDIDAD
    if(opcion == '1')
      {
        bool encontrar = false;
        int limite = 5;
        while(!encontrar)
        {
          encontrar = DFS(estadoInicial, limite);
          limite += 5;
        }
      }

      //BUSQUEDA EN ANCHURA
      else if(opcion == '2')
        BFS(estadoInicial);
        
      //SALIR DEL PROGRAMA
      else if(opcion == '3')
        break;


      //OPCION INVALIDA
      else
        system("clear");

    printf("PRESIONA UNA TECLA PARA CONTINUAR");
    while(getchar() != '\n');
  }
  // BUCLE //
  system("clear");
  printf("Hasta la proxima :D");
  list_clean(estadoInicial->acciones);
  free(estadoInicial->acciones);
  free(estadoInicial);
  return 0;
}
