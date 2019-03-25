/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Con la implimentación del TAD Pila se implemento
un programa que valida y evalua una expresión infija. 
Que toma en consideración la procedencia de los operadores, 
realiza una evaluación de paréntesis escritos correctamente,
convierte la expresión a postfijo, mostrando el resultado
y finalmente realiza la evaluación de la expresión.
COMPILACIÓN: gcc -o posfija posfija.c TADPilaDin.o
			 gcc -o posfija posfija.c TADPilaEst.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADPilaDin.h"
// #include "TADPilaEst.h"
#include <math.h>
/*
int cadParentesis(char cadena[], int tam_cadena);
Descripción: En esta función lo que se realiza es la verificación de la escritura
de los parentesis.
Recibe: char cadena[] (cadena dada por el usuario), int tam_cadena 
(tamaño de la cadena).
Devuelve: int (0 si hay un error, 1 la ejecución termina de manera correcta).
*/
int cadParentesis(char cadena[], int tam_cadena){
	int i,j;

	pila mi_pila; 	//Se declara una pila "mi_pila"
	elemento e1;	//Declaro un elemento "e1"
	Initialize(&mi_pila);	//Inicialización de "mi_pila"
	
	for(i=0;i<tam_cadena;i++){	//Recorrer cada caracter de la cadena 
		if(cadena[i]=='('){ 	//Si el caracter es ( introducirlo a la pila
			e1.c='(';
			Push(&mi_pila,e1);
		}
		else if(cadena[i]==')'){
			if(Empty(&mi_pila))	//Si se intenta extraer un elemento y la pila es vacia Error: P.g. (a+b)*c)
					return 0;
				e1=Pop(&mi_pila);
			}
	}
	
	//Si al terminar de revisar la expresión aún hay elementos en la pila Error: P.g. (a+b)*c(a-c
	if(!Empty(&mi_pila))
		return 0;
	
	//Si la ejecución termina de manera correcta
	Destroy(&mi_pila);	
	return 1;
}

/*
int tipoOperador(elemento e);
Descripción: Da la prioridad a los operadores y si esta en el alfabeto A-Z
Recibe: elemento e (elemento a asignar prioridad).
Devuelve: int (prioridad del elemento dado).
*/
int tipoOperador(elemento e){
	char op; //se declara op para asignarle que es un elemento de tipo char y asi poder realizar la comparación correctamente.
	op = e.c; 
	if(op == '-' || op == '+') //compara si el op es alguno de estos operadores y si se cumple retorna un 2.
		return 2;
	if(op == '*' || op == '/') //compara si el op es alguno de estos operadores y si se cumple retorna un 3.
		return 3;
	if( op == '^') //compara si el op es este operador y si se cumple retorna un 4.
		return 4;
	if(op == ')') //compara si el op es este operador y si se cumple retorna un 1.
		return 1;
	if(op == '(') //compara si el op es este operador y si se cumple retorna un 0.
		return 0;
	if(op>64 && op<91) ///compara si op esta dentro de este rango que es el rango de la tabla ASCII para las letras mayusculas y si se cumple retorna un 6.
		return 6;

	return 5; 
}
/*
void agreparOp(elemento op, pila *X, elemento pos[], int *j, int tipo);
Descripción: Agrega los operadores de forma correcta a la pila 
donde se encontrara la expresión posfija.
Recibe: elemento op (elemento que se ingresara a la pila de posfijo),
pila *X (referencia a la pila), elemento pos[] 
(arreglo de elementos donde se guarda la expresión posfija), 
int *j (referencia al contador del arreglo de la expresion posfija),
int tipo (tipo de operador que se va a ingresar a la pila).
Devuelve: i
Observaciones: Dependiendo de la prioridad del elemento
se realizara una accion, ya sea Push ó Pop;
*/
void agregarOp(elemento op, pila *X, elemento pos[], int *j, int tipo){
	switch(tipo){ //Se hace un switch con el valor de tipo, que se le asigno en la función tipoOperador.
		case 0:		//En caso de que sea 0, significa que es '(' por lo tanto se ingresa el operador, ya que '(' tiene precedencia 0.
			Push(X, op);
		break;
		case 1:		//En caso de que sea 1, significa que es ')' por lo tanto va a hacer el Pop, hasta que en el tope de la pila se encuentre un '('.
			while(tipoOperador(Top(X)) != 0){ //si encuentra a ")" vacia la pila.
				pos[*j] = Pop(X);
				(*j)++;
			}
			Pop(X); //Saca el '('
		break;
		case 2: case 3: case 4: //En cualquiera de los demas operadores se va a realizar un Push si la pila esta vacia o si el tipo de operador que se desea ingresar a la pila es mayor al tipo de operador que se encuentra en el tope de la pila.
			if(Empty(X) == TRUE || tipo > tipoOperador(Top(X))){
				Push(X, op);
			}else{		//Si no es ninguno de los casos anteriores, entonces se va a tener que realizar un pop, solo si la fila no esta vacia o si el tipo de operador que se desea ingresar es menor o igual al tipo de operador que se encuentra en el tope de la pila.
				while(Empty(X) == FALSE && tipo <= tipoOperador(Top(X))){ 
					pos[*j] = Pop(X);
					(*j)++;
				}
				Push(X, op);
			}
		break;	
	}
}
/*
int consultaValor(char c, int valores[]);
Descripción: Consulta el valor de los valores que se asignaron
a las letras dadas por el usuario.
Recibe: char c(letra dada por el usuario), 
int valores[](valores que se desean consultar).
Devuelve: int (valor consultado en la letra).
*/
int consultaValor(char c, int valores[]){
	 //consulta el valor exisntente en el arreglo de valores.
	return valores[c-'A'];
}
/*
float resExpresion(char expPos[], int valores[]);
Descripción: Realiza la evaluación de la expresión posfija.
Recibe: char expPos[](cadena de la expresión postfia), 
int valores[](valores de las letras).
Devuelve: float (resultado de la evaluación postfija).
*/
float resExpresion(char expPos[], int valores[]){
	int c,i; //Declaracion de contadores.
	elemento aux, val, operando1, operando2; //Declaraciones de variables tipo elemento
	pila numeros; //Declaracion de l pila que ayudara a la evaluacion de la expresion postfija
	Initialize(&numeros); //Inicializar pila.

	for(c=0; c<strlen(expPos); c++){ //Inicio del for que se realizara hasta que c sea menor al tamaño de la cadena expPos
		aux.c = expPos[c]; //Se asigna a la variable auxiliar el valor de la expPos en la posicón de c.

		if(tipoOperador(aux) == 6){ //si el elemento que esta en aux es de tipo operador 6 significa que es una letra, por lo tanto entra a la condición.
			val.f = (float)consultaValor(expPos[c], valores); //val es una elemento de tipo flotante, se le asigna el valor que se consulta de la letra que esta en ese momento en expPos[c]
			Push(&numeros, val);		//Ya encontrado el valor deseado, se realiza un push en la pila del valor de val.
		}
		if(tipoOperador(aux) < 5){ //si el elemento que esta en aux es de tipo operador menor que 5 significa que es un operador, por lo tanto entra dentro de la condicion.
			//Se realizara un pop de los dos ultimos operadores que estan en la cima de la pila y se le asignaran a operador1 y operador2 respectivamente.
			operando1 = Pop(&numeros); 	
			operando2 = Pop(&numeros);
			//switch para realizar la operación que sea necesaria, donde a val.f se le asignara el resultado de la operacion que se va a realizar.
			switch(expPos[c]){
				case '+':
					val.f = operando1.f + operando2.f;
				break;

				case '-':
					val.f = operando2.f - operando1.f;
				break;

				case '*':
					val.f = operando1.f * operando2.f;
				break;

				case '/':
					val.f = operando2.f / operando1.f;
				break;

				case '^':
					val.f = pow(operando2.f, operando1.f);
				break;
			}

			Push(&numeros, val);
		}
	}
	//Aqui se revisa si hay algun error, ya que si en la pila numeros, solo queda un elemento el final siginifica que el proceso fue el correcto, pero si hay mas de 1 significa que ocurrio algun error.
	if(Size(&numeros) > 1){ 
		system("cls");
		for(i=0; i<10; i++)
			system("@path && echo ---System protection permision denied---");
		printf("Hubo un error en la redaccion de tu expresion\n");
		return -1;
	}
	val = Pop(&numeros);
	return  val.f;
}	
/*
void tablaValores(char expPos[], int valores[]);
Descripción: Guarda los valores dados por el usuario.
Recibe: char expPos(cadena de expresión postfija), 
int valores[](campo en el cual se va a guardar el número asignado).
Devuelve:
Boservaciones: Si la letra esta repetida no vuelve a pedir
el valor.
*/
void tablaValores(char expPos[], int valores[]){
	int c, valorTemp, pos;
	elemento aux;
	for(c=0; c<strlen(expPos); c++){ //Se inicia el for desde c=0 hasta que sea menor al tamaño de la cadena.
		aux.c = expPos[c];		//a aux se le asigna el valor que este en expPos en la posición de c
		if(tipoOperador(aux) == 6){ //Si el elemento que este en aux es igual a 6 significa que es una letra, por lo tanto entra a la condición.
			pos = expPos[c] - 'A';; //a pos se le va a asignar la posicion que resulte al restar el valor ASCII de la letra guardada en la expPos en la posición de c, menos el valor ASCII de A 
			if(valores[pos] == -1){ //Si valores e -1 significa que NUNCA se le ha asignado un valor.
				printf("Introduce el valor de la variable %c: ", expPos[c]);
				fflush(stdin);
				scanf("%d", &valorTemp);
				valores[expPos[c] - 'A'] = valorTemp;
			}
		}
	}
}
//PROGRAMA PRINCIPAL
int main(){
	//Declaracion de variables
	int k, m, tam, i, jpos=0, x=10, valores[26];
	char cad[100], cadPos[100];		//cad --> la que da el usuario. cadPos --> es donde se va a escribir la expresión porfija
	elemento arrElemento[100], pos[100];		// arrElemento --> Arreglo de elementos donde se copiara la cadena dada por el usuario, pos--> Arreglo donde se guardara la expresión postfija.
	float res;		// Variable tipo flotante al que se le asignara el resultado de la evaluación de la expresión dada.
	printf("Ingresa la expresion infija: ");
	scanf("%s", &cad);		//Se captura la cadena dada por el usuario.
	system("cls");		//Limpia la pantalla y vuelve a escribir la cadena dada por el usuario.
	printf("Expresion infija: %s\n", cad);
	tam = strlen(cad);		//Guarda en tam el valor de la cadena da da por el usuario
	// printf("%d\n", tam);
	for (i = 0; i < tam; ++i){		//Se captura la cadena y se convierte a cadena de tipo elemento.
		arrElemento[i].c = cad[i];
	}

	//Se valida la escritura de la cadena invocado a la función cadParentesis 
	if(cadParentesis(cad, tam) == 0){ //pregunta si el valor que retorno la función es cero, si sí es cero, es que hubo un error en la escritura de la función.
		printf("ERROR: expresion mal escrita\n");
		exit(0);
	}

	pila p; 
	Initialize(&p); //Se inicializa pila para poderar operar sobre las prioridades de los operandos.

	//Se evalua toda la funcion para convertirla a posfija
	for(i=0; i<tam; i++){		//se comienza un ciclo for con i=0 hasta que sea menor al tamaño de la cadena ya y comienza a recorrer todo el arreglo verificando si los elementos que estan dentro de ella son operadores o letras.
		if(tipoOperador(arrElemento[i]) < 5){		
			agregarOp(arrElemento[i], &p, pos, &jpos, tipoOperador(arrElemento[i]));		//Si el elemento es operador se invoca a la función agregarOp, que agregara el operador a la pila que se creo anteriormente.
		}
		else{ //Si el elemento es una letra se agrega automaticamente a la cadena pos. (que es la cadena donde se guardara la expresión postfija)
			pos[jpos] = arrElemento[i];
			jpos++;
		}
	}

	while(Empty(&p) == FALSE){
		pos[jpos] = Pop(&p);
		jpos++;
	}
	pos[jpos].c = '\0';

	//Imprime la cadena posfija
	for(i=0; pos[i].c != '\0'; i++){
		cadPos[i] = pos[i].c;
	}
	cadPos[i] = '\0';

	strupr(cadPos); //Convierte los caracteres a mayusculas para no tener problema con cadPos

	for(i=0; i<26; i++)		//Asigna el valor -1 a todas las celdas del arreglo valores para idnicar que no se le ha asignado ningun valor.
		valores[i] = -1;

	printf("Expresion postfijas: %s\n", cadPos);		//Imprime la expresión en postfijo.


	tablaValores(cadPos, valores);

	printf("\n\n-------------------------------------\nResultado: %.2f\n", resExpresion(cadPos, valores));
	Destroy(&p);
}
