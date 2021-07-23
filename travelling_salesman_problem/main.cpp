

#include "draw.h"
#include "tsp.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"
#include <thread>

TSP tsp_solver(1);
int _gen = 0;

std::vector<std::vector<int>> prev_paths;

std::vector<sf::CircleShape> points_draw;
bool start_sim = false;
bool show_sim = false;
sf::Clock clk;

bool show_adv = false;
bool show_info = false;


int main(int argc, char* argv[]) {
	//		
	std::string arg_n;
	if (argc > 1) {
		arg_n = argv[1];
		init_tsp(std::atoi(arg_n.c_str()));
	}
	else
		init_tsp(43);


	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	
	sf::RenderWindow window(sf::VideoMode(1300, 800), "Travelling salesman problem", sf::Style::Default , settings);

	sf::Font myfont;
	if (!myfont.loadFromFile("Roboto-Regular.ttf")) { return 0; }


	tsp_solver.evolve();
	Solution_TSP result = tsp_solver.get_result();

	init_circles(result.pts_count, points_draw,result.points);


	while (window.isOpen()) {
		sf::Event event;

		//managing events...
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::Enter) {
					start_sim = !start_sim;
					show_sim = false;
				}
				if (event.key.code == sf::Keyboard::Space) {
					show_sim = !show_sim;
					start_sim = false;
					clk.restart();
				}
				if (event.key.code == sf::Keyboard::B) {
					show_adv = !show_adv;
				}
				if (event.key.code == sf::Keyboard::Tab) {
					show_info = !show_info;
				}
			}
		}



		//graphics..
		window.clear(sf::Color::Black);
		

		//drawing options...
		sf::Text text;
		text.setFont(myfont);
		text.setCharacterSize(28);
		text.setFillColor(sf::Color::White);

		int textoffsety = 40;
		
		if (!show_info)
		{
			//title
			text.setString("Travelling salesman problem(GA)");
			text.setPosition(60, 40);
			window.draw(text);

			text.setCharacterSize(16);
			//model details...
			text.setString("Generation : ");
			text.setPosition(60, 100 + textoffsety);
			window.draw(text);
			text.setString(std::to_string(result.gen_no));
			text.setPosition(200, 100 + textoffsety);
			window.draw(text);

			text.setString("Distance:");
			text.setPosition(60, 100 + 2 * textoffsety);
			window.draw(text);
			text.setString(std::to_string(result.distance));
			text.setPosition(200, 100 + 2 * textoffsety);
			window.draw(text);

			text.setString("Points:");
			text.setPosition(60, 100 + 3 * textoffsety);
			window.draw(text);
			text.setString(std::to_string(result.pts_count));
			text.setPosition(200, 100 + 3 * textoffsety);
			window.draw(text);

			if (!show_adv) {
				//start button...
				text.setString("Press space to check solution..");
				text.setPosition(60, 100 + 9 * textoffsety);
				sf::RectangleShape r1(sf::Vector2f(310, 30));
				r1.setPosition(sf::Vector2f(60 - 10, 100 + 9 * textoffsety - 5));
				r1.setOutlineThickness(0.8f);
				r1.setOutlineColor(sf::Color::White);
				r1.setFillColor(sf::Color::Black);
				window.draw(r1);
				window.draw(text);

				text.setString("Press Enter to start/continue simulation..");
				r1.setPosition(60 - 10, 100 + 11 * textoffsety - 5);
				text.setPosition(60, 100 + 11 * textoffsety);
				window.draw(r1);
				window.draw(text);

				text.setString("Press B to view adv params, TAB for info");
				r1.setPosition(60 - 10, 100 + 13 * textoffsety - 5);
				text.setPosition(60, 100 + 13 * textoffsety);
				window.draw(r1);
				window.draw(text);

			}

			else {
				//displaying adv params...
				text.setString("fitness_rule:");
				text.setPosition(60, 100 + 4 * textoffsety);
				window.draw(text);
				text.setString(std::to_string(result.fitnessrule));
				text.setPosition(200, 100 + 4 * textoffsety);
				window.draw(text);

				text.setString("mutation_rate:");
				text.setPosition(60, 100 + 5 * textoffsety);
				window.draw(text);
				text.setString(std::to_string(result.mutation_rate));
				text.setPosition(200, 100 + 5 * textoffsety);
				window.draw(text);

				text.setString("crossover\nstrength:");
				text.setPosition(60, 100 + 6 * textoffsety);
				window.draw(text);
				text.setString(std::to_string(result.crossoverbalance));
				text.setPosition(200, 100 + 6 * textoffsety);
				window.draw(text);

				text.setString("Population\ncount:");
				text.setPosition(60, 100 + 8 * textoffsety);
				window.draw(text);
				text.setString(std::to_string(result.pop_count));
				text.setPosition(200, 100 + 8 * textoffsety);
				window.draw(text);

				text.setString("thread_id:");
				text.setPosition(60, 100 + 9 * textoffsety);
				window.draw(text);
				std::ostringstream ss;
				ss << std::this_thread::get_id();
				text.setString((ss.str()));
				text.setPosition(200, 100 + 9 * textoffsety);
				window.draw(text);

			}



			//drawing rest...
			for (int i = 0; i < result.path.size() - 1; i++)
			{
				sf::Vertex line[] = {
					sf::Vertex(sf::Vector2f(SCREEN_OFFSET_X + result.points[result.path[i]].first , SCREEN_OFFSET_Y + result.points[result.path[i]].second),sf::Color::White),
					sf::Vertex(sf::Vector2f(SCREEN_OFFSET_X + result.points[result.path[i + 1]].first , SCREEN_OFFSET_Y + result.points[result.path[i + 1]].second),sf::Color::White)
				};
				window.draw(line, 2, sf::Lines);
			}

			//drawing all circles...
			for (int i = 0; i < points_draw.size(); i++)
				window.draw(points_draw[i]);


			if (show_sim) {
				int i;
				sf::Color clr(75, 0, 130);
				sf::Color clr2(82, 0, 107);
				for (i = 0; i < result.path.size() - 1; i++)
				{
					sf::Vertex line[] = {
						sf::Vertex(sf::Vector2f(SCREEN_OFFSET_X + result.points[result.path[i]].first , SCREEN_OFFSET_Y + result.points[result.path[i]].second),clr),
						sf::Vertex(sf::Vector2f(SCREEN_OFFSET_X + result.points[result.path[i + 1]].first , SCREEN_OFFSET_Y + result.points[result.path[i + 1]].second),clr2)
					};
					if (clk.getElapsedTime().asSeconds() > 0.5 * i) {
						window.draw(line, 2, sf::Lines);
						text.setString(std::to_string(i));
						text.setPosition(line[0].position);
						window.draw(text);
						text.setString(std::to_string(i + 1));
						text.setPosition(line[1].position);
						window.draw(text);
					}
					else break;
				}
				if ((i == result.path.size() - 1 || start_sim) && clk.getElapsedTime().asSeconds() > 0.5 * result.path.size()) {
					show_sim = false;

				}

			}
		}
		else {
		//model details...
		int offset = 3;
		sf::RectangleShape rect(sf::Vector2f(window.getSize().x-2*offset, window.getSize().y-2*offset));
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(offset, offset);
		rect.setOutlineThickness((float)offset);
		rect.setOutlineColor(sf::Color::White);

		window.draw(rect);
		text.setCharacterSize(42);

		text.setString("About");
		text.setPosition(600, 100 + textoffsety);
		text.setFillColor(sf::Color::Magenta);
		window.draw(text);
		text.setFillColor(sf::Color::White);

		text.setCharacterSize(20);
		text.setString("A SFML application for GA simulation..");
		text.setPosition(480, 100 + 5*textoffsety);
		window.draw(text);
		text.setString("Author: Pradeep S");
		text.setPosition(550, 100 + 6 * textoffsety);
		window.draw(text);
		
		}
		window.display();

		if (start_sim) {
			tsp_solver.evolve();
			result = tsp_solver.get_result();
		}


	}
	return 0;
}


void init_tsp(int n) {
	//problem params...
	int no_points = n;
	float fitnessrule = 0.7, mutation_rate = 0.1; //params for algo..
	int crossoverbalance = (int)(0.5*n);
	int init_pop_count = 30;
	//client params...
	int cx = 600, cy = 600, offset = 0;

	//running solver...
	tsp_solver = TSP(no_points);
	tsp_solver.init(cx, cy, offset, init_pop_count, fitnessrule, mutation_rate, crossoverbalance);
}


void init_circles(int n,std::vector<sf::CircleShape> &pts,std::vector<std::pair<int,int>> p) {
	float r = 6.0f;
	for (int i = 0; i < n; i++) {
		sf::CircleShape shape(r);
		shape.setPosition(SCREEN_OFFSET_X + p[i].first-r, SCREEN_OFFSET_Y + p[i].second-r);
		shape.setFillColor(sf::Color(100, 250, 50));

		pts.push_back(shape);
	}
	}

