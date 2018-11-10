MapForPlaying *gameMap = NULL;

bool gameMapDragging;
float gameMapDraggingMouseX1,
	  gameMapDraggingMouseY1;
sf::Vector2f gameMapDraggingMapInitialCoordinates;

unsigned int gameBaseHealth;

#include "monsters/Monster.cpp"
#include "monsters/ModelA.cpp"
#include "monsters/ModelB.cpp"
std::vector<Monster*> monsters;

#include "gameFunctions.cpp"
#include "gameInfo.cpp"

void updateGameVariables()
{
	updateGameInfoVariables();
}

void setGameVariables(const char *gameMapFileName)
{
	gameMap = new MapForPlaying(gameMapFileName, sf::Color(150, 150, 64, 196),
								sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	gameMap->setTextures(0.9);
	gameMap->setPosition(0, 0);
	gameMapDragging = false;

	windowSize = window.getSize();
	setGameInfoVariables();

	gameBaseHealth = 100;
	updateBaseHealthText();

	startWaving();
}
