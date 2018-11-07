#include "Timer.cpp"

void spawn()
{
	//monsters.push_back(ModelA(gameMap->getSpawnPoint(), 19, gameMap->getCellTextureSize() / 2.5, 60, gameMap));
	monsters.push_back(ModelB(	gameMap->getSpawnPoint(), 25, gameMap->getCellTextureSize() / 2.5,
								sf::Color(20, 20, 20, 0), sf::Color(100, 100, 100),
								sf::Color(100, 100, 100, 0), sf::Color(180, 180, 180),
								gameMap));
	monsters[monsters.size()-1].changeScale(gameMap->getScale());
}

void spawnWave(float timeToWait, unsigned int numberOfMonsters, float secondsBetweenSpawns)
{
	for (unsigned int i = 0; i < numberOfMonsters; i++, timeToWait += secondsBetweenSpawns)
		Timer *timer = new Timer(timeToWait, spawn);
}
