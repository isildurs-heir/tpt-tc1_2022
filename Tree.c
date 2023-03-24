#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----CODIGO PARA ARBOL-----*/

struct dataType* creaData(char *String){
	struct dataType* nvoNodo;
	nvoNodo = (struct dataType*) malloc(sizeof(struct dataType)*10);
	if(String[0] == 123){ 
		nvoNodo->nodeType = SET;
		nvoNodo->data = NULL;
		nvoNodo->sig = NULL;
	}
	else{
		if(String[0] == 91){  //[
			nvoNodo->nodeType = LIST;
			nvoNodo->data = NULL;
			nvoNodo->sig = NULL; 
		}
		else{  //es otra cosa
			nvoNodo->nodeType = STR;
			nvoNodo->dataStr = String;
		}
	}
	return nvoNodo;
}

void creaTree(struct dataType* *Root, char* String){  
	if((*Root) == NULL){
		*Root = creaData(String);
	}
	if(typeTree(*Root) == 2){
		creaTreeSet(&*Root,clean(String));
	}
	else{
		if((typeTree(*Root) == 3)){
			creaTreeList(&*Root,clean(String));
		}
	}
}
	
void creaTreeSet(struct dataType* *Root, char* String){
	struct dataType* auxRoot = NULL;
	struct dataType* nvaData = NULL;
	struct dataType* sigNodo = NULL;
	auxRoot = *Root;
	char* Rest;
	char* Extr;

	Rest = String;
	getElem(&Rest,&Extr);
	nvaData = creaData(Extr);
	if((typeTree(nvaData) != 1)){ //si no es STR se trata como tree
		creaTree(&nvaData,Extr);
	}
	auxRoot->data = nvaData;
	
	while(Rest != NULL){
		getElem(&Rest,&Extr);
		nvaData = creaData(Extr);
		
		if(typeTree(nvaData) != 1){
			creaTree(&nvaData,Extr);
		}
		if(inSet(*Root,nvaData) == 0){    // SI EL ELEMENTO NO ESTA EN LA LISTA
			sigNodo = creaData("{");      //CREO UN NODO SIGUIENTE 
			auxRoot->sig = sigNodo;
			auxRoot = auxRoot->sig;       //ACTUALIZO MI AUXROOT			
			auxRoot->data = nvaData;       //ENLAZO EL DATO
		}
	}
	
}
	
void creaTreeList(struct dataType* *Root, char* String){
	struct dataType* auxRoot = NULL;
	struct dataType* nvaData = NULL;
	struct dataType* sigNodo = NULL;
	auxRoot = *Root;
	char* Rest;
	char* Extr;
	
	Rest = String;
	getElem(&Rest,&Extr);
	nvaData = creaData(Extr);
	if(typeTree(nvaData) != 1){
		creaTree(&nvaData,Extr);
	}
	auxRoot->data = nvaData;
	
	while(Rest != NULL){
		getElem(&Rest,&Extr);
		nvaData = creaData(Extr);
		
		if(nvaData->nodeType != STR){
			creaTree(&nvaData,Extr); //crea elemento (?
		}
		sigNodo = creaData("[");      //CREO UN NODO SIGUIENTE 
		auxRoot->sig = sigNodo;
		auxRoot = auxRoot->sig;       //ACTUALIZO MI AUXROOT
		auxRoot->data = nvaData;
	}
	
}


/*-----   MUESTRA DE ARBOL   -----*/
	
void muestraTree(struct dataType* Root){
	char* String = NULL;
	String = (char*)malloc(sizeof(char)*1000);
	if(emptyRoot(Root) == 1){
		if(typeTree(Root) != 1){
			String = readTree(Root);
		}
		else{
			String = Root->dataStr;
		}
		printf("\nARBOL : %s\n",String);
	}
	else{
		printf("\nNo existe arbol para mostrar\n");
	}
}
	
char* readTree(struct dataType* Root){ //lee abroles
	char* String = NULL;
	char* aux = NULL;
	String = (char*)malloc(sizeof(char)*1000);
	if(typeTree(Root) == 2){   // abro el formato al string de salida"   
		String[0] = '{';
		String[1] = '\0';
	}
	else{
		if(Root->nodeType == LIST){
			String[0] = '[';
			String[1] = '\0';
		}
	}
	aux = TransNodes(Root);
	strcat(String,aux);  //concateno el resultado de la traduccion de los nodos
	if(String[0] == 123){  //cierro el formato de salida
		strcat(String,"}");
	}
	else{
		if(String[0] == 91){
			strcat(String,"]");
		}
		
	}
	return String;
	
}
	
char* TransNodes(struct dataType* nodo){ //transcribe nodos
	char* String = NULL;
	char* aux = NULL;
	
	String = (char*)malloc(sizeof(char)*1000);
	String[0] = '\0';   //Un string vacio
	while(nodo != NULL){ // voy a recorrer la "lista enlazada" de nodos 
		if(nodo->nodeType == STR){ // Si es un tipo de dato simple
			strcat(String,(nodo->dataStr));  //concateno el dato del nodo con el string a mostrar
		}
		else{ //Si no, leo un arbol de nuevo
			aux = readTree(nodo->data);  
			strcat(String,aux);
		}
		strcat(String,",");
		nodo = nodo->sig;
	}
	String[strlen(String)-1] = '\0'; // Le coloco un fin de linea al String consultar
	
	return String;
}
	
/*-----CODIGO PARA OPERACIONES-----*/
	
struct dataType* unionSet(struct dataType* treeA, struct dataType* treeB){  //vacio  y vacio = vacio.
	struct dataType* treeC = NULL;
	if((emptyRoot(treeA) == 1) && (emptyRoot(treeB) == 1)){
		if(typeTree(treeA) == 2 && typeTree(treeB) == 2){
			creaTree(&treeC,"{}");
			if(emptySet(treeA) == 0){
				treeC = creaData("{");
				while(emptyRoot(treeA) == 1){
					pushTop(&treeC,treeA->data);
					treeA = treeA->sig;
				}
			}
			if(emptySet(treeB) == 0){
				if(emptySet(treeC) == 1)
					treeC = creaData("{");
				while(emptyRoot(treeB) == 1){
					if(inSet(treeC,treeB->data) == 0){
						pushTop(&treeC,treeB->data);
					}
					treeB = treeB->sig;
				}
				
			}
		}
		else{
			printf("No puede realizarse union de un conjunto y una lista.\n");
		}
	}
	else{
		printf("\nNo puede realizarse union si no existen arboles.\n");
	}
	return treeC;
}
	
struct dataType* intersecSet(struct dataType* treeA, struct dataType* treeB){
	struct dataType* treeC = NULL;
	int fl = 0;
	if((emptyRoot(treeA) == 1) && (emptyRoot(treeB) == 1)){
		if(typeTree(treeA) == 2 && typeTree(treeB) == 2){
			if(emptySet(treeA) == 0 && emptySet(treeB) == 0){
				treeC = creaData("{");
				while(emptyRoot(treeB) == 1){
					if(inSet(treeA,treeB->data) == 1){
						pushTop(&treeC,treeB->data);
						fl = 1;
					}
					treeB = treeB->sig;
				}
				if(fl == 0){    // atado con alambre
					creaTree(&treeC,"{}");
				}
			}
			else{
				creaTree(&treeC,"{}");
			}
		}
		else{
			printf("\nNo puede realizarse interseccion de un conjunto y una lista.\n");
		}
	}
	else{
		printf("\nNo puede realizarse interseccion si no existen arboles.\n");
	}
	
	return treeC;
}
	
struct dataType* diffSet(struct dataType* treeA, struct dataType* treeB){   // interseccion a con no b
	struct dataType* treeC = NULL;
	if((emptyRoot(treeA) == 1) && (emptyRoot(treeB) == 1)){
		if(typeTree(treeA) == 2 && typeTree(treeB) == 2){
			if(emptySet(treeA) == 0){
				treeC = creaData("{");
				if(emptySet(treeB) == 0){
					while(emptyRoot(treeA) == 1){
						if(inSet(treeB,treeA->data) == 0){    
							pushTop(&treeC,treeA->data);
						}
						treeA = treeA->sig;
					}
				}
				else{
					treeC = treeA;
				}
				if(emptyData(treeC) == 0) {
					creaTree(&treeC,"{}");
				}
			}
			else{
				creaTree(&treeC,"{}");
			}
		}
		else{
			printf("\nNo puede realizarse diferencia de un conjunto y una lista.\n");
		}
	}
	else{
		printf("\nNo puede realizarse diferencia si no existen arboles.\n");
	}
	return treeC;
}

short inSet(struct dataType* Root, struct dataType* elemento){ // reviso todo root buscando el elemento
	short in = 0;  //NO ESTA
	do{
		if(cmpData(elemento,Root->data) ==  1){
			in = 1;	//ESTA
		}
		Root = Root->sig;
	}
	while(emptyRoot(Root) == 1 && in != 1);
	return in;
}
	
	
short emptyData(struct dataType* Root){
	if(Root->data != NULL){
		return 1;
	}
	return 0; //vacia
}

short emptyRoot(struct dataType* Root){
	if(Root != NULL){
		return 1;
	}
	return 0;   //VACIA
}

struct dataType* creaElemento(char* String){  //elementos para insertar
	struct dataType* nvaData = NULL;
	creaTree(&nvaData,String);
	return nvaData;
}
	
void pushCab(struct dataType* *Root, struct dataType* elemento){  //root no tiene que ser null, es decir tiene que estar seteado cuanto menos
	struct dataType* nvaData = NULL;
	if(emptyRoot(*Root) == 1){
		if(emptyData(*Root) == 1){
			if(typeTree(*Root) == 2){  
				nvaData = creaData("{");
			}
			else{
				nvaData = creaData("[");
				
			}
			nvaData->data = elemento;
			nvaData->sig = (*Root);   
			(*Root) = nvaData;
		}
		else{
			(*Root)->data = elemento;
		}
	}
	else{
		printf("\nNo se puede ingresar elementos a un arbol que no existe.\n");
	}
}


void pushTop(struct dataType* *Root, struct dataType* elemento){  //root no tiene que ser nul, es decir tiene que estar seteado cuanto menos
	struct dataType* auxRoot;
	if(emptyRoot(*Root) == 1){
		if(emptyData(*Root) == 1){
			auxRoot = *Root;
			while(auxRoot->sig != NULL){  //si trato como posible raiz a todo elemento del arbol, aqui posiblemente pueda usar emptyRoot(auxRoot->sig) == 1 (?
				auxRoot = auxRoot->sig;
			}
			if(typeTree(*Root) == 2){  
				auxRoot->sig = creaData("{");
			}
			else{
				auxRoot->sig = creaData("[");
				
			}
			auxRoot = auxRoot->sig;
			auxRoot->data = elemento;
		}
		else{
			(*Root)->data = elemento;
		}
	}
	else{
		printf("\nNo se puede ingresar elementos a un arbol que no existe.\n");
	}
	
	
	auxRoot = NULL;
	free(auxRoot);
}
	
int tamTree(struct dataType* Root){
	int cnt = 0;
	while(Root != NULL){
		cnt++;
		Root = Root->sig;
	}
	return cnt;
}
	
short cmpData(struct dataType* A, struct dataType* B){
	char* aString = NULL;
	char* bString = NULL;
	
	aString = TransNodes(A);
	bString = TransNodes(B);
	
	
	if(strcmp(aString,bString) == 0){
		if(typeTree(A) == typeTree(B)){  //resuelve el problema al analizar
			return 1;					//{1,2,3} y [1,2,3] por ejemplo
		}								//es decir, son iguales si son del mismo tipo y tienen el mismo contenido
		return 0;
	}
	else{
		return 0;
	}
}
	
short typeTree(struct dataType* Root){  //me devuelve el tipo de abrol con el que estoy trabajando, no se si es necesario
	return (Root->nodeType);
}
	
int findElement(struct dataType* Root, struct dataType* elemento){
	struct dataType* auxRoot = NULL;
	int pos = 0;
	if(emptyRoot(Root) == 1){
		auxRoot = Root;
		while(auxRoot != NULL && cmpData(auxRoot->data,elemento) == 0){
			auxRoot = auxRoot->sig;
			pos++;
		}
		if(auxRoot == NULL){
			return -1;
		}
		else{
			return pos;
		}
	}
	else{
		return -1;
	}
}
	
void removeElement(struct dataType* *Root,struct dataType* elemento){  //solo tiene que aplicarse a listas!!!!
	struct dataType* ant = NULL;
	struct dataType* prox = NULL;
	int pos = findElement(*Root,elemento);
	if(pos != -1){
		ant = NULL;
		prox = (*Root);
		while(pos-1 >= 0){
			ant = prox;
			prox = prox->sig;
			pos--;
		}
		if(emptyRoot(ant) == 1){
			ant->sig = prox->sig;
		}
		else{
			ant->sig = NULL;
		}
		
	}
	else{
		printf("El elemento no se encuentra en el arbol. No se puede eliminar.\n");
	}
}
	
struct dataType* getData(struct dataType* Root, int nodeP){
	struct dataType* aux;
	while(nodeP != 0){
		Root = Root->sig;
		nodeP--;
	}
	aux = Root;
	return aux->data;
}
	
short emptySet(struct dataType* Root){
	Root = Root->data;
	if((Root->dataStr)[0] == '\0'){
		return 1; //vacio
	}
	else{
		return 0; //no vacio
	}
}
	
/*-----CODIGO PARA CADENAS-----*/

char * clean(char* s){
	int i = 1;
	char* aux;
	aux = (char*) malloc(sizeof(char)*255);
	while(s[i] != '\0'){
		aux[i-1] = s[i];
		i++;
	}
	aux[i-2] = '\0';
	return aux;
}

void getElem(char**s, char**aux){
	char* s_aux;
	int i=0;
	int cont_abre_l=0;
	int cont_cierra_l=0;
	int cont_abre_c=0;
	int cont_cierra_c=0;
	int j,salir;
	
	*aux=(char*) malloc(sizeof(char)*255); 
	s_aux=(char*) malloc(sizeof(char)*255);
	if ((*s)[0]!='{' && (*s)[0]!='['){
		while ((*s)[i]!='\0' && (*s)[i]!=',') {
			(*aux)[i]=(*s)[i];
			i++;
		}
		(*aux)[i]='\0';
	} else {
		salir=0;
		while ((*s)[i]!='\0' && !salir) {
			(*aux)[i]=(*s)[i];
			switch ((*s)[i]) {
			case '{':
				cont_abre_l++;
				break;
			case '[':
				cont_abre_c++;
				break;	
			case '}':
				cont_cierra_l++;
				break;
			case ']':
				cont_cierra_c++;
				break;
			}
			if (cont_abre_l-cont_cierra_l==0 && cont_abre_c-cont_cierra_c==0) 
				salir=1;
			i++;
		}
		(*aux)[i]='\0';
	}
	i++;
	if (i<strlen(*s)) {
		j=0;
		while ((*s)[i]!='\0'){
			s_aux[j]=(*s)[i];
			j++;
			i++;
		}
		s_aux[j]='\0';
		*s=s_aux;
	} else *s=NULL;
}
