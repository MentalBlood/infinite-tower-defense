#include "Timer.cpp"

void spawn()
{
	monsters.push_back(new ModelA(19, 60, gameMap));
	//monsters.push_back(new ModelB(25,
	//								sf::Color(20, 20, 20, 0), sf::Color(100, 100, 100),
	//								sf::Color(100, 100, 100, 0), sf::Color(180, 180, 180),
	//								gameMap));
}

void spawnWave(float timeToWait, unsigned int numberOfMonsters, float secondsBetweenSpawns)
{
	for (unsigned int i = 0; i < numberOfMonsters; i++, timeToWait += secondsBetweenSpawns)
		Timer *timer = new Timer(timeToWait, spawn);
}
