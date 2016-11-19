#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "grafo.h"

/*
	FUNCOES
*/
/*******************************************************
*Função: Cria Grafo
*Descrição
*	Inicializa uma estrutura de um Grafo.
*	Nomeia o grafo inicializado com a string de entrada.
*Parâmetros
*	nome - string referente ao nome do Grafo.
*Valor retornado
*	G - ponteiro para a estrutura Grafo inicializada.
*Assertiva de entrada
*	A variável nome não pode ter o valor NULL.
*Assertiva de saida
*	O ponteiro G não pode ter valor NULL.
*********************************************************/

tp_grafo *cria_grafo(char *nome)
{
	assert(nome);
	tp_grafo *G;

	G = (tp_grafo *)malloc(sizeof(tp_grafo));
	assert(G);

	assert(strcpy(G->nome, nome));

	G->primeiro = NULL;
	G->ultimo = G->primeiro;

	return G;
}
/*******************************************************
*Função: Retorna nome do Grafo.
*Descrição
*	Retorna o nome do grafo, presente dentro da estrutura dada na entrada.
*Parâmetros
*	G - Ponteiro para a estrutura Grafo que se deseja obter o nome.
*Valor retornado
*	Retorna o ponteiro para a string do nome do grafo.
*Assertiva de entrada
*	A estrutura de grafo necessita estar inicializada, não possuindo o valor NULL.
*Assertiva de saida
*	O ponteiro para a string não pode ter valor NULL.
*********************************************************/

char *retorna_nome_grafo(tp_grafo *G)
{
	assert(G);

	printf("\nNome do Grafo: %s\n", G->nome);
	
	assert(G->nome);
	return G->nome;
}

/*******************************************************
*Função: Destroi Grafo
*Descrição
*	Realiza a liberação correta de memória de um Grafo.
*Parâmetros
*	G - Ponteiro para uma estrutura de grafo.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

void destroi_grafo(tp_grafo *G)
{
	p_vertice v_aux = G->primeiro, v_aux2;
	p_aresta a_aux, a_aux2;

	assert(G);
	/*verifica fim da lista de vertices*/
	while(v_aux != NULL)
	{
		a_aux = v_aux->primeiro;
		/*verifica fim da lista de arestas*/         
		while(a_aux != NULL){
			a_aux2 = a_aux;
			a_aux = a_aux->prox;
			free(a_aux2);
		}
		v_aux2 = v_aux;
		v_aux = v_aux->prox;
		free(v_aux2);
	}
	free(G);
}

/*******************************************************
*Função: Adjacente
*Descrição
*	Verifica se dois vértices são adjacentes em um grafo.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	y - Identificador de outro vértice.
*Valor retornado
*	Retorna um valor booleano que indica se os vértices de entrada são adjacentes ou não.
*	True - são adjacentes.
*	False -  não são adjacentes.
*Assertiva de entrada
*	O ponteiro G não pode ser NULL.
*	Os vértices x e y não podem possuir o mesmo valor.
*********************************************************/
boolean adjacente(tp_grafo *G, int x, int y)
{
	p_vertice v_aux = G->primeiro;
	p_aresta a_aux;
	int i;

	assert(x != y);
	assert(G);
	/*Realiza duas vezes para conferir os dois casos x->y e y<-x */
	for (i = 0; i < 2; ++i)
	{
		while(v_aux != NULL && v_aux->ch_vertice != x && v_aux->ch_vertice != y)
			v_aux = v_aux->prox;
		/*caso nao exista nem x, nem y*/
		if(v_aux == NULL)
			return FALSE;
		else
		{
			a_aux = v_aux->primeiro;
			while(a_aux != NULL && a_aux->vizinho->ch_vertice != x && a_aux->vizinho->ch_vertice != y)
				a_aux = a_aux->prox;
			if(a_aux != NULL)
				return TRUE;
		}
		v_aux = v_aux->prox;
	}
	return FALSE;
} 

/*******************************************************
*Função:
*Descrição
*	Imprime uma lista de todos os vértices que podem ser visitados a partir de x
*(existe uma aresta que vai de x para este vértice).
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
void vizinhos(tp_grafo *G,int x)
{
	p_vertice v_aux = G->primeiro;
	p_aresta a_aux;

	assert(G);

	while(v_aux != NULL && v_aux->ch_vertice != x)
		v_aux = v_aux->prox;
	if(v_aux == NULL)
	{
		printf("Erro - Vertice nao encontrado\n");
		return;
	}
	printf("Vertice %d: ", x);

	a_aux = v_aux->primeiro;
	while(a_aux != NULL)
	{
		printf("%d ",a_aux->vizinho->ch_vertice);
		a_aux = a_aux->prox;
	}
}

/*******************************************************
*Função: Adiciona Vértice
*Descrição
*	Adiciona um vértice a um grafo.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Indentificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

void adiciona_vertice(tp_grafo *G, int x)
{
	p_vertice p = G->primeiro;

	assert(G);

	if(grafo_vazio(*G) == FALSE)
	{
		G->ultimo->prox = (p_vertice)malloc(sizeof(tp_vertice));
		p = G->ultimo->prox;
	}
	else
	{
		G->primeiro = (p_vertice)malloc(sizeof(tp_vertice));
		p = G->primeiro;
	}
	
	G->ultimo = p;
	p->prox = NULL;
	p->ch_vertice = x;
	p->primeiro = NULL;
	p->ultimo = NULL;
	p->valor = -1;
}

/*******************************************************
*Função: Remove Vértice 
*Descrição
*	Remove um vértice de um grafo. Além disso, realiza a liberação correta de memória.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Indentificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessitar estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

void remove_vertice(tp_grafo *G,int x)
{
	p_vertice v_aux = G->primeiro, v_aux2;

	assert(G);
	/*caso nao seja o primeiro da lista*/
	if(v_aux->ch_vertice != x)
		while(v_aux->prox != NULL && v_aux->prox->ch_vertice != x)
			v_aux = v_aux->prox;
	else
	{
		G->primeiro = v_aux->prox;
		free(v_aux);
		return;
	}
	if(v_aux->prox == NULL)
		printf("ERRO - Vertice nao encontrado\n");
	else
	{
		v_aux2 = v_aux->prox;
		/*Sendo o ultimo da lista*/
		if(v_aux2 == G->ultimo)
			G->ultimo = v_aux;
		v_aux->prox = v_aux2->prox;
		free(v_aux2);
	}
}

/*******************************************************
*Função: Adiciona Aresta
*Descrição
*	Adiciona uma aresta entre dois vértices.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Indentificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

void adiciona_aresta(tp_grafo *G,int x,int y)
{
	p_vertice v_aux = G->primeiro, p_x = NULL,p_y = NULL;
	p_aresta a_aux;

	assert(G);

	while(v_aux != NULL){
		if (v_aux->ch_vertice == x)
			p_x = v_aux;
		if (v_aux->ch_vertice == y)
			p_y = v_aux;
		v_aux = v_aux->prox;
	}
	if(p_x == NULL)
	{
		printf("Erro - Vertice inicial nao encontrado\n");
	}
	else
	{
		if(p_y == NULL){
			printf("Erro - Vertice final nao encontrado\n");
		}
		else
		{
			a_aux = (p_aresta)malloc(sizeof(tp_aresta));

			if(vertice_isolado(p_x) == TRUE)
			{
				p_x->primeiro = a_aux;
				p_x->ultimo = a_aux;
			}
			else
				p_x->ultimo->prox = a_aux;

			a_aux->vizinho = p_y;
			a_aux->prox = NULL;
			a_aux->ch_aresta = -1;
		}
	}
}

/*******************************************************
*Função: Remove Aresta
*Descrição
*	Remove aresta entre dois vértices.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	y - Identificador de outro vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

void remove_aresta(tp_grafo *G,int x,int y)
{
	p_vertice v_aux = G->primeiro;
	p_aresta a_aux, a_aux2;

	assert(G);

	while(v_aux != NULL && v_aux->ch_vertice != x)
		v_aux = v_aux->prox;
	if(v_aux == NULL)
		printf("Erro - Vertice inicial nao encontrado\n");
	else
	{
		a_aux = v_aux->primeiro;
		/*caso o primeiro da lista seja y*/
		if(a_aux->vizinho->ch_vertice == y)
		{
			v_aux->primeiro = a_aux->prox;
			/*caso seja ultimo tambem*/
			if(v_aux->ultimo == a_aux)
				v_aux->ultimo = a_aux->prox;
			free(a_aux);
		}
		else
		{
			while(a_aux->prox != NULL && a_aux->prox->vizinho->ch_vertice != y)
				a_aux = a_aux->prox;
			if(a_aux->prox == NULL)
			{
				printf("Erro - Aresta nao encontrada\n");
				return;
			}
			/*caso seja a ultima aresta da lista*/
			else if(a_aux->prox == v_aux->ultimo)
				v_aux->ultimo = a_aux;

			a_aux2 = a_aux->prox;
			a_aux->prox = a_aux2->prox;
			free(a_aux2);
		}
	}
} 

/*******************************************************
*Função: Retorna valor vértice
*Descrição
*	Retorna o valor de um vértice.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*Valor retornado
*	Valor do vértice de entrada.
*	Caso o vértice não exista retorna -1.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

int retorna_valor_vertice(tp_grafo *G,int x)
{
	p_vertice p = G->primeiro;

	assert(G);
	assert(x != -1);

	if(grafo_vazio(*G) == TRUE){
		printf("Erro - Grafo vazio\n");
		return -1;
	}
	else
	{
		while(p != NULL && p->ch_vertice != x)
			p = p->prox;
		if(p != NULL)
			return p->valor;
		else
			return -1;
	}
}

/*******************************************************
*Função: Muda valor vértice
*Descrição
*	Altera o valor de um vértice.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	v - Valor a ser alterado no vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*	Valor de v deve ser diferente de -1.
*********************************************************/

void muda_valor_vertice(tp_grafo *G,int x,int v)
{
	p_vertice v_aux = G->primeiro;

	assert(G);
	assert(v != -1);

	if(grafo_vazio(*G) == TRUE){
		printf("Erro - Grafo vazio\n");
	}
	else
	{
		while(v_aux != NULL && v_aux->ch_vertice != x)
			v_aux = v_aux->prox;
		if(v_aux != NULL)
			v_aux->valor = v;
		else
			printf("Erro - Vertice nao encontrado\n");;
	}
}

/*******************************************************
*Função: Retorna valor aresta
*Descrição
*	Retorna o valor de uma aresta.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	y - Identificador de outro vértice.
*Valor retornado
*	Retorna o valor da aresta caso ela exista.
*	Caso contrário, a função retorna -1.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
/*retorna valor da aresta x,y em G*/
int retorna_valor_aresta(tp_grafo *G,int x,int y)
{
	p_vertice v_aux = G->primeiro;
	p_aresta a_aux;

	assert(G);

	while(v_aux != NULL && v_aux->ch_vertice != x)
		v_aux = v_aux->prox;
	if(v_aux == NULL){
		printf("Erro - Vertice inicial nao encontrado.\n");
		return -1;
	}
	else
	{
		a_aux = v_aux->primeiro;
		while(a_aux != NULL && a_aux->vizinho->ch_vertice != y)
			v_aux = v_aux->prox;
		if(a_aux == NULL){
			printf("Erro - Vertice final nao encontrado\n");
			return -1;	
		}
		else
		{
			return a_aux->ch_aresta;
		}
	}
}

/*******************************************************
*Função: Muda valor aresta
*Descrição
*	Altera o valor de uma aresta que liga dois vértices
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	y - Identificador de outro vértice.
*	v - Valor a ser alterado no vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*	Valor de v deve ser diferente de -1.
*********************************************************/

void muda_valor_aresta(tp_grafo *G,int x, int y, int v)
{
	p_vertice v_aux = G->primeiro;
	p_aresta a_aux;

	assert(G);
	assert(v != -1);

	if(grafo_vazio(*G) == TRUE){
		printf("Erro - Grafo vazio\n");
	}
	else
	{
		while(v_aux != NULL && v_aux->ch_vertice != x)
			v_aux = v_aux->prox;
		if(v_aux->ch_vertice == x)
		{
			a_aux = v_aux->primeiro;
			while(a_aux != NULL && a_aux->vizinho->ch_vertice != y)
				a_aux = a_aux->prox;
			if(a_aux == NULL)
				printf("Erro - Aresta nao encontrada\n");
			else
				a_aux->ch_aresta = v;
		}
		else 
			printf("Erro - Vertice nao encontrado\n");
	}
}

/*
	FUNCOES EXTRAS
*/

/*******************************************************
*Função: Grafo vazio
*Descrição
*	Verifica se uma esturutra grafo está vazia.
*Parâmetros
*	G - Estrutura de um grafo.
*Valor retornado
*	Retorna um valor booleano que indica se o grafo está vazio ou não.
*	True - caso o grafo esteja vazio.
*	False - caso contrário.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
boolean grafo_vazio(tp_grafo G)
{
	if(G.primeiro == G.ultimo && G.primeiro == NULL)
		return TRUE;
	else 
		return FALSE;
}

/*******************************************************
*Função: Vértice isolado
*Descrição
*	Verifica se um vértice não possui arestas.
*Parâmetros
*	A - Ponteiro para a estrutura de um vértice.
*Valor retornado
*	Retorna um valor booleano que indica se um vértice não possui arestas.
*	True - Caso o vértice não possua arestas.
*	False - Caso contrário.
*Assertiva de entrada
*	A estrutura do vértice necessita estar inicializada. A não pode possuir o valor NULL.
*********************************************************/
boolean vertice_isolado(p_vertice A)
{
	if(A->primeiro == A->ultimo && A->primeiro == NULL)
		return TRUE;
	else
		return FALSE;
}
