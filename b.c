#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void *f(int **X, int n);
void imprimeMatriz(int **X, int n);
void liberaMatriz(int **X, int n);

struct arg_struct
{
    int matriz;
    int tamanho;
}*args;


int main(void)
{

    int **X, n;
    args = malloc(sizeof(struct arg_struct)*1);
   

    printf("Tamanho da matriz: ");
    scanf("%d", &n);

    int threadId[n];
    pthread_t threads[n];
    pthread_barrier_t bar1, bar2;

    X = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        X[i] = malloc(n * sizeof(int));
    }

    pthread_barrier_init(&bar1, NULL, n);
    pthread_barrier_init(&bar1, NULL, n + 1);

    for (int i = 0; i < n; i++)
    {
        threadId[i] = pthread_create(&threads[i], NULL, (void *)f, (void *)X);
    }

    args->matriz = X;
    args->tamanho = n;

    f(X, n);
    imprimeMatriz(X, n);

    return 0;
}

void *f(int **X, int n)
{
    srand(time(NULL));
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (j == 0)
            {
                X[i][j] = rand() % 100;
            }
            else
            {
                X[i][j] = X[rand() % n][rand() % j];
            }
        }
    }
}

void imprimeMatriz(int **X, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", X[i][j]);
        }
        printf("\n");
    }
    liberaMatriz(X, n);
}

void liberaMatriz(int **X, int n) {
    for (int i = 0; i < n; i++)
    {
        free(X[i]);
    }
    free(X);    
}