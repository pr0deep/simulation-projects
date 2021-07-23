#include "result.h"

Solution_TSP::Solution_TSP(int pts_ct, float d, int gn, std::vector<int> pth, std::pair<int, int> pts[MAX_NODES_STP],float f1,float f2,int i1,int i2) :pts_count(pts_ct), distance(d), gen_no(gn),fitnessrule(f1),mutation_rate(f2),crossoverbalance(i1),pop_count(i2) {

	path = pth;

	for (int i = 0; i < pts_ct; i++) {
		points.push_back(pts[i]);
	}
}