#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <list>

sf::RenderWindow window;
sf::Vector2u windowSize(800, 600);
sf::Event event;
sf::Time elapsed;
void (*updateFunction)(),
	 (*drawFunction)();

#include "graphicsFunctions/vertexArrays.cpp"

#include "events.cpp"

#include "map/map.cpp"

#include "mapEditor/mapEditorVariables.cpp"
#include "mapEditor/updateMapEditor.cpp"
#include "mapEditor/drawMapEditor.cpp"
#include "mapEditor/mapEditorEvants.cpp"
#include "mapEditor/startMapEditor.cpp"

#include "newMapSettings/newMapSettingsVariables.cpp"
#include "newMapSettings/updateNewMapSettings.cpp"
#include "newMapSettings/drawNewMapSettings.cpp"
#include "newMapSettings/newMapSettingsEvents.cpp"
#include "newMapSettings/startNewMapSettings.cpp"

#include "menu/menuVariables.cpp"
#include "menu/updateMenu.cpp"
#include "menu/drawMenu.cpp"
#include "menu/menuEvents.cpp"
#include "menu/startMenu.cpp"

int main(void)
{
	//sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(800, 600), "Infinite Tower Defense");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	setCommonEvents();

	startMenu();

	sf::Clock clock;
	while (window.isOpen())
	{
		elapsed = clock.restart();
		printf("elapsed %f\n", elapsed.asSeconds());
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
