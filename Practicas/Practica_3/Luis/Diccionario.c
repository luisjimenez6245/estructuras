/*
	DICCIONARIO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "TADHashTable.h"

/*
	FUNCIÓN: caracterLatino(int c)
	RECIBE: int c (VALOR ASCII DE UN CARACTER)
	DEVUELVE: int 
	DESCRIPCIÓN: ESTA FUNCIÓN RECIBE EL VALOR ASCII DE UN CARACTER QUE MUESTRA UN SÍMBOLO EN LA CONSOLA Y LO CONVIERTE A SU CORRESPONDIENTE CARACTER
	OBSERVACIONES:
*/
int caracterLatino(int c){
	switch(c){
		case 177: return 164; //ñ
		break;
		case 145: return 165; //Ñ
		break;
		case 193: return 181; //Á
		break;
		case 201: return 144; //É
		break;
		case 205: return 214; //Í
		break;
		case 211: return 224; //Ó
		break;
		case 218: return 233; //Ú
		break;
		case 225: return 160; //á
		break;
		case 233: return 130; //é
		break;
		case 237: return 161; //í
		break;
		case 243: return 162; //ó
		break;
		case 250: return 163; //ú
		break;
		case 241: return 164; //ñ
		break;
		case 209: return 165; //Ñ
		break;
		case 252: return 129; //ü
		break;
		default: return c; //RETORNA EL MISMO CARACTER
		break;
	}
}

/*
	FUNCIÓN: cargarDiccionario(tablaHash *diccionario).
	RECIBE: int (DIRECCIÓN DE MEMORIA DE LA TABLA HASH A OPERAR).
	DEVUELVE: NADA.
	DESCRIPCIÓN: SE ENCARGA DE EXTRAER LOS CARACTERES CONTENIDOS EN UN ARCHIVO DE TEXTO, SEPARANDO LA PALABRA DE SU DEFINICIÓN. POSTERIORMENTE
		AGREGA ESTE PAR DE CADENAS A UN ELEMENTO Y ES AGREGADO A UNA LISTA DENTRO DE LA TABLA HASH INDICADA EN EL PARÁMETRO.
	OBSERVACIONES:
*/
void cargarDiccionario(tablaHash *diccionario){
	FILE *archivo;
	registro nuevaPalabra; 
	char rutaArchivo[100],palabra[100],palabraAlt[100],definicion[251],estado='p';
	/*	ES NECESARIOO CREAR LA VARIABLE palabraAlt PUESTO QUE ALGUNAS PALABRAS TIENEN "ALTERNATIVAS"
		MARCADAS POR EL SIMBOLO /, EL PROGRAMA DEBE RECONOCERLAS COMO PALABRAS DIFERENTES
		LA VARIABLE estado INDICA LA TRANSICIÓN DE PALABRA A DEFINICIÓN
	*/
	int charArchivo,i=0;
	printf("Ingresa la ruta del archivo:\n>");
	scanf("%s", &rutaArchivo);
	archivo = fopen(rutaArchivo,"r");
	palabraAlt[0] = '#';
	while((charArchivo = getc(archivo)) != EOF){
		charArchivo = caracterLatino(charArchivo);
		if(charArchivo != 195){
			if (charArchivo=='/' && estado == 'p'){//ESTA PALABRA TIENE UNA VERSIÓN ALTERNATIVA
				estado='q';
				palabra[i] = '\0';
				i=0;
				continue;
			}
			if (charArchivo==':'){//COMIENZA LA DEFINICIÓN
				if(estado == 'p')//SE TRATA DE UNA PALABRA SIN ALTERNATIVAS
					palabra[i] = '\0';
				if(estado == 'q')//SE TRATA DE LA ALTERNATIVA DE ALGUNA PALABRA
					palabraAlt[i] = '\0';
				estado='s';
				i=0;
				continue;
			}
			if (charArchivo=='\n'){//SI OCURRE UN SALTO DE LÍNEA ES EL FINAL DE LA DEFINICIÓN
				definicion[i]=charArchivo;
				definicion[i+1] = '\0';//SE CIERRA LA DEFINICIÓN
				strcpy(&nuevaPalabra.palabra[0],&palabra[0]);//LA PALABRA SE COPIA AL ATRIBUTO palabra DEL NUEVO registro
				strcpy(&nuevaPalabra.definicion[0],&definicion[0]);//LA PALABRA SE COPIA AL ATRIBUTO palabra DEL NUEVO registro
				AgregarATabla(diccionario,nuevaPalabra);
				printf("\nPalabra %s agregada exitosamente!",nuevaPalabra.palabra);
				if(palabraAlt[0] != '#'){
					strcpy(&nuevaPalabra.palabra[0],&palabra[0]);
					strcpy(&nuevaPalabra.definicion[0],&definicion[0]);
					AgregarATabla(diccionario,nuevaPalabra);
					printf("\nPalabra %s agregada exitosamente!",nuevaPalabra.palabra);
					palabraAlt[0] = '#';
				}
				fflush(stdout);
				estado = 'p';
				palabra[0] = '#';
				i=0;
				continue;
			}
			if(estado == 'p'){//ESCRIBE LA PALABRA NORMAL
				palabra[i]=charArchivo;
				i++;
			}
			if(estado == 'q'){//COMIENzA A ESRIBIR LA PALABRA ALTERNA
				palabraAlt[i]=charArchivo;
				i++;
			}
			if(estado == 's'){//COMIENZA A ESCRIBIR LA DEFINICIÓN
				definicion[i]=charArchivo;
				i++;
			}
		}
	}
	printf("\n\nPor favor, espere...");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

/*
	FUNCIÓN: nuevaPalabra(tablaHash *diccionario).
	RECIBE: int (DIRECCIÓN DE MEMORIA DE LA TABLA HASH A OPERAR).
	DEVUELVE: NADA.
	DESCRIPCIÓN: SE ENCARGA DE SOLICITAR UNA NUEVA PALABRA CON SU RESPECTIVA DEFINICIÓN, AÑADE ESTAS CADENAS A UN NUEVO ELEMENTO Y ÉSTE ES AGREGADO
		AL DICCIONARIO INDICADO EN EL PARÁMETRO.
	OBSERVACIONES: NO SE VALIDA SI EL USUARIO INTRODUCE UNA PALABRA CON ALGUNA ALTERNTIVA. EJEMPLO: PIEDRA/ROCA
*/
void nuevaPalabra(tablaHash *diccionario){
	registro nueva;
	char palabra[100],definicion[255];
	int aux;
	printf("Ingresa la nueva palabra:\n>");
	scanf("%s[a-zA-Z ]",&palabra);
	fflush(stdin);
	//LIMPIANDO CARACTERES
	for(aux=0;aux<strlen(palabra);aux++){
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	printf("Ingresa su definicion:\n>");
	scanf("%[a-zA-Z ,.]s",&definicion);
	fflush(stdin);
	//LIMPIANDO CARACTERES
	for(aux=0;aux<strlen(definicion);aux++){
		definicion[aux]=caracterLatino(definicion[aux]);
	}
	strcpy(&nueva.palabra[0],&palabra[0]);
	strcpy(&nueva.definicion[0],&definicion[0]);
	AgregarATabla(diccionario,nueva);
	printf("Palabra %s agregada exitosamente!\n",palabra);
	printf("Por favor, espere...\n");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

/*
	FUNCIÓN: buscaPalabra(tablaHash *diccionario).
	RECIBE: int (DIRECCIÓN DE MEMORIA DE LA TABLA HASH A OPERAR).
	DEVUELVE: NADA.
	DESCRIPCIÓN: SE ENCARGA DE SOLICITAR LA PALABRA QUE SE DESEA BUSCAR, ÉSTA ES INGRESADA A UN NUEVO ELEMENTO TEMPORAL Y ENVIADA A LA FUNCIÓN
		CORRESPONDIENTE DE LA LIBRERÍA TADHashTable.h 
	OBSERVACIONES: EL USUARIO NO DEBE INTRODUCIR PALABRAS ALTERNATIVAS EN LA MISMA CADENA. NO ES NECESARIO SOLICITAR LA DEFINICIÓN.
*/
void buscaPalabra(tablaHash *diccionario){
	registro buscame,encontrada;
	char palabra[100],null[4]="NULL";
	int aux,index;
	printf("Ingresa la palabra a buscar:\n>");
	scanf("%s[a-zA-Z ]",palabra);
	for(aux=0;aux<strlen(palabra);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	strcpy(&buscame.palabra[0],&palabra[0]);//COPIAMOS LA PALABRA INGRESADA A LA PALABRA DEL NUEVO ELEMENTO
	encontrada=BuscarEnTabla(diccionario,buscame);
	if(strcmp(&encontrada.palabra[0],&null[0])!=0){
		printf("%s: %s\n",encontrada.palabra,encontrada.definicion);
	}
	system("pause");
	system("cls");
	//system("clear");
	return;
}

/*
	FUNCIÓN: eliminarPalabra(tablaHash *diccionario).
	RECIBE: int (DIRECCIÓN DE MEMORIA DE LA TABLA HASH A OPERAR).
	DEVUELVE: NADA.
	DESCRIPCIÓN: SE ENCARGA DE SOLICITAR LA PALABRA QUE SE DESEA ELIMINAR, LA ALMACENA EN UN NUEVO ELEMENTO TEMPORAL Y LA ENVÍA A LA RESPECTIVA
		FUNCIÓN DE LA LIBRERÍA TADHashTable.h
	OBSERVACIONES: EL USUARIO NO DEBE INTRODUCIR PALABRAS ALTERNATIVAS EN LA MISMA CADENA. NO ES NECESARIO SOLICITAR LA DEFINICIÓN.
*/
void eliminarPalabra(tablaHash *diccionario){
	registro eliminame;
	char palabra[100];
	int aux,index;
	printf("Ingresa la palabra a eliminar\n>");
	scanf("%s[a-zA-Z ]",&palabra);
	for(aux=0;aux<strlen(palabra);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	strcpy(&eliminame.palabra[0],&palabra[0]);//COPIAMOS LA PALABRA INGRESADA A LA PALABRA DEL NUEVO ELEMENTO
	printf("Eliminando...\n");
	EliminarDeTabla(diccionario,eliminame);
	printf("Eliminada exitosamente!\nPor favor espere...\n");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

/*
	FUNCIÓN: modificarDefinicion(tablaHash *diccionario).
	RECIBE: int (DIRECCIÓN DE MEMORIA DE LA TABLA HASH A OPERAR).
	DEVUELVE: NADA.
	DESCRIPCIÓN: SE ENCARGA DE SOLICITAR UNA PALABRA Y SU NUEVA DEFINICIÓN, ESTAS CADENAS SON AGREGADAS A UN NUEVO ELEMENTO Y ENVIADAS A LA RESPECTIVA
		FUNCIÓN DE LA LIBRERÍA TADHasTable.h
	OBSERVACIONES: NO SE VALIDA SI EL USUARIO INTRODUCE UNA PALABRA CON ALGUNA ALTERNTIVA. EJEMPLO: PIEDRA/ROCA
*/
void modificarDefinicion(tablaHash *diccionario){
	registro eModificado;
	char palabra[100],nuevaDefinicion[255];
	int aux,index;
	printf("Ingresa la palabra a modificar su definicion\n>");
	scanf("%s[a-zA-Z ]",&palabra);
	for(aux=0;aux<strlen(palabra);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	strcpy(&eModificado.palabra[0],&palabra[0]);//COPIAMOS LA PALABRA INGRESADA A LA PALABRA DEL ELEMENTO ACTUAL
	printf("Ingresa la nueva definicion:\n>");
	scanf("%[a-zA-Z ,.]s",&nuevaDefinicion);
	for(aux=0;aux<strlen(nuevaDefinicion);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		nuevaDefinicion[aux]=caracterLatino(nuevaDefinicion[aux]);
	}
	strcpy(&eModificado.definicion[0],&nuevaDefinicion[0]);
	printf("Modificando...\n");
	ModificarTabla(diccionario,eModificado);
	printf("Modificada exitosamente!\nPor favor espere...\n");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

int main(){
	int opcion=9,aux;
	tablaHash diccionario;
	diccionario.tamTabla=TABLE_SIZE;
	InicializarTabla(&diccionario);
	while(opcion!=0){
		printf("-------------------------\n\tBIENVENIDO\n--------------------------\n");
		printf("Ingrese la opcion deseada:\n1.- Cargar un archivo de definiciones\n");
		printf("2.- Agregar una palabra\n3.- Buscar una palabra\n4.- Eliminar palabra");
		printf("\n5.- Modificar definicion de una palabra\n6.- Mostrar estadisticas de la tabla\n7.- Exportar tabla a archivo de texto\n>");
		scanf("%i",&opcion);
		switch(opcion){
			case 1:
				cargarDiccionario(&diccionario);
			break;
			case 2:
				nuevaPalabra(&diccionario);
			break;
			case 3:
				buscaPalabra(&diccionario);
			break;
			case 4:
				eliminarPalabra(&diccionario);
			break;
			case 5:
				modificarDefinicion(&diccionario);
			break;
			case 6:
				Estadisticas(&diccionario);
				system("pause");
				system("cls");
				//system("clear");
			break;
			case 7:
				printf("Exportando...\n");
				ExportarTabla(&diccionario);
				printf("Por favor espere...\n");
				sleep(2);
				system("cls");
				//system("");
			break;
			default:
				printf("Ash, me chocas\n");
				exit(1);
			break;
		}
	}
	return 0;
}