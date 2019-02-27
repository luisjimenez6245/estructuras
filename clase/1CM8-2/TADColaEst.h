#define MAX 100
#define TRUE 1
#define FALSE 0
typedef struct elemento
{
	int n;
	//Lo que gustes
} elemento;

typedef struct cola
{
	elemento A[MAX];
	int final;
	
} cola;

typedef char booleano;


/*Inicializar cola (Initialize): recibe<- cola (C); 
Initialize (C)
Efecto: Recibe una cola, la inicializa para su trabajo normal.
*/
void Initialize(cola * C);
/*
Encolar (Queue): recibe<- cola (C) ; recibe<- elemento(e) 
Queue(C,e);
Efecto: Recibe una cola y un elemento el cuál se introduce al final de la cola.
*/
void Queue(cola *C,elemento e);
/*
Desencolar (Dequeue): recibe<- cola (C); retorna -> elemento
e=Dequeue (C);
Efecto: Recibe una cola y devuelve el elemento que se encuentra al frente de esta, quitándolo de la cola.
Excepción: Si la cola esta vacía produce error.
*/
elemento Dequeue (cola *C);

/*Es vacía (Empty): recibe<- cola (C); retorna -> booleano
Empty (C)
Efecto: Recibe la cola y verifica si esta tiene elementos, devuelve TRUE si esta vacía y FALSE en caso contrario.
*/
booleano Empty (cola *C);
/*
Frente (Front): recibe<- cola (C) ; retorna -> elemento
e=Front (C);
Efecto: Recibe una cola y devuelve el elemento que se encuentra al frente de esta.
Excepción: Si la cola esta vacía produce error.
*/
elemento Front (cola *C);

/*
Final (Final): recibe<- cola (C); retorna -> elemento
e=Final(C);
Efecto: Recibe una cola y devuelve el elemento que se encuentra al final de esta.
Excepción: Si la cola esta vacía produce error.
*/
elemento Final(cola *C);


/*
Elemento(Element): recibe<- cola (C); recibe<- índice(n); retorna -> elemento
e=Element (C,n);
Efecto: Recibe una cola y un índice (entre 1 y el tamaño de la cola) y devuelve el elemento que se encuentra en la cola en ese índice partiendo del frente de esta =1.
Excepción: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la cola se produce error.
*/
elemento Element (cola *C,int n);

/*
Eliminar cola (Destroy): recibe<- cola (C); 
Destroy(C)
Efecto: Recibe una cola y la libera completamente.
*/
void Destroy(cola *C);

/*
Tamaño (Size): recibe<- cola (C);  retorna -> numero
n=Size (C);
Efecto: Recibe una cola y devuelve el tamaño de la cola.
*/
int Size (cola *C);
