#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

sf::RenderWindow window;
sf::Vector2u windowSize(800, 600);
sf::Event event;
sf::Time elapsed;
void (*updateFunction)(),
	 (*drawFunction)();

std::vector<void (*)()> startFunctions;

#include "events.cpp"

#include "graphicsFunctions/vertexArrays.cpp"
#include "graphicsFunctions/textFunctions.cpp"

#include "guiElements/TwoConditionButton.cpp"
#include "guiElements/EnterFileNameDialog.cpp"

#include "map/map.cpp"

#include "mapEditor/mapEditorVariables.cpp"
#include "mapEditor/updateMapEditor.cpp"
#include "mapEditor/drawMapEditor.cpp"
#include "mapEditor/mapEditorEvents.cpp"
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
	startFunctions.push_back(startMenu);
	startFunctions.push_back(startNewMapSettings);

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
		updateFunction();

		while (window.pollEvent(event))
		{
			events[event.type]();
		}

		drawFunction();
	}

	return 0;
}
