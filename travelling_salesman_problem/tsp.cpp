#include "tsp.h"
#include <iostream>

TSP::TSP(int n) :node_count(n) {

}

//initialise functions...

void TSP::init(int clientW, int clientH, int offset, int pop_count, float fitr, float mutr, int crossbalance) {
	fitnessrule = fitr;
	mutation_rate = mutr;
	crossoverbalance = crossbalance;

	gen_rand_map(node_count, clientW, clientH, offset);

	init_distances();

	init_population(pop_count);
}

void TSP::gen_rand_map(int n, int w, int h, int offset) {
	for (int i = 0; i < n; i++)
		points[i] = std::make_pair(rand() % (w - offset) + offset, rand() % (h - offset) + offset);
}

void TSP::init_distances() {
	int n = node_count;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			float tempdist = sqrt(_sqr((points[i].first - points[j].first)) + _sqr((points[i].second - points[j].second)));
			distances[i][j] = tempdist;
			distances[j][i] = tempdist;
		}
	}
}

void TSP::init_population(int pop_count) {
	int n = node_count;
	std::vector<int> ipath;
	for (int i = 0; i < n; i++)
		ipath.push_back(i);


	for (int i = 0; i < pop_count; i++)
		population.push_back(init_indiv(ipath));

}

std::vector<int> TSP::init_indiv(std::vector<int> ipath) {
	std::vector<int> new_indv = ipath;
	std::random_shuffle(new_indv.begin(), new_indv.end());
	return new_indv;
}



/* fitness functions ..*/
float TSP::get_fitness(std::vector<int> path) {
	float fitness = 0;
	for (int i = 0; i < path.size(); i++)
		fitness += distances[i][path[i]];
	fitness = 1 / fitness;
	return fitness;
}

std::vector<float> TSP::fitness() {
	std::vector<float> f(population.size(), 0);
	for (int i = 0; i < population.size(); i++) {
		f[i] = get_fitness(population[i]);
	}
	return f;
}

/* crossover function ... */
std::vector<int> TSP::get_crossover(std::vector<int> p1, std::vector<int> p2) {
	int crossover_balance = crossoverbalance;
	int n = p1.size();
	std::vector<int> child(n, 0);

	std::vector<bool> check(n, false);

	int rand_pt = rand() % n;

	for (int i = rand_pt; i < n && i < rand_pt + crossover_balance; i++) {
		child[i] = p1[i];
		check[child[i]].flip();

	}
	int j = 0;
	int i = 0;
	while (i < n) {
		if (i<rand_pt || i>=rand_pt + crossover_balance) {
			for (; j < n; j++) {
				int t = p2[j];
				if (!check[t]) {
					child[i] = t;
					check[t].flip();
					j++;
					break;
				}
			}
		}
		i++;
	}

	return child;
}

bool TSP::cmp_fit(size_t i, size_t j, std::vector<float> fit) {
	return (fit[i] > fit[j]);
}

void TSP::crossover() {
	int cur_pop_size = population.size();
	int pts_count = population[0].size();
	//filling the fitness arr
	std::vector<float> cur_fitness = fitness();
	//getting the sort perm..

	std::vector<int> perm(population.size());
	std::iota(perm.begin(), perm.end(), 0);
	std::sort(perm.begin(), perm.end(), [&](size_t i, size_t j) {return cmp_fit(i, j, cur_fitness); });

	//creating sorted arrays...
	std::vector<float> sorted_fitness(cur_pop_size);
	std::vector<std::vector<int>> sorted_population(cur_pop_size);

	std::transform(perm.begin(), perm.end(), sorted_fitness.begin(), [&](size_t i) {return cur_fitness[i]; });
	std::transform(perm.begin(), perm.end(), sorted_population.begin(), [&](size_t i) {return population[i]; });

	//copy sorted to main arr...
	population = sorted_population;
	cur_fitness = sorted_fitness;

	//deleting the last ...
	int j = (int)(fitnessrule * (float)cur_pop_size);
	for (int i = j; i < cur_pop_size; i++)
	{
		population[i].clear();
	}
	//selecting first ..
	for (int i = 0; i < (int)(fitnessrule * (float)cur_pop_size); i += 2) {
		if (j < cur_pop_size)
			population[j] = (get_crossover(population[i], population[i + 1]));
		else
			population.push_back(get_crossover(population[i], population[i + 1]));
		j++;
	}

	//freeing the mem..
	population.resize(j);
	population.shrink_to_fit();

}

//mutate functions...

void TSP::mutate_indiv(std::vector<int>& v, int s) {
	for (int i = 0; i < s && i < v.size(); i++) {
		int j = rand() % v.size();
		int p = rand() % v.size();
		std::swap(v[p], v[j]);
	}
}
void TSP::mutate() {
	for (int i = 0; i < population.size(); i++) {
		mutate_indiv(population[i], (int)(mutation_rate * (float)population.size()));
	}
}


//evolve functions...

void TSP::evolve() {
	if (gen_no > 1000)
		return;

	crossover();
	//print_all_pop(pts);
	mutate();
	//print_all_pop(pts);
	gen_no++;
}


//export result...
float TSP::get_path_dist(std::vector<int> path) {
	float dist = 0;
	for (int i = 0; i < path.size(); i++)
		dist += distances[i][path[i]];
	return dist;
}

Solution_TSP TSP::get_result() {
	int cur_pop_size = population.size();
	int pts_count = population[0].size();
	//filling the fitness arr
	std::vector<float> cur_fitness = fitness();
	//getting the sort perm..

	std::vector<int> perm(population.size());
	std::iota(perm.begin(), perm.end(), 0);
	std::sort(perm.begin(), perm.end(), [&](size_t i, size_t j) {return cmp_fit(i, j, cur_fitness); });

	//creating sorted arrays...
	std::vector<float> sorted_fitness(cur_pop_size);
	std::vector<std::vector<int>> sorted_population(cur_pop_size);

	std::transform(perm.begin(), perm.end(), sorted_fitness.begin(), [&](size_t i) {return cur_fitness[i]; });
	std::transform(perm.begin(), perm.end(), sorted_population.begin(), [&](size_t i) {return population[i]; });

	//copy sorted to main arr...
	population = sorted_population;
	cur_fitness = sorted_fitness;

	//using the abv result...
	std::vector<int> _path = population[0];

	Solution_TSP result(node_count,get_path_dist(population[0]), gen_no, _path, points,fitnessrule,mutation_rate,crossoverbalance,cur_pop_size);
	return result;
}