#include <stdio.h>
#include <stdlib.h>

//This function ask for memory for the respective size of each array
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

//This function helps the function "multiplyArrays", getting the value for each position
float getValue(float **m1, float **m2, int i, int j, int size){
  int k;
  float sum = 0.0;
  for(k=0;k<size;k++){
    sum += (*(*(m1 + i) + k)) * (*(*(m2 + k) + j));
  }
  return sum;
}

//This function multiply 2 arrays and returns the resulting array
float** multiplyArrays(float **m1, float **m2, int rows1, int cols1, int rows2, int cols2){
  int i,j;
  float **mr;
  mr = startArray(mr, rows1, cols2);
  for(i=0;i<rows1;i++){
    for(j=0;j<cols2;j++){
      *(*(mr + i) + j) = getValue(m1, m2, i, j, rows1);
    }
  }
  return mr;
}

void writeArray(float **mr, int rows, int cols){
  FILE *stream;
  int i,j;
  stream = fopen("mr.txt", "w+");
  fprintf(stream, "%d\n", rows);
  fprintf(stream, "%d\n", cols);
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      fprintf(stream, "%f,", *(*(mr + i) + j) );
    }
    fprintf(stream, "%s\n","");
  }
  fclose(stream);
}

int main(int argc, char** argv){


  if(argc != 3){
    printf("This need be called with 2 arguments, the .txt files with the values of the arrays\n");
    return 1;
  }

  FILE *stream, *stream2;
  int rows1=0, cols1=0, rows2=0, cols2=0;
  float **m1, **m2, **mr;

  //open the two txt files
  stream = fopen(argv[1], "r");
  stream2 = fopen(argv[2], "r");

  //read, for each txt file, the number of rows and cols
  fscanf(stream, "%d", &rows1);
  fscanf(stream, "%d", &cols1);
  fscanf(stream2, "%d", &rows2);
  fscanf(stream2, "%d", &cols2);  

  //Verify that the number of rows of the firts array should be equal 
  //to the number of columns of the second array
  if(rows1 != cols2){
    printf("Invalid operation, the number of rows of the firts matrix should be equal to the number of columns of the second matrix\n");
    return 1;
  }

  //Initializes the array
  m1 = startArray(m1, rows1, cols1);
  m2 = startArray(m2, rows2, cols2);

  //Assign the values to the array
  m1 = assignArray(m1, stream, rows1, cols1);
  m2 = assignArray(m2, stream2, rows2, cols2);

  printf("Matriz 1:\n");
  printArray(m1, rows1, cols1);
  printf("Matriz 2:\n");
  printArray(m2, rows2, cols2);

  mr = multiplyArrays(m1, m2, rows1, cols1, rows2, cols2);

  printf("Final Matriz:\n");
  printArray(mr, rows1, cols2);

  writeArray(mr, rows1, cols2);


  fclose(stream);
  fclose(stream2);
  free(m1);
  free(m2);
  free(mr);

  return 0;
}
