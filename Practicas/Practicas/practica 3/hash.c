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

#define aureo 1.6680889885
#define tam 500

int corregirChar(int c){
	switch(c){
		case 177:
			return 164;
		break;

		case 145:
			return 165;
		break;

		case 193:
			return 181;
		break;

		case 201:
			return 144;
		break;

		case 205:
			return 214;
		break;

		case 211:
			return 224;
		break;

		case 218:
			return 233;
		break;

		case 225:
			return 160;
		break;

		case 233:
			return 130;
		break;

		case 237:
			return 161;
		break;

		case 243:
			return 162;
		break;

		case 250:
			return 163;
		break;

		case 241:
			return 164;
		break;

		case 209:
			return 165;
		break;

		case 252:
			return 129;
		break;

		default:
			return c;
		break;
	}
}

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

int hash(char cad[]){
	int i,s=0,p=cad[0], o;
	float mul;
	
	for(i=0; i<strlen(cad); i=i+1){
		s = s + (int)cad[i];
	}

	mul= (s*aureo)*p;
	mul= (int)mul%tam;

	o = (int)mul;

	if(o<0)
		o = -o;

	// printf("%d\n", o);
	return o;
}

int menu(){
	int op;
	system("cls");
	printf(" 1.- Cargar un archivo de definiciones\n 2.- Agregar una palabra y su definicion\n 3.- Buscar una palabra y ver su definicion\n 4.- Modificar una definicion\n 5.- Eliminar una palabra\n 6.- Salir\n");

	printf("\nOpcion: ");
	scanf("%d", &op);

	return op;
}

void agregarPalabra(lista diccionario[], char palabra[], char significado[]){
	definicion nuevaDef;

	strcpy(&nuevaDef.palabra[0], &palabra[0]);
	strcpy(&nuevaDef.significado[0], &significado[0]);

	// printf("Lista: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	// printf("Direccion: %p\n", &listaTemp);

	Add(&diccionario[hash(palabra)], nuevaDef);
	printf("-------------------------------\n");
	fflush(stdout);
	fflush(stdin);
	// fflush(stdio);
	// fflush(string);
	printf("\tNueva Palabra:%s\n\tNueva Definicion:%s\n\n", palabra, significado);
	return;
}

void leerDiccionario(lista diccionario[]){
	FILE *pArch;
	char nomArchivo[30], palabra[25], palabraAlt[25], definicion[251], estado='p';
	int car,i=0;
	printf("Ingresa el nombre del diccionario \n\tEjemplo: diccionario.txt \nDiccionario: ");
	scanf("%s", &nomArchivo);

	pArch = fopen(nomArchivo, "r");
	palabraAlt[0] = '#';

	while((car = getc(pArch)) != EOF){
		car = corregirChar(car);

		// printf("Val: %d\n", car);

		if(car != 195){
			if (car=='/' && estado == 'p'){
				estado='q';
				palabra[i] = '\0';
				i=0;
				continue;
			}
			if (car==':'){
				if(estado == 'p')
					palabra[i] = '\0';
				if(estado == 'q')
					palabraAlt[i] = '\0';

				estado='s';
				i=0;
				continue;
			}
			if (car=='\n'){
				definicion[i]=car;
				definicion[i+1] = '\0';

				agregarPalabra(diccionario, palabra, definicion);

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
			if(estado == 'p'){
				palabra[i]=car;
				i++;
			}
			if(estado == 'q'){
				palabraAlt[i]=car;
				i++;
			}
			if(estado == 's'){
				definicion[i]=car;
				i++;
			}
		}
		// printf("%d ", i);
	}
}

definicion buscarPalabra(lista diccionario[], char palabra[]){
	definicion candidata;
	strcpy(candidata.palabra, palabra);
	// printf("Clave de lista a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata);
	// printf("Lo que encontre es: %s %s\n", lugar->e.palabra, lugar->e.significado);

	char x[3];
	x[0] = '-';
	x[1] = '-';
	x[2] = '-';
	
	if(lugar != NULL){
		printf("Palabra encontrada en %d pasos\n", lugar->saltos + 1);
		return lugar->e;
	}
	strcpy(&candidata.significado[0], &x[0]);
	return candidata;
}

void modificarPalabra(lista diccionario[], char palabra[]){
	definicion candidata;
	strcpy(candidata.palabra, palabra);
	// printf("Clave de lista a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata);
	if(ValidatePosition(&diccionario[hash(palabra)], lugar) == TRUE){	
		char def[251];
		definicion aux = buscarPalabra(diccionario, palabra);
		fflush(stdin);
		printf("\nIngrese la nueva definicion: ");
		scanf("%251[^\n]", def);
		strcpy(aux.significado, def);
		Replace(&diccionario[hash(palabra)],lugar, aux);
		printf("\n\n----------------------------------------\n\n");
		printf("Palabra modificada con exito\n\n");
		printf("----------------------------------------\n\n");
	}else{
		printf("\nError: La palabra que quieres modificar no existe en el diccionario.\n");
	}
	return;
}

void eliminarPalabra(lista diccionario[], char palabra[]){
	definicion candidata;
	strcpy(candidata.palabra, palabra);
	// printf("Clave de lista a buscar: %d, Tam: %d\n", hash(palabra), strlen(palabra));
	posicion lugar = Search(&diccionario[hash(palabra)], candidata);
	if(ValidatePosition(&diccionario[hash(palabra)], lugar) == TRUE){
		Remove(&diccionario[hash(palabra)], lugar);
		printf("\n\n----------------------------------------\n\n");
		printf("Palabra eliminada con exito\n\n");
		printf("----------------------------------------\n\n");
	}else{
		printf("\nError: La palabra que quieres eliminar no existe en el diccionario\n");
	}
	return;
}

int main(){
	int pos,x=0, tamPal = 51, tamDef = 251, cubeta[100], moda=0, prom=0, vacias=0, max=0;
	char palabra[tamPal], def[tamDef];
	int res[tam],i,j;
	definicion defAct;
	posicion nue;

	for(i=0;i<tam; i++){
		res[i] = 0;
	}

	lista diccionario[tam];
	for(i=0; i<tam; i++){
		Initialize(&diccionario[i]);
	}

	while(1){
		switch(menu()){
			case 1:
				leerDiccionario(diccionario);
				printf("\n\n----------------------------------------\n\n");
				printf("Diccionario agregado con exito\n\n");
				printf("----------------------------------------\n\n");
				system("pause");
			break;

			case 2:
				printf("\n\n----------------------------------------\n\n");
				printf("Agregar palabra al diccionario\n\n");
				printf("----------------------------------------\n\n");
				fflush(stdin);
				printf("\nIngresa la palabra: ");
				scanf("%51[^\n]", palabra);
				for(i=0; i<strlen(palabra); i++)
					palabra[i] = corregirChar(palabra[i]);
				fflush(stdin);
				printf("\nIngresa la definicion: ");
				scanf("%251[^\n]", def);
				for(i=0; i<strlen(def); i++)
					def[i] = corregirChar(def[i]);
				agregarPalabra(diccionario, palabra, def);
				printf("\n\n----------------------------------------\n\n");
				printf("Palabra agregada con exito\n\n");
				printf("----------------------------------------\n\n");
				system("pause");
			break;

			case 3:
				printf("\n\n----------------------------------------\n\n");
				printf("BUSQUEDA\n\n");
				printf("----------------------------------------\n\n");
				fflush(stdin);
				printf("\nIngresa la palabra a buscar: ");
				scanf("%51[^\n]", palabra);
				for(i=0; i<strlen(palabra); i++)
					palabra[i] = corregirChar(palabra[i]);
				defAct = buscarPalabra(diccionario, palabra);
				if(defAct.significado[0] == '-' && defAct.significado[1] == '-')
					printf("\n----Palabra no encontrada----\n");
				else{
					printf("\n\t%s: %s\n\n", defAct.palabra, defAct.significado);
				}

				system("pause");
			break;

			case 4:
				fflush(stdin);
				printf("\nIngresa la palabra a modificar: ");
				scanf("%51[^\n]", palabra);
				modificarPalabra(diccionario, palabra);
				system("pause");
			break;

			case 5:
				fflush(stdin);
				printf("\nIngresa la palabra a eliminar: ");
				scanf("%51[^\n]", palabra);
				eliminarPalabra(diccionario, palabra);
				system("pause");
			break;

			case 7:
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

			case 6:
				exit(0);
			break;

			case 8:
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

			case 9:
				moda =0; prom = 0; vacias = 0; max=0;
				for(i=0; i<100; i++)
					cubeta[i] = 0;

				printf("\n\n----------------------------------------\n\n");
				printf("ESTADISTICAS DE DICCIONARIO HASH ABIERTO\n\n");
				printf("----------------------------------------\n\n");

				printf("Tamaño de la tabla: %d\n", tam);

				for(i=0; i<tam; i++){
					// printf("Lista %d: %d elementos\n", i, Size(&diccionario[i]));
					cubeta[Size(&diccionario[i])]++;
					if(Size(&diccionario[i]) == 0){
						vacias++;
					}
					if(Size(&diccionario[i]) > max){
						max = Size(&diccionario[i]);
					}
				}
				for(i=2; i<100; i++){
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

/*El programa deberá de ser capaz de cargar un archivo de
palabras y sus definiciones, así como permitir al usuario saber
las estadísticas de la tabla hash, orden máximo de
búsqueda, tamaño de la tabla, numero de celdas vacías,
número de pasos al consultar una palabra, modificarla o
eliminarla.

Al realizar cualquiera de las operaciones, se presentará una
estadística de colisiones, número de saltos para encontrar la
palabra o insertarla, resultado de la función de hash para
cada palabra.

El algoritmo de búsqueda de una palabra en una lista de la
tabla hash deberá ser descrito y justificado. (Documentar el
orden del algoritmo de búsqueda según la implementación
realizada).
*/