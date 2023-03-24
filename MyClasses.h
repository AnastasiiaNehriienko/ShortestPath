#pragma once
#include <vector>
class Bee {
	int status;
	int solution_quantity;
	int** matrix;
public:
	std::vector<int> solution;
	Bee(int stat, int** matrix);
	int get_solution_quantity() { return solution_quantity; }
	void generate_new_random_solution();
	void generate_changed_solution(int amount_of_place_to_change);
	void set_solution_quantity(int quantity) { solution_quantity = quantity; }
private:
	void generate_random_solution();
};
class Hive {
public:
	std::vector<Bee*> active_bees;
	std::vector<Bee*> scout_bees;
	std::vector<int> best_solution;
	int best_solution_quantity;
	int** matrix;
public:
	Hive(int** matrix, int sc_amount, int act_amount);
	void find_best(int sc_amount, int act_amount);
	int get_best_solution_quantity() { return best_solution_quantity; }
	void progress_scouts();
	void dance();
	void progress_actives(int amount_of_place_to_change);
	void show_best_solution();
};