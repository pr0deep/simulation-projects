#pragma once

#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <numeric>
#include "result.h"

constexpr auto MAX_NODES = 100;
#define _sqr(x) x*x


class TSP {
public:
	float fitnessrule, mutation_rate; //params for algo..
	int crossoverbalance, gen_no = 0;            //...
	std::pair<int, int> points[MAX_NODES]; // helps to draw pts...
	float distances[MAX_NODES][MAX_NODES]; // helps for calc..

	std::vector<std::vector<int>> population; // current generation...

	int node_count; //stores the no. of pts...

	TSP(int node_count);

	void gen_rand_map(int n, int w, int h, int offset);

	void init(int, int, int, int, float, float, int);

	void init_distances();

	void init_population(int pop_count);

	std::vector<int> init_indiv(std::vector<int> ipath);

	float get_fitness(std::vector<int> path);

	std::vector<float> fitness();

	std::vector<int> get_crossover(std::vector<int> p1, std::vector<int> p2);

	bool cmp_fit(size_t i, size_t j, std::vector<float> fit);

	void crossover();

	void mutate_indiv(std::vector<int>& v, int s);

	void mutate();

	void evolve();

	Solution_TSP get_result();
	
	float get_path_dist(std::vector<int> p);
};