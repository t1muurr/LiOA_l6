#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void Output_matrix(int **G1, int n)
{ // вывод кольцевой суммы
    int col_one;
    int isolate_top[10];
    int flag = 0;
    int flag_j = 0;

    for (int i = 0; i < n; i++)
    {
        isolate_top[i] = -1;
        col_one = 0;
        for (int j = 0; j < n; j++)
        {
            if (G1[i][j] == 1)
                col_one++;
        }

        if (col_one == 0)
        {
            isolate_top[i] = i;
        }
    }
    for (int i = 0; i < n; i++)
    {
        flag = 0;
        for (int i_is = 0; i_is < n; i_is++)
        {
            if (i == isolate_top[i_is])
            {

                flag = 1;
                break;
            }
        }
        if (flag == 1)
            continue;
        for (int j = 0; j < n; j++)
        {
            flag_j = 0;
            for (int i_is = 0; i_is < n; i_is++)
            {
                if (j == isolate_top[i_is])
                {
                    flag_j = 1;
                    break;
                }
            }

            if (flag_j == 0)
                printf(" %d", G1[i][j]);
        }
        printf("\n");
    }

    return;
}

void Print_matrix(int **G, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf(" %d", G[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n1, n2, n_tmp, menu_answer, min_n, max_n;
    int start = 1;

    setlocale(0, "rus");
    printf("Введите размер матрицы М1 -> ");
    scanf("%d", &n1);
    printf("Введите размер матрицы М2 -> ");
    scanf("%d", &n2);
    printf("\n");

    if (n2 > n1)
    {
        n_tmp = n1;
        n1 = n2;
        n2 = n_tmp;
        min_n = n1;
        max_n = n2;
    }
    min_n = n2;
    max_n = n1;

    int **G1 = (int **)malloc(min_n * sizeof(int *));
    for (int i = 0; i < min_n; i++)
    {
        G1[i] = (int *)malloc(min_n * sizeof(int));
    }

    int **G2 = (int **)malloc(max_n * sizeof(int *));
    for (int i = 0; i < max_n; i++)
    {
        G2[i] = (int *)malloc(max_n * sizeof(int));
    }

    srand(time(0));
    for (int i = 0; i < min_n; i++)
    { // формирование матрицы смежности М1
        for (int j = 0; j < min_n; j++)
        {
            if (j >= i)
            {
                if (i == j)
                    G1[i][j] = 0;
                else
                {
                    G1[i][j] = rand() % 2;
                    G1[j][i] = G1[i][j];
                }
            }
            printf(" %d", G1[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    for (int i = 0; i < max_n; i++)
    { // формирование матрицы смежности М2
        for (int j = 0; j < max_n; j++)
        {
            if (j >= i)
            {
                if (i == j)
                    G2[i][j] = 0;
                else
                {
                    G2[i][j] = rand() % 2;
                    G2[j][i] = G2[i][j];
                }
            }
            printf(" %d", G2[i][j]);
        }
        printf("\n");
    }
    printf("\n1 - Объединение графов (G = G1 + G2)\n"); // операции над графами
    printf("2 - Пересечение графов (G = G1 * G2)\n");
    printf("3 - Кольцевая сумма графов (G = G1 ^ G2)\n");
    printf("0 - Выход\n");
    while (start)
    {
        printf("\nВведите выбранный вариант -> ");
        scanf("%d", &menu_answer);
        if (menu_answer == 0)
        {
            start = 0;
        }

        else
        {
            switch (menu_answer)
            {
            case (1):
            {
                int **G3 = (int **)malloc(max_n * sizeof(int *));
                for (int i = 0; i < max_n; i++)
                {
                    G3[i] = (int *)malloc(max_n * sizeof(int));
                }

                for (int i = 0; i < max_n; i++)
                {
                    for (int j = 0; j < max_n; j++)
                    {
                        G3[i][j] = G2[i][j];
                    }
                }

                for (int i = 0; i < min_n; i++)
                {
                    for (int j = 0; j < min_n; j++)
                    {
                        G3[i][j] = G2[i][j] | G1[i][j];
                    }
                }

                printf("Результат объединения графов:\n");
                Print_matrix(G3, max_n);
                break;
            }

            case (2):
            {
                int **G3 = (int **)malloc(min_n * sizeof(int *));
                for (int i = 0; i < min_n; i++)
                {
                    G3[i] = (int *)malloc(min_n * sizeof(int));
                }

                for (int i = 0; i < min_n; i++)
                {
                    for (int j = 0; j < min_n; j++)
                    {
                        G3[i][j] = G2[i][j] & G1[i][j];
                    }
                }
                printf("Результат пересечения графов:\n");
                Print_matrix(G3, min_n);
                break;
            }
            case (3):
            {
                int **G3 = (int **)malloc(min_n * sizeof(int *));
                for (int i = 0; i < min_n; i++)
                {
                    G3[i] = (int *)malloc(min_n * sizeof(int));
                }
                for (int i = 0; i < min_n; i++)
                {
                    for (int j = 0; j < min_n; j++)
                    {
                        G3[i][j] = G2[i][j] ^ G1[i][j];
                    }
                }
                printf("Результат кольцевой суммы графов:\n");
                Output_matrix(G3, min_n);
                break;
            }

            case (0):
            {
                break;
            }
            }
        }
    }

    return 0;
}