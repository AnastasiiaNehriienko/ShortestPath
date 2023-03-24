#include <iostream>
#include "Funcs.h"
#include <vector>
void create_problem_matrix(int** matrix) {
	int* amount_left = new int[300];
	for (int i = 0; i < 300; ++i) {
		amount_left[i] = 10;
	}
	bool need;
	for (int i = 0; i < 300; ++i) {
		for (int j = i + 1; j < 300; ++j) {
			if (amount_left[i] != 0 && amount_left[j] != 0) {
				need = rand() % 2;
				if (need) {
					matrix[i][j] = rand() % 145 + 5;
					matrix[j][i] = matrix[i][j];
				}
				else {
					matrix[i][j] = 0;
					matrix[j][i] = matrix[i][j];
				}
			}
			else {
				matrix[i][j] = 0;
				matrix[j][i] = matrix[i][j];
			}
			if (matrix[i][j]) {
				amount_left[i]--;
				amount_left[j]--;
			}
		}
		matrix[i][i] = 0;
	}
	if_node_has_no_neighbours(amount_left, matrix);
	//show_problem_matrix(matrix);
	delete[]amount_left;
}
void if_node_has_no_neighbours(int* amount_left, int** matrix) {
	for (int i = 0; i < 300; ++i) {
		if (amount_left[i] == 10) {
			bool end = 0;
			int j = 299;
			while (!end) {
				if (j == i) {
					j--;
					continue;
				}
				if (amount_left[j] != 0)
					end = 1;
				else j--;
			}
			matrix[i][j] = rand() % 145 + 5;;
			matrix[j][i] = matrix[i][j];
		}
	}
}
void show_problem_matrix(int** matrix) {
	for (int i = 0; i < 300; ++i) {
		for (int j = 0; j < 300; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}