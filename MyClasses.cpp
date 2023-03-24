#include "MyClasses.h"
#include <iostream>
#include <vector>
Bee::Bee(int stat, int** matr) {
	matrix = matr;
	int status = stat; //0=Scout, 1=Active
	generate_random_solution();
}
void Bee::generate_random_solution() {
	bool end = 0;
	solution.push_back(0);
	solution_quantity = 0;
	int node = 0;
	while (!end) {
		int next = 0, next_code = 0;
		while (next_code == 0) {
			next = rand() % 100;
			next_code = matrix[node][next];
		}
		solution_quantity += next_code;
		solution.push_back(next);
		if (next == 99) {
			end = 1;
		}
		node = next;
	}
}
void Bee::generate_new_random_solution() {
	bool end = 0;
	std::vector<int> sol;
	sol.push_back(0);
	int sol_quantity = 0;
	int node = 0;
	while (!end) {
		int next = 0, next_code = 0;
		while (next_code == 0) {
			next = rand() % 100;
			next_code = matrix[node][next];
		}
		sol_quantity += next_code;
		sol.push_back(next);
		if (next == 99) {
			end = 1;
		}
		node = next;
	}
	if (sol_quantity < solution_quantity) {
		solution = sol;
		solution_quantity = sol_quantity;
	}
}
void Bee::generate_changed_solution(int amount_of_place_to_change) {
	int* rand_change = new int[amount_of_place_to_change];
	for (int i = 0; i < amount_of_place_to_change; ++i) {
		rand_change[i] = rand() % (solution.size() / 2 - 2) + solution.size() / 2;
		std::vector <int> changed_nodes;
		int quantity = 0;
		int end = 0;
		for (int j = 0; j <= rand_change[i]; ++j) {
			changed_nodes.push_back(solution[j]);
			if (j > 0) {
				quantity += matrix[solution[j - 1]][solution[j]];
			}
		}
		int node = solution[rand_change[i]];
		while (!end) {
			int next = 0, next_code = 0;
			while (next_code == 0) {
				next = rand() % 100;
				next_code = matrix[node][next];
			}
			quantity += next_code;
			changed_nodes.push_back(next);
			if (next == 99) {
				end = 1;
			}
			node = next;
		}
		if (quantity < solution_quantity) {
			solution_quantity = quantity;
			solution = changed_nodes;
		}

	}
	delete[]rand_change;
}
Hive::Hive(int** matr, int sc_amount, int act_amount) {
	matrix = matr;
	int total_act_amount = act_amount * sc_amount;
	int best_sol = 0;
	int best_bee = 0;
	bool is_active = false;
	for (int i = 0; i < sc_amount; ++i) {
		Bee* b = new Bee(0, matrix);
		if (i == 0) {
			best_sol = b->get_solution_quantity();
			best_bee = i;
		}
		else if (b->get_solution_quantity() < best_sol) {
			best_sol = b->get_solution_quantity();
			best_bee = i;
		}
		scout_bees.push_back(b);
	}
	best_solution = scout_bees[best_bee]->solution;
	best_solution_quantity = best_sol;
	for (int i = 0; i < total_act_amount; ++i) {
		Bee* b = new Bee(1, matrix);
		if (b->get_solution_quantity() < best_sol) {
			best_sol = b->get_solution_quantity();
			best_bee = i;
			is_active = true;
		}
		active_bees.push_back(b);
	}
	if (is_active) {
		best_solution = active_bees[best_bee]->solution;
		best_solution_quantity = best_sol;
	}
}
void Hive::progress_scouts() {
	for (int i = 0; i < scout_bees.size(); ++i) {
		scout_bees[i]->generate_new_random_solution();
	}

}
void Hive::find_best(int sc_amount, int act_amount) {
	int best_sol = 0;
	int best_bee = 0;
	bool is_active = false;
	int total_act_amount = act_amount * sc_amount;
	for (int i = 0; i < sc_amount; ++i) {
		if (i == 0) {
			best_sol = scout_bees[i]->get_solution_quantity();
			best_bee = i;
		}
		else if (scout_bees[i]->get_solution_quantity() < best_sol) {
			best_sol = scout_bees[i]->get_solution_quantity();
			best_bee = i;
		}
	}
	if (best_sol < best_solution_quantity) {
		best_solution = scout_bees[best_bee]->solution;
		best_solution_quantity = best_sol;
	}
	for (int i = 0; i < total_act_amount; ++i) {
		if (active_bees[i]->get_solution_quantity() < best_sol) {
			best_sol = active_bees[i]->get_solution_quantity();
			best_bee = i;
			is_active = true;
		}
	}
	if (is_active && best_sol < best_solution_quantity) {
		best_solution = active_bees[best_bee]->solution;
		best_solution_quantity = best_sol;
	}
}
void Hive::dance() {
	int act_for_sc = active_bees.size() / scout_bees.size();
	for (int i = 0; i < scout_bees.size(); ++i) {
		for (int j = i * act_for_sc; j < (i + 1) * act_for_sc; ++j) {
			if (scout_bees[i]->get_solution_quantity() < active_bees[j]->get_solution_quantity()) {
				active_bees[j]->solution = scout_bees[i]->solution;
				active_bees[j]->set_solution_quantity(scout_bees[i]->get_solution_quantity());
			}
		}
	}
}
void Hive::progress_actives(int amount_of_place_to_change) {
	for (int i = 0; i < active_bees.size(); ++i) {
		active_bees[i]->generate_changed_solution(amount_of_place_to_change);
	}
}
void Hive::show_best_solution() {
	std::cout << "\nBest Solution: ";
	for (int i = 0; i < best_solution.size(); ++i) {
		std::cout << best_solution[i];
		if (i == best_solution.size() - 1)
			std::cout << "\n";
		else std::cout << " ";
	}
}
