#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
    // Verificar filas
    for (int fila = 0; fila < 9; fila++) {
        int nums[10] = {0}; // Inicializa un array para rastrear los números en la fila
        for (int col = 0; col < 9; col++) {
            int num = n->sudo[fila][col];
            if (num != 0) {
                if (nums[num]) {
                    // El número ya se ha visto, es un duplicado en la fila
                    return 0;
                }
                nums[num] = 1;
            }
        }
    }

    // Verificar columnas
    for (int col = 0; col < 9; col++) {
        int nums[10] = {0}; // Inicializa un array para rastrear los números en la columna
        for (int fila = 0; fila < 9; fila++) {
            int num = n->sudo[fila][col];
            if (num != 0) {
                if (nums[num]) {
                    // El número ya se ha visto, es un duplicado en la columna
                    return 0;
                }
                nums[num] = 1;
            }
        }
    }

    // Verificar todas las submatrices de 3x3 (k de 1 a 9)
    for (int k = 1; k <= 9; k++) {
        int seen[10] = {0}; // Array para rastrear los números vistos en la submatriz
        for (int p = 0; p < 9; p++) {
            int i = 3 * ((k - 1) / 3) + (p / 3);
            int j = 3 * ((k - 1) % 3) + (p % 3);
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) {
                    // El número ya se ha visto, es un duplicado en la submatriz
                    return 0;
                }
                seen[num] = 1;
            }
        }
    }

    // Si no se encontraron duplicados en filas, columnas o submatrices, el Sudoku es válido
    return 1;
}


List* get_adj_nodes(Node* n){
  
    List* list=createList();

    for (int fila=0;fila<9;fila++){
      
      for (int columna=0;columna<9;columna++){
        
        if(n->sudo[fila][columna]==0){
          
          for(int num=1;num<=9;num++){
            
            Node *nuevonodo=copy(n);
            nuevonodo->sudo[fila][columna]=num;
            if(is_valid(nuevonodo)){
              pushBack(list,nuevonodo);
            }else{
              free(nuevonodo);
            }
            
          }
          return list;
        }
        
      }
    }
    
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/