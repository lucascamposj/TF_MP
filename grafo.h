  typedef struct vertice* p_vertice;
typedef struct aresta* p_aresta;

typedef struct vertice
{
	int ch_vertice;
	int valor;

	p_vertice prox;

	p_aresta primeiro;
	p_aresta ultimo;
} tp_vertice;

typedef struct aresta{
	int ch_aresta;
	p_vertice vizinho;
	
	p_aresta prox;
} tp_aresta;

typedef struct grafo 
{	
	char nome[100];

	p_vertice primeiro;
	p_vertice ultimo;
} tp_grafo;

typedef enum {
	TRUE,FALSE
} boolean;

tp_grafo *cria_grafo(char *nome);

/*retorna o nome do grafo G*/
char *retorna_nome_grafo(tp_grafo *G);

/*destrói grafo g*/
void destroi_grafo(tp_grafo *G);

/*verifica se x e y sao adjacentes em G*/
boolean adjacente(tp_grafo *G, int x, int y);

/* retorna lista de todos os vértices que podem ser visitados a partir de x
(existe uma aresta que vai de x para este vértice)*/
void vizinhos(tp_grafo *G,int x);


/*adiciona vértice x no grafo G*/
void adiciona_vertice(tp_grafo *G, int x);


/*remove vértice x do grafo G*/
void remove_vertice(tp_grafo *G,int x);

/*no grafo G adiciona uma aresta de x para y*/
void adiciona_aresta(tp_grafo *G,int x,int y);

/*remove a aresta que vai de x para y*/
void remove_aresta(tp_grafo *G,int x,int y);

/*retorna o valor associado com o vértice x*/
int retorna_valor_vertice(tp_grafo *G,int x);

/*coloca valor v no vértice x em G*/
void muda_valor_vertice(tp_grafo *G,int x,int v);

/*retorna valor da aresta x,y em G*/
int retorna_valor_aresta(tp_grafo *G,int x,int y);

/*coloca o valor v na aresta x,y em G */
void muda_valor_aresta(tp_grafo *G,int x, int y, int v);

/*
	FUNCOES EXTRAS
*/

boolean grafo_vazio(tp_grafo G);

boolean vertice_isolado(p_vertice A);
