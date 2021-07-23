#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


constexpr int winx = 1000, winy = 800, tile_size = 50,count_x = winx/tile_size,count_y = winy/tile_size,ray_res = 50;

void init_arr();

int _res(int);

void setTile(int i, int j,int status);

void addLightSrc(int x, int y);

void drawMapInp(sf::RenderWindow&);

void drawLightSrc(sf::RenderWindow&);

void drawRays(sf::RenderWindow&);

void solve();

void test_draw(sf::RenderWindow&);

void addNoise();