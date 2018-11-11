#include "Timer.cpp"
#include "monstersParametres.cpp"

#define TYPE_A 0
#define TYPE_B 1

void spawn(Monster *monster)
{
	monster->goToSpawnPoint();
	monsters.push_back(monster);
}

unsigned int currentWaveNumber;
float delayBetweenWaves,
	  *currentSecondsToNextWave;

void updateCurrentWaveNumberText();

void spawnNextWave(char *monsterType)
{
	float timeToWait = 0;
	if ((*monsterType) == TYPE_A)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn, new ModelA(	19, 60,
																nextWaveMonstersSpeed->getValue(),
																nextWaveMonstersHealth->getValue()));
	else
	if ((*monsterType) == TYPE_B)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn,
								new ModelB(	25, sf::Color(20, 20, 20, 0), sf::Color(100, 100, 100),
											sf::Color(100, 100, 100, 0), sf::Color(180, 180, 180),
											nextWaveMonstersSpeed->getValue(),
											nextWaveMonstersHealth->getValue()));

	Timer<char*> *timer = 
		new Timer<char*>(nextWaveSecondsBetweenSpawns->getValue()
						* (nextWaveNumberOfMonsters->getValue() - 1)
						+	gameMap->getCellSize() * (gameMap->getPathPointer()->size() + 2.5)
							/ nextWaveMonstersSpeed->getValue() / 1000.0,
						spawnNextWave, new char((*monsterType + 1) % 2));
	currentSecondsToNextWave = timer->getTimeLeftPointer();

	++currentWaveNumber;
	updateCurrentWaveNumberText();
	calculateNextWaveMonstersParametres();
}

void startWaving()
{
	currentWaveNumber = 0;
	delayBetweenWaves = 1;
	loadMonstersParameters();
	spawnNextWave(new char(TYPE_A));
}

void gameOver();

void updateBaseHealthText();

bool damageTheBase(unsigned int damage)
{
	if (damage >= gameBaseHealth)
	{
		gameOver();
		return true;
	}
	gameBaseHealth -= damage;
	updateBaseHealthText();

	return false;
}
