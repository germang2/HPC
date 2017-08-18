//This program multiply 2 matrices and writes the result in a .txt
//This program use threads with openMP

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char **argv){

	if(argc != 3){
	    printf("This need be called with 2 arguments, the .txt files with the values of the arrays\n");
	    return 1;
  	}

  	clock_t cl = clock();

	int nthreads, tid, i, j, k;
	float **m1, **m2, **mr, temp, suma=0.0;
	FILE *stream, *stream2, *stream_writer;
	int rows1=0, cols1=0, rows2=0, cols2=0;

	stream = fopen(argv[1], "r");
	fscanf(stream, "%d", &rows1);
	fscanf(stream, "%d", &cols1);

	stream2 = fopen(argv[2], "r");
	fscanf(stream2, "%d", &rows2);
	fscanf(stream2, "%d", &cols2);

	stream_writer = fopen("mr.txt", "w");
	fprintf(stream_writer, "%d\n", rows1);
	fprintf(stream_writer, "%d\n", cols2);

	
	//Ask for memerry and writes the first matriz
	m1 = (float**)malloc(rows1*sizeof(float*));
	for(i=0;i<rows1;i++)
		m1[i] = (float *)malloc(cols1*sizeof(float));

	m2 = (float**)malloc(rows2*sizeof(float*));
	for(i=0;i<rows2;i++)
		m2[i] = (float *)malloc(cols2*sizeof(float));

	mr = (float**)malloc(rows1*sizeof(float*));
	for(i=0;i<cols2;i++)
		mr[i] = (float *)malloc(cols2*sizeof(float));

	printf("DEBUG 1\n");

	for(i=0;i<rows1;i++){
	    for(j=0;j<cols1;j++){
	      fscanf(stream, "%f,", &temp);
	      *(*(m1 + i) + j) = temp;
	    }
	}		
	printf("DEBUG 2\n");	
	
	//Reads and writes the second matriz
	for(i=0;i<rows2;i++){
	    for(j=0;j<cols2;j++){
	      fscanf(stream2, "%f,", &temp);
	      *(*(m2 + i) + j) = temp;
	    }
	}

	#pragma omp parallel private(i, j, k, suma)
	{

		printf("DEBUG 3\n");
		//Multiply the firts and second matriz and save the result en mr
		#pragma omp for
		for(i=0;i<rows1;i++){
		    for(j=0;j<cols2;j++){
		    	suma = 0.0;
		    	for(k=0;k<rows1;k++){
		    		suma += (*(*(m1 + i) + k)) * (*(*(m2 + k) + j));
		    	}
		      *(*(mr + i) + j) = suma;
		    }
        }
	}//Finish the pragma code

	printf("DEBUG 4\n");
    //Writes the result of mr in mr.txt 
    for(i=0;i<rows1;i++){
	    for(j=0;j<cols2;j++){
	      fprintf(stream_writer, "%.2f,", *(*(mr + i) + j) );
	    }
	    fprintf(stream_writer, "%s\n","");
	}

	printf("DEBUG 5\n");
	fclose(stream);
	fclose(stream2);
	fclose(stream_writer);
	free(m1);
	free(m2);
	free(mr);
	printf("\tExcution time: %f ms\n", (float)(clock()-cl)*1000/CLOCKS_PER_SEC);

	return 0;
}
