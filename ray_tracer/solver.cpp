#include "solver.h"
#define PI 3.14

bool map[winy][winx];
bool tiles[winy / tile_size][winx / tile_size];
std::vector<std::vector<int>> light; //stores all the light sources...
std::vector<std::vector<int>> rays; //stores all the solved rays...

void init_arr() {
	for (int i = 0; i < winx; i++) {
		for (int j = 0; j < winy; j++) {
			map[j][i] = 0;
		}
	}

	for (int i = 0; i < count_x; i++) {
		for (int j = 0; j < count_y; j++)
			tiles[j][i] = 0;
	}
}

int get_r() {
	int r = rand();
	int t = r % 2;
	if (t)
		return -10*sin(r);
	return 10*sin(r);
}

void addNoise() {
	for (auto& it : light) {
		it[0] += get_r();
		it[1] += get_r();
	}
}

int _res(int x) { 
	return x / tile_size;
}

void setTile(int i, int j,int status) {
	bool st;
	if (status) st = true;
	else st = false;

	tiles[i][j] = st;
	for (int k = i * tile_size; k < (i + 1) * tile_size; k++) 
		for (int r = j * tile_size; r < (j + 1) * tile_size; r++)
			map[k][r] = st;
	
}

void drawMapInp(sf::RenderWindow& win) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color::White);
	rs.setOutlineColor(sf::Color::Blue);
	rs.setOutlineThickness(1.5f);
	rs.setSize(sf::Vector2f(tile_size, tile_size));

	for (int i = 0; i < count_y; i++) {
		for (int j = 0; j < count_x; j++) {
			if (tiles[i][j]) {
				rs.setPosition(j*tile_size, i*tile_size);
				win.draw(rs);
			}
		}
	}
}

void test_draw(sf::RenderWindow& win) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color::White);
	rs.setSize(sf::Vector2f(1, 1));

	for (int i = 0; i < winx; i++) {
		for (int j = 0; j < winy; j++) {
			if (map[j][i]) {
				rs.setPosition(i,j);
				win.draw(rs);
			}
		}
	}
}

void drawRays(sf::RenderWindow& win) {
	int cur_ray = 0;
	for (auto it : light) {
		for (int i = 0; i <= ray_res; i++) {
			sf::Vertex line[] =
		{
			//	sf::Vertex(sf::Vector2f(rays[cur_ray][0], rays[cur_ray][1])),
				sf::Vertex(sf::Vector2f(rays[cur_ray][0],rays[cur_ray][1])),
				sf::Vertex(sf::Vector2f(it[0], it[1]))
			};
			win.draw(line, 2, sf::Lines);
			cur_ray++;

		}
	}
}

void drawLightSrc(sf::RenderWindow& win) {
	sf::CircleShape cs;
	cs.setRadius(4);
	cs.setFillColor(sf::Color::White);
	for (auto it : light) {
		cs.setPosition(it[0], it[1]);
		win.draw(cs);
	}
}


void solve() {
	//delete the prev rays..
	rays.clear();
	rays.shrink_to_fit();


	double ray_theta, ray_slope, ray_c, theta_step_size = 360 / (ray_res);
	int cx, cy, _x, _y;

	for (auto it : light) {
		for (int r = 0; r <= ray_res; r++) {
			//shoot r rays...
			cx = it[0];
			cy = it[1];

			ray_theta = r * theta_step_size;
			ray_slope = tan(ray_theta * PI / 180);
			ray_c = cy - ray_slope * cx;

			if ((ray_theta >= 0 && ray_theta <= 90) || (ray_theta >= 270 && ray_theta < 360)) {
				for (_x = cx + 1; _x < winx; _x++) {
					_y = ray_slope * _x + ray_c;
					if (_y >= 0 && _y < winy && map[_y][_x]) {
						cx = _x;
						cy = _y;
						break;
					}

				}
				if (_x == winx) {
					cx = _x;
					_y = ray_slope * _x + ray_c;
					cy = _y;
				}
			}

			else {
				for (_x = cx - 1; _x > 0; _x--) {
					_y = ray_slope * _x + ray_c;
					if (_y >= 0 && _y < winy && map[_y][_x]) {
						cx = _x;
						cy = _y;
						break;
					}

				}
				if (_x == 0) {
					cx = _x;
					_y = ray_slope * _x + ray_c;
					cy = _y;
				}

			}

			std::vector<int>temp(2);
			temp[0] = cx;
			temp[1] = cy;

			rays.push_back(temp);
		}

	}
	return;
}

void addLightSrc(int x, int y){
	std::vector<int> t(2);
	t[0] = x;
	t[1] = y;
	light.push_back(t);
}






