/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Con la implimentación del TAD Cola se implemento
un programa que realiza la simulación del sistemaoperativo 
Que toma en consideración del tiempo de ejecución, el ID, actividad,

COMPILACIÓN: gcc -o posfija posfija.c TADPilaDin.o
			 gcc -o posfija posfija.c TADPilaEst.o
*/			 
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "presentacion.h"
#include "TADColaDin.h"

#define tiempoEspera 500

void hidecursor(void){ //Esta función oculta el cursor, ya que es moleto el que este parpadeando.
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
/*
elemento nuevoProceso(int id);
Descripción: En esta función lo que se realiza es el ingreso de los datos de cada uno de los procesos 
Recibe: int id (ID del proceso);
Devuelve: Elemento (que es el elemento con los datos necesarios de un proceso).
*/
elemento nuevoProceso(int id){
	elemento procesoAux;
	char *temp, num[4];
	int tam;

	fflush(stdin); //Se imprime en pantalla el proceso que se esta ejecutando.
	printf("-----------Proceso %d ---------\n", id);

	temp = procesoAux.processName;
	tam = 45;
	printf("Introduce el nombre del proceso %d: ", id); //Usuario ingresa el nombre del proceso que quiere realizar.
	getline(&temp, &tam, stdin); //Se guarda el nombre del proceso en temp en la parte del elemento procesoAux en la parte de processName.
	fflush(stdin);

	temp = procesoAux.processActivity;
	tam = 200;
	printf("Introduce la descripcion del proceso: "); //Usuario ingresa la descripción del proceso
	getline(&temp, &tam, stdin); //Se guarda la descripcion del proceso en temp en la parte del elemento procesoAux en la parte de processActivity
	fflush(stdin);

	itoa(id, num, 10); //itoa es pasar un numero entero a una cadena de caracteres segun una base (en este caso es 10)
	strcpy(procesoAux.processID, num); //copia a num en procesoAux.ProcessID
	printf("Introduce el tiempo que necesita el proceso: "); //El usurio ingresa el tiempo que desea que tarde en ejecutarse el proceso que ingreso.
	scanf("%d", &procesoAux.processTime); //Guarda el tiempo el procesoAux.processTime

	printf("\n");

	return procesoAux; //Retorna el proceso ingresado por el usario
}
/*
void enEjecucion(elemento Ejec);
Descripción: En esta función lo que se realiza es la impresion del proceso que se esta ejecutando actualmente
Recibe: elemento Ejec (elemento ejecutado en el que se invoca a la función);
Devuelve: void.
*/
void enEjecucion(elemento Ejec){ 
	int i;
	MoverCursor(0,0); //SE imprimira en la parte superior de la pantalla
	printf("Ejecutando el siguiente proceso:\n");
	MoverCursor(0,1); //Se imprimira el proceso que se esta ejecutando
	for(i=0; i<90; i++)
		printf("-"); //Se imprime una linea de separación
	MoverCursor(0, 2); //en estas coordenada se escribe Nombre del proceso
	printf("Nombre del Proceso");
	MoverCursor(30,2); //en estas coordenadas se escribe Actividad
	printf("Actividad");
	MoverCursor(70,2); //en estas coordenadas se escribe ID
	printf("ID");
	MoverCursor(80,2); //en estas coordenadas se escribe tiempo
	printf("Tiempo");

	MoverCursor(0,3); //en estas coordenadas se comienza una linea de separación
	for(i=0; i<90; i++)
		printf("-"); //Linea de separación

	MoverCursor(0,4); //En esta coordenada se escribe | Nombre del proceso
	printf("| %s", Ejec.processName);
	MoverCursor(30, 4); //En esta coordenada se escribe | Actividad del proceso
	printf("| %s", Ejec.processActivity);
	MoverCursor(70, 4); //En esta coordenada se escribe | ID del proceso
	printf("| %s", Ejec.processID);
	MoverCursor(80, 4); //En esta coordenada se escribe | Tiempo del proceso
	printf("| %d  |", Ejec.processTime);
	
	MoverCursor(0,5); //Se escribe una linea de separación
	for(i=0; i<90; i++)
		printf("-");
}
/*
void imprimirEspera(cola *esperandoEjecucion);
Descripción: En esta función lo que se realiza es la impresion del los procesos que estan en la cola de espera
Recibe: cola *esperandoEjecucion (Cola en la cual se encuentran los procesos en espera de ejecución);
Devuelve: void.
*/
void imprimirEspera(cola *esperandoEjecucion){
	//Declaracion de variables
	elemento procesoAux;
	int a,b,c,d,l,i,k,j; //i,k,j son contadores que utilizares en algunos ciclos.
	//Son las posiciones en donde se va a mover el cursor para poder imprimir.
	a = 0;
	b = 30;
	c = 70;
	d = 80;
	l = 9;

	MoverCursor(0,l-2);
	for(i=0; i<92; i++)//Aqui se imprime una linea de separación
		printf("-");
	//Se imprime cada uno de los encabezados para identificar los procesos en espera correctamente
	MoverCursor(a,l);
	printf("Procesos esperando a la Ejecucion:\n");
	MoverCursor(a, l+2);
	printf("Nombre del Proceso");
	MoverCursor(b,l+2);
	printf("Actividad");
	MoverCursor(c,l+2);
	printf("ID");
	MoverCursor(d,l+2);
	printf("Tiempo");
	//En este ciclo se van a imprimir todos los procesos, por eso en la condición se incluye en tamaño de la cola.
	for(i=0, k=0; i<Size(esperandoEjecucion); i++, k++){
		procesoAux = Element(esperandoEjecucion, i+1); 

		if(i==0) //Si i==0 se mandara llamar la función enEjecución la cual imprime en pantalla los datos del proceso que se esta ejecutando actualmente
			// lo cual ocurrira siempre al inicio del ciclo
			enEjecucion(procesoAux); 
		else{ //sino se imprimiran los demas procesos en la cola 
			MoverCursor(a, k*2+2+l);
			printf("%s", procesoAux.processName); //Se imprime el proceso en la cola
			MoverCursor(b, k*2+2+l);
			for(j=0; j<strlen(procesoAux.processActivity); j++){
				if(j%40 != 39){
					printf("%c", procesoAux.processActivity[j]); //Se imprime la actividad del proceso en la cola cuidando que no se encime el enunciado
				}
				else{
					printf("-\n");
					k++;
					MoverCursor(b, k+2+l);
				}
			}
			MoverCursor(c, k*2+2+l);
			printf("%s", procesoAux.processID); //Se escribe el ID del proceso en la cola
			MoverCursor(d, k*2+2+l);
			printf("%d", procesoAux.processTime); //Se escribe el tiempo del proceso en la cola
		}
	}
}
/*
void imprimirFinalizados(cola *Finalizados);
Descripción: En esta función lo que se realiza es la impresion del los procesos que estan en la cola de finalizados
Recibe: cola *Finalizados (Cola en la cual se encuentran los procesos finalizados);
Devuelve: void.
*/
void imprimirFinalizados(cola *Finalizados){
	elemento procesoAux;
	int k,i;
	int a = 100;
	int b = 130;
	int c = 150;

	for(k=0; k<30; k++){ //escribe una linea de separación
		MoverCursor(a-8, k);
		printf("|");
	}

	MoverCursor(a,0);//Se escribe Procesos finalizados en las coordenadas dadas
	printf("Procesos Finalizados:");
	MoverCursor(b,0);//Se escribe ID en las coordenadas dadas
	printf("ID");
	MoverCursor(c,0);//Se escribe tiempo total en las coordenadas dadas
	printf("Tiempo total");

	for(i=0; i<Size(Finalizados); i++){
		procesoAux = Element(Finalizados, i+1); 
		MoverCursor(a, i*2+2);
		printf("%s", procesoAux.processName);
		MoverCursor(b, i*2+2);
		printf("%s", procesoAux.processID);
		MoverCursor(c, i*2+2);
		printf("%d", procesoAux.processTimeReal);
	}
}
//PROGRAMA PRINCIPAL
int main(){
	//Declaración de variabñes
	elemento procesoAux;
	unsigned int tiempo=0, cantProcesos; //Tiempo y cantidad de procesos que el usuario elegira.
	int i;
	hidecursor(); //Se llama a la función para ocultar cursor.

	cola esperandoEjecucion; //Se declara la cola en la cual estaran los procesos que estan esperando a ser ejecutados.
	// cola Ejecutando; //?? Dudo de que sea correcto poner una cola para ejecutados, puede ser constante
	cola Finalizados; //Declaración de la cola en la cual se guardaran los elementos que ya han finalizado
	//Inicialización de las colas.
	Initialize(&esperandoEjecucion);
	Initialize(&Finalizados);

	printf("Ingresa cuantos procesos quieres ejecutar : ");
	scanf("%d", &cantProcesos); //Usuario ingresa cuantos procesos quiere ejecutar y se guarda en la variable cantProcesos.

	for(i=0; i<cantProcesos; i++) //Se hace un queue de la pila donde estaran los procesos que estan esperando a hacer ejecutados, donde
		//lla a la función nuevoProceso. 
		Queue(&esperandoEjecucion, nuevoProceso(i+1)); //nuevoProceso envia el ID que es el numero de proceso más 1, en el cual se ingresan
	// todos los datos del proceso que se quiere ingresar y lo retorna con toda la informacion necesaria.

	system("cls");

	while(!Empty(&esperandoEjecucion)){ //Ciclo en el cual mientras cola esperando ejecución no este vacia
		// la variable elemento procesoAux guarda al elemento que sale de la cola esperandoEjecución.
		procesoAux = Dequeue(&esperandoEjecucion);
		procesoAux.processTime--; //Disminuye el tiempo del proceso que salio de la cola esperandoEjecución.

		if(procesoAux.processTime == 0){ //Si el tiempo del procesoAux ya es cero.
			procesoAux.processTimeReal = tiempo + 1; //el tiempo real de ejecución es más 1, ya que se comienza a contar desde cero.
			Queue(&Finalizados, procesoAux); //El procesoAux se agrega a la cola de finalizados, ya que su tiempo de ejecución ya finalizo.
		}
		else{
			Queue(&esperandoEjecucion, procesoAux); //si el tiempo es diferente de cero, entonces el procesoAux vuelve a la cola 
			//de esperando ejecucion haciendo un queue.
		}
		
		system("cls");

		imprimirEspera(&esperandoEjecucion); //Funcion que imprime la cola de los procesos que estan esperando a ser ejecutados
		imprimirFinalizados(&Finalizados); //Función que imprime la cola de los procesos que ya terminaron su proceso de ejecución.

		Sleep(tiempoEspera);
		tiempo++; //Incremento del tiempo
		
	}

	MoverCursor(0,30);
	//printf("Ia akave we xdd\n");


	return 0;

}
