#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <typeinfo>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

sf::RenderWindow window;
sf::Vector2u windowSize(800, 600);
sf::Event event;
sf::Time elapsed;
void (*updateFunction)(),
	 (*drawFunction)();

void startMenu();
void (*helpScreenFunctionAfterExit)() = startMenu;
void startHelpScreen();
void startSelectMapScreen();
void startGame();
void startGameOverScreen();
void startChooseNewOrSavedMapToEditDialog();
void startNewMapSettings();
void startMapEditor();

#include "events.cpp"
#include "loadFonts.cpp"

#include "graphicsFunctions/vertexArrays.cpp"
#include "graphicsFunctions/textFunctions.cpp"
#include "graphicsFunctions/colorFunctions.cpp"

#include "guiElements/TwoConditionButton.cpp"
#include "guiElements/EnterFileNameDialog.cpp"
#include "guiElements/List.cpp"
#include "guiElements/Message.cpp"
#include "guiElements/Text.cpp"

#include "map/checkMapFile.cpp"
#include "map/Map.cpp"

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

#include "gameOverScreen/gameOverScreenVariables.cpp"
#include "gameOverScreen/updateGameOverScreen.cpp"
#include "gameOverScreen/drawGameOverScreen.cpp"
#include "gameOverScreen/gameOverScreenEvents.cpp"
#include "gameOverScreen/startGameOverScreen.cpp"

#include "game/gameVariables.cpp"
#include "game/updateGame.cpp"
#include "game/drawGame.cpp"
#include "game/gameEvents.cpp"
#include "game/startGame.cpp"

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
	window.create(sf::VideoMode(800, 600), "Infinite Tower Defense");
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(60);
	setCommonEvents();
	loadFonts();

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
