#include <SFML/Graphics.hpp>
#include <math.h>

sf::RenderWindow window(sf::VideoMode(800, 600), "Infinite Tower Defense");
sf::Vector2u windowSize(800, 600);
sf::Event event;
sf::Time elapsed;
void (*updateFunction)(),
	 (*drawFunction)();

#include "events.cpp"

#include "menu/menuVariables.cpp"
#include "menu/updateMenu.cpp"
#include "menu/drawMenu.cpp"
#include "menu/menuEvents.cpp"
#include "menu/startMenu.cpp"

int main(void)
{
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	setCommonEvents();

	startMenu();

	sf::Clock clock;
	while (window.isOpen())
	{
		elapsed = clock.restart();
		updateFunction();

		while (window.pollEvent(event))
		{
			printf("event %d\n", event.type);
			events[event.type]();
		}

		drawFunction();
	}

	return 0;
}
