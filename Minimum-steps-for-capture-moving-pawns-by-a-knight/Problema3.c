#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
typedef struct 
{
   int px;
   int py;
   bool captured;
}Pawn; //estrutura que representa um peao

typedef struct 
{
   int x;
   int y;
}Knight; //estrutura que representa um cavalo

bool isSafe(Knight h, Pawn copy[], int P){ 

   if(h.x > 7 || h.x < 0 || h.y > 7 || h.y < 0){ //retorna false para uma posicao fora do tabuleiro
      return false;
   }

   for(int i = 0; i < P; i++){
      if(h.x == copy[i].px && h.y == copy[i].py){ //se houver um peao marca que ele foi capturado
         copy[i].captured = true;
      }
      if(copy[i].px == h.x-1 && copy[i].py == h.y && !(copy[i].captured)){ //se houver um peao uma linha acima na mesma coluna, ele captura o cavalo e nao nos leva a solucao do problema
         return false;
      }
      if(copy[i].px == 7 && !(copy[i].captured)){ //um peao na ultima linha nao capturado, na proxima jogada captura o cavalo
         return false;
      }
   }
   return true; //se nao houver perigo, podemos testar essa posicao
}

void moveForward(Pawn copy[], int P){ //movimenta os peoes para frente a cada jogada do cavalo
   for(int i = 0; i < P; i++){
      if(copy[i].captured){
         continue;
      }
      copy[i].px++;
   }
}

Pawn * copyArray(Pawn pawns[], int P){ // copia um vetor de peoes
   Pawn * copy = malloc(sizeof(Pawn) * P);
   for (int i = 0; i < P; i++)
   {
      copy[i].px = pawns[i].px;
      copy[i].py = pawns[i].py;
      copy[i].captured = pawns[i].captured;
      
   }
   return copy;
}

bool pruning(Knight H, Pawn pawns[], int P){ //faz as podas necessarias para otimizar a execucao
   for (int i = 0; i < P; i++)
   {
      if(pawns[i].px == H.x + 2 && pawns[i].py == H.y){     //se houver um peao com distancia de
         return true;                                      //2 linhas ou duas colunas do cavalo
      }                                                   //sempre sera impossivel capturar
      if(pawns[i].px == H.x - 2 && pawns[i].py == H.y){
         return true;
      }
      if(pawns[i].px == H.x && pawns[i].py == H.y + 2){
         return true;
      }
      if(pawns[i].px == H.x && pawns[i].py == H.y - 2){
         return true;
      }
      
      
      if(pawns[i].px == H.x - 7 && pawns[i].py == H.y - 7){      //tambem sera sempre impossivel se 
         return true;                                           //um peao estiver numa extremidade 
      }if(pawns[i].px == H.x - 7 && pawns[i].py == H.y + 7){   //e o cavalo na outra
         return true;
      }if(pawns[i].px == H.x + 7 && pawns[i].py == H.y + 7){
         return true;
      }if(pawns[i].px == H.x + 7 && pawns[i].py == H.y - 7){
         return true;
      }
   }
   return false;
}

int findMinimumStepsBacktracking(Knight H, Pawn pawns[], int min, int currPlay, int P)
{   //calcula os passos minimos para capturar todos os peoes pela tecnica de backtracking
   if(pruning(H, pawns, P)){ //faz algumas podas
      return 8;
   }
   bool allCaptured = true;

   if(currPlay >= min){ //se esse caminho for maior que o minimo retornamos 8, o maximo de jogadas possivel
      return 8;
   }

   for (int i = 0; i < P; i++)
   {
      if(!(pawns[i].captured)){ //verifica se ja capturou tudo
         allCaptured = false;
         break;
      }
   }

   if(allCaptured){ //com todos capturados, retornamos a qtde de passos q foram tomados nesse caminho
      return currPlay;
   }

   
   Knight moves[8] = { //guarda as 8 possiveis posicoes/jogadas do cavalo a partir da atual posicao
      {H.x - 1, H.y - 2},
      {H.x - 2, H.y - 1},
      {H.x - 1, H.y + 2},
      {H.x - 2, H.y + 1},
      {H.x + 1, H.y - 2},
      {H.x + 2, H.y - 1},
      {H.x + 1, H.y + 2},
      {H.x + 2, H.y + 1}
   };

   for(int i = 0; i < 8; i++){
      Pawn *copy = copyArray(pawns, P);
      if(!isSafe(moves[i], copy, P)){ //se nao for seguro, testamos outro caminho
         continue;
      }
      moveForward(copy, P); //move peoes pra frente

      int result = findMinimumStepsBacktracking(moves[i], copy, min, currPlay+1, P);
      if(result < min){ //veirifica o menor caminho e atualiza o minimo
         min = result;
      }
   }
   return min;
}

void printResult(Knight H, Pawn pawns[], int P){
   int min = 8;
   int result = findMinimumStepsBacktracking(H, pawns, min, 0, P);
   if(result == 8){
      printf("impossible");
   }else{
      printf("%d", result);
   }
}


int main()
{
   int P, A, h;
   Knight H;

   scanf("%d", &P);
   
   Pawn pawns[P];

   for (int i = 0; i < P; i++)  //le e armazena as posicoes dos peoes
   {
      scanf("%d", &A);
      pawns[i].px = (A - 1) / 8; //linha do tabuleiro
      pawns[i].py = (A - 1) % 8; //coluna do tabuleiro
      pawns[i].captured = false;
   }

   scanf("%d", &h); //le e armazena posicao do cavalo
   H.x = (h - 1) / 8; //linha do tabueleiro
   H.y = (h - 1) % 8; //coluna do tabuleiro

   printResult(H, pawns, P);
   return 0;
}