#include <stdlib.h>
#include <stdio.h>

// CUDA kernel
__global__ void multMatGPU(double *A, int rowsA, int colsA, double *B, int rowsB, int colsB, double *C){
   double sum = 0.0;
   int k;
   // Gets the id for the row and the col
   int row = blockIdx.y * blockDim.y + threadIdx.y;
   int col = blockIdx.x * blockDim.x + threadIdx.x;
   
   // Multiplication, needs one cycle
   if(row < rowsA && col < colsB){
      sum = 0.0;
      for(k = 0; k < rowsB; k++){
         sum += A[(row * colsA) + k] * B[(k * colsB) + col];
       }
       C[row*colsB+col] = sum;
   }
}

__host__ void multMatHost(double *A, int rowsA, int colsA, double *B, int rowsB, int colsB, double *C){
   int k, i, j, index = 0;
   double sum = 0.0;
   for(i = 0; i < rowsA; i++){
      for(j = 0; j < colsB; j++){
         sum = 0.0;
         for(k = 0; k < rowsA; k++){
            sum += A[(i * colsA) + k] * B[(k * colsB) + j]; 
         }
         C[i*colsB+j] = sum;
         index += 1; 
      }
   }
}


int main(){
   double *h_A, *h_B, *h_C, *CPU, *d_A, *d_B, *d_C;
   int rowsA = 1000, colsA = 1000, rowsB = 1000, colsB = 1000;
   int i, j;   
   if (colsA != rowsA)
	return 1;

   h_A = (double*)malloc((rowsA*colsA)*sizeof(double));
   h_B = (double*)malloc((rowsB*colsB)*sizeof(double));
   CPU = (double*)malloc((rowsA*colsB)*sizeof(double));


   for(i = 0; i < rowsA; i++)
      for(j = 0; j < colsA; j++)
         h_A[i* colsA+j] = i+j;
   
   for(i = 0; i < rowsB; i++)
      for(j = 0; j < colsB; j++)
         h_B[i* colsB+j] = i+j;
   
   cudaMalloc((void **)&d_A, rowsA*colsA);
   cudaMalloc((void **)&d_B, rowsB*colsB);
   cudaMalloc((void **)&d_C, rowsA*colsB); 
   
   cudaMemcpy(d_A, h_A, rowsA*colsA, cudaMemcpyHostToDevice);
   cudaMemcpy(d_B, h_B, rowsA*colsB, cudaMemcpyHostToDevice);

   int gridSize, blockSize;
   blockSize = 1024;
   gridSize = (int)ceil((float)colsB/blockSize);   

   multMatGPU<<<gridSize, blockSize>>>(d_A, rowsA, colsA, d_B, rowsB, colsB, d_C);
   cudaMemcpy(h_C, d_C, rowsA*colsB, cudaMemcpyDeviceToHost);
   multMatHost(h_A, rowsA, colsA, h_B, rowsB, colsB, CPU);

   int val = 1;
   for(i = 0; i < colsB; i++)
      if(CPU[i] != h_C[i])
         val = 0;

   if(val == 1)
      printf("Same results");
   else
      printf("Diferents results");

   free(h_A);
   free(h_B);
   free(h_C);
   free(CPU);

   cudaFree(d_A);
   cudaFree(d_B);
   cudaFree(d_C);

   return 0;
}


