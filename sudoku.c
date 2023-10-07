#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int fila, columna;
  for (fila = 0; fila < 9; fila++) {
    int array[9] = {0};
    for (columna = 0; columna < 9; columna++) {
      if (n->sudo[fila][columna] == 0) {
        continue;
      }
      if (array[n->sudo[fila][columna] - 1] == 1) {
        return 0;
      }
      array[n->sudo[fila][columna] - 1] = 1;
    }
  }

  for (columna = 0; columna < 9; columna++) {
    int col[9] = {0};
    for (fila = 0; fila < 9; fila++) {
      if (n->sudo[fila][columna] == 0) {
        continue;
      }
      if (col[n->sudo[fila][columna] - 1] == 1) {
        return 0;
      }
      col[n->sudo[fila][columna] - 1] = 1;
    }
  }
  

    for (int k = 0; k < 9; k++) {
        int used[9] = {0}; // Arreglo para verificar números utilizados en la fila, columna y subgrid

        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int num = n->sudo[i][j];

            // Verificar si el número ya ha sido utilizado en la fila, columna o subgrid
            if (num == 0 || used[num - 1] == 1) {
                return 0; // Sudoku no es válido
            }
            
            used[num - 1] = 1; // Marcar el número como utilizado
        }
    }

    return 1; // Sudoku es válido
}


  return 1;
}

List *get_adj_nodes(Node *n) {

  List *list = createList();

  for (int fila = 0; fila < 9; fila++) {

    for (int columna = 0; columna < 9; columna++) {

      if (n->sudo[fila][columna] == 0) {

        for (int num = 1; num <= 9; num++) {

          Node *nuevonodo = copy(n);
          nuevonodo->sudo[fila][columna] = num;
          if (is_valid(nuevonodo)) {
            pushBack(list, nuevonodo);
          } else {
            free(nuevonodo);
          }
        }
        return list;
      }
    }
  }

  return list;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/