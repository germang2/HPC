#include <stdio.h>
#include <stdlib.h>


float** inciarMatriz(float **m, int rows, int cols){
  int i;
  m = (float **)malloc(rows*sizeof(float));

  for(i=0;i<rows;i++)
    m[i] = (float *)malloc(cols*sizeof(float));

  return m;
}

int main(int argc, char** argv){

/*
  if(argc != 3){
    printf("This need be called with 2 arguments\n", );
    return 1;
  }
*/
  FILE *stream;
  int rows1=0, cols1=0;
  int i, j;
  float temp;
  float **m1, **m2;
  stream = fopen("matriz1.txt", "r");

  fscanf(stream, "%d", &rows1);
  fscanf(stream, "%d", &cols1);

  m1 = inciarMatriz(m1, rows1, cols1);

//lee la matriz y la guarda a la matriz
  for(i=0;i<rows1;i++){
    for(j=0;j<cols1;j++){
      fscanf(stream, "%f,", &temp);
      *(*(m1 + i) + j) = temp;
    }
  }

//imprime la matriz
  for(i=0;i<rows1;i++){
    for(j=0;j<cols1;j++){
      printf("%.2f ", *(*(m1 + i) + j));
    }
    printf("\n");
  }

  fclose(stream);
  free(m1);
  return 0;
}
