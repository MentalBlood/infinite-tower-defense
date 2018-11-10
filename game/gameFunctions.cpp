#include "Timer.cpp"

#define TYPE_A 0
#define TYPE_B 1

void spawn(char monsterType)
{
	if (monsterType == TYPE_A)
		monsters.push_back(new ModelA(19, 60, gameMap));
	else
	if (monsterType == TYPE_B)
		monsters.push_back(new ModelB(	25,
										sf::Color(20, 20, 20, 0), sf::Color(100, 100, 100),
										sf::Color(100, 100, 100, 0), sf::Color(180, 180, 180),
										gameMap));
}

void spawnWave(	float timeToWait, char monsterType, unsigned int numberOfMonsters,
				float secondsBetweenSpawns)
{
	for (unsigned int i = 0; i < numberOfMonsters; i++, timeToWait += secondsBetweenSpawns)
		new Timer(timeToWait, spawn, monsterType);
}

unsigned int currentWaveNumber;
unsigned int nextWaveNumberOfMonsters;
float nextWaveSecondsBetweenSpawns,
	  delayBetweenWaves,
	  *currentSecondsToNextWave;

void updateCurrentWaveNumberText();

void spawnNextWave(char monsterType)
{
	spawnWave(0, monsterType, nextWaveNumberOfMonsters, nextWaveSecondsBetweenSpawns);
	++currentWaveNumber;
	updateCurrentWaveNumberText();
	nextWaveNumberOfMonsters += 1;
	nextWaveSecondsBetweenSpawns /= 1.1;

	Timer *timer = new Timer(nextWaveSecondsBetweenSpawns * nextWaveNumberOfMonsters + delayBetweenWaves, spawnNextWave, (monsterType+1) % 2);
	currentSecondsToNextWave = timer->getTimeLeftPointer();
}

void startWaving()
{
	currentWaveNumber = 0;
	nextWaveNumberOfMonsters = 1;
	nextWaveSecondsBetweenSpawns = 1.5;
	delayBetweenWaves = 2;
	spawnNextWave(TYPE_A);
}

void updateBaseHealthText();

void damageTheBase(unsigned int damage)
{
	gameBaseHealth -= damage;
	updateBaseHealthText();
}
