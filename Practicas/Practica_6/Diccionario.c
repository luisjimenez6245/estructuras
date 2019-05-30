/*
	DICCIONARIO ÁRBOL ALV
	AUTORES: 
		JIMÉNEZ DELGADO LUIS DIEGO
		SÁNCHEZ CASTRO AARÓN GAMALIEL
		SÁNCHEZ TIRADO CITLALI YASMÍN
	VERSIÓN 1.0
	DESCRIPCÍÓN: EL MISMO PROGRAMA DE DICCIONARIO PERO CON ÁRBOLES
*/
#include <stdio.h>
#include <stdlib.h>

//A PARTIR DE AQUÍ HASTA LA LÍNEA ES CÓDIGO COPIADO DE LA PRÁCTICA 3 :)
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
void cargarDiccionario(){
	FILE *archivo;
	Elemento nuevaPalabra; 
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
				/*

				AGREGAMOS LA PALABRA AL ÁRBOL

				*/
				printf("\nPalabra %s agregada exitosamente!",nuevaPalabra.palabra);
				if(palabraAlt[0] != '#'){
					strcpy(&nuevaPalabra.palabra[0],&palabra[0]);
					strcpy(&nuevaPalabra.definicion[0],&definicion[0]);
					/*

					AGREGAMOS LA PALABRA AL ÁRBOL
	
					*/
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

boolean agregarPalabra(){
	boolean pAgregada=FALSE;
	return pAgregada;
}

elemento buscarPalabra(){
	elemento pEncontrada;
	return pEncontrada;
}

boolean modificarPalabra(){
	boolean pModificada;
	return pModificada;
}

boolean eliminarPalabra(){
	boolean pEliminada;
	return pEliminada;
}

int main(){
	int opcion;
	printf("---------------------\n\tBIENVENIDO\n---------------------");
	printf("1.- Cargar un archivo de definiciones.\n2.- Agregar una palabra y su definicion");
	printf("3.- Buscar una palabra.\n4.- Modificar una definición");
	printf("5.- Eliminar una palabra.\n6.- Recorrido PreOrden");
	printf("7.- Recorrido InOrden.\n8.- Recorrido PostOrden");
	printf("9.- Mostrar estadisticas.\n10.- Salir.\n>");
	scanf("%i",&opcion);
	switch(opcion){
		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		case 5:
		break;
		case 6:
		break;
		case 7:
		break;
		case 8:
		break;
		case 9:
		break;
		case 10:
		break;
	}
	return 0;
}
