#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
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
#include "graphicsFunctions/colorFunctions.cpp"

#include "guiElements/TwoConditionButton.cpp"
#include "guiElements/EnterFileNameDialog.cpp"
#include "guiElements/List.cpp"
#include "guiElements/Message.cpp"

#include "map/MapForEditing.cpp"
#include "map/MapForPlaying.cpp"
#include "map/checkMapFile.cpp"

#include "game/gameVariables.cpp"
#include "game/updateGame.cpp"
#include "game/drawGame.cpp"
#include "game/gameEvents.cpp"
#include "game/startGame.cpp"

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

#include "chooseNewOrSavedMapToEditDialog/chooseNewOrSavedMapToEditDialogVariables.cpp"
#include "chooseNewOrSavedMapToEditDialog/updateChooseNewOrSavedMapToEditDialog.cpp"
#include "chooseNewOrSavedMapToEditDialog/drawChooseNewOrSavedMapToEditDialog.cpp"
#include "chooseNewOrSavedMapToEditDialog/chooseNewOrSavedMapToEditDialogEvents.cpp"
#include "chooseNewOrSavedMapToEditDialog/startChooseNewOrSavedMapToEditDialog.cpp"

#include "selectMapScreen/selectMapScreenVariables.cpp"
#include "selectMapScreen/updateSelectMapScreen.cpp"
#include "selectMapScreen/drawSelectMapScreen.cpp"
#include "selectMapScreen/selectMapScreenEvents.cpp"
#include "selectMapScreen/startSelectMapScreen.cpp"

#include "helpScreen/helpScreenVariables.cpp"
#include "helpScreen/updateHelpScreen.cpp"
#include "helpScreen/drawHelpScreen.cpp"
#include "helpScreen/helpScreenEvents.cpp"
#include "helpScreen/startHelpScreen.cpp"

#include "menu/menuVariables.cpp"
#include "menu/updateMenu.cpp"
#include "menu/drawMenu.cpp"
#include "menu/menuEvents.cpp"
#include "menu/startMenu.cpp"

int main(void)
{
	startFunctions.push_back(startMenu);
	startFunctions.push_back(startChooseNewOrSavedMapToEditDialog);
	startFunctions.push_back(startNewMapSettings);
	startFunctions.push_back(startSelectMapScreen);

	window.create(sf::VideoMode(800, 600), "Infinite Tower Defense");
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(60);
	setCommonEvents();

	startMenu();

	sf::Clock clock;
	while (window.isOpen())
	{
		elapsed = clock.restart();
		updateFunction();

		while (window.pollEvent(event))
			events[event.type]();

		drawFunction();
	}

	return 0;
}
