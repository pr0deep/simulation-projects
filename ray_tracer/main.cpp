#include "solver.h"

bool isSimRunning = false,needSolving = true;

int main() {
	init_arr();

	sf::RenderWindow window(sf::VideoMode(winx, winy), "RTX ON");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
			//add a light src...
			else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { addLightSrc(event.mouseButton.x, event.mouseButton.y); 
			needSolving = true;
			}
	
			//delete a tile
			else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !isSimRunning) { setTile(_res(event.mouseButton.y), _res(event.mouseButton.x), 0); 
			}
			else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !isSimRunning) { setTile(_res(event.mouseMove.y), _res(event.mouseMove.x), 0); 
			}
			//draw tile
			else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isSimRunning) setTile(_res(event.mouseButton.y), _res(event.mouseButton.x), 1);
			else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isSimRunning) setTile(_res(event.mouseMove.y), _res(event.mouseMove.x), 1);

			//start simulation
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) { isSimRunning = !isSimRunning; 
			needSolving = true;
			}
		}
		//solving ...
		if (isSimRunning && needSolving) {
			//simulate raycasting...
			solve();
		//	test();
			needSolving = false;
		}
		
		//drawing ...
		
		window.clear(sf::Color::Color(30,30,30));

		drawMapInp(window);
	//	test_draw(window);
		drawLightSrc(window);

		if (isSimRunning && !needSolving) drawRays(window);
		window.display();
	}
	return 0;
}