#pragma once

#include <vector>

constexpr int MAX_NODES_STP = 30;

class Solution_TSP {
public:
	float distance;
	std::vector<int> path;
	int gen_no;
	std::vector<std::pair<int, int>> points;
	int pts_count;
	int pop_count;

	//adv params
	float fitnessrule, mutation_rate; //params for algo..
	int crossoverbalance;

	Solution_TSP(int, float, int, std::vector<int>, std::pair<int, int>[MAX_NODES_STP],float,float,int,int);
};