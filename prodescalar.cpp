#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char **argv)
{
   int rank, size, erro;
   float *v1, *v2, *sv1, *sv2;
   int k, j, nelementos, my_k, maisum;
   float mysoma, soma;
    
   MPI_Init( &argc, &argv );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    
    
   if (rank == 0)
   {
   	printf("Tamanho dos vectores ? ");
   	scanf("%d", &k);
      //k = 21; //????
   	maisum = (k % size)==0 ? 0 : 1;
   	nelementos = ((k/size)+maisum)*size;
   	v1 = new float[nelementos];
   	v2 = new float[nelementos];
   	for(j=0; j<k; j++)
   	{	v1[j]=j;	v2[j]=1;}
		for(j=k; j<nelementos; j++)
   	{	v1[j]=0;	v2[j]=0;}
   	   	
   }

	// broadcast de k a todos os processos
   MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
   
   // reservar espaco para os dados, o ultimo processador podera ficar com zeros no fim
	maisum = (k % size)==0 ? 0 : 1;
	my_k = (k/size)+maisum;
	sv1 = new float[my_k];
	sv2 = new float[my_k];

	// distribui os dados

	erro = MPI_Scatter(v1, my_k, MPI_FLOAT, sv1, my_k, MPI_FLOAT, 0, MPI_COMM_WORLD);
	printf("processo %d recebeu %d elementos, erro=%d\n",rank, my_k, erro);    

	erro = MPI_Scatter(v2, my_k, MPI_FLOAT, sv2, my_k, MPI_FLOAT, 0, MPI_COMM_WORLD);
	printf("processo %d recebeu %d elementos, erro=%d\n",rank, my_k, erro);    
    
  
   // calcula produto interno
   mysoma = 0.0;
   for(j=0; j<my_k; j++){
      mysoma += sv1[j]*sv2[j];
      printf("processo %d mysoma = %f\n",rank,mysoma);
   }
   		
   	
   // processo 0 obtem resultado
   erro = MPI_Reduce(&mysoma, &soma,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD); 
   	
   if (rank == 0)
   {	printf("Produto interno = %.1f\n", soma);
		delete [] v1;
		delete [] v2;
   }


  delete [] sv1;
  delete [] sv2;
   	
   MPI_Finalize();
    
   return 0;
}
