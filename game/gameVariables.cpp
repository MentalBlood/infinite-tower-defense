bool gameMapDragging,
	 monstersMoving,
	 shotsFlying;
float gameMapDraggingMouseX1,
	  gameMapDraggingMouseY1,
	  gameScaleDelta,
	  gameScale;
sf::Vector2f	gameMapDraggingMapInitialCoordinates,
				gameDragOffset,
				gameScaleCenter;

unsigned int gameBaseHealth;

#include "../map/MapForPlaying.cpp"
MapForPlaying *gameMap;

#include "GraphicalEntity.cpp"

#include "monsters/Monster.cpp"
#include "monsters/ModelA.cpp"
#include "monsters/ModelB.cpp"
std::list<Monster*> monsters;

#include "gameFunctions.cpp"
#include "gameInfo.cpp"

#include "towers/towersPanel.cpp"
std::list<Tower*> towers;

#include "shooting.cpp"

void updateGameVariables()
{
	updateGameInfoVariables();
	updateTowersPanelPositionAndSize();
}

void setGameVariables(const char *gameMapFileName)
{
	gameMap = new MapForPlaying(gameMapFileName, sf::Color(150, 150, 64, 196),
								sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	gameMap->setTextures(0.9);
	gameMap->setPosition(0, 0);
	gameScale = 1;
	gameMapDragging = false;
	monstersMoving = false;
	shotsFlying = true;

	loadMonstersParameters();
	setTowersPanel();
	addingTower = NULL;

	windowSize = window.getSize();
	setGameInfoVariables();

	gameBaseHealth = 100;
	updateBaseHealthText();

	startWaving();
}
