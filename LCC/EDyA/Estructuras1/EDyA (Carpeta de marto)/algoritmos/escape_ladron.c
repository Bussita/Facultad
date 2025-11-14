#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RANGE 100
#define ROWS 1000
#define COLUMNS 1000

#define MIN(x,y) (x < y) ? x : y

typedef struct {

  int** elements;
  int rows;
  int columns;

} Matrix;

Matrix* create_matrix(int rows, int columns);

void destroy_matrix(Matrix* matrix);

void random_elements(Matrix* matrix, int range);

void show_matrix(Matrix* matrix);

int minimal_cost(Matrix* cost_matrix);

int minimal_cost_recursive(int i, int j, Matrix* cost_matrix, Matrix* pass, Matrix* minimal);


int main() {

  Matrix* cost_matrix = create_matrix(ROWS, COLUMNS);
  random_elements(cost_matrix, MAX_RANGE);

  //show_matrix(cost_matrix);

  int minimal_value = minimal_cost(cost_matrix);

  printf("MINIMAL COST: %d\n", minimal_value);

  destroy_matrix(cost_matrix);

  return 0;
}


int minimal_cost(Matrix* cost_matrix) {

  Matrix* pass = create_matrix(cost_matrix->rows, cost_matrix->columns);
  Matrix* minimal = create_matrix(cost_matrix->rows, cost_matrix->columns);

  int minimal_value = minimal_cost_recursive(0, 0, cost_matrix, pass, minimal);

  destroy_matrix(pass);
  destroy_matrix(minimal);

  return minimal_value;
}


int minimal_cost_recursive(int i, int j, Matrix* cost_matrix, Matrix* pass, Matrix* minimal) {

  // Checked if we've already pass this element
  if (pass->elements[i][j])
    
    return minimal->elements[i][j];

  // If we did not pass this element
  pass->elements[i][j] = 1;

  // Checked if we are in the right-bottom corner
  if (i == cost_matrix->rows - 1 && j == cost_matrix->columns - 1) {
    
    minimal->elements[i][j] = cost_matrix->elements[i][j];    
    return minimal->elements[i][j];
  } 

  // Checked if we are in the right side
  else if (j == cost_matrix->columns - 1) {
    
    minimal->elements[i][j] = cost_matrix->elements[i][j] + minimal_cost_recursive(i + 1, j, cost_matrix, pass, minimal);
    return minimal->elements[i][j];
  }

  // Checked if we are in the bottom side
  else if (i == cost_matrix->rows - 1) {
  
    minimal->elements[i][j] = cost_matrix->elements[i][j] + minimal_cost_recursive(i, j + 1, cost_matrix, pass, minimal);
    return minimal->elements[i][j];
  }

  // Finally, we can move in both directions
  else {

    int best_value = MIN(minimal_cost_recursive(i, j + 1, cost_matrix, pass, minimal),
                          minimal_cost_recursive(i + 1, j, cost_matrix, pass, minimal));

    minimal->elements[i][j] = cost_matrix->elements[i][j] + best_value;
    return minimal->elements[i][j];
  }
}




Matrix* create_matrix(int rows, int columns) {

  Matrix* new_matrix = malloc(sizeof(Matrix));

  new_matrix->rows = rows;
  new_matrix->columns = columns;

  new_matrix->elements = malloc(sizeof(int*) * rows);

  for (int i = 0 ; i < rows ; i++)
    new_matrix->elements[i] = calloc(columns, sizeof(int));

  return new_matrix;
}


void destroy_matrix(Matrix* matrix) {

  for (int i = 0 ; i < matrix->rows ; i++)
    free(matrix->elements[i]);

  free(matrix->elements);
  free(matrix);
}


void random_elements(Matrix* matrix, int range) {

  srand(time(NULL));

  for (int i = 0 ; i < matrix->rows ; i++) {

    for (int j = 0 ; j < matrix->columns ; j++) 

      matrix->elements[i][j] = rand() % range;

  }
}



void show_matrix(Matrix* matrix) {

  for (int i = 0 ; i < matrix->rows ; i++) {

    for (int j = 0 ; j < matrix->columns ; j++) 

      printf("%d  ",matrix->elements[i][j]);

    printf("\n");
  }
}
