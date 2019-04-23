/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD LISTA (TADLista.h)
AUTORES:
	Luis Diego Jiménez Delgado (Abril 2019) ©
    Aarón Gamaliel Sanchez Castro (Abril 2019) ©
    Citlalli Yasmin Sanchez Tirado (Abril 2019) ©
		Copyright (c) 2019 Copyright Holder All Rights Reserved.
VERSION: 1.0 (Abril 2019)

DESCRIPCION: TAD lista o (list)
Estructura de datos en la que se cumple:
Los elementos se consultan, aniaden y se remueven con base en posiciones
dentro de un arreglo lineal el cual cuenta con un frente o cabeza
y un final o cola.

OBSERVACIONES: TADLista por definicion es una Estructura de Datos dinamica.
La implementacion del presente codigo se realiza mediante el principo de "Lista Doblemente Ligada"
i.e. nodos que contienen un elemento y se encuentran ligados hacia siguiente de estos y al anterior de estos.

COMPILACION PARA GENERAR EL CODIGO OBJETO: gcc TADListaDL.c -c

*/

//LIBRERAS
#include "TADHashTable.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

//DEFINICION DE CONSTANTES
#define AKEY 73571

/*
	FUNCIÓN: aplicarHash(char *palabra, int tamTabla)
	RECIBE: char * (APUNTADOR A UNA CADENA DE CARACTERES), int (TAMAÑO DE LA TABLA)
	DEVUELVE:
	DESCRIPCIÓN: RECIBE COMO PARÁMETRO UNA CADENA DE CARACTERES, APLICA LA FUNCIÓN HASH A DICHA CADENA
		Y REGRESA EL ÍNDICE QUE LE CORRESPONDE DENTRO DE LA TABLA HASH.
	OBSERVACIONES: LA FRECUENCIA CON LA QUE ESTA FUNCIÓN REGRESE EL MISMO VALOR PARA DIFERENTES PALABRAS
		DEPENDERÁ DE LA FUNCIÓN HASH DISEÑADA POR EL EQUIPO.
*/
int aplicarHash(char *palabra,int tamTabla){
	/*
//Esta variante consiste en tomar el valor de cada carácter
//y hacer dos corrimientos de bits
//Uno hacia la izquierda y hacia a derecha con dos valores distintos
//Estos se unen por medio de un or de bits
//El resultado obtenido se utliza como codigo hash

int HashCode(char *palabra, int tamTabla)
{
	int tam=strlen(palabra);
	//declaración de la variable que obtendrá el resultado del hash
	unsigned int h=0;
	int i;
	//Por cada uno lo que se va a hacer es asignar un valor or
	for (i=0; i<tam; i++)
	{
		//utilizamos operadores de desplazamiento
		//<< corrimiento 5 espacios a la izquierda
		//>> corrimiento 27 espacios a la derecha

		h=(h<<5)|(h>>27);
		h+=(unsigned int)palabra[i];
	}
	return h;
}


//Esta basada en el algoritmo de Dan Bernstein
//En esta función hash tenemos dos numeros 33 y 5381
//El número 33 se elige porque es facil de calcular
//Usar 33 hace dos copias de la mayoría de los bits de entrada en el acumulador de hash

    int HashCodee( char *palabra)
    {
        unsigned long hash1 = 5381;
        int c;

        while (c = *palabra++)
        //El desplazamiento de 5 se hace ya que es relativamente
        //primo a 32 lo que ayuda con el avalanchamiento
        //ya que un caracter ascii puede considerarse como un selector de tipo
        //caracteres de 4 bits
            hash1 = ((hash1 << 5) + hash1) + c; // hash * 33 + c

        return hash1;
    }
    */
	/*
		LA SIGUIENTE FUNCIÓN CONSISTE EN OBTENER EL VALOR ASCII DEL CARACTER EN TURNO Y MULTIPLICARLO POR UNA POTENCIA
		DE 2, DE ACUERDO A SU ÍNDICE CORRESPONDIENTE DENTRO DE UNA CADENA. EJEMPLO
		H = 72*2^0
		O = 79*2^1
		L = 76*2^2
		A = 65*2^3
		POSTERIORMENTE ESTOS VALORES SON SUMADOS Y FINALMENTE SOMETIDOS AL OPERADOR % JUNTO CON EL TAMAÑO DE LA TABLA
		ESTO GARANTIZA QUE EL VALOR OBTENIDO POR LA FUNCIÓN SE ENCUENTRE SIEMPRE DENTRO DE LOS LÍMITES DE LA TABLA
	*/
	int index=0,m_posicion,valor_letra,aux;//m_posicion = MÚLTIPLO DE LA POSICIÓN
	for(aux=0;aux<strlen(palabra);aux++){
		m_posicion=pow(2,aux+1);
		valor_letra=(int)palabra[aux];
		index=index+valor_letra*m_posicion;
	}
	if(index<0){
		index=index*-1;
	}
	return index%tamTabla;

	/*int aux = 0;
	int i = 0, resultado = 0, tam, derecha;
	tam = strlen(palabra);
	for (i = 0; i < tam; ++i)
	{
		aux = ((AKEY * palabra[i]) % ((int)pow(2, i + 13))) >> ((int)(pow(8, i + 3)));
		resultado += aux;
	}
	resultado = (resultado % tamTabla);
	if (resultado < 0)
		resultado = tamTabla + resultado;

	return resultado;*/
}

/*
	FUNCIÓN: InicializarTabla(tablaHash *tabla).
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash).
	DEVUELVE:
	DESCRIPCIÓN: SE ENCARGA DE INICIALIZAR TODAS LAS LISTAS DOBLEMENTE LIGADAS CONTENIDAS EN LA TABLA HASH.
	OBSERVACIONES: EL USUARIO DEBE CREAR UNA STRUCT DEL TIPO tablaHash.
*/
void InicializarTabla(tablaHash *tabla){
	int aux;
	for (aux = 0; aux < tabla->tamTabla; aux++)
	{
		Initialize(&tabla->listas[aux]);
	}
	return;
}

/*
	FUNCIÓN: DestruirTabla(tablaHash *tabla)
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash).
	DEVUELVE:
	DESCRIPCIÓN: SE ENCARGA DE DESTRUIR LA TABLA HASH, DESTRUYENDO CADA LISTA CONTENIDA EN LA TABLA.
	OBSERVACIONES: EL USUARIO DEBE CREAR UN STRUCT DEL TIPO tablaHash.
*/
void DestruirTabla(tablaHash *tabla){
	int aux;
	for (aux = 0; aux < tabla->tamTabla; aux++)
	{
		Destroy(&tabla->listas[aux]);
	}
	return;
}

/*
	FUNCIÓN: AgregarATabla(tablaHash *tabla, elemento e)
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash), elemento (ELEMENTO QUE SERÁ AÑADIDO).
	DEVUELVE:
	DESCRIPCIÓN: ECARGADA DE AGREGAR UN NUEVO ELEMENTO A LA LISTA CORRESPONDIENTE INDICARA POR LA FUNCIÓN HASH.
	OBSERVACIONES: EL USUARIO CUENTA CON UNA tablaHash INICIALIZADA.
*/
void AgregarATabla(tablaHash *tabla, elemento e){
	int index;
	index = aplicarHash(e.palabra, tabla->tamTabla);
	Add(&tabla->listas[index], e);
	return;
}

/*
	FUNCIÓN: EliminarDeTabla
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash), elemento (ELEMENTO QUE SERÁ REMOVIDO).
	DEVUELVE:
	DESCRIPCIÓN: SE ENCARGA DE REMOVER EL ELEMENTO INDICADO DE SU CORRESPONDIENTE LISTA, UTILIZA LA FUNCIÓN HASH.
	OBSERVACIONES: EL USUARIO CUENTA CON UNA tablaHash INICIALIZADA Y LA LISTA QUE CORRESPONDE AL ELEMENTO NO
		SE ENCUENTRA VACÍA.
*/
void EliminarDeTabla(tablaHash *tabla, elemento e){
	int index;
	posicion posEnTabla;
	index = aplicarHash(e.palabra, tabla->tamTabla);
	posEnTabla = Search(&tabla->listas[index], e);
	Remove(&tabla->listas[index], posEnTabla);
	return;
}

/*
	FUNCIÓN: BuscarEnTabla (tablaHash *tabla, elemento e)
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash).
	DEVUELVE: elemento (ELEMENTO ENCONTRADO DENTRO DE LA TABLA)
	DESCRIPCIÓN:
	OBSERVACIONES: EL USUARIO CUENTA CON UNA tablaHash INICIALIZADA Y LA LISTA QUE CORRESPONDE AL ELEMENTO NO
		SE ENCUENTRA VACÍA.
*/
elemento BuscarEnTabla(tablaHash *tabla, elemento e){
	elemento encontrada;
	int index;
	posicion posEnTabla;
	index = aplicarHash(e.palabra, tabla->tamTabla);
	posEnTabla = Search(&tabla->listas[index], e);
	if (posEnTabla != NULL)
	{ //COMPROBAMOS QUE EXISTE LA PALABRA DENTRO DE LA LISTA
		encontrada = Position(&tabla->listas[index], posEnTabla);
		printf("Encontrada en %i pasos\n", posEnTabla->pasos);
	}
	else
	{
		printf("La palabra solicitada no existe en el diccionario...\n");
		char no_encontrada[4] = "NULL";
		strcpy(&encontrada.palabra[0], &no_encontrada[0]);
	}
	return encontrada;
}

/*
	FUNCIÓN: ModificarTabla (tablaHash *tabla, elemento e).
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash).
	DEVUELVE:
	DESCRIPCIÓN: REEMPLAZA UN ELEMENTO EXISTENTE EN UNA LISTA POR EL INDICADO EN EL PARÁMETRO.
	OBSERVACIONES: EL USUARIO CUENTA CON UNA tablaHash INICIALIZADA Y LA LISTA QUE CORRESPONDE AL ELEMENTO NO
		SE ENCUENTRA VACÍA.
*/
void ModificarTabla(tablaHash *tabla, elemento e){
	int index;
	posicion posEnTabla;
	index = aplicarHash(e.palabra, tabla->tamTabla);
	posEnTabla = Search(&tabla->listas[index], e);
	Replace(&tabla->listas[index], posEnTabla, e);
	return;
}

/*
	FUNCIÓN: Estadisticas(tablaHash *tabla)
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash).
	DEVUELVE: IMPRIME EN PANTALLA.
	DESCRIPCIÓN: MUESTRA EL NÚMERO DE LISTAS CONTENIDAS EN LA TABLA, PROMEDIO DE COLISIONES PARA LA FUNCIÓN,
		CANTIDAD DE LISTAS VACÍAS Y CANTIDAD DE ELEMENTOS QUE CONTIENE CADA LISTA.
	OBSERVACIONES: EL USUARIO CUENTA CON UNA tablaHash INICIALIZADA.
*/
void Estadisticas(tablaHash *tabla){
	printf("Total de listas en la tabla: %i\n",TABLE_SIZE);
	int aux,vacias=0,tamLista,totalElementos=0,noVacias=0;
	for(aux=0;aux<TABLE_SIZE;aux++){
		tamLista=Size(&tabla->listas[aux]);
		totalElementos=totalElementos+tamLista;
		if(tamLista==0){
			vacias++;
		}
		printf("La lista %i contiene %i elemento(s)\n", aux, tamLista);
	}
	printf("Total de listas vacias: %i\n", vacias);
	noVacias = TABLE_SIZE - vacias;
	noVacias != 0 ? printf("Promedio de colisiones: %i\n", totalElementos / noVacias) : printf("No se ha podido determinar el promedio de colisiones\n");
	printf("Total de elementos: %i", totalElementos);
	return;
}

/*
--------------------OPCIONAL--------------------
	FUNCIÓN: ExportarTabla(tablaHash *tabla)
	RECIBE: tablaHash * (APUNTADOR A UNA STRUCT DEL TIPO tablaHash).
	DEVUELVE: CREA UN ARCHIVO .txt EN LA UBICADO EN LA CARPETA CONTENEDORA DE ESTE PROGRAMA.
	DESCRIPCIÓN: OBTIENE TODOS LOS ELEMENTOS DE LAS LISTAS CORRESPONDIENTES A LA TABLA HASH INDICADA
		Y LAS AGREGA A UN ARCHIVO .txt CREADO POR ESTA MISMA FUNCIÓN.
	OBSERVACIONES: EL USUARIO CUENTA CON UNA tablaHash INICIALIZADA Y LA LISTA QUE CORRESPONDE AL ELEMENTO NO
		SE ENCUENTRA VACÍA.
*/
void ExportarTabla(tablaHash *tabla){
	int aux;
	FILE *nuevoArchivo;
	char nombreArchivo[] = "Diccionario.txt", palabra[100], definicion[255];
	nuevoArchivo = fopen(nombreArchivo, "w");
	if (nuevoArchivo != NULL)
	{
		posicion finLista;
		elemento actual;
		for (aux = 0; aux < TABLE_SIZE; aux++)
		{
			finLista = tabla->listas[aux].frente;
			while (finLista != NULL)
			{
				actual = Position(&tabla->listas[aux], finLista);
				strcpy(palabra, actual.palabra);
				strcpy(definicion, actual.definicion);
				strcat(palabra, ": ");
				strcat(palabra, definicion);
				fprintf(nuevoArchivo, palabra);
				finLista = finLista->siguiente;
			}
		}
		fclose(nuevoArchivo);
		printf("Exportado exitosamente!\n");
	}
	else
	{
		printf("Exportado exitosamente fallido!\n");
	}
	return;
}
