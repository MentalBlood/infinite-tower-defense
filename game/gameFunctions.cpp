#include "Timer.cpp"
#include "Parameter.cpp"
#include "monstersParametres.cpp"

#define	TYPE_A 0
#define TYPE_B 1
#define TYPE_C 2
#define TYPE_D 3
#define TYPE_E 4

void spawn(Monster *monster)
{
	monster->goToSpawnPoint();
	monsters.push_back(monster);
}

unsigned int currentWaveNumber;
float delayBetweenWaves,
	  *currentSecondsToNextWave;

void updateCurrentWaveNumberText();

void spawnNextWave(char monsterType)
{
	float timeToWait = 0;
	if (monsterType == TYPE_A)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn, new ModelA(	rand() % 9 * 2 + 11, 60,
																nextWaveMonstersSpeed->getValue(),
																nextWaveMonstersHealth->getValue()));
	else
	if (monsterType == TYPE_B)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn,
								new ModelB(	rand() % 9 * 2 + 11, sf::Color(20, 20, 20, 0), sf::Color(100, 100, 100),
											sf::Color(100, 100, 100, 0), sf::Color(180, 180, 180),
											nextWaveMonstersSpeed->getValue(),
											nextWaveMonstersHealth->getValue()));
	else
	if (monsterType == TYPE_C)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn,
								new ModelC(nextWaveMonstersSpeed->getValue(),
										   nextWaveMonstersHealth->getValue()));
	else
	if (monsterType == TYPE_D)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn,
								new ModelD(nextWaveMonstersSpeed->getValue(),
										   nextWaveMonstersHealth->getValue()));
	else
	if (monsterType == TYPE_E)
		for (	unsigned int i = 0;
				i < nextWaveNumberOfMonsters->getValue();
				i++, timeToWait += nextWaveSecondsBetweenSpawns->getValue())
			new Timer<Monster*>(timeToWait, spawn,
								new ModelE(nextWaveMonstersSpeed->getValue(),
										   nextWaveMonstersHealth->getValue()));

	Timer<char> *timer = 
		new Timer<char>(nextWaveSecondsBetweenSpawns->getValue()
						* (nextWaveNumberOfMonsters->getValue() - 1)
						+	gameMap->getCellSize() * (gameMap->getPathPointer()->size() + 2.5)
							/ nextWaveMonstersSpeed->getValue() / 1000.0 + delayBetweenWaves,
						spawnNextWave, char((monsterType + 1) % 5));
	currentSecondsToNextWave = timer->getTimeLeftPointer();

	++currentWaveNumber;
	updateCurrentWaveNumberText();
	calculateNextWaveMonstersParametres();
}

void startWaving()
{
	currentWaveNumber = 0;
	delayBetweenWaves = 0;
	loadMonstersParameters();
	spawnNextWave(TYPE_A);
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
