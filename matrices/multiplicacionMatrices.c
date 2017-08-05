#include <stdio.h>
#include <stdlib.h>

//This function ask for memory for the respective size of each matrix
float** startArray(float **m, int rows, int cols){
  int i;
  m = (float **)malloc(rows*sizeof(float));

  for(i=0;i<rows;i++)
    m[i] = (float *)malloc(cols*sizeof(float));

  return m;
}

//This function reads the .txt values and assign it to the array
float** assignArray(float **m, FILE *stream, int rows, int cols){
  int i,j;
  float temp;
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      fscanf(stream, "%f,", &temp);
      *(*(m + i) + j) = temp;
    }
  }
  return m;
}

//This function prints the array
void printArray(float **m, int rows, int cols){
  int i,j;
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      printf("%.2f ", *(*(m + i) + j));
    }
    printf("\n");
  }
}

int main(int argc, char** argv){


  if(argc != 3){
    printf("This need be called with 2 arguments\n");
    return 1;
  }

  FILE *stream, *stream2;
  int rows1=0, cols1=0, rows2=0, cols2=0;
  float **m1, **m2;

  //open the two txt files
  stream = fopen(argv[1], "r");
  stream2 = fopen(argv[2], "r");

  //read, for each txt file, the number of rows and cols
  fscanf(stream, "%d", &rows1);
  fscanf(stream, "%d", &cols1);
  fscanf(stream2, "%d", &rows2);
  fscanf(stream2, "%d", &cols2);  

  //Initializes the matrix
  m1 = startArray(m1, rows1, cols1);
  m2 = startArray(m2, rows2, cols2);

  //Assign the values to the array
  m1 = assignArray(m1, stream, rows1, cols1);
  m2 = assignArray(m2, stream2, rows2, cols2);

  printf("Matriz 1:\n");
  printArray(m1, rows1, cols1);
  printf("Matriz 2:\n");
  printArray(m2, rows2, cols2);


  fclose(stream);
  fclose(stream2);
  free(m1);
  free(m2);

  return 0;
}
