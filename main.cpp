#include <iostream>
#include <vector>
#include "Funcs.h"
#include "MyClasses.h"
#include <chrono>
#include <fstream>

int main() {
	srand(time(NULL));
	int** matrix = new int* [300];
	for (int i = 0; i < 300; ++i) {
		matrix[i] = new int[300];
	}
	create_problem_matrix(matrix);
	int scouts = 2, active = 6, amount_of_place_to_change = 2;
	double dur;
	int d_pl, d_s, d_a;
	int res;
	int r_pl, r_s, r_a;
	auto start = std::chrono::high_resolution_clock::now();
	Hive hive(matrix, scouts, active);
	int iterations = 50;
	for (int i = 0; i < iterations; ++i) {
		if (i > 0) {
			hive.progress_scouts();
		}
		hive.dance();
		hive.progress_actives(amount_of_place_to_change);
		hive.find_best(scouts, active);
		/*std::cout << "Best sol: " << hive.get_best_solution_quantity() << std::endl;*/
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	dur = (double)duration.count() / 1000;
	res = hive.get_best_solution_quantity();
	std::cout << "Duration in milisec: " << dur << "\t" << "result: " << res;
	hive.show_best_solution();
	for (int i = 0; i < 300; ++i) {
		delete[]matrix[i];
	}
	delete[] matrix;
	return 0;
}
