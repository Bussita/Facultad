// We receive a matrix with only 0's and 1's. A number 1 represents a wall.
// We have to find the number of paths from the top-left corner to the bottom-right one.
// I CONSIDERED THAT I CAN ONLY DO DOWN AND RIGH MOVEMENTS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 2
#define ROWS 20
#define COLUMNS 20

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

int number_paths(Matrix* wall);

int number_paths_recursive(int i, int j, Matrix* wall, Matrix* pass, Matrix* paths);


int main(void) {

  Matrix* wall = create_matrix(ROWS, COLUMNS);
  
  // random_elements(wall, RANGE);

  // for (int i = 1 ; i < ROWS - 2 ; i++) 
  //   wall->elements[i][1] = 1;

  // for (int j = 1 ; j < COLUMNS - 2 ; j++) 
  //   wall->elements[1][j] = 1;


  //show_matrix(wall);

  printf("NUMBER OF PATHS: %d\n", number_paths(wall));

  destroy_matrix(wall);

  return 0;
}


int number_paths(Matrix* wall) {

  Matrix* pass = create_matrix(ROWS, COLUMNS);
  Matrix* paths = create_matrix(ROWS, COLUMNS);

  int number_of_paths = number_paths_recursive(0, 0, wall, pass, paths);

  destroy_matrix(pass);
  destroy_matrix(paths);

  return number_of_paths;
}


int number_paths_recursive(int i, int j, Matrix* wall, Matrix* pass, Matrix* paths) {

  // Checked if we are in a wall
  if (wall->elements[i][j])

    return 0;


  // Checked if we've already passed
  if (pass->elements[i][j])
    
    return paths->elements[i][j];

  // In the other case
  pass->elements[i][j] = 1;

  // If we are in the right-bottom corner
  if (i == wall->rows - 1 && j == wall->columns - 1) {

    paths->elements[i][j] = 1;
    return 1;
  }

  // If we are in the right side 
  else if (j == wall->columns - 1) {

    paths->elements[i][j] = number_paths_recursive(i + 1, j, wall, pass, paths);
    return paths->elements[i][j];
  }

  // If we are in the bottom side 
  else if (i == wall->rows - 1) { 

    paths->elements[i][j] = number_paths_recursive(i, j + 1, wall, pass, paths);
    return paths->elements[i][j];
  }

  // We are somewhere in the center
  else {

    int paths_right = number_paths_recursive(i + 1, j, wall, pass, paths);
    int paths_down = number_paths_recursive(i, j + 1, wall, pass, paths);

    paths->elements[i][j] = paths_right + paths_down;
    return paths_right + paths_down; 
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
