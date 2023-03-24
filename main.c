//SALINAS LAVAYEN ROBERTO JAVIER - ARGUELLO FRANCISCO CARLOS

#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

#define TamMaxStr 1000
#define CardListaAF 5
#define Estados 0
#define Alfabeto 1
#define Transiciones 2
#define EstadoInicial 3
#define EstadosAceptacion 4

void menu0();
void menu1();
void menu2();
void menu3();
char* ingresaCadena();
void leeCad(char*);


short ctrlAF(struct dataType*);
void showAf(struct dataType*);
void computarString(struct dataType*,char*);
struct dataType* delta(struct dataType*,struct dataType*,char);



/*
//acepta cadenas ba-....
//char* StringA = "[{p0,p1,p2},{a,b},{[p0,a,{}],[p0,b,{p2}],[p1,a,{p0}],[p1,b,{p1,p2}],[p2,a,{p0,p1,p2}],[p2,b,{}]},{p0},{p1}]";
//acepta cadenas 
//char* StringA = "[{q0,q1,q2,q3,q4,q5},{0,1},{[q0,0,{q0}],[q0,1,{q0,q1,q2}],[q1,0,{q2,q3}],[q1,1,{}],[q2,0,{}],[q2,1,{q4}],[q3,0,{q5}],[q3,1,{}],[q4,0,{q5}],[q4,1,{}],[q5,0,{q5}],[q5,1,{q5}]},{q0},{q5}]";
//ejemplo de la profe
//char* StringA = "[{q0,q1,q2},{0,1},{[q0,0,{q0,q1}],[q0,1,{q0}],[q1,0,{}],[q1,1,{q2}],[q2,0,{}],[q2,1,{}]},{q0},{q2}]";
*/

int main(){
	struct dataType* treeA = NULL;
	struct dataType* treeB = NULL;
	struct dataType* result = NULL;
	struct dataType* AF = NULL;

	char* StringA = NULL;
	char* StringB = NULL;
	char* StringAux = NULL;
	char* StringAF = NULL;
	
	short op0;
	short op3;
	short op1;
	short op2;

	
	do{
		menu0();
		scanf("%hd",&op0);
		__fpurge(stdin);
		switch(op0){
		case 1:
			do{
				menu1();
				scanf("%hd",&op1);
				__fpurge(stdin);
				switch(op1){
				case 1:
					treeA = NULL;
					StringA = ingresaCadena();
					printf("\nString ingresado: %s\n",StringA);
					creaTree(&treeA,StringA);
					break;
				case 2:
					treeB = NULL;
					StringB = ingresaCadena();
					printf("\nString ingresado: %s\n",StringB);
					creaTree(&treeB,StringB);
					break;
				case 3:
					result = unionSet(treeA,treeB);
					if(result != NULL){
						muestraTree(result);
					}
					break;
				case 4:
					result = intersecSet(treeA,treeB);
					if(result != NULL){
						muestraTree(result);
					}
					break;
				case 5:
					result = diffSet(treeA,treeB);
					if(result != NULL){
						muestraTree(result);
					}
					break;
				case 6:
					do{
						menu2();
						scanf("%hd",&op2);
						__fpurge(stdin);
						switch(op2){
						case 1:
							StringAux = ingresaCadena();
							printf("\nElemento a ingresarse: %s\n",StringAux);
							result = creaElemento(StringAux);
							pushCab(&treeA,result);
							break;
						case 2: 
							StringAux = ingresaCadena();
							printf("\nElemento a ingresarse: %s\n",StringAux);
							result = creaElemento(StringAux);
							pushTop(&treeA,result);
							break;
						case 3: 
							StringAux = ingresaCadena();
							printf("\nElemento a buscar: %s\n",StringAux);
							result = creaElemento(StringAux);
							if(findElement(treeA,result) != -1){
								printf("\nEl elemento se encuentra en la lista.\n\n");
							}
							else{
								printf("\nEl elemento no se encuentra en la lista.\n\n");
							}
							break;
						case 4: 
							StringAux = ingresaCadena();
							printf("\nElemento a remover: %s\n\n",StringAux);
							result = creaElemento(StringAux);
							removeElement(&treeA,result);
							break;
						case 5:
							if(emptyRoot(treeA) == 1){
								printf("\nEl arbol tiene %d elementos.\n",tamTree(treeA));
							}
							else{
								printf("\nNo existe arbol\n");
							}
							break;
						case 6:
							muestraTree(treeA);
							break;
						case 0: 
							break;
						default:
							printf("Ingrese un valor permitido.\n");
							break;
						}
					} while(op2 != 0);
					break;
				case 7: 
					muestraTree(treeA);
					break;
				case 8: 
					muestraTree(treeB);
					break;
				default:
					printf("Ingrese un valor permitido.\n");
					break;
				case 0:
					break;
				}
			}
			while(op1 != 0);
			break;
		case 2:
			do{
				menu3();
				scanf("%hd",&op3);
				__fpurge(stdin);
				switch(op3){
				case 1:
					printf("\nAF = [Q,a,d,q0,F]\n");
					StringAF = ingresaCadena();
					printf("\nString ingresado: %s\n",StringAF);
					//para prueba, acepta cadenas que terminen en -01
					//StringAF = "[{p0,p1,p2},{a,b},{[p0,a,{}],[p0,b,{p2}],[p1,a,{p0}],[p1,b,{p1,p2}],[p2,a,{p0,p1,p2}],[p2,b,{}]},{p0},{p1}]";
					creaTree(&AF,StringAF);
					if(ctrlAF(AF) == 1){
						showAf(AF);
					}
					else{
						printf("Algo anda mal, ingrese otra vez el AF.\n");
					}
					break;
				case 2:
					StringAF = ingresaCadena();
					computarString(AF,StringAF);
					break;
				default:
					printf("Ingrese un valor permitido.\n");
					break;
				case 0:
					break;
				}
			}
			while(op3 != 0);
			break;
		default:
			printf("Ingrese un valor permitido.\n");
		case 0:
			break;
		}
	} while(op0 != 0);
	
	
	
	
	return 0;
}

void menu0(){
	printf("--- MENU INICIAL ---\n\n");
	printf("1)_Operaciones bascias.\n");
	printf("2)_Operar AF.\n");
	printf("0)_Salir\n");
	printf("Su opcion:");
}
	
void menu3(){
	printf("---MENU 3---\n\n");
	printf("1)_Ingresar un AF.\n");
	printf("2)_Ingresar cadena en AF.\n");
	printf("0)_Salir\n");
	printf("Su opcion: ");
}
	
void menu1(){
	printf("---MENU 1---\n\n");
	printf("1)_Ingresar arbol A\n");
	printf("2)_Ingresar arbol B\n");
	printf("3)_Crear arbol AuB\n");
	printf("4)_Crear arbol AnB\n");
	printf("5)_Crear arbol A-B\n");
	printf("6)_Operar solo con arbol A\n");
	printf("7)_Ver arbol A.\n");
	printf("8)_ver arbol B.\n");
	printf("0)_Salir\n");
	printf("Su opcion: ");
}
	
void menu2(){
	printf("---MENU 2---\n\n");
	printf("1)_Agregar elemento por cabeza.\n");
	printf("2)_agrega elemento por cola/arriba\n");
	printf("3)_Buscar elemento.\n");
	printf("4)_Remover elemento.\n");
	printf("5)_Calcular el tamaño del arbol.\n");
	printf("6)_muestra arbol A.\n");
	printf("0)_salir.\n");
	printf("Su opcion: ");
}

char* ingresaCadena(){
	char* string = NULL;
	string = (char*) malloc(sizeof(char)*255);
	printf("\nIngrese una cadena:\n");
	__fpurge(stdin);
	leeCad(string);
	return string;
}
	
void leeCad(char* String){
	int j,m;
	m = getchar();
	if(m != EOF){
		j = 0;
		if(m != '\n'){
			String[j] = m;
			j++;
		}
		m = getchar();
		while((j < TamMaxStr-1) && (m != EOF) && (m != '\n')){
			String[j] = m;
			m = getchar();
			j++;
		}
		String[j] = '\0';
		
		while((m != EOF) && (m != '\n')){
			m = getchar();
		}
	}
	else{
	String[0] = '\0';	
	}
}

	
short ctrlAF(struct dataType* AF ){
	short flag = 0;
	if(tamTree(AF) == CardListaAF && typeTree(AF) == LIST){
		if((emptyData(AF) == 1 && typeTree(AF->data) == SET)){  //estados
			AF = AF->sig;
			if(emptyData(AF) == 1 && typeTree(AF->data) == SET){ //alfabeto
				AF = AF->sig;
				if(emptyData(AF) == 1 && typeTree(AF->data) == SET){ //transiciones
					AF = AF->sig;
					if(typeTree(AF->data) == SET){ //estados de aceptacion
						AF = AF->sig;
						if(emptyData(AF) == 1 && typeTree(AF->data) == SET){ //estado inicial
							flag = 1;
						}
					}
				}
			}
		}
	}
	return flag;
}

void showAf(struct dataType* AF){
	char* Q = NULL;
	char* ALF = NULL;
	char* DEL = NULL;
	char* F = NULL;
	char* q0 = NULL;
	Q = readTree(getData(AF,Estados));
	ALF = readTree(getData(AF,Alfabeto));
	DEL = readTree(getData(AF,Transiciones));
	F = readTree(getData(AF,EstadosAceptacion));
	q0 = readTree(getData(AF,EstadoInicial));
	printf("AUTOMATA FINITO INGRESADO:\n\nEstados: %s\nAlfabeto: %s\nTransiciones: %s\nEstados de aceptacion: %s\nEstadios iniciales: %s\n",Q,ALF,DEL,F,q0);
}

void computarString(struct dataType* AF, char* cadena){  
	struct dataType* conjuntoFinal = NULL;
	struct dataType* conjuntoAuxiliar = NULL;
	struct dataType* devuelto = NULL;
	int tam = 0;//aux[0] = *(*cadena+tam);
	short fl = 0;
	
	//conjuntoFinal = creaData("{");                     //coloco al estado inicial 
	//conjuntoFinal->data = getData(AF,EstadoInicial);   //dentor de un conjunto      CONSULTAR
	conjuntoFinal = getData(AF,EstadoInicial);
	printf("Estado inicial -> %s\n",readTree(getData(AF,EstadoInicial)));
	
	
	do{
		
		printf("\nconjunto de Partida->:%s\n",readTree(conjuntoFinal));
		creaTree(&conjuntoAuxiliar,"{}");
		
		
		while(emptyRoot(conjuntoFinal) == 1){
			printf("\nEstado a analizar ->%s\n",readTree(conjuntoFinal->data));
			
			devuelto = delta(getData(AF,Transiciones),conjuntoFinal->data,*(cadena+tam));
			conjuntoAuxiliar = unionSet(conjuntoAuxiliar,devuelto);
			
			conjuntoFinal = conjuntoFinal->sig;
		}
		conjuntoFinal = conjuntoAuxiliar;
		if(emptySet(conjuntoFinal) == 0){    // Si mi conjunto final no es un conjunto vacio sigo procesando
			conjuntoAuxiliar = NULL;
			tam++;
		}
		else{ // si es vacio, ya no me interesa procesar la cadena
			fl = 1;
		}
		
	}
	while(tam < strlen(cadena) && fl == 0); 
	
	if(emptySet(conjuntoFinal) == 0){
		printf("\nConjunto resultado de delta -> %s n %s Conjunto de estados de aceptacion\n",readTree(conjuntoFinal),readTree(getData(AF,EstadosAceptacion)));
		printf("\n\tInterseccion entre conjuntos -> %s\t\n",readTree(intersecSet(conjuntoFinal,getData(AF,EstadosAceptacion))));
		if(emptySet(intersecSet(conjuntoFinal,getData(AF,EstadosAceptacion))) == 0){
			printf("\nCadena Aceptada. %s pertenece al lenguaje del AF\n",cadena);
		}
		else{
			printf("\nCadena Rechazada. %s no pertenece al lenguaje del AF\n",cadena);
		}
	}
	else{
		printf("\nCadena Rechazada. %s no pertenece al lenguaje del AF\n",cadena);
	}
}

struct dataType* delta(struct dataType* transiciones,struct dataType* q,char c){
	struct dataType* transData = NULL;
	struct dataType* devuelto = NULL;
	char* aux = (char*) malloc(sizeof(char)*255);
	short fl = 0;
	aux[0] = c;
	while(transiciones != NULL && fl == 0){
		transData = transiciones->data;
		
		printf("\n\testado en delta -> %s == %s <-estado analizado\n",readTree(transData->data),readTree(q));
		if(cmpData(transData->data,q) == 1){
			printf("\nCaracter a analizar ->%s\n",aux);
			
			transData = transData->sig;
			
			printf("\n\t\tcaracter en delta-> %s == %s <-caracter analizado\n",(transData->data)->dataStr,aux);
			if(strcmp(((transData->data)->dataStr),aux) == 0){
				
				transData = transData->sig;
				devuelto = transData->data;
				fl = 1;
				printf("\n\t\t\tEstado devuelto -> %s\t\t\n",readTree(devuelto));
			}
			else{
				printf("\n\t\tLos caracteres no coinciden. No se sigue analizando.\t\t\n");
			}
		}
		else{
			printf("\n\tLos estados no coinciden. NO se sigue analizando.\t\n");
		}
		transiciones = transiciones->sig;
	}
	return devuelto; 
}
	


