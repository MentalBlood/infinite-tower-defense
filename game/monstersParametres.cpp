Parameter *nextWaveNumberOfMonsters,
		  *nextWaveSecondsBetweenSpawns,
		  *nextWaveMonstersSpeed,
		  *nextWaveMonstersHealth;

void loadMonstersParameters()
{
	FILE *file = fopen("monstersParametres.txt", "rb");
	if (!file) Closed();

	nextWaveNumberOfMonsters = new Parameter(file);
	nextWaveSecondsBetweenSpawns = new Parameter(file);
	nextWaveMonstersSpeed = new Parameter(file);
	nextWaveMonstersHealth = new Parameter(file);

	fclose(file);
}

void clearMonsterParameters()
{
	delete nextWaveNumberOfMonsters;
	delete nextWaveSecondsBetweenSpawns;
	delete nextWaveMonstersSpeed;
	delete nextWaveMonstersHealth;
}

void calculateNextWaveMonstersParametres()
{
	nextWaveNumberOfMonsters->setNextValue();
	nextWaveSecondsBetweenSpawns->setNextValue();
	nextWaveMonstersSpeed->setNextValue();
	nextWaveMonstersHealth->setNextValue();
}
