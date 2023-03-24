#ifndef TREE_H
#define TREE_H

#define STR 1
#define SET 2
#define LIST 3

struct dataType{
	int nodeType;
	union{
		char* dataStr;
		struct{
			struct dataType* data;
			struct dataType* sig;
		};
	};
};

struct dataType* creaData(char*); //Analiza el primer caracter y setea el tipo de nodo. Si es tipo STR lo carga, si no, dataType se mantiene NULL;
struct dataType* creaElemento(char* String); //crea elementos //consultar
void creaTree(struct dataType**,char*); //Invoca creaTreeList o creaTreeSet 
void creaTreeList(struct dataType**,char*); //Trata los datos ingresados como requieren ser tratados para una lista
void creaTreeSet(struct dataType**,char*); //Trata los datos ingresados como requieren ser tratados para un conjunto
void muestraTree(struct dataType*); //Imprime el string resultado de leer el arbol
char* readTree(struct dataType*); //le da formato de salida a la traduccion de los nodos del arbol
char* TransNodes(struct dataType*); //traduce los nodos de una determinada raiz

short emptyRoot(struct dataType*);
short emptyData(struct dataType*);


short typeTree(struct dataType*);
short cmpData(struct dataType*,struct dataType*);


//operaciones binarias
struct dataType* unionSet(struct dataType*,struct dataType*); 
struct dataType* intersecSet(struct dataType*,struct dataType*);
struct dataType* diffSet(struct dataType*,struct dataType*);
short emptySet(struct dataType* Root);
void pushTop(struct dataType**,struct dataType*); // arreglado, no agrega repetidos en conjuntos
void pushCab(struct dataType**,struct dataType*); // arreglado, no agrega repetidos en conjuntos
int findElement(struct dataType*,struct dataType*);// me devuelve una posicion, lo utilizo para remover un elemento
short inSet(struct dataType*,struct dataType*); // me recorre el arbol en busca de un elemento repetido, lo utilizo para conjuntos
void removeElement(struct dataType**,struct dataType*);

//operaciones unitarias
int tamTree(struct dataType*);   //me puede determinar el tamaño de una lista de igual manera


struct dataType* getData(struct dataType*,int nodeP); //para trabajar con el AF

/*---------------------------------------------------*/

char* clean(char *s); //va a quitar carateres de conjunto
void getElem(char **,char**);

#endif
