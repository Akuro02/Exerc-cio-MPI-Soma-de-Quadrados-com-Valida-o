#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int *data = NULL;
    int *vetorFinal = NULL;
    int *vetorLocal = NULL;
    int somaLocal = 0;
    int somaFinal = 0;
    int tamanhoTotal = 40;
    int tamanhoChunk;

    int local = 1;
    int total;

    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    // Pega o número total de processos em execução
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Pega o identificador (rank) do processo atual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Dividir os dados no vetor
    tamanhoChunk = tamanhoTotal / size;
    if(rank == 0){
        data = (int *)malloc(tamanhoTotal * sizeof(int));
        for(int i = 0; i < tamanhoTotal; i++){
            data[i] = i+1;
        }
    }
    // DATA RETEM O VETOR COM OS NUMEROS A SEREM SOMADOS

    // enviar data para processos somarem
    vetorLocal = (int *)malloc(tamanhoChunk * sizeof(int));

    MPI_Scatter(data, tamanhoChunk, MPI_INT, vetorLocal, tamanhoChunk, MPI_INT, 0, MPI_COMM_WORLD); // distribui os dados para cada processo.
    /* MPI_Scatter(data = Onde esta os dados a serem dispersos
    tamanhoChunk, = O numero de elementos no buffer a ser enviado
    MPI_INT, = Tipo de dados sendo enviados
    vetorLocal, = Onde os dados serao recebidos
    tamanhoChunk, = Numero de elementos no buffer de recebimento
    MPI_INT, = Tipo de dados sendo recebidos 
    0, = id do processo que esta enviando os dados
    MPI_COMM_WORLD = comunicador
    ); 
    */
    printf("Processo %i recebeu: ", rank);
    for(int i = 0; i < tamanhoChunk; i++){
        printf("%i, ", vetorLocal[i]);
    }
    printf("\n");

    for(int i = 0; i < tamanhoChunk; i++){
        somaLocal += vetorLocal[i] * vetorLocal[i];
    }

    printf("Processo %i: soma local dos quadrados = %i\n", rank, somaLocal);

    MPI_Reduce(&somaLocal, &somaFinal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        free(data);
        free(vetorFinal);
    }

    free(vetorLocal);

    MPI_Finalize();

    // Verificacao com a formula
    int verSoma = 0;
    verSoma = (tamanhoTotal*(tamanhoTotal+1)*(2*tamanhoTotal+1)) / 6;


    if(rank == 0){
        printf("\n\nsoma paralela dos quadrados = %i\n", somaFinal);
        printf("soma sequencial esperada = %i\n\n", verSoma);
        if(somaFinal == verSoma){
            printf("As somas conferem!\n");
        }
        else{
            printf("As somas NÃO conferem!\n");
        }
    }
    
    return 0;
}