/*
LIBRERÍA: Cabecera del TAD PILA DINÁMICA.
AUTORES:
    Jiménez Delgado Luis Diego (C) Febrero 2019
    Sánchez Castro Aarón Gamaliel (C) Febrero 2019
    Sánchez Tirado Citlali Yasmín (C) Febrero 2019
VERSIÓN: 1.0
DESCRIPCIÓN:
    Estructura de datos que permite su almacenamiento y recuperación, el modo de acceso a los elementos
    es del tipo LIFO (Last In, First Out). Cuenta con múltiples operaciones que se describen a detalle
    en su respectiva función.
OBSERVACIONES:
    El presente archivo implica la construcción de una pila (stack) dinámica, es decir, la memoria
    que utiliza el programa para almacenar los elementos varía durante el tiempo de ejecución del mismo.
*/
//Definición de constantes booleanas
#define TRUE 1
#define FALSE 0
//Definición de boolean, tipo de dato inexistente en C.
typedef char boolean;
//Definición de element (elemento) que contendrá la pila <<stack>>
typedef struct element
{
  char c;
} element;
//Definición de node (nodo) que contendrá elementos y estarán conectados en la pila <<stack>>
typedef struct node
{
  element e;
  struct node *below;
} node;
//Definición de pila <<stack>>, arreglo dinámico que contiene nodes (nodos).
typedef struct stack
{
  node *top;
  int size;
} stack;
//Declarando las funciones principales de una pila <<stack>>
void Initialize(stack *s);      //Inicializar pila (Iniciar una pila para su uso)
void Push(stack *s, element e); //Empilar (Introducir un elemento a la pila)
element Pop(stack *s);          //Desempilar (Extraer un elemento de la pila)
boolean Empty(stack *s);        //Vacia (Preguntar si la pila esta vacia)
element Top(stack *s);          //Tope (Obtener el "elemento" del tope de la pila si extraerlo de la pila)
int Size(stack *s);             //Tamaño de la pila (Obtener el número de elementos en la pila)
void Destroy(stack *s);         //Elimina pila (Borra a todos los elementos y a la pila de memoria)
