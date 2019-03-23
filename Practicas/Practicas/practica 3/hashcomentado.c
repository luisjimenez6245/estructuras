/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Con la implimentación del TAD Lista se implemento
un programa el cual tiene la función de diccionario.
Que realiza las operaciones de cargar un archivo de definciones, agregar una palabra y su definición, buscar una palabra y ver su definición,
modificar una definición, eliminar una palabra.
COMPILACIÓN: gcc -o hash hash.c TADListaDL.o
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <windows.h>
#include <wchar.h>
// #include <locale.h>
#include "TADListaDL.h"

#define aureo 1.6680889885 //Declaración global de el número aureo
#define tam 500				//Tamaño de la lista
/*
int corregirChar(int c)
Descripción: En esta función lo que se realiza es cambiar los valores ascii de caracteres latinos como la ñ,ü, entre otros.
Recibe: int c(valor ascii del caracter)
Devuelve: int(que es el valor correcto de la letra)
*/
int corregirChar(int c){
	switch(c){
		case 177: 
			return 164; //ñ
		break;

		case 145:
			return 165; //Ñ
		break;

		case 193:
			return 181; //Á
		break;

		case 201:
			return 144; //É
		break;

		case 205:
			return 214; //Í
		break;

		case 211:
			return 224; //Ó
		break;

		case 218:
			return 233; //Ú
		break;

		case 225:
			return 160; //á
		break;

		case 233:
			return 130; //é
		break;

		case 237:
			return 161; //í
		break;

		case 243:
			return 162; //ó
		break;

		case 250:
			return 163; //ú
		break;

		case 241:
			return 164; //ñ
		break;

		case 209:
			return 165; //Ñ
		break;

		case 252:
			return 129; //ü
		break;

		default:
			return c;
		break;
	}
}
/*
int hashAlt(char cad[])
Descripción: En esta función lo que se realiza es la dispersión de las palabras del diccionario dentro de la lista
Recibe: char cad[](la palabra de la que se desa sacar un valor)
Devuelve: int(que es el valor donde se acomodara en la lista)
*/
int hashAlt(char cad[]){
	int mul=1, i, tamCad = sizeof(&cad), dif=0, dif2=0;
	double res;
	float temp;

	for(i=0; i<tamCad; i++){
		mul = mul * cad[i];
		if(i%2==0)
			dif = dif + cad[i];
		if(i%3 == 0)
			dif2 = dif2 +1;
	}
	mul = mul*aureo;
	mul = mul/dif+tamCad;
	mul = mul%250;

	res = exp(mul)/dif2+dif;
	while(res>3500){
		res = res/exp(aureo);
		// res = res + dif2*exp(dif);
	}

	temp = (float)res+tamCad*aureo;
	mul=0;
	mul = ((int)temp)%tam;

	return mul;
}
/*
int hash(char cad[])
Descripción: En esta función lo que se realiza es la dispersión de las palabras del diccionario dentro de la lista
Recibe: char cad[](la palabra de la que se desa sacar un valor)
Devuelve: int(que es el valor donde se acomodara en la lista)
*/
int hash(char cad[]){
	int i,s=0,p=cad[0], o; //Declaración de variables
	float mul;
	//ciclo for que recorre la cadena
	for(i=0; i<strlen(cad); i=i+1){
		s = s + (int)cad[i]; //Suma de los valores ascii de la cadena
	}

	mul= (s*aureo)*p; //Multiplicación de la suma por el número aureo por el valor ascii de la primera letra de la cadena
	mul= (int)mul%tam; //Modulo del la multiplicacion y el tamaño de la lista

	o = (int)mul;

	if(o<0) //Si el valor es negativo se multiplica por -1 para que se vuelva positivo
		o = -o;

	// printf("%d\n", o);
	return o;
}
/*
int menu()
Descripción: En esta función se imprime el menu de opciones del diccionario
Recibe: ()
Devuelve: int(opcion que el usuario eligio)
*/
int menu(){
	int op; //Declaracion de las variables
	system("cls");
	printf(" 1.- Cargar un archivo de definiciones\n 2.- Agregar una palabra y su definicion\n 3.- Buscar una palabra y ver su definicion\n 4.- Modificar una definicion\n 5.- Eliminar una palabra\n 6.- Salir\n");
	//Se imprime el menu
	printf("\nOpcion: "); //Usuario ingresa opcion 
	scanf("%d", &op); //Se la opción se guarda en la variable op

	return op;
}
/*
void agregarPalabra(lista diccionario[], char palabra[], char significado[])
Descripción: En esta función se agrega una palabra al diccionario junto con su significado.
Recibe: lista diccionario[](diccionario), char palabra[](palabra que se va a agregar), char significado[](significado de la palabra)
Devuelve: void
*/
void agregarPalabra(lista diccionario[], char palabra[], char significado[]){
	definicion nuevaDef; //Se crea una definicion
	strcpy(&nuevaDef.palabra[0], &palabra[0]); //Se copia la palabra a la nueva definicion es su parte de palabra
	strcpy(&nuevaDef.significado[0], &significado[0]); //Se copia el significado a la nueva definicion en su parte de significado

	// printf("Lista: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	// printf("Direccion: %p\n", &listaTemp);

	Add(&diccionario[hash(palabra)], nuevaDef); //Se agrega la nueva definicion a la lista del diccionario usando la función hash
	printf("-------------------------------\n");
	fflush(stdout);
	fflush(stdin);
	// fflush(stdio);
	// fflush(string);
	printf("\tNueva Palabra:%s\n\tNueva Definicion:%s\n\n", palabra, significado); //Se imprime lo que se agrego
	return;
}
/*
void leerDiccionario(lista diccionario[])
Descripción: En esta función se lee el documento.txt en el cual se encuentran diversas definiciones y se guarda en el diccionario.
Recibe: lista diccionario[]
Devuelve: void
*/
void leerDiccionario(lista diccionario[]){
	FILE *pArch;
	char nomArchivo[30], palabra[25], palabraAlt[25], definicion[251], estado='p'; //Declaracion de las variables
	int car,i=0;
	printf("Ingresa el nombre del diccionario \n\tEjemplo: diccionario.txt \nDiccionario: "); //Usuario ingresa el documento .txt
	scanf("%s", &nomArchivo); //Se guarda en la variable nomArchivo ya declarado anteriormente 

	pArch = fopen(nomArchivo, "r"); //Se va a leer el archivo
	palabraAlt[0] = '#';

	while((car = getc(pArch)) != EOF){ //Este while lo que hace es recorrer todo el archivo ya que termina hasta que sea igual a End of file
		//lee caracter por caracter
		car = corregirChar(car); //se manda a llamar a la funcion corregir char

		// printf("Val: %d\n", car);

		if(car != 195){
			if (car=='/' && estado == 'p'){ //Si encuentra '/' y el estado es p(palabra)
				estado='q'; //Estado cambia a q que es otra palabra
				palabra[i] = '\0';
				i=0;
				continue;
			}
			if (car==':'){ //Si encuentra ':' 
				if(estado == 'p') //y el estado es palabra
					palabra[i] = '\0';//Se agrega terminador de cadena
				if(estado == 'q') //y el estado es q
					palabraAlt[i] = '\0';//Se agrega terminador de cadena

				estado='s'; //Cambia de estado a significado
				i=0;
				continue;
			}
			if (car=='\n'){ //si encuentra un salto de linea
				definicion[i]=car; //Se agrega el punto
				definicion[i+1] = '\0';//Se agrega el terminador de cadena

				agregarPalabra(diccionario, palabra, definicion); //Se llama a la funcion agregar palabra
				//Se limpia todo y empieza todo desde el principio
				if(palabraAlt[0] != '#'){
					agregarPalabra(diccionario, palabraAlt, definicion);
					palabraAlt[0] = '#';
				}
				fflush(stdout);
				estado = 'p';

				palabra[0] = '#';

				// printf("Palabra Limpia: %s\n", palabra);
				// printf("Palabra Limpia: %s\n", palabraAlt);
				// printf("Palabra Limpia: %s\n", definicion);

				i=0;

				continue;
			}
			if(estado == 'p'){ //Si el estado es p se va guardado en 'palabra' ya declarada anteriormente
				palabra[i]=car;
				i++;
			}
			if(estado == 'q'){ //Si el estado es q se va guardando en 'palabraAlt' ya declarada anteriormente
				palabraAlt[i]=car;
				i++;
			}
			if(estado == 's'){ //Si el estafo es s se va guardando en 'definicion' ya declarada anteriormente
				definicion[i]=car;
				i++;
			}
		}
		// printf("%d ", i);
	}
}
/*
definicion buscarPalabra(lista diccionario[], char palabra[])
Descripción: En esta función busca una palabra dentro del diccionario
Recibe: lista diccionario[](diccionario), char palabra[](palabra que se desea buscar)
Devuelve: definicion (la palabra que encontro)
*/
definicion buscarPalabra(lista diccionario[], char palabra[]){
	definicion candidata; //Declracion de una definicion
	strcpy(candidata.palabra, palabra); //se copia la palabra a la definicion candidata en su parte de palabra
	// printf("Clave de lista a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata); //se llama a la funcion Search de la lista y es igual a la posicion 'lugar'
	// printf("Lo que encontre es: %s %s\n", lugar->e.palabra, lugar->e.significado);

	char x[3];
	x[0] = '-';
	x[1] = '-';
	x[2] = '-';
	
	if(lugar != NULL){
		printf("Palabra encontrada en %d pasos\n", lugar->saltos + 1); //Cuantos saltos se dieron para encontrar a la palabra
		return lugar->e;
	}
	strcpy(&candidata.significado[0], &x[0]);
	return candidata; //Regresa la definicion canditata
}
/*
void modificarPalabra(lista diccionario[], char palabra[])
Descripción: En esta función modifica una palabra que esta dentro del diccionario
Recibe: lista diccionario[], char palabra[]
Devuelve: void
*/
void modificarPalabra(lista diccionario[], char palabra[]){
	definicion candidata; //Declaracion de una definicion 
	strcpy(candidata.palabra, palabra); //Se copia la palabra a la definicion candidata a su parte de palabra
	// printf("Clave de lista a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata); //Se llama a la funcion Search de la lista es es igual a la posicion lugar
	if(ValidatePosition(&diccionario[hash(palabra)], lugar) == TRUE){	//Si la posicion existe entonces entra a la condicion
		char def[251]; //Se crea un char def
		definicion aux = buscarPalabra(diccionario, palabra); //Se crea una defincion aux que es igual a la palabra que se busca
		fflush(stdin);
		printf("\nIngrese la nueva definicion: "); //solicitar nueva definicion
		scanf("%251[^\n]", def); //Se guarda en la variable def
		strcpy(aux.significado, def); //def se copia a la definicion aux en su parte de sifnificado
		Replace(&diccionario[hash(palabra)],lugar, aux); //Se llama a la funcion replace y dando el diccionario con el hash de la palabra
		//el lugar solicitado antes y aux.
		printf("\n\n----------------------------------------\n\n");
		printf("Palabra modificada con exito\n\n");
		printf("----------------------------------------\n\n");
	}else{
		printf("\nError: La palabra que quieres modificar no existe en el diccionario.\n");
	}
	return;
}
/*
void eliminarPalabra(lista diccionario[], char palabra[]
Descripción: En esta función elimina una palabra que esta dentro del diccionario.
Recibe: lista diccionario[], char palabra[]
Devuelve: void
*/
void eliminarPalabra(lista diccionario[], char palabra[]){
	definicion candidata; //Se crea una definicion candidata
	strcpy(candidata.palabra, palabra); //Se copia la palabra a la definicion candidata en su parte de palabra
	// printf("Clave de lista a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata); //Se busca la posicion de la palabra candidata
	if(ValidatePosition(&diccionario[hash(palabra)], lugar) == TRUE){
		Remove(&diccionario[hash(palabra)], lugar); //Se llama a la funcion Remove de la lista
		printf("\n\n----------------------------------------\n\n");
		printf("Palabra eliminada con exito\n\n");
		printf("----------------------------------------\n\n");
	}else{
		printf("\nError: La palabra que quieres eliminar no existe en el diccionario\n");
	}
	return;
}
//Funcion princial
int main(){
	int pos,x=0, tamPal = 51, tamDef = 251, cubeta[100], moda=0, prom=0, vacias=0, max=0; //Declaracion de las variables
	char palabra[tamPal], def[tamDef];  //Donde se guardaran palabras y definiciones nuevas.
	int res[tam],i,j;
	definicion defAct;
	posicion nue;

	for(i=0;i<tam; i++){
		res[i] = 0;
	}

	lista diccionario[tam]; //Se crea un arreglo listas de tamaño de tam (global)
	for(i=0; i<tam; i++){ //initialize de las listas
		Initialize(&diccionario[i]);
	}

	while(1){ //Menu
		switch(menu()){
			case 1: //En caso de que sea la opcion 1 Cargar un archivo de definiciones
				leerDiccionario(diccionario); //SE llama a la funcion leerDiccionario
				printf("\n\n----------------------------------------\n\n");
				printf("Diccionario agregado con exito\n\n");
				printf("----------------------------------------\n\n");
				system("pause");
			break;

			case 2: //En caso de que sea la opcion 2 Agregar una palabra y su definicion
				printf("\n\n----------------------------------------\n\n");
				printf("Agregar palabra al diccionario\n\n");
				printf("----------------------------------------\n\n");
				fflush(stdin);
				printf("\nIngresa la palabra: "); //Palabra que se quiere agrefar
				scanf("%51[^\n]", palabra); //Se guarda en palabra ya declarada anteriormente
				for(i=0; i<strlen(palabra); i++) //Se recorre la palabra y se corrigen caracteres 
					palabra[i] = corregirChar(palabra[i]);
				fflush(stdin);
				printf("\nIngresa la definicion: "); //Deficion de la palabra agregada
				scanf("%251[^\n]", def); //Se guarda en def ya declarada anteriormente
				for(i=0; i<strlen(def); i++) //Se recorre la definicion y se corrigen los caracteres
					def[i] = corregirChar(def[i]);
				agregarPalabra(diccionario, palabra, def); //SE agrega la palabra al diccionario
				printf("\n\n----------------------------------------\n\n");
				printf("Palabra agregada con exito\n\n");
				printf("----------------------------------------\n\n");
				system("pause");
			break;

			case 3: //En caso de que sea la opcion 3 Buscar una palabra y ver su definicion 
				printf("\n\n----------------------------------------\n\n");
				printf("BUSQUEDA\n\n");
				printf("----------------------------------------\n\n");
				fflush(stdin);
				printf("\nIngresa la palabra a buscar: "); //Se solicita la palabra deseada
				scanf("%51[^\n]", palabra); //se guarda en palabra que ya esta declarada anteriormente
				for(i=0; i<strlen(palabra); i++) //Se corrige la palabra
					palabra[i] = corregirChar(palabra[i]);
				defAct = buscarPalabra(diccionario, palabra);//Definicion definicion de la palabra que se quiere buscar
				if(defAct.significado[0] == '-' && defAct.significado[1] == '-') //Si tienen guion
					printf("\n----Palabra no encontrada----\n");
				else{
					printf("\n\t%s: %s\n\n", defAct.palabra, defAct.significado); //Si no tienen guion se imprime la definicion
				}

				system("pause");
			break;

			case 4: //En caso de que sea la opcion 4 Modificar una definicion
				fflush(stdin);
				printf("\nIngresa la palabra a modificar: "); //SE ingresa la palabra
				scanf("%51[^\n]", palabra);
				modificarPalabra(diccionario, palabra); //Se llama a la funcion modificar
				system("pause");
			break;

			case 5: //En caso de que sea la opcion 5 Eliminar una palabra
				fflush(stdin);
				printf("\nIngresa la palabra a eliminar: ");
				scanf("%51[^\n]", palabra);
				eliminarPalabra(diccionario, palabra); // se llama a la Funcion eliminar palabra
				system("pause");
			break;

			case 7://Se muentran todas las listas y cuantos elementos tienen
				for(i=0; i<tam; i++){
					printf("Lista %d: %d elementos\n", i, Size(&diccionario[i]));
					for(j=0; j<Size(&diccionario[i]); j++){
						if(j==0){
							nue = First(&diccionario[i]);
						}
						else{
							nue = Following(&diccionario[i], nue);
						}
						// printf("\tElemento: %s %s\n", nue->e.palabra, nue->e.significado);
					}
				}
				system("pause");
			break;

			case 6: //Salir del programa
				exit(0);
			break;

			case 8://muetra los elementos de la lista
				for(i=0; i<tam; i++){
					printf("Lista %d: %d elementos\n", i, Size(&diccionario[i]));
					for(j=0; j<Size(&diccionario[i]); j++){
						if(j==0){
							nue = First(&diccionario[i]);
						}
						else{
							nue = Following(&diccionario[i], nue);
						}
						printf("\tElemento: %s %s\n", nue->e.palabra, nue->e.significado);
					}
				}
				system("pause");

			break;

			case 9: //muestra las estadisitcas y los datos del diccionario
				moda =0; prom = 0; vacias = 0; max=0;
				for(i=0; i<100; i++)
					cubeta[i] = 0; //Arreglo de enteros declarado ateriormente

				printf("\n\n----------------------------------------\n\n");
				printf("ESTADISTICAS DE DICCIONARIO HASH ABIERTO\n\n");
				printf("----------------------------------------\n\n");

				printf("Tamaño de la tabla: %d\n", tam);

				for(i=0; i<tam; i++){
					// printf("Lista %d: %d elementos\n", i, Size(&diccionario[i]));
					cubeta[Size(&diccionario[i])]++;
					if(Size(&diccionario[i]) == 0){ //Listas vacias
						vacias++; 
					}
					if(Size(&diccionario[i]) > max){ //orden maximo de busqueda (tamaño de la lista)
						max = Size(&diccionario[i]);
					}
				}
				for(i=2; i<100; i++){ //Colisiones
					// printf("%d elementos: %d\n", i, cubeta[i]);
					if(cubeta[i] >= moda){
						moda = cubeta[i];
						prom = i;
					}
				}

				printf("El numero promedio de colisiones es de: %d\n", prom);
				printf("El numero de listas vacias es %d\n", vacias);
				printf("El orden maximo de busqueda es: %d\n", max);
				printf("El numero maximo de pasos para encontrar un elemento es: %d\n", max+1);

				system("pause");
			break;

			case 100:
				for(i=0; i<tam; i++){
					Initialize(&diccionario[i]);
				}
			break;

			default:
				printf("Opcion no reconocida\n");
			break;
		}
	}

	return 0;
}

