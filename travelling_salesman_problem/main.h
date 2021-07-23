#pragma once
#include <sfml/Graphics.hpp>
#include <vector>

#define SCREEN_OFFSET_X 500
#define SCREEN_OFFSET_Y 100

void init_circles(int, std::vector<sf::CircleShape>&,std::vector<std::pair<int,int>>);
void init_tsp(int);