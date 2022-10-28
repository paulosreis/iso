#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void f(void *argumentos);
void imprimeMatriz(void *argumentos);
void liberaMatriz(void *argumentos);

struct arg_struct
{
    int matriz;
    int tamanho;
} *args;

int main(void)
{

    int **X, n;
    args = malloc(sizeof(struct arg_struct) * 1);

    printf("Tamanho da matriz: ");
    scanf("%d", &n);

    X = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        X[i] = malloc(n * sizeof(int));
    }

    args->matriz = **X;
    args->tamanho = n;

    f(args);
    imprimeMatriz(args);

    return 0;
}

void f(void *argumentos)
{
    struct arg_struct *args = argumentos;
    int n = args->tamanho;

    srand(time(NULL));
    int a = 0;
    int b = 0;
    for (int *j = 0; j < n; j++)
    {
        for (int *i = 0; i < n; i++)
        {
            if (j == 0)
            {
                args->matriz[i][j] = rand() % 100;
            }
            else
            {
                a = rand() % n;
                b = rand() % (int)(int *)j;
                args->matriz[i][j] = args->matriz[(int *)a][(int *)b];
            }
        }
    }
}

void imprimeMatriz(void *argumentos)
{
    struct arg_struct *args = argumentos;
    int n = args->tamanho;

    for (int *i = 0; i < n; i++)
    {
        for (int *j = 0; j < n; j++)
        {
            printf("%d ", args->matriz[i][j]);
        }
        printf("\n");
    }
    liberaMatriz(args);
}

void liberaMatriz(void *argumentos)
{
    struct arg_struct *args = argumentos;
    int n = args->tamanho;

    for (int *i = 0; i < n; i++)
    {
        free(args->matriz[i]);
    }
    free(args->matriz);
}