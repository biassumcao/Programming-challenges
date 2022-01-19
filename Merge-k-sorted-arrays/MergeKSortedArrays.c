#include <stdio.h>
#include <malloc.h>
#define MAX 10000000
//estrutura de no de um minHeap
typedef struct {
    int arrOrig; //guarda o indice que identifica o vetor origem de cada num
    int prox; //guarda o indice do proximo item do vetor a ser adicionado ao heap
    unsigned long long num;
    int tam; //guarda o tamanho do vetor origem do num
}minHeapNo;
 
minHeapNo *ptrHeap; //vetor que representa uma estrutura de heap
 
void swap(minHeapNo *x, minHeapNo *y){
  minHeapNo temp = *x;  
	*x = *y;  
	*y = temp;
}
//tamanhoHeap é a quantidade de elementos no heap, ou seja k elementos, pois temos k vetores e n representa o total de valores entre todos os vetores
int tamanhoHeap, n=0;
 
void minHeapify(int i){ //mantem as propriedades do heap
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    int menor = i;
    if (esq < tamanhoHeap && ptrHeap[esq].num < ptrHeap[i].num)
        menor = esq;
    if (dir < tamanhoHeap && ptrHeap[dir].num < ptrHeap[menor].num)
        menor = dir;
    if (menor != i){
        swap(&ptrHeap[i], &ptrHeap[menor]);
        minHeapify(menor);
    }
}
 
void constroiMinHeap(int t){ //cria um heap de minimo a partir de um vetor (ptrHeap)
    tamanhoHeap = t;
    int i = (tamanhoHeap - 1)/2;
    while (i >= 0){
        minHeapify(i);
        i--;
    }
}
 
unsigned long long *mergeK(int *arr[], int k, int i){ //intercala os k vetores
    constroiMinHeap(k);
		//guarda o vetor final ordenado ate a iesima intercalacao
    unsigned long long *vetorFinal = malloc(sizeof(unsigned long long) * n);
 
    for(int count = 0; count < n; count++){
        minHeapNo raiz = ptrHeap[0]; //a raiz é o menor valor do heap, que esta localizada na primeira posicao
        vetorFinal[count] = raiz.num; //vetor de saida contem elementos ordenados
 
        if(raiz.prox < raiz.tam){ //se ainda tem elementos no vetor
            raiz.num = arr[raiz.arrOrig][raiz.prox]; //remove o menor elemento, atualizando a raiz
      			raiz.prox += 1; //atualiza qual sera o proximo menor valor de derminado vetor a ser inserido no heap
        }else{
            raiz.num = MAX; //se nao tem mais elementos do vetor atual, entao a raiz recebe um valor que representa infinito
        }

        ptrHeap[0] = raiz; //trocando a raiz precisamos verificar se as propriedades do heap ainda se mantem:
				minHeapify(0); 
    }
    return vetorFinal;
}

int main(){
    int k, i, j, tam, x, l; 
    unsigned long long soma=0;
    scanf("%i %i", &k, &i);
    int *vetor[k];
    minHeapNo heap[k];
    
    for(j=0; j<k; j++){
        scanf("%i", &tam);
        vetor[j] = malloc(sizeof(unsigned long long) * tam);
        n+=tam;
        for(l=0; l<tam; l++){
            scanf("%i", &x);
            vetor[j][l] = x;
        }
 
        //criando um vetor de heap sem seguir suas propriedades ainda
        if(tam == 0){
            heap[j].num = MAX;
            heap[j].prox = 0;
            heap[j].tam = 0;
        }else{
            heap[j].num = vetor[j][0];
            heap[j].arrOrig = j;
            heap[j].prox = 1;
            heap[j].tam = tam;
        }
    }
    ptrHeap = heap;
    unsigned long long *vetorFinal = mergeK(vetor, k, i);
}