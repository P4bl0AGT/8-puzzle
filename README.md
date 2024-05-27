## Descripción del Programa
Este programa permite desde un estado inicial de un tablero del juego 8-puzzle, encontrar la solucion de este tablero utilizando dos mecanismos de busqueda (DFS y BFS).

## Como compilar y ejecutar
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/P4bl0AGT/8-puzzle`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar la aplicación.

# Funcionalidades

## Funcionando correctamente:
* (1) Búsqueda en Profundidad
* (2) Buscar en Anchura
* (3) Salir

## Problemas conocidos:
* Existen algunos puzzles que la solucion esta en una profundidad muy grande por ende el programa se cae al no tener mas memoria para almacenar los nodos. por ejemplo el tablero
|8 0 6 5 4 7 2 3 1|
y con la busqueda en BFS el programa se cae,

## A mejorar:
* Mejorar el manejo de memoria
* Crear una interfaz mas amigable con el usuario.
* Implementar el algoritmo para la busqueda "Buscar Mejor Primero"

# Ejemplo de uso

## Menú

* Al comenzar el programa se mostrará un menú en el cual aparecerán todas las opciones que se pueden seleccionar en este programa

````
========================================
       Escoga método de búsqueda
========================================
(1) Búsqueda en Profundidad
(2) Buscar en Anchura
(3) Salir
Ingrese una opción:
````

## Búsqueda en Produndidad

* Esta opcion va a buscar la solucion a tu tablero a traves de la busqueda en profundidad, para una vez encontrada la solucion entregar al usuario los movimientos que tuvo que hacer para llegar desde el estado inicial hasta el estado final del tablero.

````
ESTADO INICIAL:
0 2 8 
1 3 4 
6 5 7 

MOVER ABAJO
MOVER DERECHA
MOVER DERECHA
MOVER ARRIBA
MOVER IZQUIERDA
MOVER IZQUIERDA
MOVER ABAJO
MOVER DERECHA
MOVER ABAJO
MOVER DERECHA
MOVER ARRIBA
MOVER IZQUIERDA
MOVER IZQUIERDA
MOVER ARRIBA

ESTADO FINAL:
0 1 2 
3 4 5 
6 7 8 

PRESIONA UNA TECLA PARA CONTINUAR
````

## Búsqueda en Anchura

* Esta opcion va a buscar la solucion a tu tablero a traves de la busqueda en enchura, para una vez encontrada la solucion entregar al usuario los movimientos que tuvo que hacer para llegar desde el estado inicial hasta el estado final del tablero.

````
ESTADO INICIAL:
0 2 8 
1 3 4 
6 5 7 

MOVER ABAJO
MOVER DERECHA
MOVER DERECHA
MOVER ARRIBA
MOVER IZQUIERDA
MOVER ABAJO
MOVER ABAJO
MOVER DERECHA
MOVER ARRIBA
MOVER IZQUIERDA
MOVER ARRIBA
MOVER IZQUIERDA

ESTADO FINAL:
0 1 2 
3 4 5 
6 7 8 

PRESIONA UNA TECLA PARA CONTINUAR
````

## Ssalir

* Con esta opcion vamos a salir del programa.

````
Hasta la proxima :D 
````
