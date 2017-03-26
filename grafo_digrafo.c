#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vet
{
	int vert;
	struct vet *prox;
};

void grafo(struct vet **vetOrig, int nroArest);
void digrafo(struct vet **vetOrig, int nroArest);
void showMatAdj(struct vet **vetOrig, int nroArestas, int nroVertices);
void insertGrafo(struct vet **vetOrig, int dest);
void insertDigrafo(struct vet **vetOrig, int dest);
void getDest(char *dest, int *iDest);
void getOrig(char *orig, int *iOrig);
struct vet * getVert(struct vet *vetOrig, int *vert);
void freeMemory(struct vet**data, int datSize);

int main(void)
{
  struct vet **vetOrig;
  char nv[4], na[4], grafo_digrafo[2];
  int i, iNv, iNa, iGrDgr;

  memset(nv, 0, sizeof(nv));
  memset(na, 0, sizeof(na));
	memset(grafo_digrafo,0,sizeof(grafo_digrafo));

  printf("Numero de vertices: ");
  fgets(nv, sizeof(nv), stdin);
	// sscanf(nv,"%d",&iNv);
  iNv = atoi(nv);	// numero de vertices

  printf("Numero de Arestas: ");
  fgets(na, sizeof(na), stdin);
	// sscanf(na,"%d",&iNa);
  iNa = atoi(na); // numero de arestas

  vetOrig = (struct vet**) malloc(sizeof(struct vet) * iNv);

  for (i = 0; i < iNv; i++)
    vetOrig[i] = NULL;

	printf("Grafo ou Digrafo?\nDigite 1 para Grafo e 2 para Digrafo: ");
	fflush(stdin);
	fgets(grafo_digrafo, sizeof(grafo_digrafo), stdin);
	iGrDgr = atoi(grafo_digrafo);

	// grafo
	if (iGrDgr == 1)
	{
		grafo(vetOrig,iNa);
		showMatAdj(vetOrig,iNa,iNv);

		// printf("vertice 1: %d, %d\n",vetOrig[0]->vert, vetOrig[0]->prox->vert);
		// printf("vertice 2: %d, %d\n",vetOrig[1]->vert, vetOrig[1]->prox->vert);
		// printf("vertice 3: %d, %d\n",vetOrig[2]->vert, vetOrig[2]->prox->vert);
		// printf("vertice 4: %d, %d\n",vetOrig[3]->vert, vetOrig[3]->prox->vert);
		// printf("vertice 5: %d, %d\n",vetOrig[4]->vert, vetOrig[4]->prox->vert);

		freeMemory(vetOrig,iNv);
	}
	// Digrafo
	else
	{
		digrafo(vetOrig,iNa);
		showMatAdj(vetOrig,iNa,iNv);

		// printf("vertice 1: %d\n",vetOrig[0]->vert);
		// printf("vertice 2: %d\n",vetOrig[1]->vert);
		// printf("vertice 3: %d\n",vetOrig[2]->vert);
		// printf("vertice 4: %d\n",vetOrig[3]->vert);
		// printf("vertice 5: %d\n",vetOrig[4]->vert);

		freeMemory(vetOrig,iNv);
	}

  return 0;
}

void digrafo(struct vet **vetOrig, int nroArest)
{
	int i, iOrig, iDest;
	char orig[4], dest[4];

	for (i = 1; i <= nroArest; i++)
	{
		printf("(Aresta %d)\n",i);

		fflush(stdin);
		memset(orig, 0, sizeof(orig));
		memset(dest, 0, sizeof(dest));

		getOrig(orig,&iOrig);
		// fix bug
		if(iOrig == 0)
			iOrig = 1;

		getDest(dest,&iDest);
		insertDigrafo(&vetOrig[iOrig - 1],iDest);
	}
}

void grafo(struct vet **vetOrig, int nroArest)
{
	int i, iOrig, iDest; //converter para int
	char orig[4], dest[4]; //pega entrada do usuario

	for (i = 1; i <= nroArest; i++)
	{

		printf("(Aresta %d)\n",i);

		fflush(stdin);
    memset(orig, 0, sizeof(orig));
    memset(dest, 0, sizeof(dest));

    getOrig(orig,&iOrig);
		// fix bug
		if(iOrig == 0)
			iOrig = 1;

		getDest(dest,&iDest);

		insertGrafo(&vetOrig[iOrig - 1],iDest);
		if (iOrig != iDest)
			insertGrafo(&vetOrig[iDest - 1], iOrig);
  }
}

void getOrig(char *orig, int *iOrig)
{
	printf("Origem: \n");
	fgets(orig, sizeof(orig), stdin);
	*iOrig = atoi(orig);
}

void getDest(char *dest, int *iDest)
{
	printf("Destino: \n");
	fgets(dest, sizeof(dest), stdin);
	*iDest = atoi(dest);
}

void insertDigrafo(struct vet **vetOrig, int dest)
{
	struct vet *aux;

	aux = (struct vet*) malloc(sizeof(struct vet));

	aux->vert = dest;
	aux->prox = NULL;

	if (*vetOrig == NULL)
		*vetOrig = aux;
}

void insertGrafo(struct vet **vetOrig, int dest)
{
	struct vet *ult, *aux;

	aux = (struct vet*) malloc(sizeof(struct vet));

	aux->vert = dest;
	aux->prox = NULL;

	if (*vetOrig == NULL)
		*vetOrig = aux;
	else
	{
		ult = *vetOrig;
		while (ult->prox != NULL)
			ult = ult->prox;

		ult->prox = aux;
	}
}

void showMatAdj(struct vet **vetOrig, int nroArestas, int nroVertices)
{
	int i, j, vertMat;
	int matAdj[nroVertices+1][nroArestas+1];
	struct vet *aux;

	memset(matAdj, 0, sizeof(matAdj[0][0]) * (nroVertices+1) * (nroArestas+1));

	for (i = 1; i <= nroVertices; i++)
	{
		aux = vetOrig[i-1];
		while (aux != NULL)
		{
			aux = getVert(aux,&vertMat);
			matAdj[i][vertMat] = 1;
		}
	}
	printf("\n\n");
	for (i = 1; i <= nroVertices; i++)
	{
		printf("vertice: %d| ",i);
		for (j = 1; j <= nroArestas; j++)
		{
			printf("%d ",matAdj[i][j]);
		}
		printf("\n");
	}
}

struct vet * getVert(struct vet *vetOrig, int *vertMat)
{
	*vertMat = vetOrig->vert;
	return vetOrig->prox;
}

void freeMemory(struct vet **data, int datSize) {
  int i;

  for (i = 0; i < datSize; i++) {
    free(data[i]);
  }
	free(data);
}
