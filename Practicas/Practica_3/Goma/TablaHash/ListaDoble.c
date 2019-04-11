/*
	LISTA DOBLEMENTE LIGADA
	AUTOR: AARÓN GAMALIEL SÁNCHEZ CASTRO (C) FEBRERO 2019
	VERSIÓN: 1.2 MODIFICADA PARA LA PRÁCTICA 3
	DESCRIPCIÓN: EL SIGUIENTE CÓDIGO MUESTRA LA IMPLEMENTACIÓN DE UNA LISTA DOBLEMENTE LIGADA.
	OBSERVACIONES: SE TRATA DE UNA LISTA DINÁMICA, POR LO QUE LA MEMORIA OCUPADA POR EL PROGRAMA CRECERÁ
		DURANTE EL TIEMPO DE EJECUCIÓN.
	COMPILACIÓN: gcc ListaDoble.c ListaDoble.h -c
*/
//LIBRERÍAS A UTILIZAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDoble.h"

/*
	FUNCIÓN: Initialize(List* list).
	RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR).
	RETORNA: NADA.
	DESCRIPCIÓN: INICIALIZA LA LISTA PARA PODER OPERALA.
	OBSERVACIONES: EL USUARIO HA CREADO UNA LISTA Y CUENTA CON LA REFERENCIA A ELLA.
*/
void Initialize(List* list){
	list->front=NULL;
	list->final=NULL;
	list->listSize=0;
}

/*
	FUNCIÓN: Empty(List* list)
	RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR).
	RETORNA: TRUE O FALSE, SEGÚN SEA EL CASO.
	DESCRIPCIÓN: OPERACIÓN DE CONSULTA QUE INDICA SI LA LISTA INDICADA SE ENCUENTRA VACÍA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA. 
*/
boolean Empty(List* list){
	boolean value=FALSE;
	if(list->listSize==0){
		value=TRUE;
	}
	return value;
}

/*
	FUNCIÓN: ElementPosition(List* list, int position)
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), int position (REFERENCIA DE LA POSICIÓN DEL ELEMENTO 
		SOLICITADO).
	RETORNA: Position (DIRECCIÓN DE MEMORIA DEL ELEMENTO SOLICITADO). 
	DESCRIPCIÓN: RETORNA LA DIRECCIÓN DE MEMORIA DEL ELEMENTO ESPECIFICADO CON EL IDENTIFICADOR int position
	OBSERVACIONES: SE VALIDA SI LA POSICIÓN ESTÁ DENTRO DEL RANGO DE LA LISTA, SI NO LO ESTÁ CAUSA ERROR.
*/
Position ElementPosition(List* list, int position){
	if(Empty(list)){
		printf("ERROR ElementPosition(list,position): LA LISTA SE ENCUENTRA VACIA");
		exit(1);
	}
	printf("ELEMENTPOSITION RECIBIENDO LA POSICION %i...",position);
	Position aux_position;
	//DEBEMOS COMPROBAR SI ESTÁ DENTRO DEL RANGO DE LA LISTA
	if(position>=0&&position<=Size(list)){
		int i;
		Position aux=list->front;
		for(i=1;i<=position;i++)
			aux=aux->following;
		return aux;
	}else{
		printf("ERROR ElementPosition(list,position): POSICION FUERA DE RANGO");
		exit(1);
	}
}

/*
	FUNCIÓN: ValidatePosition(List* list, Position position)
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), position (POSICIÓN EN LA LISTA A BUSCAR).
	RETORNA: TURE O FALSE, SEGÚN SEA EL CASO.
	DESCRIPCIÓN: OPERACIÓN QUE INDICA SI UNA POSICIÓN ESTÁ DEFINIDA DENTRO DE UNA LISTA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UN LISTA. ADEMÁS, 
		LA LISTA NO SE ENCUENTRA VACÍA.
*/
boolean ValidatePosition(List* list, Position position){
	boolean exist;
	if(Empty(list)==TRUE){
		printf("ERROR ValidatePosition(list,position): LA LISTA SE ENCUENTRA VACÍA");
		exit(1);
	}
	Position aux_position;
	aux_position=list->front;
	while(aux_position!=NULL){
		if(aux_position==position){
			exist=TRUE;
			break;
		}else{
			aux_position=aux_position->following;
		}
	}
	return exist;
}

/*
	FUNCIÓN: Remove(List* list, Position position)
	RECIBE: RECIBE:  RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), position (POSICIÓN DEL ELEMENTO A REMOVER).
	RETORNA: NADA
	DESCRIPCIÓN: OPERACIÓN PARA REMOVER UN ELEMENTO DE LA PILA EN LA POSICIÓN INDICADA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
		ADEMÁS, LA PILA NO DEBE ESTAR VACÍA PUES CAUSA ERROR.
*/
void Remove(List* list, Position position){
	if(Empty(list)==TRUE){
		printf("\nERROR Remove(list,position): LA LISTA SE ENCUENTRA VACIA");
		exit(1);
	}
	if(ValidatePosition(list,position)==TRUE){
		if(position==list->front){//LA POSICIÓN ES EL FRENTE
			position->following->previous=NULL;
			list->front=position->following;
		}else if(position==list->final){//LA POSICIÓN ES EL FINAL
			position->previous->following=NULL;
			list->final=position->previous;
		}else{//LA POSICIÓN NO ES NINGUNA DE LAS DOS ANTERIORES
			position->previous->following=position->following;
			position->following->previous=position->previous;
		}
		free(position);
		list->listSize--;
	}else{
		printf("\nERROR Remove(list,position): POSICION FUERA DE RANGO");
		exit(1);
	}
}

/*
	FUNCIÓN: Final(List* list)
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR).
	RETORNA: Position (POSICIÓN FINAL EN LA LISTA INDICADA).
	DESCRIPCIÓN: OPERACIÓN QUE CONSULTA Y REGRESA LA ÚLTIMA POSICIÓN EN LA LISTA INDICADA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UN LISTA. ADEMÁS, LA LISTA NO SE ENCUENTRA VACÍA.
*/
Position Final(List* list){
	return list->final;
}

/*
	FUNCIÓN: First(List* list)
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR).
	RETORNA: Position (PRIMERA POSICIÓN EN LA LISTA INDICADA).
	DESCRIPCIÓN: OPERACIÓN QUE CONSULTA Y REGRESA LA PRIMERA POSICIÓN EN LA LISTA INDICADA.
	OBSERVACIONES: OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UN LISTA. ADEMÁS, 
		LA LISTA NO SE ENCUENTRA VACÍA.
*/
Position First(List* list){
	return list->front;
}

/*
	FUNCIÓN: Size(List* list)
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR).
	RETORNA: int (TAMAÑO DE LA LISTA).
	DESCRIPCIÓN: RETORNA EL TAMAÑO DE LA LISTA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
		NO SE VALIDA SI ESTÁ VACÍA O NO, PUES NO DEBERÍA CAUSAR ERROR EN AMBOS CASOS.
*/
int Size(List* list){
	return list->listSize;
}

/*
	FUNCIÓN: Following(List* list).
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), Position position (DIRECCIÓN
		DE UN ELEMENTO EN LA LISTA, DEL CUAL ENCONTRARÁ SU SIGUIENTE).
	RETORNA: Position (POSICIÓN SIGUIENTE).
	DESCRIPCIÓN: RETORNA LA POSICIÓN (DIRECCIÓN DE MEMORIA) DEL SIGUIENTE ELEMENTO AL INDICADO.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
		SE VALIDA SI LA LISTA ESTÁ VACÍA, EN CASO DE SER CIERTO CAUSA ERROR. ADEMÁS, SE VALIDA
		QUE LA POSICIÓN ESTÉ DENTRO DEL RANGO DE LA LISTA, EN CASO DE NO ESTARLO CAUSA ERROR.
*/
Position Following(List* list, Position position){
	if(Empty(list)==TRUE){
		printf("ERROR Following(list,position): LA LISTA SE ENCUENTRA VACIA");
		exit(1);
	}
	if(ValidatePosition(list,position)==TRUE){//COMPROBANDO SI EXISTE LA POSICIÓN EN LA LISTA
		return position->following;
	}else{
		printf("ERROR Following(list,position): POSICION FUERA DE RANGO");
		exit(1);
	}
}

/*
	FUNCIÓN: Previous(List* list)
	RECIBE: RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), Position position (DIRECCIÓN
		DE UN ELEMENTO EN LA LISTA, DEL CUAL ENCONTRARÁ SU ANTERIOR).
	RETORNA: Position (POSICIÓN ANTERIOR).
	DESCRIPCIÓN: RETORNA LA POSICIÓN (DIRECCIÓN DE MEMORIA) DEL ELEMENTO ANTERIOR AL INDICADO.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
		SE VALIDA SI LA LISTA ESTÁ VACÍA, EN CASO DE SER CIERTO CAUSA ERROR. ADEMÁS, SE VALIDA
		QUE LA POSICIÓN ESTÉ DENTRO DEL RANGO DE LA LISTA, EN CASO DE NO ESTARLO CAUSA ERROR.
*/
Position Previous(List* list,Position position){
	if(Empty(list)==TRUE){
		printf("ERROR Previous(list,position): LA LISTA SE ENCUENTRA VACIA");
		exit(1);
	}
	if(ValidatePosition(list,position)==TRUE){//COMPROBANDO SI EXISTE LA POSICIÓN EN LA LISTA
		return position->previous;
	}else{
		printf("ERROR Previous(list,position): POSICION FUERA DE RANGO");
		exit(1);
	}
}

/*
	FUNCIÓN: Search(List* list, Element element)
	RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), Element element (ELEMENTO QUE SE PRETENDE BUSCAR).
	RETORNA: Position (DIRECCIÓN DE MEMORIA DEL ELEMENTO INDICADO).
	DESCRIPCIÓN: BUSCA EN TODOS LOS ELEMENTOS DE LA LISTA UNA COINCIDENCIA CON EL ELEMENTO INDICADO, EN 
		CASO DE ENCONTRARLA REGRESA LA DIRECCIÓN DE MEMORIA DE DICHO ELEMENTO.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
		 SI LA LISTA ESTÁ VACÍA NO ENTRA A LA FUNCIÓN POR COMPLETO.
*/
Position Search(List* list, Element element){
	Position aux_position;
	int pasos=0;
	aux_position=list->front;
	while(aux_position!=NULL){
		pasos++;
		if(strcmp(aux_position->content.palabra,element.palabra)==0){
			break;
		}
		aux_position=aux_position->following;
	}
	aux_position->pasos=pasos;
	return aux_position;
}

/*
	FUNCIÓN: Destroy(List* list).
	RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR).
	RETORNA: NADA.
	DESCRIPCIÓN: DESTRUYE LA LISTA INDICADA POR EL USUARIO.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
*/
void Destroy(List* list){
	Position aux_position;
	while(list->front!=NULL){
		aux_position=list->front->following;//RECORREMOS EL AUXILIAR AL SIGUIENTE DEL FRENTE
		free(list->front);
		list->front=aux_position;//ACTUALIZAMOS EL FRENTE
	}
	list->final=NULL;
	list->listSize=0;
}

/*
	FUNCIÓN: Insert(List* list, Element element, Position position, boolean bool)
	RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), element (ELEMENTO QUE SE DESEA INTRODUCIR A LA LISTA),
		position (POSICIÓN OBJETIVO DEL ELEMENTO), bool (DATO TIPO BOOLEAN INDICANDO LA POSICIÓN DEL ELEMENTO NUEVO).
	RETORNA: NADA
	DESCRIPCIÓN: OPERACIÓN PARA INGRESAR UN ELEMENTO NUEVO A LA LISTA, EL USUARIO INDICA SI EL ELEMENTO SERÁ AÑADIDO
		ANTES O DESPUÉS DE LA POSICIÓN INDICADA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA. 
*/
void Insert(List* list, Element element, Position position, boolean booln){
 	Position aux_node;
 	aux_node=malloc(sizeof(Node));
 	if(aux_node!=NULL){//COMPROBAMOS SI SE HA OTORGADO LA MEMORIA
 		aux_node->content=element;//ASIGNAMOS EL ELEMENTO CONTENIDO EN EL NODO
 		if(ValidatePosition(list,position)==TRUE){
 			if(booln==TRUE){//SI booln ES 1, SE INSERTA ANTES DE position
 				if(position->previous==NULL){//position ES EL FRENTE DE LA LISTA
 					aux_node->previous=NULL;
					position->previous=aux_node;
					aux_node->following=position;
					list->front=aux_node;
 				}else{//position NO ES EL FRENTE DE LA LISTA
 					aux_node->previous=position->previous;
					position->previous->following=aux_node;
					position->previous=aux_node;
					aux_node->following=position;
 				}
 			}else{//SI booln ES 0, SE INSERTA DESPUÉS DE position
 				if(position->following==NULL){//position ES EL FINAL DE LA LISTA
 					aux_node->following=NULL;
					aux_node->previous=position;
					position->following=aux_node;
 				}else{//position NO ES EL FINAL DE LA LISTA
 					aux_node->following=position->following;
					aux_node->previous=position;
					position->following->previous=aux_node;
					position->following=aux_node;
 				}
 			}
 			list->listSize++;
 		}else{
 			printf("\nERROR Insert(list,element,position,bool): POSICION FUERA DE RANGO");
 			exit(1);
 		}
 	}else{
 		printf("\nERROR Insert(list,element,position,bool): MEMORIA INSUFICIENTE");
 		exit(1);
 	}
}

/*
	FUNCIÓN: Add(List* list, Element element)
	RECIBE:  RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), element (ELEMENTO A INTRODUCIR EN LA LISTA).
	RETORNA: NADA
	DESCRIPCIÓN: OPERACIÓN PARA AGREGAR UN NUEVO ELEMENTO AL FINAL DE LA LISTA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
*/
void Add(List* list, Element element){
	Position aux_node;
	aux_node=malloc(sizeof(Node));
	if(aux_node!=NULL){
		if(Empty(list)){
			aux_node->previous=NULL;
			list->front=aux_node;
		}else{
			list->final->following=aux_node;
			aux_node->previous=list->final;
		}
		aux_node->content=element;
		list->final=aux_node;
		aux_node->following=NULL;
		list->listSize++;
	}else{
		printf("\nERROR Add(list,element): MEMORIA NO ASIGNADA PARA EL NUEVO NODO");
	}
}

/*
	FUNCIÓN: GetElement(List* list, Position position)
	RECIBE: int *list (REFERENCIA A LA LISTA A OPERAR), Position position (POSICIÓN DEL ELEMENTO).
	RETORNA: Element (CONTENIDO DE LA DIRECCIÓN position)
	DESCRIPCIÓN: RETORNA EL CONTENIDO DE LA DIRECCIÓN DE MEMORIA INDICADA.
	OBSERVACIONES: EL USUARIO HA CREADO E INICIALIZADO UNA LISTA, Y CUENTA CON LA REFERENCIA A ELLA.
		 SE VALIDA SI LA LISTA ESTÁ VACÍA LA LISTA, EN CASO DE ESTARLO CAUSA ERROR. ADEMÁS, SE VALIDA SI
		 LA POSICIÓNO INDICADA SE ENCUENTRA DENTRO DEL RANGO DE LA LISTA, EN CASO DE NO ESTARLO CAUSA ERROR.
*/
Element GetElement(List *list, Position position){
	Element delement;
	if(!Empty(list)){
		if(ValidatePosition(list,position)){
			delement=position->content;
		}else{
			printf("\nERROR GetElement(list,position): LA POSICION SOLICITADA NO ESTA DENTRO DE LA LISTA");
			exit(1);
		}
	}else{
		printf("\nERROR GetElement(list,position): LA LISTA SE ENCUENTRA VACIA");
		exit(1);
	}
	return delement;
}
