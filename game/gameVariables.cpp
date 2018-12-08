bool gameMapDragging,
	 pause,
	 printTowersLevels;
float gameMapDraggingMouseX1,
	  gameMapDraggingMouseY1,
	  gameScaleDelta,
	  gameScale;
sf::Vector2f	gameMapDraggingMapInitialCoordinates,
				gameDragOffset,
				gameScaleCenter;

unsigned int gameBaseHealth,
			 money;

TwoConditionButton *gameHelpButton;

#include "../map/MapForPlaying.cpp"
MapForPlaying *gameMap;

#include "GraphicalEntity.cpp"
#include "effects/Splinter.cpp"
#include "effects/collapse.cpp"

#include "monsters/Monster.cpp"
#include "monsters/ModelA.cpp"
#include "monsters/ModelB.cpp"
#include "monsters/ModelC.cpp"
#include "monsters/ModelD.cpp"
#include "monsters/ModelE.cpp"
std::list<Monster*> monsters;

#include "gameFunctions.cpp"
#include "gameInfo.cpp"

#include "towers/towersPanel.cpp"
std::list<Tower*> towers;
unsigned int towerToAddNumber;
Tower *currentShowingUpgradeInfoTower;

#include "Grid.cpp"
#include "shooting.cpp"

#include "Bot.cpp"

void updateGameVariables()
{
	updateGameInfoVariables();
	updateTowersPanelPositionAndSize();
	if (currentShowingUpgradeInfoTower)
		currentShowingUpgradeInfoTower->getUpgradeInfo()->updatePositionAndSize();
	gameHelpButton->updatePositionAndSize();
}

void dragGameObjects()
{
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->updatePosition();
	for (std::list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
		(*i)->drag();
	for (std::list<Shot*>::iterator i = shots.begin(); i != shots.end(); i++)
		(*i)->updatePosition();
	dragSplinters();
}

void makeMapCentered()
{
	gameDragOffset = gameMap->fitInRectangle(sf::Vector2f(0, 0),
											sf::Vector2f(towersPanelRelativeX, 1));
}

void setGameEvents();
void updateGame();
void drawGame();

void continueToGame()
{
	setGameEvents();
	updateFunction = updateGame;
	drawFunction = drawGame;
}

void gameShowHelpScreen()
{
	pause = true;
	helpScreenFunctionAfterExit = continueToGame;
	startHelpScreen();
}

void setGameVariables(const char *gameMapFileName)
{
	gameMap = new MapForPlaying(gameMapFileName);
	gameMap->setTextures(0.9);
	makeMapCentered();
	gameScale = 1;
	gameMapDragging = false;
	pause = true;
	printTowersLevels = false;

	loadMonstersParameters();
	setTowersPanel();
	towerToAddNumber = 0;
	addingTower = NULL;
	currentShowingUpgradeInfoTower = NULL;

	windowSize = window.getSize();
	setGameInfoVariables();

	gameHelpButton = new TwoConditionButton(nothing, gameShowHelpScreen, "?", helpButtonFont,
											sf::Color(255, 196, 64), sf::Color(0, 0, 64, 128), sf::Color(64, 64, 128),
											0.01, 0.01, 0.03, 0.06, 1, 4);

	gameBaseHealth = 100;
	updateBaseHealthText();
	money = 350;
	updateMoneyText();

	setGrid();

	startWaving();
}
