#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void Output_matrix(int** G1, int n) {
	for (int i = 0; i < n; i++) {				//вывод матрицы
		for (int j = 0; j < n; j++) {
			printf(" %d", G1[i][j]);
		}
		printf("\n");
	}

	return;
}

int** Otogd_tops(int **G1, int n) {
	int v1_keyboard, v2_keyboard, v_tmp;

	printf("\nОтождествление вершин матрицы\n");
	printf("Введите вершину №1 -> ");
	scanf("%d", &v1_keyboard);
	printf("Введите вершину №2 -> ");
	scanf("%d", &v2_keyboard);
	printf("\n");

	int** G1_otogd = (int**)malloc((n - 1) * sizeof(int*));
	for (int i = 0; i < (n - 1); i++) {
		G1_otogd[i] = (int*)malloc((n - 1) * sizeof(int));
	}

	if (v1_keyboard > v2_keyboard) {
		v_tmp = v1_keyboard;
		v1_keyboard = v2_keyboard;
		v2_keyboard = v_tmp;
	}
	v1_keyboard--;
	v2_keyboard--;

	for (int i = 0; i < n; i++) {				//"ИЛИ" для строки
		if (i == v1_keyboard) {
			for (int j = 0; j < n; j++) {
				G1[v1_keyboard][j] = G1[v1_keyboard][j] || G1[v2_keyboard][j];		 
				G1[v2_keyboard][j] = 0;
			}
		}
	}

	for (int j = 0; j < n; j++) {				//"ИЛИ" для столбца
		if (j == v1_keyboard) {
			for (int i = 0; i < n; i++) {
				G1[i][v1_keyboard] = G1[i][v1_keyboard] || G1[i][v2_keyboard];		
				G1[i][v2_keyboard] = 0;
			}
		}
	}
	int i_otogd = 0;							//отождествление вершин
	int j_otogd = 0;

	for (int i = 0; i < n; i++) {
		if (i != v2_keyboard) {
			for (int j = 0; j < n; j++) {
				if (j != v2_keyboard) {
					if ((i_otogd == v1_keyboard) and (i_otogd == j_otogd))  G1_otogd[i_otogd][j_otogd] = 1; 	//петля
					else G1_otogd[i_otogd][j_otogd] = G1[i][j];
					//printf(" %d", G1_otogd[i_otogd][j_otogd]);
					j_otogd++;
				}
			}
			i_otogd++;
			j_otogd = 0;
			//printf("\n");
		}	
	}
	
	return G1_otogd;
}

int ** Connection_rib(int** G1, int n) {
	int v1_keyboard, v2_keyboard, v_tmp;

	printf("\nСтягивание ребра матрицы\n");
	printf("Введите вершину №1 -> ");
	scanf("%d", &v1_keyboard);
	printf("Введите вершину №2 -> ");
	scanf("%d", &v2_keyboard);
	printf("\n");

	int** G1_connect = (int**)malloc((n - 1) * sizeof(int*));
	for (int i = 0; i < (n - 1); i++) {
		G1_connect[i] = (int*)malloc((n - 1) * sizeof(int));
	}

	if (v1_keyboard > v2_keyboard) {
		v_tmp = v1_keyboard;
		v1_keyboard = v2_keyboard;
		v2_keyboard = v_tmp;
	}
	v1_keyboard--;
	v2_keyboard--;

	for (int i = 0; i < n; i++) {			//"ИЛИ" для строки
		if (i == v1_keyboard) {
			for (int j = 0; j < n; j++) {
				G1[v1_keyboard][j] = G1[v1_keyboard][j] || G1[v2_keyboard][j];
				G1[v2_keyboard][j] = 0;
			}
		}
	}

	for (int j = 0; j < n; j++) {			//"ИЛИ" для столбца
		if (j == v1_keyboard) {
			for (int i = 0; i < n; i++) {
				G1[i][v1_keyboard] = G1[i][v1_keyboard] || G1[i][v2_keyboard];
				G1[i][v2_keyboard] = 0;
			}
		}
	}


	int i_otogd = 0;					//стягивание вершин
	int j_otogd = 0;

	for (int i = 0; i < n; i++) {
		if (i != v2_keyboard) {
			for (int j = 0; j < n; j++) {
				if (j != v2_keyboard) {
					if ((i_otogd == v1_keyboard) and (i_otogd == j_otogd))  G1_connect[i_otogd][j_otogd] = 0; 	//удаление петли
					else G1_connect[i_otogd][j_otogd] = G1[i][j];
					//printf(" %d", G1_otogd[i_otogd][j_otogd]);
					j_otogd++;
				}
			}
			i_otogd++;
			j_otogd = 0;
			//printf("\n");
		}
	}

	return G1_connect;
}

int** Destroy_tops(int** G1, int n) {
	int v_keyboard, v2_keyboard, v_tmp;

	printf("\nРасщепление вершины матрицы\n");
	printf("Введите вершину -> ");
	scanf("%d", &v_keyboard);
	printf("\n");
	n++;

	int** G1_destroy = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		G1_destroy[i] = (int*)malloc(n * sizeof(int));
	}

	v_keyboard--;


	int i_destroy = 0;							//расщепление вершины 
	int j_destroy = 0;


	for (int i = 0; i < n-1; i++) {
		if (i == v_keyboard) {
			for (int j = 0; j < n - 1; j++) {//повторная запись данных для новой вершины (строка)
				G1_destroy[i_destroy][j_destroy] = G1[i][j];
				G1_destroy[i_destroy + 1][j_destroy] = G1[i][j];
					
				if (j == v_keyboard) {
					G1_destroy[i_destroy][j_destroy + 1] = G1[i][j];
					G1_destroy[i_destroy + 1][j_destroy + 1] = G1[i][j];
					j_destroy++;
				}
				j_destroy++;
			}
				
			i_destroy += 2;
			j_destroy = 0;
		}

		else {
			for (int j = 0; j < n - 1; j++) {
				if (j == v_keyboard) {
					G1_destroy[i_destroy][j_destroy] = G1[i][j];
					G1_destroy[i_destroy][j_destroy + 1] = G1[i][j];	//повторная запись данных для новой вершины (столбец)
					j_destroy += 2;
				}
				else {
					G1_destroy[i_destroy][j_destroy] = G1[i][j];
					j_destroy++;
				}
			}

			i_destroy++;
			j_destroy = 0;
		}
	}

	G1_destroy[v_keyboard][v_keyboard + 1] = 1;
	G1_destroy[v_keyboard + 1][v_keyboard] = 1;

	return G1_destroy;
}

int main(){
	int menu_answer;
	int n, v1, v2;
	int start = 1;


	setlocale(0, "rus");
	printf("Введите размер для формировнаия матрицы -> ");
	scanf("%d", &n);
	printf("\n");


	int** G1 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		G1[i] = (int*)malloc(n * sizeof(int));
	}

	srand(time(0));
	for (int i = 0; i < n; i++) {				//формирование матрицы смежности
		for (int j = 0; j < n; j++) {
			if (i == j) G1[i][j] = 0;
			else  G1[i][j] = rand() % 2;
			printf(" %d", G1[i][j]);
		}
		printf("\n");
	}
	//меню
	printf("\n1 - Отождествление вершины матрицы\n");
	printf("2 - Стягивание ребра матрицы\n");
	printf("3 - Расщепление вершины матрицы\n");
	printf("0 - Выход\n");
	while (start){
		printf("Введите выбранный вариант -> ");
		scanf("%d", &menu_answer);

		if (menu_answer == 0) {
			start = 0;
		}

		else {
			switch (menu_answer) {
			case(1): {
				G1 = Otogd_tops(G1, n);
				n--;
				Output_matrix(G1, n);
				printf("\n\n");
				break; 
			}

			case(2): {
				G1 = Connection_rib(G1, n);
				n--;
				Output_matrix(G1, n);
				printf("\n\n");
				break;
			}

			case(3): {
				G1 = Destroy_tops(G1, n);
				n++;
				Output_matrix(G1, n);
				printf("\n\n");
				break;
			}

			case(0): {
				break;
			}  
			}
		}	
	}	
}
